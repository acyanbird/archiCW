# Advanced Computer Architecture - Conjugate Gradient Solver (ACA CGS)
## Description
This is a simple conjugate gradient benchmark code for a 3D mesh. The mesh will run for a set amount of iterations, or until the residual falls before a given threshold.

## Dependencies
The application has two optional dependencies, [Silo](https://wci.llnl.gov/simulation/computer-codes/silo) and [VisIt](https://visit-dav.github.io/visit-website/). These allow for visualisations of the conjugate gradient. If you are using the DCS system, these have been installed for you.

### Silo
Silo is a library for reading and writing data in a binary format, that can be read by VisIt amongst other programs, across larger cluster systems. It is widely utilised in the HPC community due to it's versatility and ease of implementation. Whilst this is often utilised alongside [HDF5](https://www.hdfgroup.org/solutions/hdf5/), it is not required for this application.

To build and install Silo, unzip the package from the website linked above and build through the commands listed in the INSTALL file. For Windows and Mac OSX users, it is recommended they use the BSD Open Source version. Windows users can use the specialised windows script provided, whereas Mac OSX will have to use the terminal and manually build it.

If you are using your own machine, once you have installed SILO, you will need to alter the Makefile to reflect the new path of SILO. To do this, change the path given to SILO_DIR.

Versions tested with: 
  * 4.10.2-bsd
  * 4.11


### VisIt
Visit is a visualisation software (surprise!) that is widely utilised to read a huge collection of file types, including Silo. It has been designed to work over large cluster systems, where multiple files exist for each iteration step, and there are large amount of iterations per simulation.

VisIt has been pre-compiled for multiple OS', including [Windows (exe)](https://github.com/visit-dav/visit/releases/download/v3.2.0/visit3.2.0_x64.exe) and [Mac OSX (dmg)](https://github.com/visit-dav/visit/releases/download/v3.2.0/visit3.2.0.darwin-x86_64-10_14.dmg). There are also custom tgz files for different flavours of Linux. Alternatively, if you want to go hardcore, you can clone the git repository and build it yourself [(git repo)](https://github.com/visit-dav/visit). Just make sure you build it with Silo support!

Version tested with:
  * 3.2.0 Release
  * 3.2.1 (CentOS 8 Release)

## Compiling the code
In order to compile the code, a Makefile has been provided. This Makefile defines how the program should be compiled, where it should be managed, and to enable/disable options. The key ones that you may want to change are shown bellow. `CC` is the C compiler, and `CPPFLAGS` is the flags that will be applied when compiling C files, alongside when the object files are linked. You should not need to edit any other option.
```makefile
CC = gcc
CPPFLAGS = -O0 -Wall -Wextra -Werror
```

Before building the program, it is recommended that you always clean any object files. These can cause confusion if you try and build multiple times. 
```shell
#Clean up all .o and compiled programs
make clean
```

To build the program, all you need to do is to is run the following command. You should also make sure you load in the GCC 9 compiler module (gcc9), as well as the SILO (cs257-silo) and VisIt (cs257-visit) modules if you plan on using those, if you haven't already.
```shell
#Load compilers
module load gcc9

#Load these if you need them
module load cs257-silo
module load cs257-visit

#Build program
make
```

If you want to print out text for each iteration, you can use the following command.
```shell
#Build program with verbose mode turned on
make VERBOSE=1
```

If you want to have a look at the visualisation, you will need to enable Silo. This can be done with the following command. Note: if you are not using a DCS system, you will need to edit the `SILO_DIR` parameter to point to your version of Silo.
```shell
#Build program with SILO outputs turned on
make SILO=1
```

You can also enable multiple options, as can be seen in the following example.
```shell
#build program with both verbose and SILO outputs turned on
make VERBOSE=1 SILO=1
```

## Running the code
Running the code is relatively easy. The Makefile will produce an executable, `acacgs`. This takes 3 parameters, a x dimension (`nx`), a y dimension (`ny`) and a z dimension (`nz`). As such, you can get creative and set your own sizes!
```shell
#./acacgs nx ny nz
./acacgs 10 10 10
```

If you are using Silo on the DCS system, it is **highly recommended that you don't use a mesh size larger than $25^3$**.
Approximate Silo directory sizes produced per mesh:
 - $10^3$ mesh => 4MB
 - $25^3$ mesh => 39MB
 - $50^3$ mesh => 301MB
 - $100^3$ mesh => 2.4GB
 - $200^3$ mesh => 19.3GB (!)

check