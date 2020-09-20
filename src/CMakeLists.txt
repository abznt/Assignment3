set(targetName Main)
project(${targetName})

add_subdirectory(tictactoe)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH C:/Qt/5.15.1/msvc2019_64/lib/cmake)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(${targetName} main.cpp mainwindow.cpp mainwindow.h mainwindow.ui)
target_link_libraries(${targetName} Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${targetName} tictactoe)

#function(COPY_QT_DLL TGT DLL_IN DLL_OUT)
#    add_custom_command(
#            TARGET ${TGT} POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy
#            ${DLL_IN}
#            ${DLL_OUT}
#    )
#endfunction()

#set(QT_BIN_DIR C:/Qt/5.15.1/msvc2019_64/bin)

#copy_qt_dll(${targetName} ${QT_BIN_DIR}/Qt5Widgets.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Widgets.dll)
#copy_qt_dll(${targetName} ${QT_BIN_DIR}/Qt5Gui.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Gui.dll)
#copy_qt_dll(${targetName} ${QT_BIN_DIR}/Qt5Core.dll ${CMAKE_CURRENT_BINARY_DIR}/Qt5Core.dll)

unset(targetName)
