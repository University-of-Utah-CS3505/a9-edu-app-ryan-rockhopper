#include "statsmodel.h"
#include <string>

using std::string;
using std::to_string;


statsModel::statsModel(QObject *parent) : QObject{parent}
{
    level           = 1;
    popUpsClosed    = 0;
    catsDodged      = 0;

    popUpFrequency  ->setInterval(5000);
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

    //game over, send to game over screen
    string finalTimeAlive           = millisecondsToMinAndSec(playTimeStopwatch.elapsed());
    string secondsSinceLastPopUp    = to_string(popUpToDeath.elapsed() / 1000);

    emit deathScreen(catsDodged, finalTimeAlive, secondsSinceLastPopUp, popUpsClosed, level);
}

void statsModel::startGame()
{
    playTimeStopwatch.start();
    oneSecond       ->start();
    popUpFrequency  ->start();
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
}

void statsModel::calculateStats()
{
    string timePlayedSoFar = millisecondsToMinAndSec(playTimeStopwatch.elapsed());

    if(playTimeStopwatch.elapsed() % thirtySeconds < 1000) //Every 30 seconds with a margin of error of 1 second, update the game level.
        setGameLevel();

    emit updateLabels(catsDodged, timePlayedSoFar, popUpsClosed, level);
}

void statsModel::generatePopUp()
{
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

void statsModel::setGameLevel()
{
    if(level == 5)
        return;

    if(playTimeStopwatch.elapsed() > twoMin)
    {
        level = 5;
        popUpFrequency->setInterval(1000);
    }
    else if(playTimeStopwatch.elapsed() > oneMinThirtySeconds)
    {
        level = 4;
        popUpFrequency->setInterval(2000);
    }
    else if(playTimeStopwatch.elapsed() > oneMin)
    {
        level = 3;
        popUpFrequency->setInterval(3000);
    }
    else if(playTimeStopwatch.elapsed() > thirtySeconds)
    {
        level = 2;
        popUpFrequency->setInterval(4000);
    }
    else if(playTimeStopwatch.elapsed() < thirtySeconds)
    {
        level = 1;
        popUpFrequency->setInterval(5000);
    }
}
