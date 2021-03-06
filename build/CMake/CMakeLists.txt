# #################################################################################################
#  CMakeList.txt - CMake sample file for ALib distribution module "Singleton".
#
#  (c) 2019 A-Worx GmbH, Germany
#  Published under Boost Software License (a free software license, see LICENSE.txt)
#
#  Note:
#   This is just a very simple CMake file. The main purpose of ALib "modules" is to include the
#   corresponding portion of ALib directly into a client software. Hence, also the rather complex
#   CMake file that is provided with the full distribution of ALib is not used here.
#   As a result, ALib compilation settings will use default values.
# #################################################################################################
cmake_minimum_required(VERSION 3.6)
project(ALib_Singleton_Sample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES        ../../src/alib/lib/predef_compiler.hpp
                        ../../src/alib/lib/typedemangler.hpp
                        ../../src/alib/lib/typedemangler.cpp
                        ../../src/alib/lib/typemap.hpp


                        ../../src/alib/singletons/singletons_predef.hpp
                        ../../src/alib/singletons/singleton.hpp
                        ../../src/alib/singletons/singleton.cpp

                        ../../sample.cpp     )

add_executable            ( ALib_Singleton_Sample ${SOURCE_FILES})
target_include_directories( ALib_Singleton_Sample PRIVATE   "../../src")

# Force feature to "mapped implementation" mode. Usually this is enabled only on windows platform
# By setting this compilation symbol, we enable this on all platforms like GNU/Linux or macOS.
# This is done for demonstration purpose only!
target_compile_definitions( ALib_Singleton_Sample    PRIVATE    "ALIB_FEAT_SINGLETON_MAPPED_ON")


