/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/*
 This file has been autogenerated by update_pch.sh. It is possible to edit it
 manually (such as when an include file has been moved/renamed/removed). All such
 manual changes will be rewritten by the next run of update_pch.sh (which presumably
 also fixes all possible problems, so it's usually better to use it).

 Generated on 2015-11-14 14:16:40 using:
 ./bin/update_pch tools tl --cutoff=5 --exclude:system --exclude:module --exclude:local

 If after updating build fails, use the following command to locate conflicting headers:
 ./bin/update_pch_bisect ./tools/inc/pch/precompiled_tl.hxx "/opt/lo/bin/make tools.build" --find-conflicts
*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <limits.h>
#include <memory>
#include <new>
#include <ostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <boost/checked_delete.hpp>
#include <boost/optional/optional.hpp>
#include <boost/rational.hpp>
#include <osl/diagnose.h>
#include <osl/endian.h>
#include <osl/file.hxx>
#include <osl/interlck.h>
#include <osl/mutex.hxx>
#include <osl/process.h>
#include <osl/signal.h>
#include <osl/thread.h>
#include <rtl/alloc.h>
#include <rtl/bootstrap.hxx>
#include <rtl/character.hxx>
#include <rtl/crc.h>
#include <rtl/math.hxx>
#include <rtl/ref.hxx>
#include <rtl/strbuf.hxx>
#include <rtl/string.h>
#include <rtl/string.hxx>
#include <rtl/stringutils.hxx>
#include <rtl/tencinfo.h>
#include <rtl/textcvt.h>
#include <rtl/textenc.h>
#include <rtl/uri.hxx>
#include <rtl/ustrbuf.hxx>
#include <rtl/ustring.hxx>
#include <sal/config.h>
#include <sal/log.hxx>
#include <sal/macros.h>
#include <sal/saldllapi.h>
#include <sal/types.h>
#include <sal/typesizes.h>
#include <basegfx/basegfxdllapi.h>
#include <basegfx/range/b2drange.hxx>
#include <basegfx/tuple/b2dtuple.hxx>
#include <basegfx/vector/b2enums.hxx>
#include <com/sun/star/lang/Locale.hpp>
#include <i18nlangtag/i18nlangtagdllapi.h>
#include <i18nlangtag/lang.h>
#include <o3tl/cow_wrapper.hxx>
#include <tools/debug.hxx>
#include <tools/gen.hxx>
#include <tools/resid.hxx>
#include <tools/solar.h>
#include <tools/stream.hxx>
#include <tools/toolsdllapi.h>

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
