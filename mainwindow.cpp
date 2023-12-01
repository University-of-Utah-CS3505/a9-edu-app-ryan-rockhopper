#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>


MainWindow::MainWindow(statsModel& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Start button
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::mainScreen);
    connect(ui->startButton,
            &QPushButton::clicked,
            &model,
            &statsModel::startGame);

    //Generate a pop up based on the timer in the model
    connect(&model,
            &statsModel::drawPopUp,
            this,
            &MainWindow::placePopUp);
    connect(this,
            &MainWindow::spawnStringMatcher,
            &distractionWindow2,
            &StringMatcherPopup::changeText);

    //Update stats in main screen every second
    connect(&model,
            &statsModel::updateLabels,
            this,
            &MainWindow::updateStatValues);

    //When the player is hit by a mouse, call processDeath in model
    connect(&ui->gameplayArea->listener,
            &GameCollisionListener::catHitsMouse,
            &model,
            &statsModel::processDeath);
    connect(&model,
            &statsModel::deathScreen,
            this,
            &MainWindow::gameOverScreen);
    connect(&model,
            &statsModel::updateCatSpawnMaxWait,
            ui->gameplayArea,
            &World::setCatSpawnMaxWait);

    //Update cats dodged
    connect(&ui->gameplayArea->listener,
            &GameCollisionListener::catHitsFloor,
            &model,
            &statsModel::updateCatsDodged);

    connect(this,
            &MainWindow::rightKeyPressed,
            ui->gameplayArea,
            &World::moveRight);
    connect(this,
            &MainWindow::rightKeyReleased,
            ui->gameplayArea,
            &World::stopMove);
    connect(this,
            &MainWindow::leftKeyPressed,
            ui->gameplayArea,
            &World::moveLeft);
    connect(this,
            &MainWindow::leftKeyReleased,
            ui->gameplayArea,
            &World::stopMove);


    startupScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startupScreen()
{
    ui->gameOverScreen  ->setEnabled(false);
    ui->mainScreen      ->setEnabled(false);
    ui->gameOverScreen  ->hide();
    ui->mainScreen      ->hide();

    ui->startUpScreen   ->setEnabled(true);
    ui->startUpScreen   ->show();
}

void MainWindow::mainScreen()
{
    ui->startUpScreen   ->setEnabled(false);
    ui->gameOverScreen  ->setEnabled(false);
    ui->startUpScreen   ->hide();
    ui->gameOverScreen  ->hide();

    ui->mainScreen      ->setEnabled(true);
    ui->mainScreen      ->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
    {
        emit rightKeyPressed();
    }
    if(event->key() == Qt::Key_Left)
    {
        emit leftKeyPressed();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
    {
        emit rightKeyReleased();
    }
    if(event->key() == Qt::Key_Left)
    {
        emit leftKeyReleased();
    }
}

void MainWindow::gameOverScreen(int catsDodged, string timeAlive, string timeSincePopUp, int popUpsClosed, int maxLevel)
{
    //TODO: Pass these stats into the game over screen so the player can see
    //TODO: Add some stats about distracted driving and how it relates
    //TODO: Add a Qimage to the game over screen?
    //TODO: Delete the game over button
    ui->startUpScreen   ->setEnabled(false);
    ui->mainScreen      ->setEnabled(false);
    ui->startUpScreen   ->hide();
    ui->mainScreen      ->hide();

    ui->gameOverScreen  ->setEnabled(true);
    ui->gameOverScreen  ->show();
}

//TODO: Create a stack (or vector or something) of pop-ups that are on screen. Right now generating a pop up gets rid of the old one even if it wasn't closed.
//TODO: Pop up appears on my (Ryan) second monitor and not within game window DEBUG
void MainWindow::placePopUp()
{
    if (rand() % 2 == 0) {
        // 950x693 is the game screen size so it appears within the game screen always, also make a signal in model to do this and add timer.
        int xPosition = rand() % 950;
        int yPosition = rand() % 693;
        distractionWindow.setGeometry(xPosition, yPosition, 400, 300);
        distractionWindow.setWindowFlags(Qt::FramelessWindowHint);
        distractionWindow.show();
    } else {
        int xPosition2 = rand() % 950;
        int yPosition2 = rand() % 693;
        distractionWindow2.setGeometry(xPosition2, yPosition2, 620, 238);
        distractionWindow2.setWindowFlags(Qt::FramelessWindowHint);
        distractionWindow2.show();
        emit spawnStringMatcher();
    }
}

void MainWindow::updateStatValues(int catsDodged, string timeAlive, int popUpsClosed, int currentLevel)
{
    ui->catsDodgedValue->setText(QString::number(catsDodged));
    ui->timeAliveValue->setText(QString::fromStdString(timeAlive));
    ui->notificationsAcknowledgedValue->setText(QString::number(popUpsClosed));
    ui->levelValue->setText(QString::number(currentLevel));
}
