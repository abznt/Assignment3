#include "gtest/gtest.h"
#include "Board.h"

class BoardTests : public ::testing::Test
{
protected:
    static constexpr int rowDim = 3;
    static constexpr int colDim = 3;
    using TttBoard = Board<rowDim, colDim>;
    TttBoard *board;

    void SetUp() override
    {
        board = new TttBoard();
    }

    void TearDown() override
    {
        delete(board);
    }
};

TEST_F(BoardTests, TestConstructor)
{
    TttBoard::dims_t dims = board->dimensions();
    ASSERT_EQ(dims.first, rowDim);
    ASSERT_EQ(dims.second, colDim);
    // Check that every cell value is empty
    for (int row = 0; row < dims.first; ++row)
    {
        for (int col = 0; col < dims.second; ++col)
        {
            EXPECT_EQ(board->getCellValue(row, col), TttValue::EMPTY);
        }
    }
}

TEST_F(BoardTests, TestPlayMove)
{
    board->playMove(0, 0, TttValue::X);
    EXPECT_EQ(board->getCellValue(0, 0), TttValue::X);
    board->playMove(2, 2, TttValue::O);
    EXPECT_EQ(board->getCellValue(2, 2), TttValue::O);
    EXPECT_THROW(board->playMove(3, 3, TttValue::X), std::invalid_argument);
    EXPECT_THROW(board->playMove(-1, -1, TttValue::X), std::invalid_argument);
    EXPECT_THROW(board->playMove(0, 0, TttValue::O), std::runtime_error);
}

TEST_F(BoardTests, TestResetBoard)
{
    board->playMove(0, 0, TttValue::X);
    board->playMove(1, 1, TttValue::O);
    board->playMove(2, 2, TttValue::X);
    board->resetBoard();
    EXPECT_EQ(board->getCellValue(0, 0), TttValue::EMPTY);
    EXPECT_EQ(board->getCellValue(1, 1), TttValue::EMPTY);
    EXPECT_EQ(board->getCellValue(2, 2), TttValue::EMPTY);
}

TEST_F(BoardTests, TestGetCurrentMoves)
{
    TttBoard::cellList_t inputList{std::make_pair(0, 0), std::make_pair(1, 1),
                std::make_pair(2, 2)};
    for (auto &move : inputList)
    {
        board->playMove(move.first, move.second, TttValue::X);
    }
    const TttBoard::cellList_t outList = board->getCurrentMoves();
    ASSERT_EQ(inputList.size(), outList.size());
    for (size_t i = 0; i < inputList.size(); ++i)
    {
        EXPECT_EQ(inputList.at(i), outList.at(i));
    }
}

TEST_F(BoardTests, TestGetAvailabeMoves)
{
    // All cells should be available for a fresh board
    TttBoard::cellList_t compList{std::make_pair(0,0), std::make_pair(0,1),
                std::make_pair(0,2), std::make_pair(1,0), std::make_pair(1,1),
                std::make_pair(1,2), std::make_pair(2,0), std::make_pair(2,1),
                std::make_pair(2,2)};
    // Available move list should be [(0,0),(0,1),(0,2),(1,0),(1,1),(1,2),(2,0),(2,1),(2,2)]
    TttBoard::cellList_t availMoves = board->getAvailableMoves();
    ASSERT_EQ(availMoves.size(), compList.size());
    for (size_t i = 0; i < compList.size(); ++i)
    {
        EXPECT_EQ(availMoves.at(i), compList.at(i));
    }
    // Play some moves and test again
    board->playMove(0, 0, TttValue::X);
    board->playMove(0, 1, TttValue::O);
    board->playMove(0, 2, TttValue::X);
    compList.erase(compList.begin() + 2);
    compList.erase(compList.begin() + 1);
    compList.erase(compList.begin() + 0);
    // Available move list should be [(1,0),(1,1),(1,2),(2,0),(2,1),(2,2)]
    availMoves = board->getAvailableMoves();
    ASSERT_EQ(availMoves.size(), compList.size());
    for (size_t i = 0; i < compList.size(); ++i)
    {
        EXPECT_EQ(availMoves.at(i), compList.at(i));
    }
}
