//
// Dynamic Array Toolset for Maya
//
// Copyright (C) 2012  Jeroen Hoolmans
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "dynArrayUtils.h"

MStatus dynArrayUtils::copyDynArray(MFnArrayAttrsData &fnInDynArray, MFnArrayAttrsData &fnDynArray)
{
    MStatus stat;

    //
    // COPY INPUT DATA
    //

    MStringArray inputArrayNames;
    MString inputArrayName;

    MFnArrayAttrsData::Type arrayType;

    inputArrayNames = fnInDynArray.list(&stat);
    CHECK_MSTATUS(stat);

    unsigned i;
    unsigned j;

    for (i = 0; i < inputArrayNames.length(); i++) {
        // GET ARRAY TYPE
        inputArrayName = inputArrayNames[i];
        fnInDynArray.checkArrayExist(inputArrayName, arrayType, &stat);
        CHECK_MSTATUS(stat);

        //
        // Copy vector array data
        //
        if (arrayType == MFnArrayAttrsData::kVectorArray) {
            MVectorArray vecArray = fnDynArray.vectorArray(inputArrayName, &stat);
            CHECK_MSTATUS(stat);

            stat = vecArray.copy( fnInDynArray.getVectorData(inputArrayName) );
            CHECK_MSTATUS(stat);
        }

        //
        // Copy double array data
        //
        if (arrayType == MFnArrayAttrsData::kDoubleArray) {
            MDoubleArray dblArray = fnDynArray.doubleArray(inputArrayName, &stat);
            CHECK_MSTATUS(stat);

            stat = dblArray.copy(fnInDynArray.getDoubleData(inputArrayName) );
            CHECK_MSTATUS(stat);
        }

        //
        // Copy string array data
        //
        if (arrayType == MFnArrayAttrsData::kStringArray) {
            MStringArray strArray = fnDynArray.stringArray(inputArrayName, &stat);
            CHECK_MSTATUS(stat);

            MStringArray inStrArray = fnInDynArray.getStringData(inputArrayName, &stat);
            CHECK_MSTATUS(stat);

            for (j = 0; j < inStrArray.length(); j++) {
                strArray.append(inStrArray[j]);
            }
        }

        //
        // Copy int array data
        //
        if (arrayType == MFnArrayAttrsData::kIntArray) {
            MIntArray intArray = fnDynArray.intArray(inputArrayName, &stat);
            CHECK_MSTATUS(stat);

            stat = intArray.copy(fnInDynArray.getIntData(inputArrayName) );
            CHECK_MSTATUS(stat);
        }
    }

    return stat;
}
