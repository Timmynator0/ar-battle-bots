This is OpenCV 2.3.0 binary package.

Please, see http://opencv.willowgarage.com for details.
In particular, common OpenCV installation instructions can be found at
http://opencv.willowgarage.com/wiki/InstallGuide

Directory structure of the package:

   opencv - the complete source tree, 2.3.0 snapshot of
            https://code.ros.org/svn/opencv/branches/2.3/opencv

   build  - pre-build libraries for VS2008, VS2010 and MinGW users

       bin - statically linked binaries that can be used with any compiler or
             even without any compiler.
             opencv_ffmpeg[_64].dll are the ffmpeg codecs. put the DLLs
             to the system path in order to make OpenCV use FFMPEG.

       include - OpenCV headers put together

       Python - statically linked OpenCV modules for 32-bit Python 2.6 or 2.7.
                copy the packages into your Python installation directory.

       x86/x64 - DLLs, import libs and static libs for 32-bit and 64-bit compilers, respectively.

          vc9/vc10/mingw - the binaries for VS2008, VS2010 or MinGW, respectively.

              bin - OpenCV DLLs + TBB (if needed)
              lib - import libs
              staticlib - static libs

Notes:

1) Add build\bin and one of build\{x86|x64}\{vc9\vc10\mingw}\bin to your system path (to use DLLs)
   Add build\{x86|x64}\{vc9\vc10\mingw}\lib or
       build\{x86|x64}\{vc9\vc10\mingw}\staticlib as library directories to your linker settings,
   Add build\include and build\include\opencv as include directories to your compiler settings.

2) DLLs for VS2008 and VS2010 have been built with TBB support.

3) Binaries for VS2005 are not included, but this version of OpenCV is known to build with VS2005.

4) For MinGW users the package only includes release builds of dynamic libs without TBB support.
  That is, there are no static libs, no debug libraries, no TBB support.
  32-bit DLLs have been built using official MinGW 4.5.2 (with dwarf2 exception handling mechanism)
  64-bit DLLs have been built using TDM MinGW 4.5.2 (with sjlj exception handling mechanism)
  If you need some other configuration or use different incompatible MinGW version,
  you can rebuild OpenCV from source code.

5) For the sake of package compactness, debug information is stripped from the binaries and
  PDB files are not supplied.

6) Python modules have been built statically, for 32-bit Python and without TBB support.
  That is, no additional compilers or DLLs are needed to use the modules -
  just install Python and NumPy. Python 3.x is not supported yet.

7) GPU-accelerated modules are not included. Download the GPU pack separately from SourceForge site
   and copy it on top of this unpacked archive.
