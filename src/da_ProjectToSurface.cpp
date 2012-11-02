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

    aInVector = nAttr.createPoint("inVector", "ivec");
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


    return stat;
}


// Validate if array matches our requirements
MStatus DA_ProjectToSurface::validateArray(const MFnArrayAttrsData& array)
{
    MStatus stat;

    return stat;
}

