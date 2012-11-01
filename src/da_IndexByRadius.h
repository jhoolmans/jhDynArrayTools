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

#ifndef DA_INDEXBYRADIUS_H
#define DA_INDEXBYRADIUS_H

#include <maya/MPxNode.h>
#include <maya/MTypeId.h>
#include <maya/MGlobal.h>

#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MPlug.h>

#include <maya/MVectorArray.h>
#include <maya/MFnVectorArrayData.h>

#include <maya/MPointArray.h>
#include <maya/MPoint.h>

#include <maya/MFnDoubleArrayData.h>
#include <maya/MDoubleArray.h>

#include <maya/MMatrix.h>

#include <maya/MFnArrayAttrsData.h>

#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnMatrixAttribute.h>
#include <maya/MFnCompoundAttribute.h>

#include "dynArrayUtils.h"



class DA_IndexByRadius : MPxNode
{
public:
    DA_IndexByRadius();
    virtual ~DA_IndexByRadius();

    static void *creator();
    static MStatus initialize();

    virtual MStatus compute(const MPlug &plug, MDataBlock &data);

    static MTypeId id;

    // inputs
    static MObject aInPointArray;
    static MObject aInDynamicArray;
    static MObject aInMatrix;

    // controls
    static MObject aRadius;
    static MObject aIndexMin;
    static MObject aIndexMax;
    static MObject aIndex;

    // outputs
    static MObject aOutIndexPP;
    static MObject aOutDynamicArray;
};

#endif /*DYNARRAYINDEXBYRADIUS_H*/
