### INKchain Transaction Sign SDK For C++

This SDK provided offline transaction signature, generate address and public key, export public key from private key interface.

## Building from source

### Get the source code

Git and GitHub are used to maintain the source code. Clone the repository by:

```shell
git clone https://github.com/inklabsfoundation/inkerface-cpp-client.git
cd inkerface-cpp-client
```

### Install CMake

CMake is used to control the build configuration of the project. Quite recent 
version of CMake is required 
(at the time of writing [3.4.3 is the minimum](CMakeLists.txt#L25)).
We recommend installing CMake by downloading and unpacking the binary 
distribution  of the latest version available on the 
[**CMake download page**](https://cmake.org/download/).

The CMake package available in your operating system can also be installed
and used if it meets the minimum version requirement.

> **Alternative method**
>
> The repository contains the
[scripts/install_cmake.sh](scripts/install_cmake.sh) script that downloads 
> a fixed version of CMake and unpacks it to the given directory prefix. 
> Example usage: `scripts/install_cmake.sh --prefix /usr/local`.

### Install dependencies (Linux, macOS)

The following *libraries* are required to be installed in the system in their
development variant:

We also support a "one-button" shell script 
[scripts/install_deps.sh](scripts/install_deps.sh)
which attempts to aggregate dependencies installation instructions for Unix-like
operating systems. It identifies your distro and installs the external packages.

### Build

Configure the project build with the following command to create the 
`build` directory with the configuration.

```shell
mkdir build; cd build  # Create a build directory.
cmake ..               # Configure the project.
cmake --build .        # Build all default targets.
```
### Test

Test transaction signature function
```
cd libsign
./txsign
```

### Compile sign library
```
cd ../../libsign
vi CMakeLists.txt

line 8: add_library(txsign ${sources})
line 9: # add_executable(txsign ${sources})
```

