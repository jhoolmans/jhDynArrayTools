#
# Dynamic Array Toolset for Maya
#
# Copyright (C) 2012  Jeroen Hoolmans
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/vfxcmake/cmake/")

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(dynArrayTools)

FIND_PACKAGE( Maya REQUIRED )
FIND_PACKAGE( Boost REQUIRED )

SET( dynArrayTools_SRCS
	src/da_ProjectToSurface.cpp
	src/da_IndexByRadius.cpp
	src/dynArrayUtils.cpp
	src/pluginMain.cpp
)

SET( dynArrayTools_H
	src/da_ProjectToSurface.h
	src/da_IndexByRadius.h
	src/dynArrayUtils.h
)

INCLUDE_DIRECTORIES(
	${PUBLIC_INCLUDE_DIRS}
	${dynArrayTools_SOURCE_DIR}/src
	${MAYA_INCLUDE_DIR}
)


# create the plugin
ADD_LIBRARY( dynArrayTools_plugin SHARED
  ${dynArrayTools_SRCS}
  ${dynArrayTools_H}
)

TARGET_LINK_LIBRARIES( dynArrayTools_plugin
   ${MAYA_Foundation_LIBRARY}
   ${MAYA_OpenMaya_LIBRARY}
)

SET_TARGET_PROPERTIES( dynArrayTools_plugin PROPERTIES
  OUTPUT_NAME dynArrayTools
  CLEAN_DIRECT_OUTPUT 1
)

# this is a macro defined in FindMaya that sets up our plugin with standard Maya build settings
MAYA_SET_PLUGIN_PROPERTIES( dynArrayTools_plugin )
