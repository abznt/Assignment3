#ifndef MOVERESULT_H
#define MOVERESULT_H

#include "GameStatus.h"

/**
 * @brief The MoveResult struct conveys the results of a move
 */
struct MoveResult
{
    int row; /**< Board cell row where the move was played */
    int col; /**< Board cell column where the move was played */
    GameStatus status; /**< Result of the move */
};

#endif // MOVERESULT_H
