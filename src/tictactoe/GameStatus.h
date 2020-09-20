#ifndef GAMESTATUS_H
#define GAMESTATUS_H

/**
 * @brief The GameStatus enum defines the possible game statuses
 */
enum class GameStatus
{
    IN_PROGRESS, /**< Game is in progress */
    CPU_WIN, /**< CPU has won the game */
    PLAYER_WIN, /**< Player has won the game */
    STALEMATE /**< A stalemate has occured */
};

#endif // GAMESTATUS_H
