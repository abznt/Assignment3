#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <time.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_game{}
{
    ui->setupUi(this);
    ui->gameover->hide();
    m_rows = ui->layout->rowCount();
    m_cols = ui->layout->rowCount();
    configureCells();
    // Configure the "restart" button callback
    connect(ui->restart, &QPushButton::clicked, this, &MainWindow::resetBoard);
    // Set the random seed based on the current time
    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureCells()
{
    // Iterate over rows and columns of the buttons
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            // Get the button at (row, col) from the QGridLayout
            QLayoutItem * const item =ui->layout->itemAtPosition(row, col);
            if(item->widget())
            {
                QPushButton *cell = dynamic_cast<QPushButton*>(item->widget());
                // Register the game logic to the current button
                connect(cell, &QPushButton::clicked, [cell, row, col, this](){
                    // Perform a player move
                    MoveResult result = m_game.playerMove(row, col);
                    cell->setText("X");
                    cell->setDisabled(true);
                    evaluateMove(result);
                    // If the game isn't over, perform a CPU move
                    if (m_game.getStatus() == GameStatus::IN_PROGRESS)
                    {
                        MoveResult cpuResult = m_game.cpuMove();
                        QLayoutItem * const itemCpu = ui->layout->itemAtPosition(
                                    cpuResult.row, cpuResult.col);
                        if(itemCpu->widget())
                        {
                            QPushButton *cellCpu = dynamic_cast<QPushButton*>(
                                        itemCpu->widget());
                            cellCpu->setText("O");
                            cellCpu->setDisabled(true);
                            evaluateMove(cpuResult);
                        }
                    }
                });
            }
        }
    }
}

void MainWindow::resetBoard()
{
    ui->gameover->hide();
    m_game.resetGame();
    // Iterate over rows and cols of the buttons
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_cols; ++col)
        {
            // Get the button at (row, col) from the QGridLayout
            QLayoutItem * const item = ui->layout->itemAtPosition(row, col);
            if(item->widget())
            {
                // Reset the button to the default state
                QPushButton *cell = dynamic_cast<QPushButton*>(item->widget());
                cell->setText("");
                cell->setDisabled(false);
            }
        }
    }
    ui->board->setEnabled(true);
}

void MainWindow::evaluateMove(MoveResult result)
{
    // Modify the board UI according to the MoveResult
    switch (result.status)
    {
        case GameStatus::PLAYER_WIN :
            ui->board->setDisabled(true);
            ui->gameover->setText("PLAYER WINS");
            ui->gameover->show();
            return;
        case GameStatus::CPU_WIN :
            ui->board->setDisabled(true);
            ui->gameover->setText("CPU WINS");
            ui->gameover->show();
            return;
        case GameStatus::STALEMATE :
            ui->board->setDisabled(true);
            ui->gameover->setText("STALEMATE");
            ui->gameover->show();
            return;
        case GameStatus::IN_PROGRESS :
            return;
    }
}
