#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QScreen>


MainWindow::MainWindow(gameModel& model, QWidget *parent)
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
            &gameModel::startGame);

    //Generate a pop up based on the timer in the model
    connect(&model,
            &gameModel::drawPopUp,
            this,
            &MainWindow::placePopUp);

    //Update stats in main screen every second
    connect(&model,
            &gameModel::updateLabels,
            this,
            &MainWindow::updateStatValues);






    //TODO: Remove this entire button later. It is only as a manual way to "lose" the game.
    connect(ui->gameOverButton,
            &QPushButton::clicked,
            this,
            &MainWindow::gameOverScreen);

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

void MainWindow::gameOverScreen()
{
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
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    // 950x693 is the game screen size so it appears within the game screen always, also make a signal in model to do this and add timer.
    int xPosition = rand() % 950;
    int yPosition = rand() % 693;
    distractionWindow.setGeometry(xPosition, yPosition, 400, 300);
    distractionWindow.setWindowFlags(Qt::FramelessWindowHint);
    distractionWindow.show();
}

void MainWindow::updateStatValues(int catsDodged, string timeAlive, int popUpsClosed, int currentLevel)
{
    ui->catsDodgedValue->setText(QString::number(catsDodged));
    ui->timeAliveValue->setText(QString::fromStdString(timeAlive));
    ui->notificationsAcknowledgedValue->setText(QString::number(popUpsClosed));
    ui->levelValue->setText(QString::number(currentLevel));
}
