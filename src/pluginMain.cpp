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

#include <maya/MFnPlugin.h>
#include <maya/MTypeId.h>

#include <maya/MGlobal.h>


#include "da_IndexByRadius.h"
MTypeId DA_IndexByRadius::id(0x001178BF);

#include "da_ProjectToSurface.h"
MTypeId DA_ProjectToSurface::id(0x001178BE);

#include "da_GridGenerator.h"
MTypeId DA_GridGenerator::id(0x001178BD);

#include "da_Randomizer.h"
MTypeId DA_Randomizer::id(0x001178BC);


MStatus initializePlugin(MObject obj)
{
    MStatus stat;
    MFnPlugin plugin(obj, "Jeroen Hoolmans", "0.3", "Any", &stat);
    CHECK_MSTATUS(stat);

    // Output GPL license
    MGlobal::displayInfo("");
    MGlobal::displayInfo("jhDynArrayTools Copyright (C) 2012 Jeroen Hoolmans");
    MGlobal::displayInfo("This program comes with ABSOLUTELY NO WARRANTY.");
    MGlobal::displayInfo("This is free software, and you are welcome to redistribute it");
    MGlobal::displayInfo("under certain conditions.");
    MGlobal::displayInfo("Visit http://jhoolmans.github.com/jhDynArrayTools for more info.");
    MGlobal::displayInfo("");
    //

    // Index by Radius
    plugin.registerNode("daIndexByRadius",
                        DA_IndexByRadius::id,
                        DA_IndexByRadius::creator,
                        DA_IndexByRadius::initialize);

    // Project To Surface
    plugin.registerNode("daProjectToSurface",
                        DA_ProjectToSurface::id,
                        DA_ProjectToSurface::creator,
                        DA_ProjectToSurface::initialize);

    // Grid Generator
    plugin.registerNode("daGridGenerator",
                        DA_GridGenerator::id,
                        DA_GridGenerator::creator,
                        DA_GridGenerator::initialize);

    // Randomizer
    plugin.registerNode("daRandomizer",
                        DA_Randomizer::id,
                        DA_Randomizer::creator,
                        DA_Randomizer::initialize);

    return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj)
{
    MStatus stat;
    MFnPlugin plugin(obj);

    // Index by Radius
    plugin.deregisterNode(DA_IndexByRadius::id);

    // Project To Surface
    plugin.deregisterNode(DA_ProjectToSurface::id);

    // Grid Generator
    plugin.deregisterNode(DA_GridGenerator::id);

    // Randomizer
    plugin.deregisterNode(DA_Randomizer::id);

    return MS::kSuccess;
}
