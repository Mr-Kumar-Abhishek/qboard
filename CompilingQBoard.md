# Compiling QBoard #

QBoard uses Qt's qmake tool for its build process, the goal being to have a single build process which can, in theory, run on any system supported by Qt.

QBoard needs Qt version 4.3.x or 4.4.x, and you will need to have Qt's development files (headers/libs) in a suitable place on your system (where your compiler and linker can find them). It also requires some implementation of the C++ STL, but most C++ environments have that built in. It will not compile using "older" compilers (e.g. gcc 3.x or MSVC6), because it uses newer C++ features not provided by pre-standards compilers. gcc 4.1+ and newer MS compilers (2005+?) are believed to be OK.

# Unix systems #

To build QBoard, simply:

```
~> qmake
~> make
```

If you have a multi-processor or multi-core machine, try passing `-j2` to make, as this will speed up compilation by using two processors.

The application will compile to `bin/QT_VERSION/QBoard`. To install it, simply copy it to your favourite binaries directory (e.g. `~/bin` is good).

As of 20080906, the build creates a couple shared libraries which will need to be in your library path before running QBoard. You can try it out without installing it by doing:

```
me@host:qboard-VERSION> cd bin/QT_VERSION
me@host:qboard-VERSION> LD_LIBRARY_PATH=".:$LD_LIBRARY_PATH" ./QBoard
```

# Non-Unix systems #

Instructions for building it on non-Unix environments would be appreciated, if anyone gets it working.

## Mac ##
It "should" work as-is on OS/X, but to be honest i wouldn't touch a Mac with a 3 meter pole, so i don't know for sure if it works.

## Windows ##

The build tree "might" work on Windows platforms, but it's untested.

While the source is essentially platform-independent...

There are known problems when trying to link libs11n as a DLL on Windows. The libs will build, but loading s11n files won't work. (It's a long, sad story involving exportation of DLL symbols.) The only known workaround on Windows platforms is to link the s11n object files (from `s11n/*.cpp`) into the application directly, without using a DLL. If i can get access to a Windows machine with Cygwin (or similar) on it, i'll work on testing/fixing the build to accommodate this.

**Big tips:** if you try to build it on Windows, make sure you enable the "keep unreferenced data" option (it is off by default, AFAIK). It is critical for the deserialization classloader to function properly (so, e.g. pasting won't work without it). In MSVC this is `/OPT:NOREF`. Also make sure to turn OFF precompiled headers - they won't work with this template-heavy code.


# And now what? #

Now see [HOWTOGettingStarted](HOWTOGettingStarted.md).