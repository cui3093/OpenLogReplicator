/* Header for OracleLob class
   Copyright (C) 2018-2022 Adam Leszczynski (aleszczynski@bersler.com)

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

#include <vector>

#include "types.h"

#ifndef ORACLE_LOB_H_
#define ORACLE_LOB_H_

namespace OpenLogReplicator {
    class OracleTable;

    class OracleLob {
    public:
        OracleTable* table;
        typeObj obj;
        typeDataObj dataObj;
        typeObj lObj;
        typeCol col;
        typeCol intCol;
        std::vector<typeDataObj> lobIndexes;

        OracleLob(OracleTable* table, typeObj newObj, typeObj newDataObj, typeObj newLObj, typeCol newCol, typeCol newIntCol);
        virtual ~OracleLob();

        void addIndex(typeDataObj newDataObj);

        friend std::ostream& operator<<(std::ostream& os, const OracleLob& column);
    };
}

#endif
