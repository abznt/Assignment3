#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "Game.h"

namespace Ui
{
    class MainWindow;
}

/**
 * @brief The MainWindow class defines the tic-tac-toe user interface
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent QWidget
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int m_rows, m_cols;
    Game m_game;

    /**
     * @brief Registers callbacks to the buttons that represent the tic-tac-toe
     * board. This enables the game to be played interactively.
     */
    void configureCells();

    /**
     * @brief Resets the board UI to the default state.
     */
    void resetBoard();

    /**
     * @brief Evaluates a MoveResult and updates the board UI accordingly.
     * @param result MoveResult
     */
    void evaluateMove(MoveResult result);
};


#endif // MAINWINDOW_H
