/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 *  Effective License of whole file:
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 *  Parts "Copyright by Sun Microsystems, Inc" prior to August 2011:
 *
 *    The Contents of this file are made available subject to the terms of
 *    the GNU Lesser General Public License Version 2.1
 *
 *    Copyright: 2000 by Sun Microsystems, Inc.
 *
 *    Contributor(s): Joerg Budischewski
 *
 *  All parts contributed on or after August 2011:
 *
 *    This Source Code Form is subject to the terms of the Mozilla Public
 *    License, v. 2.0. If a copy of the MPL was not distributed with this
 *    file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 ************************************************************************/

#include "pq_preparedstatement.hxx"
#include "pq_resultset.hxx"
#include "pq_tools.hxx"
#include "pq_statics.hxx"
#include "pq_statement.hxx"

#include <rtl/strbuf.hxx>
#include <rtl/ustrbuf.hxx>


#include <cppuhelper/typeprovider.hxx>
#include <cppuhelper/queryinterface.hxx>
#include <comphelper/sequence.hxx>
#include <com/sun/star/beans/PropertyAttribute.hpp>

#include <com/sun/star/sdbc/ResultSetConcurrency.hpp>
#include <com/sun/star/sdbc/ResultSetType.hpp>

#include <string.h>

#include <connectivity/dbconversion.hxx>

using osl::Mutex;
using osl::MutexGuard;


using com::sun::star::uno::Any;
using com::sun::star::uno::makeAny;
using com::sun::star::uno::Type;
using com::sun::star::uno::RuntimeException;
using com::sun::star::uno::Exception;
using com::sun::star::uno::Sequence;
using com::sun::star::uno::Reference;
using com::sun::star::uno::UNO_QUERY;

using com::sun::star::lang::IllegalArgumentException;

using com::sun::star::sdbc::XCloseable;
using com::sun::star::sdbc::XResultSet;
using com::sun::star::sdbc::XRef;
using com::sun::star::sdbc::XBlob;
using com::sun::star::sdbc::XClob;
using com::sun::star::sdbc::XArray;
using com::sun::star::sdbc::XConnection;
using com::sun::star::sdbc::SQLException;

using com::sun::star::beans::Property;
using com::sun::star::beans::XPropertySetInfo;

using namespace dbtools;

namespace pq_sdbc_driver
{
static ::cppu::IPropertyArrayHelper & getPreparedStatementPropertyArrayHelper()
{
    static ::cppu::IPropertyArrayHelper *pArrayHelper;
    if( ! pArrayHelper )
    {
        MutexGuard guard( Mutex::getGlobalMutex() );
        if( ! pArrayHelper )
        {
            static Property aTable[] =
                {
                    Property(
                        OUString("CursorName"), 0,
                        ::cppu::UnoType<OUString>::get() , 0 ),
                    Property(
                        OUString("EscapeProcessing"), 1,
                        cppu::UnoType<bool>::get() , 0 ),
                    Property(
                        OUString("FetchDirection"), 2,
                        ::cppu::UnoType<sal_Int32>::get() , 0 ),
                    Property(
                        OUString("FetchSize"), 3,
                        ::cppu::UnoType<sal_Int32>::get() , 0 ),
                    Property(
                        OUString("MaxFieldSize"), 4,
                        ::cppu::UnoType<sal_Int32>::get() , 0 ),
                    Property(
                        OUString("MaxRows"), 5,
                        ::cppu::UnoType<sal_Int32>::get() , 0 ),
                    Property(
                        OUString("QueryTimeOut"), 6,
                        ::cppu::UnoType<sal_Int32>::get() , 0 ),
                    Property(
                        OUString("ResultSetConcurrency"), 7,
                        ::cppu::UnoType<sal_Int32>::get() , 0 ),
                    Property(
                        OUString("ResultSetType"), 8,
                        ::cppu::UnoType<sal_Int32>::get() , 0 )
                };
            OSL_ASSERT( sizeof(aTable)/ sizeof(Property)  == PREPARED_STATEMENT_SIZE );
            static ::cppu::OPropertyArrayHelper arrayHelper( aTable, PREPARED_STATEMENT_SIZE, true );
            pArrayHelper = &arrayHelper;
        }
    }
    return *pArrayHelper;
}

static bool isOperator( char c )
{
    static const char * operators = "<>=()!/&%.,;";

    const char * w = operators;
    while (*w && *w != c)
    {
        ++w;
    }
    return *w != 0;
}

static bool isNamedParameterStart( const OString & o , int index )
{
    return o[index] == ':' && (
        isWhitespace( o[index-1] ) || isOperator(o[index-1]) );
}

static bool isQuoted( const OString & str )
{
    return str[0] == '"' || str[0] == '\'';
}

PreparedStatement::PreparedStatement(
    const ::rtl::Reference< RefCountedMutex > & refMutex,
    const Reference< XConnection > & conn,
    struct ConnectionSettings *pSettings,
    const OString & stmt )
    : PreparedStatement_BASE(refMutex->mutex)
    , OPropertySetHelper(PreparedStatement_BASE::rBHelper)
    , m_connection(conn)
    , m_pSettings(pSettings)
    , m_stmt(stmt)
    , m_refMutex(refMutex)
    , m_multipleResultAvailable(false)
    , m_multipleResultUpdateCount(0)
    , m_lastOidInserted( InvalidOid )
{
    m_props[PREPARED_STATEMENT_QUERY_TIME_OUT] = makeAny( (sal_Int32)0 );
    m_props[PREPARED_STATEMENT_MAX_ROWS] = makeAny( (sal_Int32)0 );
    m_props[PREPARED_STATEMENT_RESULT_SET_CONCURRENCY] = makeAny(
        css::sdbc::ResultSetConcurrency::READ_ONLY );
    m_props[PREPARED_STATEMENT_RESULT_SET_TYPE] = makeAny(
        css::sdbc::ResultSetType::SCROLL_INSENSITIVE );

    splitSQL( m_stmt, m_splittedStatement );
    int elements = 0;
    for(OString & str : m_splittedStatement)
    {
        // ignore quoted strings ....
        if( ! isQuoted( str ) )
        {
            // the ':' cannot be the first or the last part of the
            // token,
            // the ? cannot be the first part of the token , so we start
            // at one
            for( int index = 1 ; index < str.getLength() ; index ++ )
            {
                if( str[index] == '?' ||
                    isNamedParameterStart( str , index )
                    )
                {
                    elements ++;
                }
            }
        }
    }
    m_vars = OStringVector ( elements );
}

PreparedStatement::~PreparedStatement()
{
    POSTGRE_TRACE( "dtor PreparedStatement" );
}

void PreparedStatement::checkColumnIndex( sal_Int32 parameterIndex )
{
    if( parameterIndex < 1 || parameterIndex > (sal_Int32) m_vars.size() )
    {
        OUStringBuffer buf( 128 );
        buf.append( "pq_preparedstatement: parameter index out of range (expected 1 to " );
        buf.append( (sal_Int32 ) m_vars.size() );
        buf.append( ", got " );
        buf.append( parameterIndex );
        buf.append( ", statement '" );
        buf.append( OStringToOUString( m_stmt, m_pSettings->encoding ) );
        buf.append( "')" );
        throw SQLException( buf.makeStringAndClear(), *this, OUString(), 1, Any () );
    }
}
void PreparedStatement::checkClosed() throw (SQLException, RuntimeException )
{
    if( ! m_pSettings || ! m_pSettings->pConnection )
        throw SQLException(
            "pq_driver: PreparedStatement or connection has already been closed !",
            *this, OUString(),1,Any());
}

Any PreparedStatement::queryInterface( const Type & rType ) throw (RuntimeException, std::exception)
{
    Any aRet = PreparedStatement_BASE::queryInterface(rType);
    return aRet.hasValue() ? aRet : OPropertySetHelper::queryInterface(rType);
}


Sequence< Type > PreparedStatement::getTypes() throw ( RuntimeException, std::exception )
{
    static Sequence< Type > *pCollection;
    if( ! pCollection )
    {
        MutexGuard guard( osl::Mutex::getGlobalMutex() );
        if( !pCollection )
        {
            static Sequence< Type > collection(
                ::comphelper::concatSequences(
                    OPropertySetHelper::getTypes(),
                    PreparedStatement_BASE::getTypes()));
            pCollection = &collection;
        }
    }
    return *pCollection;
}

Sequence< sal_Int8> PreparedStatement::getImplementationId() throw ( RuntimeException, std::exception )
{
    return css::uno::Sequence<sal_Int8>();
}

void PreparedStatement::close(  ) throw (SQLException, RuntimeException, std::exception)
{
    // let the connection die without acquired mutex !
    Reference< XConnection > r;
    Reference< XCloseable > resultSet;
    {
        MutexGuard guard( m_refMutex->mutex );
        m_pSettings = nullptr;
        r = m_connection;
        m_connection.clear();

        resultSet = m_lastResultset;
        m_lastResultset.clear();
    }
    if( resultSet.is() )
    {
        resultSet->close();
    }
}

void PreparedStatement::raiseSQLException( const char * errorMsg )
    throw( SQLException )
{
    OUStringBuffer buf(128);
    buf.append( "pq_driver: ");
    buf.append(
        OUString( errorMsg, strlen(errorMsg) , m_pSettings->encoding ) );
    buf.append( " (caused by statement '" );
    buf.appendAscii( m_executedStatement.getStr() );
    buf.append( "')" );
    OUString error = buf.makeStringAndClear();
    log( m_pSettings, LogLevel::ERROR, error );
    throw SQLException( error, *this, OUString(), 1, Any() );
}

Reference< XResultSet > PreparedStatement::executeQuery( )
        throw (SQLException, RuntimeException, std::exception)
{
    Reference< XCloseable > lastResultSet = m_lastResultset;
    if( lastResultSet.is() )
        lastResultSet->close();

    if( ! execute( ) )
    {
        raiseSQLException(  "not a query" );
    }
    return Reference< XResultSet > ( m_lastResultset, css::uno::UNO_QUERY );
}

sal_Int32 PreparedStatement::executeUpdate( )
        throw (SQLException, RuntimeException, std::exception)
{
    if( execute( ) )
    {
        raiseSQLException( "not a command" );
    }
    return m_multipleResultUpdateCount;
}

sal_Bool PreparedStatement::execute( )
        throw (SQLException, RuntimeException, std::exception)
{
    osl::MutexGuard guard( m_refMutex->mutex );

    OStringBuffer buf( m_stmt.getLength() *2 );

    OStringVector::size_type vars = 0;
    for(OString & str : m_splittedStatement)
    {
        // LEM TODO: instead of this manual mucking with SQL
        // could we use PQexecParams / PQExecPrepared / ...?
        // Only snafu is giving the types of the parameters and
        // that it needs $1, $2, etc instead of "?"

//         printf( "Splitted %d %s\n" , i , str.getStr() );
        if( isQuoted( str ) )
        {
            buf.append( str );
        }
        else
        {
            int start = 0,index;
            for( index = 1 ; index < str.getLength() ; index ++ )
            {
                if( str[index] == '?' )
                {
                    buf.append( str.getStr()+start, index - start );
                    buf.append( m_vars[vars] );
                    vars ++;
                    start =index+1;
                }
                else
                {
                    if ( isNamedParameterStart( str, index ) )
                    {
                        buf.append( str.getStr()+start, index -start );
                        buf.append( m_vars[vars] );

                        // skip to the end of the named parameter
                        while (   index < str.getLength()
                               && !(   isWhitespace(str[index])
                                    || isOperator  (str[index])))
                        {
                            ++index;
                        }
                        start = index;
                        vars ++;
                    }
                }
            }
//             if( index +1 >= str.getLength() )
//             {
            buf.append( str.getStr() + start, index -start );
//             }
        }
    }

    m_executedStatement = buf.makeStringAndClear();

    m_lastResultset.clear();
    m_lastTableInserted.clear();

    struct CommandData data;
    data.refMutex = m_refMutex;
    data.ppSettings = &m_pSettings;
    data.pLastOidInserted = &m_lastOidInserted;
    data.pLastQuery = &m_lastQuery;
    data.pMultipleResultUpdateCount = &m_multipleResultUpdateCount;
    data.pMultipleResultAvailable = &m_multipleResultAvailable;
    data.pLastTableInserted = &m_lastTableInserted;
    data.pLastResultset = &m_lastResultset;
    data.owner = *this;
    data.tableSupplier.set( m_connection, UNO_QUERY );
    data.concurrency = extractIntProperty( this, getStatics().RESULT_SET_CONCURRENCY );

    return executePostgresCommand( m_executedStatement , &data );   // see pq_statement.cxx
}

Reference< XConnection > PreparedStatement::getConnection(  )
        throw (SQLException, RuntimeException, std::exception)
{
    Reference< XConnection > ret;
    {
        MutexGuard guard( m_refMutex->mutex );
        checkClosed();
        ret = m_connection;
    }
    return ret;
}


void PreparedStatement::setNull( sal_Int32 parameterIndex, sal_Int32 sqlType )
    throw (SQLException, RuntimeException, std::exception)
{
    (void)sqlType;
    MutexGuard guard( m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    m_vars[parameterIndex-1] = OString( "NULL" );
}

void PreparedStatement::setObjectNull(
    sal_Int32 parameterIndex, sal_Int32 sqlType, const OUString& typeName )
    throw (SQLException, RuntimeException, std::exception)
{
    (void) sqlType; (void) typeName;
    MutexGuard guard( m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    m_vars[parameterIndex-1] = OString( "NULL" );
}


void PreparedStatement::setBoolean( sal_Int32 parameterIndex, sal_Bool x )
    throw (SQLException, RuntimeException, std::exception)
{
    MutexGuard guard(m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    if( x )
        m_vars[parameterIndex-1] = OString( "'t'" );
    else
        m_vars[parameterIndex-1] = OString( "'f'" );
}

void PreparedStatement::setByte( sal_Int32 parameterIndex, sal_Int8 x )
    throw (SQLException, RuntimeException, std::exception)
{
    setInt(parameterIndex,x);
}

void PreparedStatement::setShort( sal_Int32 parameterIndex, sal_Int16 x )
    throw (SQLException, RuntimeException, std::exception)
{
    setInt(parameterIndex, x );
}

void PreparedStatement::setInt( sal_Int32 parameterIndex, sal_Int32 x )
    throw (SQLException, RuntimeException, std::exception)
{
//     printf( "setString %d %d\n ",  parameterIndex, x);
    MutexGuard guard(m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    OStringBuffer buf( 20 );
    buf.append( "'" );
    buf.append( (sal_Int32) x );
    buf.append( "'" );
    m_vars[parameterIndex-1] = buf.makeStringAndClear();
}

void PreparedStatement::setLong( sal_Int32 parameterIndex, sal_Int64 x )
    throw (SQLException, RuntimeException, std::exception)
{
    MutexGuard guard(m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    OStringBuffer buf( 20 );
    buf.append( "'" );
    buf.append( (sal_Int64) x );
    buf.append( "'" );
    m_vars[parameterIndex-1] = buf.makeStringAndClear();
}

void PreparedStatement::setFloat( sal_Int32 parameterIndex, float x )
    throw (SQLException, RuntimeException, std::exception)
{
    MutexGuard guard(m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    OStringBuffer buf( 20 );
    buf.append( "'" );
    buf.append( x );
    buf.append( "'" );
    m_vars[parameterIndex-1] = buf.makeStringAndClear();
}

void PreparedStatement::setDouble( sal_Int32 parameterIndex, double x )
    throw (SQLException, RuntimeException, std::exception)
{
    MutexGuard guard(m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    OStringBuffer buf( 20 );
    buf.append( "'" );
    buf.append( x );
    buf.append( "'" );
    m_vars[parameterIndex-1] = buf.makeStringAndClear();
}

void PreparedStatement::setString( sal_Int32 parameterIndex, const OUString& x )
    throw (SQLException, RuntimeException, std::exception)
{
//     printf( "setString %d %s\n ", parameterIndex,
//             OUStringToOString( x , RTL_TEXTENCODING_ASCII_US ).getStr());
    MutexGuard guard(m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    OStringBuffer buf( 20 );
    buf.append( "'" );
    OString y = OUStringToOString( x, m_pSettings->encoding );
    buf.ensureCapacity( y.getLength() * 2 + 2 );
    int len = PQescapeString( const_cast<char*>(buf.getStr())+1, y.getStr() , y.getLength() );
    buf.setLength( 1 + len );
    buf.append( "'" );
    m_vars[parameterIndex-1] = buf.makeStringAndClear();
}

void PreparedStatement::setBytes(
    sal_Int32 parameterIndex, const Sequence< sal_Int8 >& x )
    throw (SQLException, RuntimeException, std::exception)
{
    MutexGuard guard(m_refMutex->mutex );
    checkClosed();
    checkColumnIndex( parameterIndex );
    OStringBuffer buf( 20 );
    buf.append( "'" );
    size_t len;
    unsigned char * escapedString =
        PQescapeBytea( reinterpret_cast<unsigned char const *>(x.getConstArray()), x.getLength(), &len);
    if( ! escapedString )
    {
        throw SQLException(
            "pq_preparedstatement.setBytes: Error during converting bytesequence to an SQL conform string",
            *this, OUString(), 1, Any() );
    }
    buf.append( reinterpret_cast<char *>(escapedString), len -1 );
    free( escapedString );
    buf.append( "'" );
    m_vars[parameterIndex-1] = buf.makeStringAndClear();
}


void PreparedStatement::setDate( sal_Int32 parameterIndex, const css::util::Date& x )
    throw (SQLException, RuntimeException, std::exception)
{
    setString( parameterIndex, DBTypeConversion::toDateString( x ) );
}

void PreparedStatement::setTime( sal_Int32 parameterIndex, const css::util::Time& x )
    throw (SQLException, RuntimeException, std::exception)
{
    setString( parameterIndex, DBTypeConversion::toTimeString( x ) );
}

void PreparedStatement::setTimestamp(
    sal_Int32 parameterIndex, const css::util::DateTime& x )
    throw (SQLException, RuntimeException, std::exception)
{
    setString( parameterIndex, DBTypeConversion::toDateTimeString( x ) );
}

void PreparedStatement::setBinaryStream(
    sal_Int32 parameterIndex,
    const Reference< css::io::XInputStream >& x,
    sal_Int32 length )
    throw (SQLException, RuntimeException, std::exception)
{
    (void) parameterIndex; (void)x; (void) length;
    throw SQLException(
        "pq_preparedstatement: setBinaryStream not implemented",
        *this, OUString(), 1, Any () );
}

void PreparedStatement::setCharacterStream(
    sal_Int32 parameterIndex,
    const Reference< css::io::XInputStream >& x,
    sal_Int32 length )
    throw (SQLException, RuntimeException, std::exception)
{
    (void) parameterIndex; (void)x; (void) length;
    throw SQLException(
        "pq_preparedstatement: setCharacterStream not implemented",
        *this, OUString(), 1, Any () );
}

void PreparedStatement::setObject( sal_Int32 parameterIndex, const Any& x )
    throw (SQLException, RuntimeException, std::exception)
{
    if( ! implSetObject( this, parameterIndex, x ))
    {
        OUStringBuffer buf;
        buf.append( "pq_preparedstatement::setObject: can't convert value of type " );
        buf.append( x.getValueTypeName() );
        throw SQLException( buf.makeStringAndClear(), *this, OUString(), 1, Any () );
    }
}

void PreparedStatement::setObjectWithInfo(
    sal_Int32 parameterIndex,
    const Any& x,
    sal_Int32 targetSqlType,
    sal_Int32 scale )
    throw (SQLException, RuntimeException, std::exception)
{
    (void) scale;
    if( css::sdbc::DataType::DECIMAL == targetSqlType ||
        css::sdbc::DataType::NUMERIC == targetSqlType )
    {
        double myDouble = 0.0;
        OUString myString;
        if( x >>= myDouble )
        {
            myString = OUString::number( myDouble );
        }
        else
        {
            x >>= myString;
        }
        if( !myString.isEmpty() )
        {
//              printf( "setObjectWithInfo %s\n", OUStringToOString(myString,RTL_TEXTENCODING_ASCII_US).getStr());
            setString( parameterIndex, myString );
        }
        else
        {
            OUStringBuffer buf;
            buf.append( "pq_preparedstatement::setObjectWithInfo: can't convert value of type " );
            buf.append( x.getValueTypeName() );
            buf.append( " to type DECIMAL or NUMERIC" );
            throw SQLException( buf.makeStringAndClear(), *this, OUString(), 1, Any () );
        }
    }
    else
    {
        setObject( parameterIndex, x );
    }

}

void PreparedStatement::setRef(
    sal_Int32 parameterIndex,
    const Reference< XRef >& x )
    throw (SQLException, RuntimeException, std::exception)
{
    (void) parameterIndex; (void)x;
    throw SQLException(
        "pq_preparedstatement: setRef not implemented",
        *this, OUString(), 1, Any () );
}

void PreparedStatement::setBlob(
    sal_Int32 parameterIndex,
    const Reference< XBlob >& x )
    throw (SQLException, RuntimeException, std::exception)
{
    (void) parameterIndex; (void)x;
    throw SQLException(
        "pq_preparedstatement: setBlob not implemented",
        *this, OUString(), 1, Any () );
}

void PreparedStatement::setClob(
    sal_Int32 parameterIndex,
    const Reference< XClob >& x )
    throw (SQLException, RuntimeException, std::exception)
{
    (void) parameterIndex; (void)x;
    throw SQLException(
        "pq_preparedstatement: setClob not implemented",
        *this, OUString(), 1, Any () );
}

void PreparedStatement::setArray(
    sal_Int32 parameterIndex,
    const Reference< XArray >& x )
    throw (SQLException, RuntimeException, std::exception)
{
    setString( parameterIndex, array2String( x->getArray( nullptr ) ) );
}

void PreparedStatement::clearParameters(  )
    throw (SQLException, RuntimeException, std::exception)
{
    MutexGuard guard(m_refMutex->mutex );
    m_vars = OStringVector ( m_vars.size() );
}

Any PreparedStatement::getWarnings(  )
        throw (SQLException,RuntimeException, std::exception)
{
    return Any();
}

void PreparedStatement::clearWarnings(  )
        throw (SQLException, RuntimeException, std::exception)
{
}

Reference< css::sdbc::XResultSetMetaData > PreparedStatement::getMetaData()
            throw (SQLException,RuntimeException, std::exception)
{
    Reference< css::sdbc::XResultSetMetaData > ret;
    Reference< css::sdbc::XResultSetMetaDataSupplier > supplier( m_lastResultset, UNO_QUERY );
    if( supplier.is() )
        ret = supplier->getMetaData();
    return ret;
}

::cppu::IPropertyArrayHelper & PreparedStatement::getInfoHelper()
{
    return getPreparedStatementPropertyArrayHelper();
}


sal_Bool PreparedStatement::convertFastPropertyValue(
        Any & rConvertedValue, Any & rOldValue, sal_Int32 nHandle, const Any& rValue )
        throw (IllegalArgumentException)
{
    bool bRet;
    rOldValue = m_props[nHandle];
    switch( nHandle )
    {
    case PREPARED_STATEMENT_CURSOR_NAME:
    {
        OUString val;
        bRet = ( rValue >>= val );
        rConvertedValue = makeAny( val );
        break;
    }
    case PREPARED_STATEMENT_ESCAPE_PROCESSING:
    {
        bool val(false);
        bRet = ( rValue >>= val );
        rConvertedValue = makeAny( val );
        break;
    }
    case PREPARED_STATEMENT_FETCH_DIRECTION:
    case PREPARED_STATEMENT_FETCH_SIZE:
    case PREPARED_STATEMENT_MAX_FIELD_SIZE:
    case PREPARED_STATEMENT_MAX_ROWS:
    case PREPARED_STATEMENT_QUERY_TIME_OUT:
    case PREPARED_STATEMENT_RESULT_SET_CONCURRENCY:
    case PREPARED_STATEMENT_RESULT_SET_TYPE:
    {
        sal_Int32 val;
        bRet = ( rValue >>= val );
        rConvertedValue = makeAny( val );
        break;
    }
    default:
    {
        OUStringBuffer buf(128);
        buf.append( "pq_statement: Invalid property handle (" );
        buf.append( nHandle );
        buf.append( ")" );
        throw IllegalArgumentException( buf.makeStringAndClear(), *this, 2 );
    }
    }
    return bRet;
}


void PreparedStatement::setFastPropertyValue_NoBroadcast(
    sal_Int32 nHandle,const Any& rValue ) throw (Exception, std::exception)
{
    m_props[nHandle] = rValue;
}

void PreparedStatement::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    rValue = m_props[nHandle];
}

Reference < XPropertySetInfo >  PreparedStatement::getPropertySetInfo()
        throw(RuntimeException, std::exception)
{
    return OPropertySetHelper::createPropertySetInfo( getPreparedStatementPropertyArrayHelper() );
}

void PreparedStatement::disposing()
{
    close();
}


Reference< XResultSet > PreparedStatement::getResultSet(  )
    throw (css::sdbc::SQLException, css::uno::RuntimeException, std::exception)
{
    return Reference< XResultSet > ( m_lastResultset, css::uno::UNO_QUERY );
}
sal_Int32 PreparedStatement::getUpdateCount(  )
    throw (css::sdbc::SQLException, css::uno::RuntimeException, std::exception)
{
    return m_multipleResultUpdateCount;
}
sal_Bool PreparedStatement::getMoreResults(  )
    throw (css::sdbc::SQLException, css::uno::RuntimeException, std::exception)
{
    return false;
}

Reference< XResultSet > PreparedStatement::getGeneratedValues(  )
        throw (SQLException, RuntimeException, std::exception)
{
    osl::MutexGuard guard( m_refMutex->mutex );
    return getGeneratedValuesFromLastInsert(
        m_pSettings, m_connection, m_lastOidInserted, m_lastTableInserted, m_lastQuery );
}


}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
