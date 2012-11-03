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

#include "da_GridGenerator.h"

namespace DA_GridGeneratorPatterns
{
const MString NONE("Grid");
const MString BRICK_U("Brick U");
const MString BRICK_V("Brick V");
}

//
// Static Attributes
//

MObject DA_GridGenerator::aWidth;
MObject DA_GridGenerator::aHeight;
MObject DA_GridGenerator::aResolutionX;
MObject DA_GridGenerator::aResolutionY;
MObject DA_GridGenerator::aResolution;
MObject DA_GridGenerator::aPattern;

MObject DA_GridGenerator::aOutDynamicArray;


// Constructor
DA_GridGenerator::DA_GridGenerator(){}

// Destructor
DA_GridGenerator::~DA_GridGenerator(){}

// Attributes initialisation
MStatus DA_GridGenerator::initialize()
{
    MStatus stat;
    MFnCompoundAttribute cAttr;
    MFnNumericAttribute nAttr;
    MFnEnumAttribute eAttr;
    MFnTypedAttribute tAttr;

    //
    // Controls
    //
    aWidth = nAttr.create("width", "w", MFnNumericData::kDouble, 1.0);
    stat = addAttribute(aWidth);
    CHECK_MSTATUS(stat);

    aHeight = nAttr.create("height", "h", MFnNumericData::kDouble, 1.0);
    stat = addAttribute(aHeight);
    CHECK_MSTATUS(stat);

    aResolutionX = nAttr.create("resolutionX", "resx", MFnNumericData::kInt, 10);
    aResolutionY = nAttr.create("resolutionY", "resy", MFnNumericData::kInt, 10);
    aResolution = cAttr.create("resolution", "res");

    stat = cAttr.addChild(aResolutionX);
    CHECK_MSTATUS(stat);
    stat = cAttr.addChild(aResolutionY);
    CHECK_MSTATUS(stat);
    stat = addAttribute(aResolution);
    CHECK_MSTATUS(stat);


    aPattern = eAttr.create("pattern","pat",0);
    eAttr.addField(DA_GridGeneratorPatterns::NONE, 0);
    eAttr.addField(DA_GridGeneratorPatterns::BRICK_U, 1);
    eAttr.addField(DA_GridGeneratorPatterns::BRICK_V, 2);

    stat = addAttribute(aPattern);
    CHECK_MSTATUS(stat);

    //
    // Outputs
    //

    aOutDynamicArray = tAttr.create("outDynamicArray", "oda", MFnData::kDynArrayAttrs);
    tAttr.setWritable(false); // Just output
    stat = addAttribute(aOutDynamicArray);
    CHECK_MSTATUS(stat);

    //
    // Attributes affects
    //

    attributeAffects(aWidth, aOutDynamicArray);
    attributeAffects(aHeight, aOutDynamicArray);

    attributeAffects(aResolutionX, aOutDynamicArray);
    attributeAffects(aResolutionY, aOutDynamicArray);

    attributeAffects(aPattern, aOutDynamicArray);

    // Done
    return stat;
}

void * DA_GridGenerator::creator()
{
    return new DA_GridGenerator;
}


MStatus DA_GridGenerator::compute(const MPlug &plug, MDataBlock &data)
{
    MStatus stat;
    if (plug != aOutDynamicArray)
        return MS::kFailure;

    //
    // Control Inputs
    //
    double dWidth = data.inputValue(aWidth).asDouble();
    double dHeight = data.inputValue(aHeight).asDouble();

    int iResolutionX = data.inputValue(aResolutionX).asInt();
    int iResolutionY = data.inputValue(aResolutionY).asInt();

    short ePattern = data.inputValue(aPattern).asShort();

    // Create output
    MFnArrayAttrsData fnOutDynamicArray;
    fnOutDynamicArray.create();

    // Create position data
    MVectorArray outPositionPP = fnOutDynamicArray.vectorArray("position");

    //
    // Create grid
    //
    double xOffset = dWidth / (double)iResolutionX;
    double yOffset = dHeight / (double)iResolutionY;

    for(int i = 0; i < iResolutionX; i++)
    {
        for(int j = 0; j < iResolutionY; j++)
        {
            outPositionPP.append( MVector(xOffset * i, 0.0, yOffset * j) );
        }
    }


    //
    // Set output data
    //
    MDataHandle outArray = data.outputValue(aOutDynamicArray);
    outArray.set(fnOutDynamicArray.object());

    // Set plug to clean
    data.setClean(aOutDynamicArray);

    // Done
    return MS::kSuccess;
}
