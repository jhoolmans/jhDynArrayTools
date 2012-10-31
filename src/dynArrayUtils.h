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

#ifndef DYNARRAYUTILS_H
#define DYNARRAYUTILS_H

#include <maya/MFnArrayAttrsData.h>
#include <maya/MStringArray.h>
#include <maya/MString.h>
#include <maya/MVectorArray.h>
#include <maya/MVector.h>
#include <maya/MDoubleArray.h>
#include <maya/MIntArray.h>

namespace dynArrayUtils
{
    MStatus copyDynArray(MFnArrayAttrsData &fnInDynArray, MFnArrayAttrsData &fnDynArray);
}

#endif /*DYNARRAYUTILS_H*/
