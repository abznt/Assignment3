#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "GameStatus.h"
#include "MoveResult.h"

/**
 * @brief The Game class encapsulates the tic-tac-toe game
 * @brief The Game class allows a game of tic-tac-toe to be played against a CPU
 * opponent. The class is designed to be driven externally by user input. The CPU
 * plays by picking a random board cell from the list of available cells.
 */
class Game
{
// Members
private:
    using TttBoard = Board<3, 3>;
    TttBoard m_board;
    GameStatus m_status;

// Methods
private:
    void evaluateBoard();
    GameStatus evaluateResult(int sum);
public:
    /**
     * @brief Game constructor
     * @details Initializes a board of size 3-by-3
     */
    Game();

    /**
     * @brief Resets the game to the default state
     */
    void resetGame();

    /**
     * @brief Executes a player move on the specified cell
     * @param row board cell row
     * @param col board cell column
     * @return MoveResult
     */
    MoveResult playerMove(int row, int col);

    /**
     * @brief Executes a CPU move
     * @details The CPU chooses a random cell on the board from the list of
     * available cells.
     * @return MoveResult
     */
    MoveResult cpuMove();

    /**
     * @brief Gets the current status of the game
     * @return GameStatus
     */
    GameStatus getStatus() const;
};

#endif // GAME_H
