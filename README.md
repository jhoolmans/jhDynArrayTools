Dynamic Array Tools
================

***

License
-------

See LICENSE file for information about licensing


Introduction
----------------

Dynamic Arrays are special arrays in Maya that you can use with the 'instancer' node to specify points, rotation, object indexes and more.
Usually they are used with particle emitters. These particles are plugged into the inputPoints of the instancer node. This toolset tries to help the user and manipulate these points. There are more nodes for generating points in a different matter. 
Basically you get generators and manipulators.

**Note: This is a toolset that is still under development**

***

Compiling Plugins
-----------------

This toolset uses CMake for generating a build environment needed to compile the plugins. (You Developers know what I am talking about)

##Dependency List

- [CMake 2.8+](http://www.cmake.org) (Used to generate the build files)
- [Boost](http://www.boost.org) 
- Maya Developers Kit, comes with every Maya install

Windows

- Visual Studio 2008+

Linux

- GCC 4.1.2 (Search the Maya help for more information)

OSX

- XCode 3.2+

I will explain a simple way for you to start compiling if you have never done so before (or simply need a reminder).

##GUI method

+ Open CMake-gui
+ Click 'Browse Source' and go to the folder containing this readme file
+ Click 'Browse Build' and create a 'build' folder inside the source folder
+ Click 'Configure' at the bottom and wait until it is done
+ Select your build environment
	+ For Windows choose Visual Studio
	+ For Linux choose GNU Makefiles
	+ For OSX choose XCode
+ Once it has finished configuring without any issues, click 'Generate'
+ Done, your build environment is ready for action

This process will set up your files that compile the source code. From this point forward it becomes software specific. 

##Console method (OSX and Linux only)

+ cd to the source directory containing this readme file.
+ run the following code:
	
	mkdir build
	cmake ..
	make
	
+ You can skip the next section as you are done compiling from this point :)

***

**Visual Studio**

You probably chose Visual Studio on a Windows machine.

+ Open the .sln file located in the 'build' folder.
+ Run the build by pressing F7 or go to Build > Build Solution

Once everything runs as it should, there is a .mll waiting for you in either the build/Release or build/Debug folder. This is all you need.

See Install for more details.

**GNU Makefiles**

On linux you have to compile using the terminal, which you are most likely familiar with if you run a linux machine.

+ Go to the 'build' folder. ($ cd /path/to/build/directory)
+ Type *make*

Once everything runs as it should, there is a .so waiting for you in the build folder. This is all you need.

See Install for more details.

**XCode**

On an OSX system you should choose XCode.

+ Open the .xcodeproj file located in the 'build' folder.
+ Press Command+B or go to Product > Build.


Once everything runs as it should, there is a .bundle waiting for you. This is all you need.

See Install for more details.

***

Install
------------------

##Installing Scripts

Copy the contents of the 'scripts' folder into:

Windows

    C:/Users/username/My Documents/maya/version/scripts

Linux

    /home/username/maya/version/scripts

OSX

    /Users/Shared/Autodesk/Maya/version/scripts


##Installing Plugins

Copy the compiled plugin from the build folder into:

Windows

    C:/Program Files/Autodesk/Maya/bin/plugins

Linux

    /usr/autodesk/maya/bin/plugins

OSX

    /Users/Shared/Autodesk/Maya/version/plugins

***

FAQ
---

No questions so far.


Contact
-------

For any questions regarding this toolset, feel free to contact me at [jhoolmans at gmail dot com](mailto:jhoolmans@gmail.com?subject=DynArrayTools)

Any bugs, requests or issues can be reported on [GitHub](https://github.com/jhoolmans/Maya_DynArrayTools/issues).