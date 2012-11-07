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

#include "DA_Randomizer.h"

//
// Static Attributes
//
// input
MObject DA_Randomizer::aInDynamicArray;
// randomize
MObject DA_Randomizer::aSeed;
// objectIndex
MObject DA_Randomizer::aUseObjectIndex;
MObject DA_Randomizer::aObjectIndexMin;
MObject DA_Randomizer::aObjectIndexMax;
// position
MObject DA_Randomizer::aUsePosition;
MObject DA_Randomizer::aPositionMin;
MObject DA_Randomizer::aPositionMax;
MObject DA_Randomizer::aPositionRelative;
// rotation
MObject DA_Randomizer::aUseRotation;
MObject DA_Randomizer::aRotationMin;
MObject DA_Randomizer::aRotationMax;
MObject DA_Randomizer::aRotationRelative;
// scale
MObject DA_Randomizer::aUseScale;
MObject DA_Randomizer::aScaleMin;
MObject DA_Randomizer::aScaleMax;
MObject DA_Randomizer::aScaleRelative;
// output
MObject DA_Randomizer::aOutDynamicArray;

//
// Methods
//

// Constructor
DA_Randomizer::DA_Randomizer(){}

// Destructor
DA_Randomizer::~DA_Randomizer(){}

// Attributes initialisation
MStatus DA_Randomizer::initialize()
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
    return stat;
}

// Creator
void * DA_Randomizer::creator()
{
    return new DA_Randomizer;
}

// Compute
MStatus DA_Randomizer::compute(const MPlug &plug, MDataBlock &data)
{
    MStatus stat;
    if (plug != aOutDynamicArray)
        return MS::kFailure;

    return stat;
}


// Validate if array matches our requirements
MStatus DA_Randomizer::validateArray(MFnArrayAttrsData& array)
{
    // Should have position of type vectorArray
    MStatus stat;
    MFnArrayAttrsData::Type arrayType;
    if(array.checkArrayExist(MString("position"), arrayType))
        if (arrayType == MFnArrayAttrsData::kVectorArray)
            return MS::kSuccess;
    return MS::kFailure;
}



MStatus DA_Randomizer::randomizePosition(MFnArrayAttrsData &inArray)
{
    MStatus stat;

    return stat;
}


MStatus DA_Randomizer::randomizeRotation(MFnArrayAttrsData &inArray)
{
    MStatus stat;

    return stat;
}


MStatus DA_Randomizer::randomizeScale(MFnArrayAttrsData &inArray)
{
    MStatus stat;

    return stat;
}


MStatus DA_Randomizer::randomizeObjectIndex(MFnArrayAttrsData &inArray)
{
    MStatus stat;

    return stat;
}
