#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <QElapsedTimer>
#include <QObject>
#include <QTimer>
#include <string>

using std::string;

class gameModel : public QObject
{
    Q_OBJECT
public:
    explicit gameModel(QObject *parent = nullptr);

signals:
    void drawPopUp();
    void deathScreen(int catsDodged, string timeAlive, string timeSincePopUp, int popUpsClosed, int maxLevel);
    void updateLabels(int catsDodged, string timeAlive, int popUpsClosed, int currentLevel);
public slots:
    /// @brief Used to record final stats and send a signal to switch the view to the game over screen
    void processDeath();

    /// @brief Starts the timer to track play time
    void startGame();

    /// @brief Increments catsDodged every time the player dodges a cat
    void updateCatsDodged();

    /// @brief Incremements popUpsClosed every time the player closes a pop up
    void updatePopUpsClosed();

    /// @brief Used to calculate the amount of seconds passed and will pass that information to the view
    void calculateStats();

    /// @brief Starts the timer to track time from last pop up and sends a signal to the view
    ///         to draw a new pop up.
    void generatePopUp();

private:
    QTimer *popUpFrequency  = new QTimer(this);
    QTimer *oneSecond       = new QTimer(this);
    QElapsedTimer popUpToDeath;
    QElapsedTimer playTimeStopwatch;
    int catsDodged;
    int popUpsClosed;
    int level;

    /// @brief Converts the number of milliseconds elapsed to a string of mm:ss format
    /// @param millisecondsElapsed is the amount of ms since the player started playing
    /// @return a string of the form mm:ss
    string millisecondsToMinAndSec(qint64 millisecondsElapsed);

    /// @brief Sets the game level and therefore the frequency of pop ups based on the amount of time
    ///         the player has been playing. Every 30 seconds, the level increases to a max of 5.
    void setGameLevel();

    enum levelTimes
    {
        twoMinThirtySeconds = 150000,
        twoMin              = 120000,
        oneMinThirtySeconds = 90000,
        oneMin              = 60000,
        thirtySeconds       = 30000
    };
};

#endif // GAMEMODEL_H
