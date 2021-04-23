### MIT LL Simulink Interface for DAIDALUS

This folder contains the necessary software to create a [Matlab S-function](https://www.mathworks.com/help/simulink/sfg/what-is-an-s-function.html) for NASA's DAIDALUS v2.0.1c to interface with DEGAS.

To use DAIDALUS in DEGAS, you will need to first clone NASA's [DAIDALUS v2.0.1](https://github.com/nasa/daidalus/tree/DAIDALUSv2.0.1c) repository. Ensure that the path to the cloned repository does not contain any whitespaces. After cloning, follow the "Building DAIDALUS" instructions approriate for your operating system.

### Building DAIDALUS in Windows (with Visual Studio 2015)

1. Open Visual Studio 2015, click file -> New Project
    * Select *Visual C++* from templates
    * Under *Visual C++* select *Win32*, and then select *Win32 Project*.
    *. Choose an appropriate name for the project (e.g. daidalus) and the select a location to save the project.
    * Click *OK* The application wizard will then open.
        * Click *Next*
        * Select *Static Library*
        * Check off *Empty Project* (If this option is not available, select DLL, check the box, and then re-select static library)
        * De-select *Precompiled Header*
        * Click *Finish* to create the project

2. Ensure that *Solution Configuration* is set to release (by default it is set to debug)

3. Set the solution platform to *x64* (by default it is set to *x86*)

4. Add all DAIDALUS header files (*.h) and source files to the similarly named folders in Visual Studio solution explorer.
    * Go to *Projects* -> *Properties* -> *C/C++* -> *General*
    * Under *Additional Include Directories* add the path to the header files in the project folder

5. Click *Build* and then select *Build Solution*

6. The .lib file can be found in x64/Release

7. Move the .lib file to the directory pointed at by *make_daidalus_sfunc.m*, or amend the path to the file

### Building DAIDALUS in Linux

1. Open NASA's provided Makefile, which can be found in the C++ folder

2. Add -fPIC to the list of CXXFLAGS in the Makefile

3. Run the command *make lib* to build the library

4. The .a file can be found in C++/lib

5. Move the .a file to the directory pointed at by *make_daidalus_sfunc.m*, or amend the path to the file

### Creating the S-Function

1. Run make_daidalus_sfunc.m to generate the mex file. This script must be run from the SimulinkInterface folder. If running in Windows, a .mexw64 file will be generated. If running in Linux, a .mexa64 file will be generated. 

### Using with DEGAS

Before using DAIDALUS with DEGAS, ensure that the SimulinkInterface folder is on your Matlab path.
Directions on how to do this can be found in the *Quick Start* section of the DEGAS README located in the DEGAS folder.

### DAIDALUS 1.0.1 vs. 2.0.1

DAIDALUS v2 added additional vertical speed/vertical speed band pairs. The Pilot Model used by DEGAS only uses a subset of both the horizontal and vertical bands: -135 to 135 degrees for horizontal and -1500 to 1000 ft for vertical.

## Distribution Statement

DISTRIBUTION STATEMENT A. Approved for public release. Distribution is unlimited.

This material is based upon work supported by the National Aeronautics and Space Administration under Air Force Contract No. FA8702-15-D-0001. Any opinions, findings, conclusions or recommendations expressed in this material are those of the author(s) and do
 not necessarily reflect the views of the National Aeronautics and Space Administration.

© 2015 - 2020 Massachusetts Institute of Technology.

Delivered to the U.S. Government with Unlimited Rights, as defined in DFARS Part 252.227-7013 or 7014 (Feb 2014). Notwithstanding any copyright notice, U.S. Government rights in this work are defined by DFARS 252.227-7013 or DFARS 252.227-7014 as detailed above.
 Use of this work other than as specifically authorized by the U.S. Government may violate any copyrights that exist in this work.
