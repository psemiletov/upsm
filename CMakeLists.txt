cmake_minimum_required(VERSION 3.0)
set (QT_MIN_VERSION "5.4.0")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

enable_language(CXX)
enable_language(C)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)


if(Qt${QT_VERSION_MAJOR} STREQUAL "Qt6")
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Core5Compat REQUIRED)
endif()


if(Qt${QT_VERSION_MAJOR} STREQUAL "Qt5")
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
endif()

message(Qt${QT_VERSION_MAJOR} " found")

include_directories(${Qt${QT_VERSION_MAJOR}Widgets_INCLUDE_DIRS})
add_definitions(${Qt${QT_VERSION_MAJOR}Widgets_DEFINITIONS})
add_definitions(${Qt${QT_VERSION_MAJOR}Widgets_COMPILE_DEFINITIONS})


set(PROJECT "upsm")
project ($PROJECT VERSION 2.2.0)
add_definitions(-DVERSION_NUMBER="\\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}\\"")


# Populate a CMake variable with the sources
set(upsm_SRCS
    mainwindow.cpp
    main.cpp
)

set(upsm_ICONPNG
    ./icons/upsm.png
)

set(upsm_ICONSVG
    ./icons/upsm.svg
)


set(upsm_DESKTOP
    ./desktop/upsm.desktop
)



add_custom_target(dist
COMMAND git archive --format=tar --prefix=${PROJECT}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}/ HEAD | gzip >${PROJECT}-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.tar.gz
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)



find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED Core Widgets)


if(BUILD_TESTING)
  find_package(Qt${Test}${QT_VERSION_MAJOR} CONFIG REQUIRED)
endif()


if(Qt${QT_VERSION_MAJOR} STREQUAL "Qt6")
qt6_add_resources(QT_RESOURCES upsm.qrc)
endif()

if (Qt${QT_VERSION_MAJOR} MATCHES "Qt5")
qt5_add_resources(QT_RESOURCES upsm.qrc)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt${QT_VERSION_MAJOR}Widgets_EXECUTABLE_COMPILE_FLAGS}")


add_executable(${PROJECT} ${upsm_SRCS} ${QT_RESOURCES})


if(Qt${QT_VERSION_MAJOR} STREQUAL "Qt6")
   target_link_libraries(upsm Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt6::Core5Compat)
endif()


if(Qt${QT_VERSION_MAJOR} STREQUAL "Qt5")
target_link_libraries(upsm Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)
endif()


install (TARGETS ${PROJECT} DESTINATION bin)
install (FILES ${upsm_ICONSVG} DESTINATION share/icons/hicolor/scalable/apps)
install (FILES ${upsm_ICONPNG} DESTINATION share/icons/hicolor/128x128/apps)
install (FILES ${upsm_DESKTOP} DESTINATION share/applications)
