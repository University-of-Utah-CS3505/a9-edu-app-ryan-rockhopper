#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "popup.h"
#include "stringmatcherpopup.h"
#include "statsmodel.h"
#include "gamecollisionlistener.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief this is the constructor for the MainWindow Object
    /// @param model - this is the model object that goes with our game
    /// @param app - This is the appplicatation that the Main window is a part of
    MainWindow(statsModel& model, QApplication* app, QWidget *parent = nullptr);
    /// @brief This is the destructor for the MainWindow Object
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
    /// @brief This signal tells the string matcher pop-up to clear out the text that was typed in it last time
    void spawnStringMatcher();
    /// @brief This signal activates the move right event in world
    void rightKeyPressed();
    /// @brief This signal activates the stop move right event in world
    void rightKeyReleased();
    /// @brief This signal activates the move left event in world
    void leftKeyPressed();
    /// @brief This signal activates the move left event in world
    void leftKeyReleased();

private:
    Ui::MainWindow *ui;
    PopUp distractionWindow;
    StringMatcherPopup distractionWindow2;
    QApplication* app;
    /// @brief This method overides the basic key press event
    /// @param event - the QKeyEvent Object passed in
    virtual void keyPressEvent(QKeyEvent *event);
    /// @brief This method overrides the basic key released event
    /// @param event - The QKeyEvent Object pased in
    virtual void keyReleaseEvent(QKeyEvent * event);
    /// @brief Displays the start up screen when the application begins.
    void startupScreen();

    /// @brief Changes the view to display the main game screen when the user presses the start button.
    void mainScreen();

    /// @brief Changes the view to display the game over screen when the player has lost.
    void gameOverScreen(int catsDodged, string timeAlive, string timeSincePopUp, int popUpsClosed, int maxLevel);
};
#endif // MAINWINDOW_H
