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


// Constructor
DA_ProjectToSurface::DA_ProjectToSurface(){}

// Destructor
DA_ProjectToSurface::~DA_ProjectToSurface(){}

// Attributes initialisation
MStatus DA_ProjectToSurface::initialize()
{
    MStatus stat;

    //
    // Inputs
    //


    //
    // Controls
    //


    //
    // Outputs
    //


    //
    // Attributes affects
    //

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
    return stat;
}

