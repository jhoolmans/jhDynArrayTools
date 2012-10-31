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

#include "da_IndexByRadius.h"

//
// Static Attributes
//

MObject DA_IndexByRadius::aInPointArray;
MObject DA_IndexByRadius::aInDynamicArray;
MObject DA_IndexByRadius::aInMatrix;
MObject DA_IndexByRadius::aRadius;
MObject DA_IndexByRadius::aIndexMin;
MObject DA_IndexByRadius::aIndexMax;
MObject DA_IndexByRadius::aIndex;
MObject DA_IndexByRadius::aOutIndexPP;
MObject DA_IndexByRadius::aOutDynamicArray;


// Constructor
DA_IndexByRadius::DA_IndexByRadius(){}

// Destructor
DA_IndexByRadius::~DA_IndexByRadius(){}

// Attributes initialisation
MStatus DA_IndexByRadius::initialize()
{
    MStatus stat;
    MFnTypedAttribute tAttr;
    MFnMatrixAttribute mAttr;
    MFnNumericAttribute nAttr;
    MFnCompoundAttribute cAttr;

    //
    // Inputs
    //
    //aInPointArray = tAttr.create("inPointArray", "ipa", MFnData::kPointArray);
    //stat = addAttribute(aInPointArray);
    //CHECK_MSTATUS(stat);

    aInDynamicArray = tAttr.create("inDynamicArray", "ida", MFnData::kDynArrayAttrs);
    stat = addAttribute(aInDynamicArray);
    CHECK_MSTATUS(stat);

    aInMatrix = mAttr.create("inMatrix", "imat");
    stat = addAttribute(aInMatrix);
    CHECK_MSTATUS(stat);

    //
    // Controls
    //
    aRadius = nAttr.create("radius", "rad", MFnNumericData::kDouble, 1.0);
    nAttr.setMin(0);
    stat = addAttribute(aRadius);
    CHECK_MSTATUS(stat);

    aIndexMin = nAttr.create("indexMin", "imin", MFnNumericData::kInt, 0);
    nAttr.setMin(0);
    nAttr.setMax(100);

    aIndexMax = nAttr.create("indexMax", "imax", MFnNumericData::kInt, 1);
    nAttr.setMin(0);
    nAttr.setMax(100);

    aIndex = cAttr.create("Index", "idx");
    cAttr.addChild(aIndexMin);
    cAttr.addChild(aIndexMax);

    stat = addAttribute(aIndex);
    CHECK_MSTATUS(stat);

    //
    // Outputs
    //
    aOutDynamicArray = tAttr.create("outDynamicArray", "oda", MFnData::kDynArrayAttrs);
    tAttr.setReadable(true);
    tAttr.setWritable(false);
    stat = addAttribute(aOutDynamicArray);
    CHECK_MSTATUS(stat);

    aOutIndexPP = tAttr.create("outIndexPP", "oipp", MFnData::kDoubleArray);
    tAttr.setReadable(true);
    tAttr.setWritable(false);
    stat = addAttribute(aOutIndexPP);
    CHECK_MSTATUS(stat);


    //
    // Attributes affects
    //
    //attributeAffects(aInPointArray, aOutDynamicArray);
    attributeAffects(aInDynamicArray, aOutDynamicArray);
    attributeAffects(aInMatrix, aOutDynamicArray);
    attributeAffects(aRadius, aOutDynamicArray);
    attributeAffects(aIndexMin, aOutDynamicArray);
    attributeAffects(aIndexMax, aOutDynamicArray);

    attributeAffects(aInPointArray, aOutIndexPP);
    attributeAffects(aInDynamicArray, aOutIndexPP);
    attributeAffects(aInMatrix, aOutIndexPP);
    attributeAffects(aRadius, aOutIndexPP);
    attributeAffects(aIndexMin, aOutIndexPP);
    attributeAffects(aIndexMax, aOutIndexPP);
    
    return stat;
}

void * DA_IndexByRadius::creator()
{
    return new DA_IndexByRadius;
}


MStatus DA_IndexByRadius::compute(const MPlug &plug, MDataBlock &data)
{
    if( (plug != aOutDynamicArray) && (plug != aOutIndexPP))
        return MS::kFailure;

    MStatus stat;

    //
    // Get inputs
    //
    MObject inDynArray = data.inputValue(aInDynamicArray).data();
    if(inDynArray.isNull())
        return MS::kFailure;
    MFnArrayAttrsData inArray;
    inArray.setObject(inDynArray);

    MMatrix inMatrix = data.inputValue(aInMatrix).asMatrix();
    double dRadius = data.inputValue(aRadius).asDouble();
    int iIndexMin = data.inputValue(aIndexMin).asInt();
    int iIndexMax = data.inputValue(aIndexMax).asInt();

    //
    // Outputs
    //
    MDoubleArray outIndexPP;
    MFnArrayAttrsData outArray;
    outArray.create(&stat);
    CHECK_MSTATUS(stat);

    // Copy input array to output
    dynArrayUtils::copyDynArray(inArray, outArray);

    // Check if input has Position data
    MFnArrayAttrsData::Type arrayType;
    bool hasPos = outArray.checkArrayExist("position", arrayType, &stat);
    CHECK_MSTATUS(stat);

    if ( (hasPos == false) || (arrayType != MFnArrayAttrsData::kVectorArray) ) {
        MGlobal::displayWarning("Input array is missing position data");
    } else {
        MPoint origin(0,0,0);
        origin *= inMatrix;

        // loop through vectors
        MPoint pt;

        // set data and set length to match position
        MVectorArray inPositionArray = outArray.getVectorData("position");
        outIndexPP.setLength(inPositionArray.length());

        for(int i = 0; i < inPositionArray.length(); i++)
        {
            pt.x = inPositionArray[i].x;
            pt.y = inPositionArray[i].y;
            pt.z = inPositionArray[i].z;

            double dist = pt.distanceTo(origin);
            double index = double(iIndexMin) + (dist / dRadius * double(iIndexMax - iIndexMin));

            if(index > (double)iIndexMax)
                index = (double)iIndexMax;

            outIndexPP[i] = index;
        }

        MDoubleArray dblArray = outArray.doubleArray("objectIndex");
        dblArray.copy(outIndexPP);
    }

    MDataHandle dataOutArray = data.outputValue(aOutDynamicArray);
    dataOutArray.set(outArray.object());

    //MDataHandle dataIndexPP = data.outputValue(aOutIndexPP);

    data.setClean(aOutDynamicArray);
    data.setClean(aOutIndexPP);

    return MS::kSuccess;
}

