/* Class to handle character set AL16UTF16
   Copyright (C) 2018-2020 Adam Leszczynski (aleszczynski@bersler.com)

This file is part of OpenLogReplicator.

OpenLogReplicator is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 3, or (at your option)
any later version.

OpenLogReplicator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenLogReplicator; see the file LICENSE;  If not see
<http://www.gnu.org/licenses/>.  */

#include "CharacterSetAL16UTF16.h"

using namespace std;

namespace OpenLogReplicator {

    CharacterSetAL16UTF16::CharacterSetAL16UTF16() :
        CharacterSet("AL16UTF16") {
    }

    CharacterSetAL16UTF16::~CharacterSetAL16UTF16() {
    }

    typeunicode CharacterSetAL16UTF16::decode(const uint8_t* &str, uint64_t &length) {
        uint64_t byte1 = *str++;
        --length;

        if (length == 0)
            return badChar(byte1);

        uint64_t byte2 = *str++;
        --length;

        if ((byte1 & 0xFC) == 0xDC)
            return badChar(byte1, byte2);

        if ((byte1 & 0xFC) != 0xD8)
            return (byte1 << 8) | byte2;

        if (length == 0)
            return badChar(byte1, byte2);

        uint64_t byte3 = *str++;
        --length;

        if (length == 0)
            return badChar(byte1, byte2, byte3);

        uint64_t byte4 = *str++;
        --length;

        //U' = yyyy yyyy yyxx xxxx xxxx   // U - 0x10000
        //W1 = 1101 10yy yyyy yyyy      // 0xD800 + yyyyyyyyyy
        //W2 = 1101 11xx xxxx xxxx      // 0xDC00 + xxxxxxxxxx

        if ((byte3 & 0xFC) == 0xDC) {
            return 0x10000 + (((byte1 & 0x03) << 18) | (byte2 << 10) | ((byte3 & 0x03) << 8) | byte4);
        } else
            return badChar(byte1, byte2, byte3, byte4);
    }
}
