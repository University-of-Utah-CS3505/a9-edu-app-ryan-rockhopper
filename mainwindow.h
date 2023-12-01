#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "popup.h"
#include "stringmatcherpopup.h"
#include "statsmodel.h"
#include "gamecollisionlistener.h"
#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(statsModel& model, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    /// @brief Places a pop up on the screen after recieving a signal from the model.
    void placePopUp();

    /// @brief Updates all stat labels in the main screen after recieving a signal from the model.
    /// @param catsDodged is the number of cats dodged by the player so far
    /// @param timeAlive is the time the player has been playing in mm:ss format
    /// @param popUpsClosed is the amount of pop ups that has been closed by the player
    /// @param currentLevel is the level the player is currently on
    void updateStatValues(int catsDodged, string timeAlive, int popUpsClosed, int currentLevel);

signals:
    void spawnStringMatcher();
    void rightKeyPressed();
    void rightKeyReleased();
    void leftKeyPressed();
    void leftKeyReleased();

private:
    Ui::MainWindow *ui;
    PopUp distractionWindow;
    StringMatcherPopup distractionWindow2;

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void keyReleaseEvent(QKeyEvent * event);
    /// @brief Displays the start up screen when the application begins.
    void startupScreen();

    /// @brief Changes the view to display the main game screen when the user presses the start button.
    void mainScreen();

    /// @brief Changes the view to display the game over screen when the player has lost.
    void gameOverScreen(int catsDodged, string timeAlive, string timeSincePopUp, int popUpsClosed, int maxLevel);
};
#endif // MAINWINDOW_H
