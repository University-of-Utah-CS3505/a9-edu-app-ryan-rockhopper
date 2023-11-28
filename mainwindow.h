#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "popup.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

signals:

private:
    Ui::MainWindow *ui;
    PopUp distractionWindow;

    /// @brief Displays the start up screen when the application begins.
    void startupScreen();

    /// @brief Changes the view to display the main game screen when the user presses the start button.
    void mainScreen();

    /// @brief Changes the view to display the game over screen when the player has lost.
    void gameOverScreen();
};
#endif // MAINWINDOW_H
