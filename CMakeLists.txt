cmake_minimum_required(VERSION 3.5.1)

include(evmc/cmake/cable/bootstrap.cmake)
include(CableBuildInfo)
include(CableBuildType)
include(CableToolchains)
include(GNUInstallDirs)

cable_configure_toolchain(DEFAULT cxx11)

set(ETH_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${ETH_CMAKE_DIR})

set(CPP_ETHEREUM_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to the root directory for cpp-ethereum")

# Map current configuration to configurations of imported targets.
set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG Release)
set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)

set(HUNTER_CONFIGURATION_TYPES Release)
set(HUNTER_JOBS_NUMBER 4)
set(HUNTER_CACHE_SERVERS "https://github.com/ethereum/hunter-cache")
set(HUNTER_PASSWORDS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Hunter/passwords.cmake)

# In CI builds upload the binaries if the GITHUB_USER_PASSWORD was decrypted
# (only for branches and internal PRs).
if("$ENV{CI}" AND NOT "$ENV{GITHUB_USER_PASSWORD}" STREQUAL "")
    set(run_upload YES)
else()
    set(run_upload NO)
endif()
option(HUNTER_RUN_UPLOAD "Upload binaries to the cache server" ${run_upload})

include(HunterGate)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.20.73.tar.gz"
    SHA1 "5cd594b2bb12b2d66983a40b230f760187abbe5a"
    LOCAL
)

project(cpp-ethereum)
set(PROJECT_VERSION 1.4.0.dev0)

# if (NOT EXISTS ${CMAKE_SOURCE_DIR}/evmjit/.git)
#     message(FATAL_ERROR "Git submodules not initialized, execute:\n  git submodule update --init")
# endif()

cable_set_build_type(DEFAULT RelWithDebInfo CONFIGURATION_TYPES Debug;Release;RelWithDebInfo)

cable_add_buildinfo_library(PREFIX eth)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY On)

include(EthCcache)
include(EthOptions)
include(EthCompilerSettings)
include(EthExecutableHelper)
include(EthDependencies)
include(EthUtils)
include(FindProtobuf)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
hunter_add_package(Boost COMPONENTS program_options filesystem system thread context fiber log)
find_package(Boost CONFIG REQUIRED program_options filesystem system thread context fiber log)

hunter_add_package(cryptopp)
find_package(cryptopp CONFIG REQUIRED)

hunter_add_package(libscrypt)
find_package(libscrypt CONFIG REQUIRED)

hunter_add_package(ethash)
find_package(ethash CONFIG REQUIRED)

hunter_add_package(Protobuf)
find_package(Protobuf CONFIG REQUIRED)

include(ProjectSecp256k1)
include(ProjectLibFF)

# Import binaryen library before hera to make it available also to testeth.
include(hera/cmake/ProjectBinaryen.cmake)

set(UTILS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/utils")

configure_project()

#Global include path for all libs.
include_directories("${CMAKE_SOURCE_DIR}")

add_subdirectory(libdevcore)
add_subdirectory(libdevcrypto)
add_subdirectory(libethash)
add_subdirectory(libsign)

if(WIN32)
    set(CPACK_GENERATOR ZIP)
else()
    set(CPACK_GENERATOR TGZ)
endif()
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CHECKSUM SHA256)
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY FALSE)
include(CPack)
