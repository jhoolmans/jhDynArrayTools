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

#ifndef DA_PROJECTTOSURFACE_H
#define DA_PROJECTTOSURFACE_H

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
#include <maya/MFloatPoint.h>

#include <maya/MMatrix.h>

#include <maya/MFnArrayAttrsData.h>
#include <maya/MFnMesh.h>

#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>

#include "dynArrayUtils.h"



class DA_ProjectToSurface : MPxNode
{
public:
    DA_ProjectToSurface();
    virtual ~DA_ProjectToSurface();

    static void *creator();
    static MStatus initialize();

    virtual MStatus compute(const MPlug &plug, MDataBlock &data);
    MStatus validateArray(const MFnArrayAttrsData &array);

    static MTypeId id;

    // inputs
    static MObject aInDynamicArray;
    static MObject aInVector;
    static MObject aInSurface;

    // controls
    static MObject aUseNormals;

    // outputs
    static MObject aOutDynamicArray;
};

#endif /*DA_PROJECTTOSURFACE_H*/
