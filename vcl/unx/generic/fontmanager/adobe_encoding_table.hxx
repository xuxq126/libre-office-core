/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

struct AdobeEncEntry {
    sal_Unicode         aUnicode;
    sal_uInt8           aAdobeStandardCode;
    const char* const   pAdobename;
};

static const AdobeEncEntry aAdobeCodes[]=
{
    { 0x0041, 0101, "A" },
    { 0x00C6, 0341, "AE" },
    { 0x01FC, 0,    "AEacute" },
    { 0xF7E6, 0,    "AEsmall" },
    { 0x00C1, 0,    "Aacute" },
    { 0xF7E1, 0,    "Aacutesmall" },
    { 0x0102, 0,    "Abreve" },
    { 0x00C2, 0,    "Acircumflex" },
    { 0xF7E2, 0,    "Acircumflexsmall" },
    { 0xF6C9, 0,    "Acute" },
    { 0xF7B4, 0,    "Acutesmall" },
    { 0x00C4, 0,    "Adieresis" },
    { 0xF7E4, 0,    "Adieresissmall" },
    { 0x00C0, 0,    "Agrave" },
    { 0xF7E0, 0,    "Agravesmall" },
    { 0x0391, 0,    "Alpha" },
    { 0x0386, 0,    "Alphatonos" },
    { 0x0100, 0,    "Amacron" },
    { 0x0104, 0,    "Aogonek" },
    { 0x00C5, 0,    "Aring" },
    { 0x01FA, 0,    "Aringacute" },
    { 0xF7E5, 0,    "Aringsmall" },
    { 0xF761, 0,    "Asmall" },
    { 0x00C3, 0,    "Atilde" },
    { 0xF7E3, 0,    "Atildesmall" },
    { 0x0042, 0102, "B" },
    { 0x0392, 0,    "Beta" },
    { 0xF6F4, 0,    "Brevesmall" },
    { 0xF762, 0,    "Bsmall" },
    { 0x0043, 0103, "C" },
    { 0x0106, 0,    "Cacute" },
    { 0xF6CA, 0,    "Caron" },
    { 0xF6F5, 0,    "Caronsmall" },
    { 0x010C, 0,    "Ccaron" },
    { 0x00C7, 0,    "Ccedilla" },
    { 0xF7E7, 0,    "Ccedillasmall" },
    { 0x0108, 0,    "Ccircumflex" },
    { 0x010A, 0,    "Cdotaccent" },
    { 0xF7B8, 0,    "Cedillasmall" },
    { 0x03A7, 0,    "Chi" },
    { 0xF6F6, 0,    "Circumflexsmall" },
    { 0xF763, 0,    "Csmall" },
    { 0x0044, 0104, "D" },
    { 0x010E, 0,    "Dcaron" },
    { 0x0110, 0,    "Dcroat" },
    { 0x2206, 0,    "Delta" },
    { 0x0394, 0,    "Delta" },
    { 0xF6CB, 0,    "Dieresis" },
    { 0xF6CC, 0,    "DieresisAcute" },
    { 0xF6CD, 0,    "DieresisGrave" },
    { 0xF7A8, 0,    "Dieresissmall" },
    { 0xF6F7, 0,    "Dotaccentsmall" },
    { 0xF764, 0,    "Dsmall" },
    { 0x0045, 0105, "E" },
    { 0x00C9, 0,    "Eacute" },
    { 0xF7E9, 0,    "Eacutesmall" },
    { 0x0114, 0,    "Ebreve" },
    { 0x011A, 0,    "Ecaron" },
    { 0x00CA, 0,    "Ecircumflex" },
    { 0xF7EA, 0,    "Ecircumflexsmall" },
    { 0x00CB, 0,    "Edieresis" },
    { 0xF7EB, 0,    "Edieresissmall" },
    { 0x0116, 0,    "Edotaccent" },
    { 0x00C8, 0,    "Egrave" },
    { 0xF7E8, 0,    "Egravesmall" },
    { 0x0112, 0,    "Emacron" },
    { 0x014A, 0,    "Eng" },
    { 0x0118, 0,    "Eogonek" },
    { 0x0395, 0,    "Epsilon" },
    { 0x0388, 0,    "Epsilontonos" },
    { 0xF765, 0,    "Esmall" },
    { 0x0397, 0,    "Eta" },
    { 0x0389, 0,    "Etatonos" },
    { 0x00D0, 0,    "Eth" },
    { 0xF7F0, 0,    "Ethsmall" },
    { 0x20AC, 0,    "Euro" },
    { 0x0046, 0106, "F" },
    { 0xF766, 0,    "Fsmall" },
    { 0x0047, 0107, "G" },
    { 0x0393, 0,    "Gamma" },
    { 0x011E, 0,    "Gbreve" },
    { 0x01E6, 0,    "Gcaron" },
    { 0x011C, 0,    "Gcircumflex" },
    { 0x0122, 0,    "Gcommaaccent" },
    { 0x0120, 0,    "Gdotaccent" },
    { 0xF6CE, 0,    "Grave" },
    { 0xF760, 0,    "Gravesmall" },
    { 0xF767, 0,    "Gsmall" },
    { 0x0048, 0110, "H" },
    { 0x25CF, 0,    "H18533" },
    { 0x25AA, 0,    "H18543" },
    { 0x25AB, 0,    "H18551" },
    { 0x25A1, 0,    "H22073" },
    { 0x0126, 0,    "Hbar" },
    { 0x0124, 0,    "Hcircumflex" },
    { 0xF768, 0,    "Hsmall" },
    { 0xF6CF, 0,    "Hungarumlaut" },
    { 0xF6F8, 0,    "Hungarumlautsmall" },
    { 0x0049, 0111, "I" },
    { 0x0132, 0,    "IJ" },
    { 0x00CD, 0,    "Iacute" },
    { 0xF7ED, 0,    "Iacutesmall" },
    { 0x012C, 0,    "Ibreve" },
    { 0x00CE, 0,    "Icircumflex" },
    { 0xF7EE, 0,    "Icircumflexsmall" },
    { 0x00CF, 0,    "Idieresis" },
    { 0xF7EF, 0,    "Idieresissmall" },
    { 0x0130, 0,    "Idotaccent" },
    { 0x2111, 0,    "Ifraktur" },
    { 0x00CC, 0,    "Igrave" },
    { 0xF7EC, 0,    "Igravesmall" },
    { 0x012A, 0,    "Imacron" },
    { 0x012E, 0,    "Iogonek" },
    { 0x0399, 0,    "Iota" },
    { 0x03AA, 0,    "Iotadieresis" },
    { 0x038A, 0,    "Iotatonos" },
    { 0xF769, 0,    "Ismall" },
    { 0x0128, 0,    "Itilde" },
    { 0x004A, 0112, "J" },
    { 0x0134, 0,    "Jcircumflex" },
    { 0xF76A, 0,    "Jsmall" },
    { 0x004B, 0113, "K" },
    { 0x039A, 0,    "Kappa" },
    { 0x0136, 0,    "Kcommaaccent" },
    { 0xF76B, 0,    "Ksmall" },
    { 0x004C, 0114, "L" },
    { 0xF6BF, 0,    "LL" },
    { 0x0139, 0,    "Lacute" },
    { 0x039B, 0,    "Lambda" },
    { 0x013D, 0,    "Lcaron" },
    { 0x013B, 0,    "Lcommaaccent" },
    { 0x013F, 0,    "Ldot" },
    { 0x0141, 0350, "Lslash" },
    { 0xF6F9, 0,    "Lslashsmall" },
    { 0xF76C, 0,    "Lsmall" },
    { 0x004D, 0115, "M" },
    { 0xF6D0, 0,    "Macron" },
    { 0xF7AF, 0,    "Macronsmall" },
    { 0xF76D, 0,    "Msmall" },
    { 0x039C, 0,    "Mu" },
    { 0x004E, 0116, "N" },
    { 0x0143, 0,    "Nacute" },
    { 0x0147, 0,    "Ncaron" },
    { 0x0145, 0,    "Ncommaaccent" },
    { 0xF76E, 0,    "Nsmall" },
    { 0x00D1, 0,    "Ntilde" },
    { 0xF7F1, 0,    "Ntildesmall" },
    { 0x039D, 0,    "Nu" },
    { 0x004F, 0117, "O" },
    { 0x0152, 0,    "OE" },
    { 0xF6FA, 0,    "OEsmall" },
    { 0x00D3, 0,    "Oacute" },
    { 0xF7F3, 0,    "Oacutesmall" },
    { 0x014E, 0,    "Obreve" },
    { 0x00D4, 0,    "Ocircumflex" },
    { 0xF7F4, 0,    "Ocircumflexsmall" },
    { 0x00D6, 0,    "Odieresis" },
    { 0xF7F6, 0,    "Odieresissmall" },
    { 0xF6FB, 0,    "Ogoneksmall" },
    { 0x00D2, 0,    "Ograve" },
    { 0xF7F2, 0,    "Ogravesmall" },
    { 0x01A0, 0,    "Ohorn" },
    { 0x0150, 0,    "Ohungarumlaut" },
    { 0x014C, 0,    "Omacron" },
    { 0x2126, 0,    "Omega" },
    { 0x03A9, 0,    "Omega" },
    { 0x038F, 0,    "Omegatonos" },
    { 0x039F, 0,    "Omicron" },
    { 0x038C, 0,    "Omicrontonos" },
    { 0x00D8, 0351, "Oslash" },
    { 0x01FE, 0,    "Oslashacute" },
    { 0xF7F8, 0,    "Oslashsmall" },
    { 0xF76F, 0,    "Osmall" },
    { 0x00D5, 0,    "Otilde" },
    { 0xF7F5, 0,    "Otildesmall" },
    { 0x0050, 0120, "P" },
    { 0x03A6, 0,    "Phi" },
    { 0x03A0, 0,    "Pi" },
    { 0x03A8, 0,    "Psi" },
    { 0xF770, 0,    "Psmall" },
    { 0x0051, 0121, "Q" },
    { 0xF771, 0,    "Qsmall" },
    { 0x0052, 0122, "R" },
    { 0x0154, 0,    "Racute" },
    { 0x0158, 0,    "Rcaron" },
    { 0x0156, 0,    "Rcommaaccent" },
    { 0x211C, 0,    "Rfraktur" },
    { 0x03A1, 0,    "Rho" },
    { 0xF6FC, 0,    "Ringsmall" },
    { 0xF772, 0,    "Rsmall" },
    { 0x0053, 0123, "S" },
    { 0x250C, 0,    "SF010000" },
    { 0x2514, 0,    "SF020000" },
    { 0x2510, 0,    "SF030000" },
    { 0x2518, 0,    "SF040000" },
    { 0x253C, 0,    "SF050000" },
    { 0x252C, 0,    "SF060000" },
    { 0x2534, 0,    "SF070000" },
    { 0x251C, 0,    "SF080000" },
    { 0x2524, 0,    "SF090000" },
    { 0x2500, 0,    "SF100000" },
    { 0x2502, 0,    "SF110000" },
    { 0x2561, 0,    "SF190000" },
    { 0x2562, 0,    "SF200000" },
    { 0x2556, 0,    "SF210000" },
    { 0x2555, 0,    "SF220000" },
    { 0x2563, 0,    "SF230000" },
    { 0x2551, 0,    "SF240000" },
    { 0x2557, 0,    "SF250000" },
    { 0x255D, 0,    "SF260000" },
    { 0x255C, 0,    "SF270000" },
    { 0x255B, 0,    "SF280000" },
    { 0x255E, 0,    "SF360000" },
    { 0x255F, 0,    "SF370000" },
    { 0x255A, 0,    "SF380000" },
    { 0x2554, 0,    "SF390000" },
    { 0x2569, 0,    "SF400000" },
    { 0x2566, 0,    "SF410000" },
    { 0x2560, 0,    "SF420000" },
    { 0x2550, 0,    "SF430000" },
    { 0x256C, 0,    "SF440000" },
    { 0x2567, 0,    "SF450000" },
    { 0x2568, 0,    "SF460000" },
    { 0x2564, 0,    "SF470000" },
    { 0x2565, 0,    "SF480000" },
    { 0x2559, 0,    "SF490000" },
    { 0x2558, 0,    "SF500000" },
    { 0x2552, 0,    "SF510000" },
    { 0x2553, 0,    "SF520000" },
    { 0x256B, 0,    "SF530000" },
    { 0x256A, 0,    "SF540000" },
    { 0x015A, 0,    "Sacute" },
    { 0x0160, 0,    "Scaron" },
    { 0xF6FD, 0,    "Scaronsmall" },
    { 0x015E, 0,    "Scedilla" },
    { 0xF6C1, 0,    "Scedilla" },
    { 0x015C, 0,    "Scircumflex" },
    { 0x0218, 0,    "Scommaaccent" },
    { 0x03A3, 0,    "Sigma" },
    { 0xF773, 0,    "Ssmall" },
    { 0x0054, 0124, "T" },
    { 0x03A4, 0,    "Tau" },
    { 0x0166, 0,    "Tbar" },
    { 0x0164, 0,    "Tcaron" },
    { 0x0162, 0,    "Tcommaaccent" },
    { 0x021A, 0,    "Tcommaaccent" },
    { 0x0398, 0,    "Theta" },
    { 0x00DE, 0,    "Thorn" },
    { 0xF7FE, 0,    "Thornsmall" },
    { 0xF6FE, 0,    "Tildesmall" },
    { 0xF774, 0,    "Tsmall" },
    { 0x0055, 0125, "U" },
    { 0x00DA, 0,    "Uacute" },
    { 0xF7FA, 0,    "Uacutesmall" },
    { 0x016C, 0,    "Ubreve" },
    { 0x00DB, 0,    "Ucircumflex" },
    { 0xF7FB, 0,    "Ucircumflexsmall" },
    { 0x00DC, 0,    "Udieresis" },
    { 0xF7FC, 0,    "Udieresissmall" },
    { 0x00D9, 0,    "Ugrave" },
    { 0xF7F9, 0,    "Ugravesmall" },
    { 0x01AF, 0,    "Uhorn" },
    { 0x0170, 0,    "Uhungarumlaut" },
    { 0x016A, 0,    "Umacron" },
    { 0x0172, 0,    "Uogonek" },
    { 0x03A5, 0,    "Upsilon" },
    { 0x03D2, 0,    "Upsilon1" },
    { 0x03AB, 0,    "Upsilondieresis" },
    { 0x038E, 0,    "Upsilontonos" },
    { 0x016E, 0,    "Uring" },
    { 0xF775, 0,    "Usmall" },
    { 0x0168, 0,    "Utilde" },
    { 0x0056, 0126, "V" },
    { 0xF776, 0,    "Vsmall" },
    { 0x0057, 0127, "W" },
    { 0x1E82, 0,    "Wacute" },
    { 0x0174, 0,    "Wcircumflex" },
    { 0x1E84, 0,    "Wdieresis" },
    { 0x1E80, 0,    "Wgrave" },
    { 0xF777, 0,    "Wsmall" },
    { 0x0058, 0130, "X" },
    { 0x039E, 0,    "Xi" },
    { 0xF778, 0,    "Xsmall" },
    { 0x0059, 0131, "Y" },
    { 0x00DD, 0,    "Yacute" },
    { 0xF7FD, 0,    "Yacutesmall" },
    { 0x0176, 0,    "Ycircumflex" },
    { 0x0178, 0,    "Ydieresis" },
    { 0xF7FF, 0,    "Ydieresissmall" },
    { 0x1EF2, 0,    "Ygrave" },
    { 0xF779, 0,    "Ysmall" },
    { 0x005A, 0132, "Z" },
    { 0x0179, 0,    "Zacute" },
    { 0x017D, 0,    "Zcaron" },
    { 0xF6FF, 0,    "Zcaronsmall" },
    { 0x017B, 0,    "Zdotaccent" },
    { 0x0396, 0,    "Zeta" },
    { 0xF77A, 0,    "Zsmall" },
    { 0x0061, 0141, "a" },
    { 0x00E1, 0,    "aacute" },
    { 0x0103, 0,    "abreve" },
    { 0x00E2, 0,    "acircumflex" },
    { 0x00B4, 0302, "acute" },
    { 0x0301, 0,    "acutecomb" },
    { 0x00E4, 0,    "adieresis" },
    { 0x00E6, 0361, "ae" },
    { 0x01FD, 0,    "aeacute" },
    { 0x2015, 0,    "afii00208" },
    { 0x0410, 0,    "afii10017" },
    { 0x0411, 0,    "afii10018" },
    { 0x0412, 0,    "afii10019" },
    { 0x0413, 0,    "afii10020" },
    { 0x0414, 0,    "afii10021" },
    { 0x0415, 0,    "afii10022" },
    { 0x0401, 0,    "afii10023" },
    { 0x0416, 0,    "afii10024" },
    { 0x0417, 0,    "afii10025" },
    { 0x0418, 0,    "afii10026" },
    { 0x0419, 0,    "afii10027" },
    { 0x041A, 0,    "afii10028" },
    { 0x041B, 0,    "afii10029" },
    { 0x041C, 0,    "afii10030" },
    { 0x041D, 0,    "afii10031" },
    { 0x041E, 0,    "afii10032" },
    { 0x041F, 0,    "afii10033" },
    { 0x0420, 0,    "afii10034" },
    { 0x0421, 0,    "afii10035" },
    { 0x0422, 0,    "afii10036" },
    { 0x0423, 0,    "afii10037" },
    { 0x0424, 0,    "afii10038" },
    { 0x0425, 0,    "afii10039" },
    { 0x0426, 0,    "afii10040" },
    { 0x0427, 0,    "afii10041" },
    { 0x0428, 0,    "afii10042" },
    { 0x0429, 0,    "afii10043" },
    { 0x042A, 0,    "afii10044" },
    { 0x042B, 0,    "afii10045" },
    { 0x042C, 0,    "afii10046" },
    { 0x042D, 0,    "afii10047" },
    { 0x042E, 0,    "afii10048" },
    { 0x042F, 0,    "afii10049" },
    { 0x0490, 0,    "afii10050" },
    { 0x0402, 0,    "afii10051" },
    { 0x0403, 0,    "afii10052" },
    { 0x0404, 0,    "afii10053" },
    { 0x0405, 0,    "afii10054" },
    { 0x0406, 0,    "afii10055" },
    { 0x0407, 0,    "afii10056" },
    { 0x0408, 0,    "afii10057" },
    { 0x0409, 0,    "afii10058" },
    { 0x040A, 0,    "afii10059" },
    { 0x040B, 0,    "afii10060" },
    { 0x040C, 0,    "afii10061" },
    { 0x040E, 0,    "afii10062" },
    { 0xF6C4, 0,    "afii10063" },
    { 0xF6C5, 0,    "afii10064" },
    { 0x0430, 0,    "afii10065" },
    { 0x0431, 0,    "afii10066" },
    { 0x0432, 0,    "afii10067" },
    { 0x0433, 0,    "afii10068" },
    { 0x0434, 0,    "afii10069" },
    { 0x0435, 0,    "afii10070" },
    { 0x0451, 0,    "afii10071" },
    { 0x0436, 0,    "afii10072" },
    { 0x0437, 0,    "afii10073" },
    { 0x0438, 0,    "afii10074" },
    { 0x0439, 0,    "afii10075" },
    { 0x043A, 0,    "afii10076" },
    { 0x043B, 0,    "afii10077" },
    { 0x043C, 0,    "afii10078" },
    { 0x043D, 0,    "afii10079" },
    { 0x043E, 0,    "afii10080" },
    { 0x043F, 0,    "afii10081" },
    { 0x0440, 0,    "afii10082" },
    { 0x0441, 0,    "afii10083" },
    { 0x0442, 0,    "afii10084" },
    { 0x0443, 0,    "afii10085" },
    { 0x0444, 0,    "afii10086" },
    { 0x0445, 0,    "afii10087" },
    { 0x0446, 0,    "afii10088" },
    { 0x0447, 0,    "afii10089" },
    { 0x0448, 0,    "afii10090" },
    { 0x0449, 0,    "afii10091" },
    { 0x044A, 0,    "afii10092" },
    { 0x044B, 0,    "afii10093" },
    { 0x044C, 0,    "afii10094" },
    { 0x044D, 0,    "afii10095" },
    { 0x044E, 0,    "afii10096" },
    { 0x044F, 0,    "afii10097" },
    { 0x0491, 0,    "afii10098" },
    { 0x0452, 0,    "afii10099" },
    { 0x0453, 0,    "afii10100" },
    { 0x0454, 0,    "afii10101" },
    { 0x0455, 0,    "afii10102" },
    { 0x0456, 0,    "afii10103" },
    { 0x0457, 0,    "afii10104" },
    { 0x0458, 0,    "afii10105" },
    { 0x0459, 0,    "afii10106" },
    { 0x045A, 0,    "afii10107" },
    { 0x045B, 0,    "afii10108" },
    { 0x045C, 0,    "afii10109" },
    { 0x045E, 0,    "afii10110" },
    { 0x040F, 0,    "afii10145" },
    { 0x0462, 0,    "afii10146" },
    { 0x0472, 0,    "afii10147" },
    { 0x0474, 0,    "afii10148" },
    { 0xF6C6, 0,    "afii10192" },
    { 0x045F, 0,    "afii10193" },
    { 0x0463, 0,    "afii10194" },
    { 0x0473, 0,    "afii10195" },
    { 0x0475, 0,    "afii10196" },
    { 0xF6C7, 0,    "afii10831" },
    { 0xF6C8, 0,    "afii10832" },
    { 0x04D9, 0,    "afii10846" },
    { 0x200E, 0,    "afii299" },
    { 0x200F, 0,    "afii300" },
    { 0x200D, 0,    "afii301" },
    { 0x066A, 0,    "afii57381" },
    { 0x060C, 0,    "afii57388" },
    { 0x0660, 0,    "afii57392" },
    { 0x0661, 0,    "afii57393" },
    { 0x0662, 0,    "afii57394" },
    { 0x0663, 0,    "afii57395" },
    { 0x0664, 0,    "afii57396" },
    { 0x0665, 0,    "afii57397" },
    { 0x0666, 0,    "afii57398" },
    { 0x0667, 0,    "afii57399" },
    { 0x0668, 0,    "afii57400" },
    { 0x0669, 0,    "afii57401" },
    { 0x061B, 0,    "afii57403" },
    { 0x061F, 0,    "afii57407" },
    { 0x0621, 0,    "afii57409" },
    { 0x0622, 0,    "afii57410" },
    { 0x0623, 0,    "afii57411" },
    { 0x0624, 0,    "afii57412" },
    { 0x0625, 0,    "afii57413" },
    { 0x0626, 0,    "afii57414" },
    { 0x0627, 0,    "afii57415" },
    { 0x0628, 0,    "afii57416" },
    { 0x0629, 0,    "afii57417" },
    { 0x062A, 0,    "afii57418" },
    { 0x062B, 0,    "afii57419" },
    { 0x062C, 0,    "afii57420" },
    { 0x062D, 0,    "afii57421" },
    { 0x062E, 0,    "afii57422" },
    { 0x062F, 0,    "afii57423" },
    { 0x0630, 0,    "afii57424" },
    { 0x0631, 0,    "afii57425" },
    { 0x0632, 0,    "afii57426" },
    { 0x0633, 0,    "afii57427" },
    { 0x0634, 0,    "afii57428" },
    { 0x0635, 0,    "afii57429" },
    { 0x0636, 0,    "afii57430" },
    { 0x0637, 0,    "afii57431" },
    { 0x0638, 0,    "afii57432" },
    { 0x0639, 0,    "afii57433" },
    { 0x063A, 0,    "afii57434" },
    { 0x0640, 0,    "afii57440" },
    { 0x0641, 0,    "afii57441" },
    { 0x0642, 0,    "afii57442" },
    { 0x0643, 0,    "afii57443" },
    { 0x0644, 0,    "afii57444" },
    { 0x0645, 0,    "afii57445" },
    { 0x0646, 0,    "afii57446" },
    { 0x0648, 0,    "afii57448" },
    { 0x0649, 0,    "afii57449" },
    { 0x064A, 0,    "afii57450" },
    { 0x064B, 0,    "afii57451" },
    { 0x064C, 0,    "afii57452" },
    { 0x064D, 0,    "afii57453" },
    { 0x064E, 0,    "afii57454" },
    { 0x064F, 0,    "afii57455" },
    { 0x0650, 0,    "afii57456" },
    { 0x0651, 0,    "afii57457" },
    { 0x0652, 0,    "afii57458" },
    { 0x0647, 0,    "afii57470" },
    { 0x06A4, 0,    "afii57505" },
    { 0x067E, 0,    "afii57506" },
    { 0x0686, 0,    "afii57507" },
    { 0x0698, 0,    "afii57508" },
    { 0x06AF, 0,    "afii57509" },
    { 0x0679, 0,    "afii57511" },
    { 0x0688, 0,    "afii57512" },
    { 0x0691, 0,    "afii57513" },
    { 0x06BA, 0,    "afii57514" },
    { 0x06D2, 0,    "afii57519" },
    { 0x06D5, 0,    "afii57534" },
    { 0x20AA, 0,    "afii57636" },
    { 0x05BE, 0,    "afii57645" },
    { 0x05C3, 0,    "afii57658" },
    { 0x05D0, 0,    "afii57664" },
    { 0x05D1, 0,    "afii57665" },
    { 0x05D2, 0,    "afii57666" },
    { 0x05D3, 0,    "afii57667" },
    { 0x05D4, 0,    "afii57668" },
    { 0x05D5, 0,    "afii57669" },
    { 0x05D6, 0,    "afii57670" },
    { 0x05D7, 0,    "afii57671" },
    { 0x05D8, 0,    "afii57672" },
    { 0x05D9, 0,    "afii57673" },
    { 0x05DA, 0,    "afii57674" },
    { 0x05DB, 0,    "afii57675" },
    { 0x05DC, 0,    "afii57676" },
    { 0x05DD, 0,    "afii57677" },
    { 0x05DE, 0,    "afii57678" },
    { 0x05DF, 0,    "afii57679" },
    { 0x05E0, 0,    "afii57680" },
    { 0x05E1, 0,    "afii57681" },
    { 0x05E2, 0,    "afii57682" },
    { 0x05E3, 0,    "afii57683" },
    { 0x05E4, 0,    "afii57684" },
    { 0x05E5, 0,    "afii57685" },
    { 0x05E6, 0,    "afii57686" },
    { 0x05E7, 0,    "afii57687" },
    { 0x05E8, 0,    "afii57688" },
    { 0x05E9, 0,    "afii57689" },
    { 0x05EA, 0,    "afii57690" },
    { 0xFB2A, 0,    "afii57694" },
    { 0xFB2B, 0,    "afii57695" },
    { 0xFB4B, 0,    "afii57700" },
    { 0xFB1F, 0,    "afii57705" },
    { 0x05F0, 0,    "afii57716" },
    { 0x05F1, 0,    "afii57717" },
    { 0x05F2, 0,    "afii57718" },
    { 0xFB35, 0,    "afii57723" },
    { 0x05B4, 0,    "afii57793" },
    { 0x05B5, 0,    "afii57794" },
    { 0x05B6, 0,    "afii57795" },
    { 0x05BB, 0,    "afii57796" },
    { 0x05B8, 0,    "afii57797" },
    { 0x05B7, 0,    "afii57798" },
    { 0x05B0, 0,    "afii57799" },
    { 0x05B2, 0,    "afii57800" },
    { 0x05B1, 0,    "afii57801" },
    { 0x05B3, 0,    "afii57802" },
    { 0x05C2, 0,    "afii57803" },
    { 0x05C1, 0,    "afii57804" },
    { 0x05B9, 0,    "afii57806" },
    { 0x05BC, 0,    "afii57807" },
    { 0x05BD, 0,    "afii57839" },
    { 0x05BF, 0,    "afii57841" },
    { 0x05C0, 0,    "afii57842" },
    { 0x02BC, 0,    "afii57929" },
    { 0x2105, 0,    "afii61248" },
    { 0x2113, 0,    "afii61289" },
    { 0x2116, 0,    "afii61352" },
    { 0x202C, 0,    "afii61573" },
    { 0x202D, 0,    "afii61574" },
    { 0x202E, 0,    "afii61575" },
    { 0x200C, 0,    "afii61664" },
    { 0x066D, 0,    "afii63167" },
    { 0x02BD, 0,    "afii64937" },
    { 0x00E0, 0,    "agrave" },
    { 0x2135, 0,    "aleph" },
    { 0x03B1, 0,    "alpha" },
    { 0x03AC, 0,    "alphatonos" },
    { 0x0101, 0,    "amacron" },
    { 0x0026, 046,  "ampersand" },
    { 0xF726, 0,    "ampersandsmall" },
    { 0x2220, 0,    "angle" },
    { 0x2329, 0,    "angleleft" },
    { 0x232A, 0,    "angleright" },
    { 0x0387, 0,    "anoteleia" },
    { 0x0105, 0,    "aogonek" },
    { 0x2248, 0,    "approxequal" },
    { 0x00E5, 0,    "aring" },
    { 0x01FB, 0,    "aringacute" },
    { 0x2194, 0,    "arrowboth" },
    { 0x21D4, 0,    "arrowdblboth" },
    { 0x21D3, 0,    "arrowdbldown" },
    { 0x21D0, 0,    "arrowdblleft" },
    { 0x21D2, 0,    "arrowdblright" },
    { 0x21D1, 0,    "arrowdblup" },
    { 0x2193, 0,    "arrowdown" },
    { 0xF8E7, 0,    "arrowhorizex" },
    { 0x2190, 0,    "arrowleft" },
    { 0x2192, 0,    "arrowright" },
    { 0x2191, 0,    "arrowup" },
    { 0x2195, 0,    "arrowupdn" },
    { 0x21A8, 0,    "arrowupdnbse" },
    { 0xF8E6, 0,    "arrowvertex" },
    { 0x005E, 0136, "asciicircum" },
    { 0x007E, 0176, "asciitilde" },
    { 0x002A, 052,  "asterisk" },
    { 0x2217, 0,    "asteriskmath" },
    { 0xF6E9, 0,    "asuperior" },
    { 0x0040, 0100, "at" },
    { 0x00E3, 0,    "atilde" },
    { 0x0062, 0142, "b" },
    { 0x005C, 0134, "backslash" },
    { 0x007C, 0174, "bar" },
    { 0x03B2, 0,    "beta" },
    { 0x2588, 0,    "block" },
    { 0xF8F4, 0,    "braceex" },
    { 0x007B, 0173, "braceleft" },
    { 0xF8F3, 0,    "braceleftbt" },
    { 0xF8F2, 0,    "braceleftmid" },
    { 0xF8F1, 0,    "bracelefttp" },
    { 0x007D, 0175, "braceright" },
    { 0xF8FE, 0,    "bracerightbt" },
    { 0xF8FD, 0,    "bracerightmid" },
    { 0xF8FC, 0,    "bracerighttp" },
    { 0x005B, 0133, "bracketleft" },
    { 0xF8F0, 0,    "bracketleftbt" },
    { 0xF8EF, 0,    "bracketleftex" },
    { 0xF8EE, 0,    "bracketlefttp" },
    { 0x005D, 0135, "bracketright" },
    { 0xF8FB, 0,    "bracketrightbt" },
    { 0xF8FA, 0,    "bracketrightex" },
    { 0xF8F9, 0,    "bracketrighttp" },
    { 0x02D8, 0306, "breve" },
    { 0x00A6, 0,    "brokenbar" },
    { 0xF6EA, 0,    "bsuperior" },
    { 0x2022, 0267, "bullet" },
    { 0x0063, 0143, "c" },
    { 0x0107, 0,    "cacute" },
    { 0x02C7, 0317, "caron" },
    { 0x21B5, 0,    "carriagereturn" },
    { 0x010D, 0,    "ccaron" },
    { 0x00E7, 0,    "ccedilla" },
    { 0x0109, 0,    "ccircumflex" },
    { 0x010B, 0,    "cdotaccent" },
    { 0x00B8, 0313, "cedilla" },
    { 0x00A2, 0242, "cent" },
    { 0xF6DF, 0,    "centinferior" },
    { 0xF7A2, 0,    "centoldstyle" },
    { 0xF6E0, 0,    "centsuperior" },
    { 0x03C7, 0,    "chi" },
    { 0x25CB, 0,    "circle" },
    { 0x2297, 0,    "circlemultiply" },
    { 0x2295, 0,    "circleplus" },
    { 0x02C6, 0303, "circumflex" },
    { 0x2663, 0,    "club" },
    { 0x003A, 072,  "colon" },
    { 0x20A1, 0,    "colonmonetary" },
    { 0x002C, 054,  "comma" },
    { 0xF6C3, 0,    "commaaccent" },
    { 0xF6E1, 0,    "commainferior" },
    { 0xF6E2, 0,    "commasuperior" },
    { 0x2245, 0,    "congruent" },
    { 0x00A9, 0,    "copyright" },
    { 0xF8E9, 0,    "copyrightsans" },
    { 0xF6D9, 0,    "copyrightserif" },
    { 0x00A4, 0250, "currency" },
    { 0xF6D1, 0,    "cyrBreve" },
    { 0xF6D2, 0,    "cyrFlex" },
    { 0xF6D4, 0,    "cyrbreve" },
    { 0xF6D5, 0,    "cyrflex" },
    { 0x0064, 0144, "d" },
    { 0x2020, 0262, "dagger" },
    { 0x2021, 0263, "daggerdbl" },
    { 0xF6D3, 0,    "dblGrave" },
    { 0xF6D6, 0,    "dblgrave" },
    { 0x010F, 0,    "dcaron" },
    { 0x0111, 0,    "dcroat" },
    { 0x00B0, 0,    "degree" },
    { 0x03B4, 0,    "delta" },
    { 0x2666, 0,    "diamond" },
    { 0x00A8, 0310, "dieresis" },
    { 0xF6D7, 0,    "dieresisacute" },
    { 0xF6D8, 0,    "dieresisgrave" },
    { 0x0385, 0,    "dieresistonos" },
    { 0x00F7, 0,    "divide" },
    { 0x2593, 0,    "dkshade" },
    { 0x2584, 0,    "dnblock" },
    { 0x0024, 044,  "dollar" },
    { 0xF6E3, 0,    "dollarinferior" },
    { 0xF724, 0,    "dollaroldstyle" },
    { 0xF6E4, 0,    "dollarsuperior" },
    { 0x20AB, 0,    "dong" },
    { 0x02D9, 0307, "dotaccent" },
    { 0x0323, 0,    "dotbelowcomb" },
    { 0x0131, 0365, "dotlessi" },
    { 0xF6BE, 0,    "dotlessj" },
    { 0x22C5, 0,    "dotmath" },
    { 0xF6EB, 0,    "dsuperior" },
    { 0x0065, 0145, "e" },
    { 0x00E9, 0,    "eacute" },
    { 0x0115, 0,    "ebreve" },
    { 0x011B, 0,    "ecaron" },
    { 0x00EA, 0,    "ecircumflex" },
    { 0x00EB, 0,    "edieresis" },
    { 0x0117, 0,    "edotaccent" },
    { 0x00E8, 0,    "egrave" },
    { 0x0038, 070,  "eight" },
    { 0x2088, 0,    "eightinferior" },
    { 0xF738, 0,    "eightoldstyle" },
    { 0x2078, 0,    "eightsuperior" },
    { 0x2208, 0,    "element" },
    { 0x2026, 0274, "ellipsis" },
    { 0x0113, 0,    "emacron" },
    { 0x2014, 0320, "emdash" },
    { 0x2205, 0,    "emptyset" },
    { 0x2013, 0261, "endash" },
    { 0x014B, 0,    "eng" },
    { 0x0119, 0,    "eogonek" },
    { 0x03B5, 0,    "epsilon" },
    { 0x03AD, 0,    "epsilontonos" },
    { 0x003D, 075,  "equal" },
    { 0x2261, 0,    "equivalence" },
    { 0x212E, 0,    "estimated" },
    { 0xF6EC, 0,    "esuperior" },
    { 0x03B7, 0,    "eta" },
    { 0x03AE, 0,    "etatonos" },
    { 0x00F0, 0,    "eth" },
    { 0x0021, 041,  "exclam" },
    { 0x203C, 0,    "exclamdbl" },
    { 0x00A1, 0241, "exclamdown" },
    { 0xF7A1, 0,    "exclamdownsmall" },
    { 0xF721, 0,    "exclamsmall" },
    { 0x2203, 0,    "existential" },
    { 0x0066, 0146, "f" },
    { 0x2640, 0,    "female" },
    { 0xFB00, 0,    "ff" },
    { 0xFB03, 0,    "ffi" },
    { 0xFB04, 0,    "ffl" },
    { 0xFB01, 0256, "fi" },
    { 0x2012, 0,    "figuredash" },
    { 0x25A0, 0,    "filledbox" },
    { 0x25AC, 0,    "filledrect" },
    { 0x0035, 065,  "five" },
    { 0x215D, 0,    "fiveeighths" },
    { 0x2085, 0,    "fiveinferior" },
    { 0xF735, 0,    "fiveoldstyle" },
    { 0x2075, 0,    "fivesuperior" },
    { 0xFB02, 0257, "fl" },
    { 0x0192, 0246, "florin" },
    { 0x0034, 064,  "four" },
    { 0x2084, 0,    "fourinferior" },
    { 0xF734, 0,    "fouroldstyle" },
    { 0x2074, 0,    "foursuperior" },
    { 0x2044, 0244, "fraction" },
    { 0x2215, 0244, "fraction" },
    { 0x20A3, 0,    "franc" },
    { 0x0067, 0147, "g" },
    { 0x03B3, 0,    "gamma" },
    { 0x011F, 0,    "gbreve" },
    { 0x01E7, 0,    "gcaron" },
    { 0x011D, 0,    "gcircumflex" },
    { 0x0123, 0,    "gcommaaccent" },
    { 0x0121, 0,    "gdotaccent" },
    { 0x00DF, 0373, "germandbls" },
    { 0x2207, 0,    "gradient" },
    { 0x0060, 0301, "grave" },
    { 0x0300, 0,    "gravecomb" },
    { 0x003E, 076,  "greater" },
    { 0x2265, 0,    "greaterequal" },
    { 0x00AB, 0253, "guillemotleft" },
    { 0x00BB, 0273, "guillemotright" },
    { 0x2039, 0254, "guilsinglleft" },
    { 0x203A, 0255, "guilsinglright" },
    { 0x0068, 0150, "h" },
    { 0x0127, 0,    "hbar" },
    { 0x0125, 0,    "hcircumflex" },
    { 0x2665, 0,    "heart" },
    { 0x0309, 0,    "hookabovecomb" },
    { 0x2302, 0,    "house" },
    { 0x02DD, 0315, "hungarumlaut" },
    { 0x002D, 055,  "hyphen" },
    { 0x00AD, 0,    "hyphen" },
    { 0xF6E5, 0,    "hypheninferior" },
    { 0xF6E6, 0,    "hyphensuperior" },
    { 0x0069, 0151, "i" },
    { 0x00ED, 0,    "iacute" },
    { 0x012D, 0,    "ibreve" },
    { 0x00EE, 0,    "icircumflex" },
    { 0x00EF, 0,    "idieresis" },
    { 0x00EC, 0,    "igrave" },
    { 0x0133, 0,    "ij" },
    { 0x012B, 0,    "imacron" },
    { 0x221E, 0,    "infinity" },
    { 0x222B, 0,    "integral" },
    { 0x2321, 0,    "integralbt" },
    { 0xF8F5, 0,    "integralex" },
    { 0x2320, 0,    "integraltp" },
    { 0x2229, 0,    "intersection" },
    { 0x25D8, 0,    "invbullet" },
    { 0x25D9, 0,    "invcircle" },
    { 0x263B, 0,    "invsmileface" },
    { 0x012F, 0,    "iogonek" },
    { 0x03B9, 0,    "iota" },
    { 0x03CA, 0,    "iotadieresis" },
    { 0x0390, 0,    "iotadieresistonos" },
    { 0x03AF, 0,    "iotatonos" },
    { 0xF6ED, 0,    "isuperior" },
    { 0x0129, 0,    "itilde" },
    { 0x006A, 0152, "j" },
    { 0x0135, 0,    "jcircumflex" },
    { 0x006B, 0153, "k" },
    { 0x03BA, 0,    "kappa" },
    { 0x0137, 0,    "kcommaaccent" },
    { 0x0138, 0,    "kgreenlandic" },
    { 0x006C, 0154, "l" },
    { 0x013A, 0,    "lacute" },
    { 0x03BB, 0,    "lambda" },
    { 0x013E, 0,    "lcaron" },
    { 0x013C, 0,    "lcommaaccent" },
    { 0x0140, 0,    "ldot" },
    { 0x003C, 074,  "less" },
    { 0x2264, 0,    "lessequal" },
    { 0x258C, 0,    "lfblock" },
    { 0x20A4, 0,    "lira" },
    { 0xF6C0, 0,    "ll" },
    { 0x2227, 0,    "logicaland" },
    { 0x00AC, 0,    "logicalnot" },
    { 0x2228, 0,    "logicalor" },
    { 0x017F, 0,    "longs" },
    { 0x25CA, 0,    "lozenge" },
    { 0x0142, 0370, "lslash" },
    { 0xF6EE, 0,    "lsuperior" },
    { 0x2591, 0,    "ltshade" },
    { 0x006D, 0155, "m" },
    { 0x00AF, 0305, "macron" },
    { 0x02C9, 0305, "macron" },
    { 0x2642, 0,    "male" },
    { 0x2212, 0,    "minus" },
    { 0x2032, 0,    "minute" },
    { 0xF6EF, 0,    "msuperior" },
    { 0x00B5, 0,    "mu" },
    { 0x03BC, 0,    "mu" },
    { 0x00D7, 0,    "multiply" },
    { 0x266A, 0,    "musicalnote" },
    { 0x266B, 0,    "musicalnotedbl" },
    { 0x006E, 0156, "n" },
    { 0x0144, 0,    "nacute" },
    { 0x0149, 0,    "napostrophe" },
    { 0x0148, 0,    "ncaron" },
    { 0x0146, 0,    "ncommaaccent" },
    { 0x0039, 071,  "nine" },
    { 0x2089, 0,    "nineinferior" },
    { 0xF739, 0,    "nineoldstyle" },
    { 0x2079, 0,    "ninesuperior" },
    { 0x2209, 0,    "notelement" },
    { 0x2260, 0,    "notequal" },
    { 0x2284, 0,    "notsubset" },
    { 0x207F, 0,    "nsuperior" },
    { 0x00F1, 0,    "ntilde" },
    { 0x03BD, 0,    "nu" },
    { 0x0023, 043,  "numbersign" },
    { 0x006F, 0157, "o" },
    { 0x00F3, 0,    "oacute" },
    { 0x014F, 0,    "obreve" },
    { 0x00F4, 0,    "ocircumflex" },
    { 0x00F6, 0,    "odieresis" },
    { 0x0153, 0372, "oe" },
    { 0x02DB, 0316, "ogonek" },
    { 0x00F2, 0,    "ograve" },
    { 0x01A1, 0,    "ohorn" },
    { 0x0151, 0,    "ohungarumlaut" },
    { 0x014D, 0,    "omacron" },
    { 0x03C9, 0,    "omega" },
    { 0x03D6, 0,    "omega1" },
    { 0x03CE, 0,    "omegatonos" },
    { 0x03BF, 0,    "omicron" },
    { 0x03CC, 0,    "omicrontonos" },
    { 0x0031, 061,  "one" },
    { 0x2024, 0,    "onedotenleader" },
    { 0x215B, 0,    "oneeighth" },
    { 0xF6DC, 0,    "onefitted" },
    { 0x00BD, 0,    "onehalf" },
    { 0x2081, 0,    "oneinferior" },
    { 0xF731, 0,    "oneoldstyle" },
    { 0x00BC, 0,    "onequarter" },
    { 0x00B9, 0,    "onesuperior" },
    { 0x2153, 0,    "onethird" },
    { 0x25E6, 0,    "openbullet" },
    { 0x00AA, 0343, "ordfeminine" },
    { 0x00BA, 0353, "ordmasculine" },
    { 0x221F, 0,    "orthogonal" },
    { 0x00F8, 0371, "oslash" },
    { 0x01FF, 0,    "oslashacute" },
    { 0xF6F0, 0,    "osuperior" },
    { 0x00F5, 0,    "otilde" },
    { 0x0070, 0160, "p" },
    { 0x00B6, 0266, "paragraph" },
    { 0x0028, 050,  "parenleft" },
    { 0xF8ED, 0,    "parenleftbt" },
    { 0xF8EC, 0,    "parenleftex" },
    { 0x208D, 0,    "parenleftinferior" },
    { 0x207D, 0,    "parenleftsuperior" },
    { 0xF8EB, 0,    "parenlefttp" },
    { 0x0029, 051,  "parenright" },
    { 0xF8F8, 0,    "parenrightbt" },
    { 0xF8F7, 0,    "parenrightex" },
    { 0x208E, 0,    "parenrightinferior" },
    { 0x207E, 0,    "parenrightsuperior" },
    { 0xF8F6, 0,    "parenrighttp" },
    { 0x2202, 0,    "partialdiff" },
    { 0x0025, 045,  "percent" },
    { 0x002E, 056,  "period" },
    { 0x00B7, 0264, "periodcentered" },
    { 0x2219, 0,    "periodcentered" },
    { 0xF6E7, 0,    "periodinferior" },
    { 0xF6E8, 0,    "periodsuperior" },
    { 0x22A5, 0,    "perpendicular" },
    { 0x2030, 0275, "perthousand" },
    { 0x20A7, 0,    "peseta" },
    { 0x03C6, 0,    "phi" },
    { 0x03D5, 0,    "phi1" },
    { 0x03C0, 0,    "pi" },
    { 0x002B, 053,  "plus" },
    { 0x00B1, 0,    "plusminus" },
    { 0x211E, 0,    "prescription" },
    { 0x220F, 0,    "product" },
    { 0x2282, 0,    "propersubset" },
    { 0x2283, 0,    "propersuperset" },
    { 0x221D, 0,    "proportional" },
    { 0x03C8, 0,    "psi" },
    { 0x0071, 0161, "q" },
    { 0x003F, 077,  "question" },
    { 0x00BF, 0277, "questiondown" },
    { 0xF7BF, 0,    "questiondownsmall" },
    { 0xF73F, 0,    "questionsmall" },
    { 0x0022, 042,  "quotedbl" },
    { 0x201E, 0271, "quotedblbase" },
    { 0x201C, 0252, "quotedblleft" },
    { 0x201D, 0272, "quotedblright" },
    { 0x2018, 0140, "quoteleft" },
    { 0x201B, 0,    "quotereversed" },
    { 0x2019, 047,  "quoteright" },
    { 0x201A, 0270, "quotesinglbase" },
    { 0x0027, 0251, "quotesingle" },
    { 0x0072, 0162, "r" },
    { 0x0155, 0,    "racute" },
    { 0x221A, 0,    "radical" },
    { 0xF8E5, 0,    "radicalex" },
    { 0x0159, 0,    "rcaron" },
    { 0x0157, 0,    "rcommaaccent" },
    { 0x2286, 0,    "reflexsubset" },
    { 0x2287, 0,    "reflexsuperset" },
    { 0x00AE, 0,    "registered" },
    { 0xF8E8, 0,    "registersans" },
    { 0xF6DA, 0,    "registerserif" },
    { 0x2310, 0,    "revlogicalnot" },
    { 0x03C1, 0,    "rho" },
    { 0x02DA, 0312, "ring" },
    { 0xF6F1, 0,    "rsuperior" },
    { 0x2590, 0,    "rtblock" },
    { 0xF6DD, 0,    "rupiah" },
    { 0x0073, 0163, "s" },
    { 0x015B, 0,    "sacute" },
    { 0x0161, 0,    "scaron" },
    { 0x015F, 0,    "scedilla" },
    { 0xF6C2, 0,    "scedilla" },
    { 0x015D, 0,    "scircumflex" },
    { 0x0219, 0,    "scommaaccent" },
    { 0x2033, 0,    "second" },
    { 0x00A7, 0247, "section" },
    { 0x003B, 073,  "semicolon" },
    { 0x0037, 067,  "seven" },
    { 0x215E, 0,    "seveneighths" },
    { 0x2087, 0,    "seveninferior" },
    { 0xF737, 0,    "sevenoldstyle" },
    { 0x2077, 0,    "sevensuperior" },
    { 0x2592, 0,    "shade" },
    { 0x03C3, 0,    "sigma" },
    { 0x03C2, 0,    "sigma1" },
    { 0x223C, 0,    "similar" },
    { 0x0036, 066,  "six" },
    { 0x2086, 0,    "sixinferior" },
    { 0xF736, 0,    "sixoldstyle" },
    { 0x2076, 0,    "sixsuperior" },
    { 0x002F, 057,  "slash" },
    { 0x263A, 0,    "smileface" },
    { 0x0020, 040,  "space" },
    { 0x00A0, 040,  "space" },
    { 0x2660, 0,    "spade" },
    { 0xF6F2, 0,    "ssuperior" },
    { 0x00A3, 0243, "sterling" },
    { 0x220B, 0,    "suchthat" },
    { 0x2211, 0,    "summation" },
    { 0x263C, 0,    "sun" },
    { 0x0074, 0164, "t" },
    { 0x03C4, 0,    "tau" },
    { 0x0167, 0,    "tbar" },
    { 0x0165, 0,    "tcaron" },
    { 0x0163, 0,    "tcommaaccent" },
    { 0x021B, 0,    "tcommaaccent" },
    { 0x2234, 0,    "therefore" },
    { 0x03B8, 0,    "theta" },
    { 0x03D1, 0,    "theta1" },
    { 0x00FE, 0,    "thorn" },
    { 0x0033, 063,  "three" },
    { 0x215C, 0,    "threeeighths" },
    { 0x2083, 0,    "threeinferior" },
    { 0xF733, 0,    "threeoldstyle" },
    { 0x00BE, 0,    "threequarters" },
    { 0xF6DE, 0,    "threequartersemdash" },
    { 0x00B3, 0,    "threesuperior" },
    { 0x02DC, 0304, "tilde" },
    { 0x0303, 0,    "tildecomb" },
    { 0x0384, 0,    "tonos" },
    { 0x2122, 0,    "trademark" },
    { 0xF8EA, 0,    "trademarksans" },
    { 0xF6DB, 0,    "trademarkserif" },
    { 0x25BC, 0,    "triagdn" },
    { 0x25C4, 0,    "triaglf" },
    { 0x25BA, 0,    "triagrt" },
    { 0x25B2, 0,    "triagup" },
    { 0xF6F3, 0,    "tsuperior" },
    { 0x0032, 062,  "two" },
    { 0x2025, 0,    "twodotenleader" },
    { 0x2082, 0,    "twoinferior" },
    { 0xF732, 0,    "twooldstyle" },
    { 0x00B2, 0,    "twosuperior" },
    { 0x2154, 0,    "twothirds" },
    { 0x0075, 0165, "u" },
    { 0x00FA, 0,    "uacute" },
    { 0x016D, 0,    "ubreve" },
    { 0x00FB, 0,    "ucircumflex" },
    { 0x00FC, 0,    "udieresis" },
    { 0x00F9, 0,    "ugrave" },
    { 0x01B0, 0,    "uhorn" },
    { 0x0171, 0,    "uhungarumlaut" },
    { 0x016B, 0,    "umacron" },
    { 0x005F, 0137, "underscore" },
    { 0x2017, 0,    "underscoredbl" },
    { 0x222A, 0,    "union" },
    { 0x2200, 0,    "universal" },
    { 0x0173, 0,    "uogonek" },
    { 0x2580, 0,    "upblock" },
    { 0x03C5, 0,    "upsilon" },
    { 0x03CB, 0,    "upsilondieresis" },
    { 0x03B0, 0,    "upsilondieresistonos" },
    { 0x03CD, 0,    "upsilontonos" },
    { 0x016F, 0,    "uring" },
    { 0x0169, 0,    "utilde" },
    { 0x0076, 0166, "v" },
    { 0x0077, 0167, "w" },
    { 0x1E83, 0,    "wacute" },
    { 0x0175, 0,    "wcircumflex" },
    { 0x1E85, 0,    "wdieresis" },
    { 0x2118, 0,    "weierstrass" },
    { 0x1E81, 0,    "wgrave" },
    { 0x0078, 0170, "x" },
    { 0x03BE, 0,    "xi" },
    { 0x0079, 0171, "y" },
    { 0x00FD, 0,    "yacute" },
    { 0x0177, 0,    "ycircumflex" },
    { 0x00FF, 0,    "ydieresis" },
    { 0x00A5, 0245, "yen" },
    { 0x1EF3, 0,    "ygrave" },
    { 0x007A, 0172, "z" },
    { 0x017A, 0,    "zacute" },
    { 0x017E, 0,    "zcaron" },
    { 0x017C, 0,    "zdotaccent" },
    { 0x0030, 060,  "zero" },
    { 0x2080, 0,    "zeroinferior" },
    { 0xF730, 0,    "zerooldstyle" },
    { 0x2070, 0,    "zerosuperior" },
    { 0x03B6, 0,    "zeta" }
};