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

#include "da_ProjectToSurface.h"

//
// Static Attributes
//
MObject DA_ProjectToSurface::aInDynamicArray;
MObject DA_ProjectToSurface::aInSurface;
MObject DA_ProjectToSurface::aInVector;
MObject DA_ProjectToSurface::aUseNormals;
MObject DA_ProjectToSurface::aOutDynamicArray;


// Constructor
DA_ProjectToSurface::DA_ProjectToSurface(){}

// Destructor
DA_ProjectToSurface::~DA_ProjectToSurface(){}

// Attributes initialisation
MStatus DA_ProjectToSurface::initialize()
{
    MStatus stat;
    MFnTypedAttribute tAttr;
    MFnNumericAttribute nAttr;

    //
    // Inputs
    //
    aInDynamicArray = tAttr.create("inDynamicArray", "ida", MFnData::kDynArrayAttrs);
    stat = addAttribute(aInDynamicArray);
    CHECK_MSTATUS(stat);

    // Limit to be mesh for now
    aInSurface = tAttr.create("inSurface", "isrf", MFnData::kMesh);
    tAttr.setStorable(false);
    tAttr.setCached(false);
    stat = addAttribute(aInSurface);
    CHECK_MSTATUS(stat);

    aInVector = nAttr.createPoint("inVector", "ivec");
    nAttr.setDefault(0.0, 1.0, 0.0);
    stat = addAttribute(aInVector);
    CHECK_MSTATUS(stat);

    //
    // Controls
    //
    aUseNormals = nAttr.create("useNormals", "nrm", MFnNumericData::kBoolean);
    stat = addAttribute(aUseNormals);
    CHECK_MSTATUS(stat);

    //
    // Outputs
    //
    aOutDynamicArray = tAttr.create("outDynamicArray", "oda", MFnData::kDynArrayAttrs);
    tAttr.setWritable(false);
    stat = addAttribute(aOutDynamicArray);
    CHECK_MSTATUS(stat);

    //
    // Attributes affects
    //
    attributeAffects(aInDynamicArray, aOutDynamicArray);
    attributeAffects(aInSurface, aOutDynamicArray);
    attributeAffects(aInVector, aOutDynamicArray);
    attributeAffects(aUseNormals, aOutDynamicArray);

    return stat;
}

// Creator
void * DA_ProjectToSurface::creator()
{
    return new DA_ProjectToSurface;
}

// Compute
MStatus DA_ProjectToSurface::compute(const MPlug &plug, MDataBlock &data)
{
    MStatus stat;
    if (plug != aOutDynamicArray)
        return MS::kFailure;

    //
    // Get inputs
    //

    //
    // Dynamic Array
    //
    MDataHandle inDynamicArrayData = data.inputValue(aInDynamicArray);
    if(inDynamicArrayData.type() != MFnData::kDynArrayAttrs)
        return MS::kFailure;

    MFnArrayAttrsData inDynamicArray(inDynamicArrayData.data());

    // Create output based on input
    MFnArrayAttrsData outDynamicArray;
    outDynamicArray.create();

    // Copy data to new array
    dynArrayUtils::copyDynArray(inDynamicArray, outDynamicArray);

    //
    // Surface
    //
    MDataHandle inSurfaceData = data.inputValue(aInSurface);
    if(inSurfaceData.type() != MFnData::kMesh) {
        // Passthrough
        MDataHandle outDynamicArrayHandle = data.outputValue(aOutDynamicArray);
        outDynamicArrayHandle.set(outDynamicArray.object());
        data.setClean(aOutDynamicArray);
        return MS::kSuccess;
    }

    MObject inSurfaceMesh = inSurfaceData.asMesh();
    MFnMesh fnMesh(inSurfaceMesh);

    // Validate array
    if(validateArray(inDynamicArray) == MS::kFailure)
        return MS::kFailure;

    // Input vector
    MFloatVector inVector = data.inputValue(aInVector).asFloatVector();

    // TODO: Normals or Vector switch
    //

    // Note, This is a direct pointer
    MVectorArray outPointArray = outDynamicArray.vectorArray("position");

    // Intersection stuff
    MFloatPoint raySource;
    MFloatPoint hitPoint;

    for(int i = 0; i < outPointArray.length(); i++)
    {
        raySource = MFloatPoint(outPointArray[i].x,
                                outPointArray[i].y,
                                outPointArray[i].z);

        bool hit = fnMesh.closestIntersection(
                    raySource,
                    inVector,
                    NULL,
                    NULL,
                    false,
                    MSpace::kWorld,
                    1000,
                    false,
                    NULL,
                    hitPoint,
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL);

        if (hit)
        {
            outPointArray[i].x = hitPoint.x;
            outPointArray[i].y = hitPoint.y;
            outPointArray[i].z = hitPoint.z;
        }
    }

    // Set output data
    MDataHandle outDynamicArrayHandle = data.outputValue(aOutDynamicArray);
    outDynamicArrayHandle.set(outDynamicArray.object());

    // Set clean
    data.setClean(aOutDynamicArray);

    return stat;
}


// Validate if array matches our requirements
MStatus DA_ProjectToSurface::validateArray(MFnArrayAttrsData& array)
{
    // Should have position of type vectorArray
    MStatus stat;
    MFnArrayAttrsData::Type arrayType;
    if(array.checkArrayExist(MString("position"), arrayType))
        if (arrayType == MFnArrayAttrsData::kVectorArray)
            return MS::kSuccess;
    return MS::kFailure;
}

