#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Start button
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::mainScreen);
    //TODO: Remove this later, this is to show the gameplay area before we promote it to our custom widget
    ui->gameplayArea->setStyleSheet("background-color:green;");

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

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    // 950x693 is the game screen size so it appears within the game screen always, also make a signal in model to do this and add timer.
    int xPosition = rand() % 950;
    int yPosition = rand() % 693;
    distractionWindow.setGeometry(xPosition, yPosition, 400, 300);
    distractionWindow.setWindowFlags(Qt::FramelessWindowHint);
    distractionWindow.show();
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
