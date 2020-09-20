#include "Game.h"
#include "TttValue.h"
#include <stdexcept>

Game::Game() :
    m_board{}, m_status{GameStatus::IN_PROGRESS} {}

void Game::evaluateBoard()
{
    TttBoard::dims_t dims = m_board.dimensions();
    int sum;
    // Test row win condition
    for (int row = 0; row < dims.first; ++row)
    {
        sum = static_cast<int>(m_board.getCellValue(row, 0)) +
                static_cast<int>(m_board.getCellValue(row, 1)) +
                static_cast<int>(m_board.getCellValue(row, 2));
        m_status = evaluateResult(sum);
        if (m_status != GameStatus::IN_PROGRESS) return;
    }

    // Test column win condition
    for (int col = 0; col < dims.second; ++col)
    {
        sum = static_cast<int>(m_board.getCellValue(0, col)) +
                static_cast<int>(m_board.getCellValue(1, col)) +
                static_cast<int>(m_board.getCellValue(2, col));
        m_status = evaluateResult(sum);
        if (m_status != GameStatus::IN_PROGRESS) return;
    }

    // Test diagonal win condition
    sum = static_cast<int>(m_board.getCellValue(0, 0)) +
            static_cast<int>(m_board.getCellValue(1, 1)) +
            static_cast<int>(m_board.getCellValue(2, 2));
    m_status = evaluateResult(sum);
    if (m_status != GameStatus::IN_PROGRESS) return;
    sum = static_cast<int>(m_board.getCellValue(0, 2)) +
            static_cast<int>(m_board.getCellValue(1, 1)) +
            static_cast<int>(m_board.getCellValue(2, 0));
    m_status = evaluateResult(sum);
    if (m_status != GameStatus::IN_PROGRESS) return;

    // Test stalemate condition
    if (m_status == GameStatus::IN_PROGRESS &&
            static_cast<int>(m_board.getCurrentMoves().size()) == dims.first*dims.second)
    {
        m_status = GameStatus::STALEMATE;
    }
}

GameStatus Game::evaluateResult(const int sum)
{
    switch (sum)
    {
        case 3 :
            return GameStatus::PLAYER_WIN;
        case -3 :
            return GameStatus::CPU_WIN;
        default :
            return GameStatus::IN_PROGRESS;
    }
}

void Game::resetGame()
{
    m_board.resetBoard();
    m_status = GameStatus::IN_PROGRESS;
}

MoveResult Game::playerMove(const int row, const int col)
{
    if (m_status != GameStatus::IN_PROGRESS)
    {
        throw std::runtime_error("Game::playerMove cannot play a move since the game is not in progress");
    }
    m_board.playMove(row, col, TttValue::X);
    evaluateBoard();
    return MoveResult{row, col, m_status};
}

MoveResult Game::cpuMove()
{
    if (m_status != GameStatus::IN_PROGRESS)
    {
        throw std::runtime_error("Game::cpuMove cannot play a move since the game is not in progress");
    }
    TttBoard::cellList_t availMoves = m_board.getAvailableMoves();
    int choice = rand() % availMoves.size();
    TttBoard::cell_t move = availMoves.at(choice);
    m_board.playMove(move.first, move.second, TttValue::O);
    evaluateBoard();
    return MoveResult{move.first, move.second, m_status};
}

GameStatus Game::getStatus() const
{
    return m_status;
}
