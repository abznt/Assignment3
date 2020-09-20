#include "gtest/gtest.h"
#include "Game.h"

class GameTests : public ::testing::Test
{
protected:
    Game *game;

    void SetUp() override
    {
        game = new Game();
    }

    void TearDown() override
    {
        delete(game);
    }
};

TEST_F(GameTests, TestPlayerMove)
{
    EXPECT_EQ(game->getStatus(), GameStatus::IN_PROGRESS);
    MoveResult result1 = game->playerMove(0, 0);
    EXPECT_EQ(result1.row, 0);
    EXPECT_EQ(result1.col, 0);
    EXPECT_EQ(result1.status, GameStatus::IN_PROGRESS);
    MoveResult result2 = game->playerMove(1, 1);
    EXPECT_EQ(result2.row, 1);
    EXPECT_EQ(result2.col, 1);
    EXPECT_EQ(result2.status, GameStatus::IN_PROGRESS);
    MoveResult result3 = game->playerMove(2, 2);
    EXPECT_EQ(result3.row, 2);
    EXPECT_EQ(result3.col, 2);
    EXPECT_EQ(result3.status, GameStatus::PLAYER_WIN);
    EXPECT_THROW(game->playerMove(0, 1), std::runtime_error);
}
