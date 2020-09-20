set(targetName tictactoe)

set(srcList
    TttValue.h
    Board.h
    GameStatus.h
    MoveResult.h
    Game.cpp
    Game.h
    )

add_library(${targetName} STATIC ${srcList})
target_include_directories(${targetName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${targetName} PROPERTIES LINKER_LANGUAGE CXX)

unset(srcList)
unset(targetName)
