#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMovie"

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
            &MainWindow::changeTextToMatch,
            &textMessage,
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
            &statsModel::tellWorldLevelUp,
            ui->gameplayArea,
            &World::levelUpWorld);

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
    connect(&textMessage,
            &StringMatcherPopup::popupClosed,
            &model,
            &statsModel::updatePopUpsClosed);
    connect(&davidPopUp,
            &PopUp::popupClosed,
            &model,
            &statsModel::updatePopUpsClosed);
    connect(&memePopup,
            &meme::popupClosed,
            &model,
            &statsModel::updatePopUpsClosed);

    ui->startButton->setStyleSheet(QString("QPushButton {background-color: rgb(106,255,77);}"));
    ui->startButton->setIcon(QIcon(":/start.png"));
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
        lastKeyPressedLeft = false;
        emit rightKeyPressed();
    }
    if(event->key() == Qt::Key_Left)
    {
        lastKeyPressedLeft = true;
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
    davidPopUp          .hide();
    textMessage         .hide();
    ui->gameOverScreen  ->setEnabled(true);
    ui->gameOverScreen  ->show();

    QMovie *movie = new QMovie(":/catDriving.gif");
    ui->gameOverGif->setMovie(movie);
    movie->start();
}

void MainWindow::placePopUp()
{
    int randomNum = QRandomGenerator::global()->bounded(3);
    if (randomNum == 0)
    {
        // 950x693 is the game screen size, take the popup width and height to get the maximum x or y the top left corner of the pop can be, and still be on screen
        davidPopUp.setWindowFlags(Qt::FramelessWindowHint);
        davidPopUp.setWindowModality(Qt::ApplicationModal);
        davidPopUp.show();
        davidPopUp.windowHandle()->setScreen(app->screenAt(this->mapToGlobal(QPoint(this->width()/2, 0))));
        int xPosition = QRandomGenerator::global()->generate() % 500;
        int yPosition = QRandomGenerator::global()->generate() % 393;
        QPoint position = mapToGlobal(QPoint(xPosition,yPosition));
        davidPopUp.setGeometry(position.x(), position.y(), 450, 300);
        if(lastKeyPressedLeft)
        {
            emit leftKeyReleased();
        }
        else
        {
            emit rightKeyReleased();
        }

    }
    if (randomNum == 1)
    {
        textMessage.setWindowFlags(Qt::FramelessWindowHint);
        textMessage.setWindowModality(Qt::ApplicationModal);
        textMessage.show();
        textMessage.windowHandle()->setScreen(app->screenAt(this->mapToGlobal(QPoint(this->width()/2, 0))));
        int xPosition = QRandomGenerator::global()->generate() % 330;
        int yPosition = QRandomGenerator::global()->generate() % 373;
        QPoint position = mapToGlobal(QPoint(xPosition,yPosition));
        textMessage.setGeometry(position.x(), position.y(), 620, 300);
        emit changeTextToMatch();
        if(lastKeyPressedLeft)
        {
            emit leftKeyReleased();
        }
        else
        {
            emit rightKeyReleased();
        }
        emit changeTextToMatch();
        emit leftKeyReleased();
    }
    if (randomNum == 2)
    {
        memePopup.setWindowFlags(Qt::FramelessWindowHint);
        memePopup.setWindowModality(Qt::ApplicationModal);
        memePopup.show();
        memePopup.windowHandle()->setScreen(app->screenAt(this->mapToGlobal(QPoint(this->width()/2, 0))));
        int xPosition = QRandomGenerator::global()->generate() % 450;
        int yPosition = QRandomGenerator::global()->generate() % 343;
        QPoint position = mapToGlobal(QPoint(xPosition,yPosition));
        memePopup.setGeometry(position.x(), position.y(), 500, 350);
        if(lastKeyPressedLeft)
        {
            emit leftKeyReleased();
        }
        else
        {
            emit rightKeyReleased();
        }
    }
}

void MainWindow::updateStatValues(int catsDodged, string timeAlive, int popUpsClosed, int currentLevel)
{
    ui->catsDodgedValue->setText(QString::number(catsDodged));
    ui->timeAliveValue->setText(QString::fromStdString(timeAlive));
    ui->notificationsAcknowledgedValue->setText(QString::number(popUpsClosed));
    ui->levelValue->setText(QString::number(currentLevel));
}
