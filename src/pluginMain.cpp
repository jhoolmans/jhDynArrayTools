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


#include "da_IndexByRadius.h"
MTypeId DA_IndexByRadius::id(0x001178BF);

#include "da_ProjectToSurface.h"
MTypeId DA_ProjectToSurface::id(0x001178BE);


MStatus initializePlugin(MObject obj)
{
    MStatus stat;
    MFnPlugin plugin(obj, "Jeroen Hoolmans", "0.2", "Any", &stat);
    CHECK_MSTATUS(stat);

    // Index by Radius
    plugin.registerNode("daIndexByRadius",
                        DA_IndexByRadius::id,
                        DA_IndexByRadius::creator,
                        DA_IndexByRadius::initialize);

    return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj)
{
    MStatus stat;
    MFnPlugin plugin(obj);

    // Index by Radius
    plugin.deregisterNode(DA_IndexByRadius::id);

    return MS::kSuccess;
}
