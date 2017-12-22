PROJECT(yasm)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Where to look first for cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

INCLUDE(YasmMacros)
INCLUDE(VersionGen)

OPTION(ENABLE_NLS "Enable message translations" OFF)

OPTION(YASM_BUILD_TESTS "Enable building of tests" ON)

IF(YASM_BUILD_TESTS)
    ENABLE_TESTING()
ENDIF(YASM_BUILD_TESTS)

# Default build type to debug if not set
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

VERSION_GEN(PACKAGE_VERSION "${CMAKE_BINARY_DIR}/YASM-VERSION-FILE" "1.3.0")

set (PACKAGE_STRING "yasm ${PACKAGE_VERSION}")

INCLUDE_DIRECTORIES(AFTER ${CMAKE_BINARY_DIR} ${yasm_SOURCE_DIR})

INCLUDE(ConfigureChecks.cmake)

OPTION(INSTALL_YASM_ONLY "Only install the yasm executable" OFF)

IF(DEFINED YASM_VER)
  SET(ver _${YASM_VER})
  SET(verDir /${PROJECT_NAME}${ver})
ENDIF()
SET(targetsFile ${PROJECT_NAME}${ver}-targets)

ADD_SUBDIRECTORY(tools)
ADD_SUBDIRECTORY(libyasm)
ADD_SUBDIRECTORY(modules)
ADD_SUBDIRECTORY(frontends)

IF(NOT INSTALL_YASM_ONLY)

INSTALL(EXPORT ${targetsFile} DESTINATION bin/cmake)

INSTALL(FILES
    libyasm.h
    ${CMAKE_BINARY_DIR}/libyasm-stdint.h
    DESTINATION include${verDir}
    )

ENDIF(INSTALL_YASM_ONLY)
