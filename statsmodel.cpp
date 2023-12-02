#include "statsmodel.h"
#include <QDebug>

using std::string;
using std::to_string;

statsModel::statsModel(QObject *parent) : QObject{parent}
{
    level           = 1;
    popUpsClosed    = 0;
    catsDodged      = 0;

    currentPopUpFrequency   = 15000;
    currentCatSpawnMaxWait  = 5000;

    levelUpper->setInterval(thirtySeconds);
    connect(levelUpper,
            &QTimer::timeout,
            this,
            &statsModel::levelUp);

    popUpFrequency  ->setInterval(currentPopUpFrequency);
    oneSecond       ->setInterval(1000);

    connect(popUpFrequency,
            &QTimer::timeout,
            this,
            &statsModel::generatePopUp);
    connect(oneSecond,
            &QTimer::timeout,
            this,
            &statsModel::calculateStats);
}

void statsModel::processDeath()
{
    popUpFrequency  ->stop();
    oneSecond       ->stop();
    levelUpper      ->stop();
    //game over, send to game over screen

    string finalTimeAlive           = millisecondsToMinAndSec(playTimeStopwatch.elapsed());
    string secondsSinceLastPopUp    = "0";
    if(popUpToDeath.elapsed() > 0)
    {
        secondsSinceLastPopUp = to_string(popUpToDeath.elapsed() / 1000);
    }


    emit deathScreen(catsDodged, finalTimeAlive, secondsSinceLastPopUp, popUpsClosed, level);
}

void statsModel::levelUp() 
{
    level++;

    currentPopUpFrequency   = currentPopUpFrequency * 0.92f;
    popUpFrequency->setInterval(currentPopUpFrequency);

    currentCatSpawnMaxWait  = currentCatSpawnMaxWait * 0.8f;
    emit updateCatSpawnMaxWait(currentCatSpawnMaxWait);
    qDebug() << "Leveled up to:" << level << ". currentPopUpFrequency = " << currentPopUpFrequency << ". currentCatSpawnMaxWait = " << currentCatSpawnMaxWait;
    emit changeBackgroundAndEnemies();
}

void statsModel::startGame()
{
    emit updateCatSpawnMaxWait(currentCatSpawnMaxWait);
    playTimeStopwatch.start();
    oneSecond       ->start();
    popUpFrequency  ->start();
    levelUpper      ->start();
}

void statsModel::updateCatsDodged()
{
    catsDodged++;
    calculateStats();
}

void statsModel::updatePopUpsClosed()
{
    popUpsClosed++;
    calculateStats();
    qDebug() << "slot called";
}

void statsModel::calculateStats()
{
    string timePlayedSoFar = millisecondsToMinAndSec(playTimeStopwatch.elapsed());

    emit updateLabels(catsDodged, timePlayedSoFar, popUpsClosed, level);
}

void statsModel::generatePopUp()
{
    qDebug() << "generatingPopup";
    popUpToDeath.restart();

    emit drawPopUp();
}

string statsModel::millisecondsToMinAndSec(qint64 millisecondsElapsed)
{
    long int seconds    = millisecondsElapsed / 1000;
    long int minutes    = seconds / 60;
    seconds             = seconds % 60;

    string minuteString = to_string(minutes);
    string secondString = to_string(seconds);

    if(minuteString.length() < 2)
        minuteString.insert(0, "0");

    if(secondString.length() < 2)
        secondString.insert(0, "0");

    string minAndSec    = minuteString + ":" + secondString;
    return minAndSec;
}
