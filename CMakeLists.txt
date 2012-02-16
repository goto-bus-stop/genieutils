# Available settings:
#
# GUTILS_TOOLS:BOOL     if true to enable compilation of gutils tools
# GUTILS_TEST:BOOL      if true some debug/test classes will be compiled
#

cmake_minimum_required(VERSION 2.8)

set(Genieutils_LIBRARY genieutils)

project(genieutils)

find_package(ZLIB REQUIRED)
#find_package(Boost 1.42 COMPONENTS iostreams program_options REQUIRED)
find_package(Boost 1.42 COMPONENTS iostreams program_options unit_test_framework REQUIRED)

if (GUTILS_TEST)
  find_package(SFML COMPONENTS SYSTEM WINDOW GRAPHICS REQUIRED)
endif (GUTILS_TEST)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

if (GUTILS_TEST)
  include_directories(
      include/
      ${Boost_INCLUDE_DIRS}
      ${SFML_INCLUDE_DIR}
      )
else (GUTILS_TEST)
  include_directories(
      include/
      ${Boost_INCLUDE_DIRS}
      )
endif (GUTILS_TEST)

add_definitions(-Wall)

#------------------------------------------------------------------------------#
# Source files: 
#------------------------------------------------------------------------------#
set(FILE_SRC
    src/file/ISerializable.cpp
    src/file/IFile.cpp
    src/file/ICompressedFile.cpp
    )

set(LANG_SRC
    src/lang/LangFile.cpp
    )

set(DAT_SRC
    src/dat/Research.cpp 
   
    src/dat/Civ.cpp
    src/dat/TechageEffect.cpp
    src/dat/Techage.cpp

    src/dat/TechTree.cpp
    src/dat/Terrain.cpp
    src/dat/TerrainBorder.cpp
    src/dat/GraphicAttackSound.cpp
    src/dat/GraphicDelta.cpp
    src/dat/Graphic.cpp
    src/dat/SoundItem.cpp
    src/dat/Sound.cpp
    src/dat/PlayerColour.cpp
    src/dat/DatFile.cpp
    src/dat/TerrainPassGraphic.cpp
    src/dat/TerrainRestriction.cpp

    src/dat/Unit.cpp
    src/dat/UnitCommand.cpp
    src/dat/UnitHeader.cpp
    src/dat/UnitLine.cpp

    src/dat/unit/AttackOrArmor.cpp
    src/dat/unit/DamageGraphic.cpp
    src/dat/unit/BuildingAnnex.cpp
    src/dat/unit/DeadFish.cpp 
    src/dat/unit/Bird.cpp
    src/dat/unit/Projectile.cpp
    src/dat/unit/ProjectileOnly.cpp
    src/dat/unit/Creatable.cpp
    src/dat/unit/Building.cpp
    )

set(RESOURCE_SRC
    src/resource/PalFile.cpp
    src/resource/SlpFile.cpp
    src/resource/SlpFrame.cpp
    src/resource/DrsFile.cpp
    src/resource/Color.cpp
    )

set(UTIL_SRC
    src/util/Logger.cpp
    )

# Tool sources:

set(TEST_SRC
    src/tools/test/test.cpp
    src/tools/bincompare/bincomp.cpp
   )

set(EXTRACT_SRC src/tools/extract/datextract.cpp)

set(BINCOMP_SRC src/tools/bincompare/bincomp.cpp
                src/tools/bincompare/main.cpp)


#------------------------------------------------------------------------------#
# Executeable:
#------------------------------------------------------------------------------#

add_library(${Genieutils_LIBRARY} ${FILE_SRC} ${LANG_SRC} ${DAT_SRC} 
                                  ${RESOURCE_SRC} ${UTIL_SRC})
target_link_libraries(${Genieutils_LIBRARY} ${ZLIB_LIBRARIES} ${Boost_LIBRARIES})

#add_executable(main main.cpp)
#target_link_libraries(main ${Genieutils_LIBRARY})

#------------------------------------------------------------------------------#
# Dev tools:
#------------------------------------------------------------------------------#

 # test doesn't build :(
 # add_executable(test ${TEST_SRC})
 # target_link_libraries(test ${Genieutils_LIBRARY} ${Boost_LIBRARIES} ) #${ZLIB_LIBRARIES} ${Boost_LIBRARIES} ${Genieutils_LIBRARY})

if (GUTILS_TOOLS)
  add_executable(datextract ${EXTRACT_SRC})
  target_link_libraries(datextract ${ZLIB_LIBRARIES} ${Boost_LIBRARIES} ${Genieutils_LIBRARY})

  add_executable(bincomp ${BINCOMP_SRC})
endif (GUTILS_TOOLS)

#------------------------------------------------------------------------------#
# Debug/Test:
#------------------------------------------------------------------------------#
if (GUTILS_TEST)
  add_executable(main main.cpp)
  target_link_libraries(main ${Genieutils_LIBRARY}
                      ${SFML_WINDOW_LIBRARY}
                      ${SFML_SYSTEM_LIBRARY}
                      ${SFML_GRAPHICS_LIBRARY}
  )
endif(GUTILS_TEST)