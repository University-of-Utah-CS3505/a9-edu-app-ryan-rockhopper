#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(statsModel& model, QApplication* app, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->app = app;
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
    connect(&model,
            &statsModel::changeBackground,
            ui->gameplayArea,
            &World::levelUp);

    //Update cats dodged
    connect(&ui->gameplayArea->listener,
            &GameCollisionListener::catHitsFloor,
            &model,
            &statsModel::updateCatsDodged);

    //connect controls
    connect(this,
            &MainWindow::rightKeyPressed,
            ui->gameplayArea,
            &World::moveRight);
    connect(this,
            &MainWindow::rightKeyReleased,
            ui->gameplayArea,
            &World::stopMoveRight);
    connect(this,
            &MainWindow::leftKeyPressed,
            ui->gameplayArea,
            &World::moveLeft);
    connect(this,
            &MainWindow::leftKeyReleased,
            ui->gameplayArea,
            &World::stopMoveLeft);

    //connect pop-up closing
    connect(&distractionWindow2,
            &StringMatcherPopup::popupClosed,
            &model,
            &statsModel::updatePopUpsClosed);
    connect(&distractionWindow,
            &PopUp::popupClosed,
            &model,
            &statsModel::updatePopUpsClosed);

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
    if(!ui->gameOverScreen->isEnabled())
    {
        string statsString = "";
        ui->gameStats->setText("You dodged " + QString::number(catsDodged) + " cats. \n" +
                               "You lasted " + QString::fromStdString(timeAlive) + "\n" +
                               "You died " + QString::fromStdString(timeSincePopUp) + " seconds after the last pop-up\n" +
                               "You got through " + QString::number(popUpsClosed) + " pop-ups\n" +
                               "You made it to level " + QString::number(maxLevel));
    }
    ui->startUpScreen   ->setEnabled(false);
    ui->mainScreen      ->setEnabled(false);
    ui->startUpScreen   ->hide();
    ui->mainScreen      ->hide();
    distractionWindow    .hide();
    distractionWindow2   .hide();
    ui->gameOverScreen  ->setEnabled(true);
    ui->gameOverScreen  ->show();
}

void MainWindow::placePopUp()
{
    if (rand() % 2 == 0)
    {
        // 950x693 is the game screen size, take the popup width and height to get the maximum x or y the top left corner of the pop can be, and still be on screen
        distractionWindow.setWindowFlags(Qt::FramelessWindowHint);
        distractionWindow.setWindowModality(Qt::ApplicationModal);
        distractionWindow.show();
        distractionWindow.windowHandle()->setScreen(app->screenAt(this->mapToGlobal(QPoint(this->width()/2, 0))));
        int xPosition = rand() % 550;
        int yPosition = rand() % 393;
        QPoint position = mapToGlobal(QPoint(xPosition,yPosition));
        distractionWindow.setGeometry(position.x(), position.y(), 400, 300);
        emit leftKeyReleased();
    }
    else
    {

        distractionWindow2.setWindowFlags(Qt::FramelessWindowHint);
        distractionWindow2.setWindowModality(Qt::ApplicationModal);
        distractionWindow2.show();
        distractionWindow2.windowHandle()->setScreen(app->screenAt(this->mapToGlobal(QPoint(this->width()/2, 0))));
        int xPosition = rand() % 330;
        int yPosition = rand() % 373;
        QPoint position = mapToGlobal(QPoint(xPosition,yPosition));
        distractionWindow2.setGeometry(position.x(), position.y(), 620, 300);
        emit spawnStringMatcher();
        emit leftKeyReleased();
    }
}

void MainWindow::updateStatValues(int catsDodged, string timeAlive, int popUpsClosed, int currentLevel)
{
    ui->catsDodgedValue->setText(QString::number(catsDodged));
    ui->timeAliveValue->setText(QString::fromStdString(timeAlive));
    ui->notificationsAcknowledgedValue->setText(QString::number(popUpsClosed));
    ui->levelValue->setText(QString::number(currentLevel));
}
