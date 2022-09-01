CMAKE_MINIMUM_REQUIRED(VERSION 2.4...3.21)
PROJECT(yasm)
if (COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif (COMMAND cmake_policy)

OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Where to look first for cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

INCLUDE(GNUInstallDirs)
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

OPTION(XP_INSTALL_YASM_EXE_ONLY "Only install the yasm executable" OFF)
IF(XP_INSTALL_YASM_EXE_ONLY)
  SET(OPT_INSTALL EXCLUDE_FROM_ALL)
ELSE()
  SET(OPT_INSTALL)
ENDIF()
SET(targetsFile ${PROJECT_NAME}-targets)

ADD_SUBDIRECTORY(tools)
ADD_SUBDIRECTORY(libyasm)
ADD_SUBDIRECTORY(modules)
ADD_SUBDIRECTORY(frontends)

INSTALL(EXPORT ${targetsFile} DESTINATION ${CMAKE_INSTALL_BINDIR}/cmake ${OPT_INSTALL})

INSTALL(FILES
    libyasm.h
    ${CMAKE_BINARY_DIR}/libyasm-stdint.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} ${OPT_INSTALL}
    )
