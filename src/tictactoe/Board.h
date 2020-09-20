#ifndef BOARD_H
#define BOARD_H

#include "TttValue.h"
#include <vector>
#include <algorithm>
#include <stdexcept>


/**
 * @brief The Board class encapsulates a tic-tac-toe board
 * @details The Board<int rows, int cols> template class encapsulates a tic-tac-toe board
 * of size rows-by-cols using a grid of integers where the origin is the top left
 * corner. A cell with avalue of 0 is empty, a cell with a value of 1 contains
 * an X, and a cell with a value of -1 contains an O.
 */
template <int rows, int cols>
class Board
{
// Members
public:
    using dims_t = std::pair<int, int>; /**< Type alias for the board dimensions (rows, columns) */
    using cell_t = std::pair<int, int>; /**< Type alias for a cell (row, column) coordinate */
    using cellList_t = std::vector<cell_t>; /**< Type alias for a vector of cell (row, column) coordinates */

private:
    const int m_rows = rows;
    const int m_cols = cols;
    cellList_t m_currentMoves;
    cellList_t m_availableMoves;
    TttValue m_cells[rows][cols];

// Methods
public:
    /**
     * @brief Constructs a tic-tac-toe board
     * @details All cell values are initialized to 0
     */
    Board();

    /**
     * @brief Plays a move in the specified cell
     * @param row Cell row
     * @param col Cell col
     * @param val New cell value
     * @exception invalid_argument Thrown if the specified row or col is out of bounds
     * @exception runtime_error Thrown if the cell is not empty
     */
    void playMove(int row, int col, TttValue val);

    /**
     * @brief Resets the board cells to the 'EMPTY' state
     */
    void resetBoard();

    /**
     * @brief Gets the contents of the specified board cell
     * @param row Cell row
     * @param col Cell column
     * @return The specified cell contents
     * @exception invalid_argument Thrown if the specified row or col is out of bounds
     */
    TttValue getCellValue(int row, int col) const;

    /**
     * @brief Gets the current move list
     * @return A list of moves that have been played on the board
     */
    const cellList_t& getCurrentMoves() const;

    /**
     * @brief Gets a list of the available moves
     * @return A list of moves that can be played on the board
     */
    const cellList_t& getAvailableMoves() const;

    /**
     * @brief Gets the current board dimensions
     * @return The dimensions of the board (row, col)
     */
    dims_t dimensions() const;
};

// Template class definition needs to be visible at compile time

template<int rows, int cols>
Board<rows, cols>::Board()
{
    resetBoard();
}

template<int rows, int cols>
void Board<rows, cols>::playMove(const int row, const int col, const TttValue val)
{
    // Ensure the specified move is within the board boundary
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
    {
        throw std::invalid_argument("Board::playMove specified (row, col) is out of bounds");
    }
    // Ensure that the cell is empty
    if (m_cells[row][col] != TttValue::EMPTY)
    {
        throw std::runtime_error("Board::playMove cell at (row, col) is not empty");
    }
    cell_t move = std::make_pair(row, col);
    m_availableMoves.erase(std::remove(m_availableMoves.begin(),
                                       m_availableMoves.end(), move),
                           m_availableMoves.end());
    m_currentMoves.push_back(move);
    m_cells[row][col] = val;
}

template<int rows, int cols>
void Board<rows, cols>::resetBoard()
{
    // Clear the available moves list
    m_availableMoves.clear();
    // Set the value of all cells to EMPTY
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            m_availableMoves.emplace_back(row, col);
            m_cells[row][col] = TttValue::EMPTY;
        }
    }
    // Clear the current move list
    m_currentMoves.clear();
}

template<int rows, int cols>
TttValue Board<rows, cols>::getCellValue(const int row, const int col) const
{
    // Ensure the specified move is within the board boundary
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
    {
        throw std::invalid_argument("Board::playMove specified (row, col) is out of bounds");
    }
    return m_cells[row][col];
}

template<int rows, int cols>
const typename Board<rows, cols>::cellList_t& Board<rows, cols>::getCurrentMoves() const
{
    return m_currentMoves;
}

template<int rows, int cols>
const typename Board<rows, cols>::cellList_t& Board<rows, cols>::getAvailableMoves() const
{
    return m_availableMoves;
}

template<int rows, int cols>
typename Board<rows, cols>::dims_t Board<rows, cols>::dimensions() const
{
    return std::make_pair(m_rows, m_cols);
}

#endif // BOARD_H
