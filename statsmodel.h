#ifndef STATSMODEL_H
#define STATSMODEL_H
#include <QElapsedTimer>
#include <QObject>
#include <QTimer>
#include <string>

using std::string;

class statsModel : public QObject
{
    Q_OBJECT
public:
    /// @brief This is the constructor for our stas model
    explicit statsModel(QObject *parent = nullptr);

signals:
    /// @brief This signal tells the window to display a pop-up
    void drawPopUp();

    /// @brief This signal tells the main window to switch to the death screen, and passes in stats for it to display
    /// @param catsDodged - The amount of cats the player dodged in the game
    /// @param timeAlive - The length of time the player stayed alive as a string
    /// @param timeSincePopUp - The length of time since the last pop-up appeared
    /// @param maxLevel - the level that the player died on
    void deathScreen(int catsDodged, string timeAlive, string timeSincePopUp, int popUpsClosed, int maxLevel);

    /// @brief This signal tells the main window to update the stas labels, and passes in stats for it to display
    /// @param catsDodged - The amount of cats the player dodged in the game
    /// @param timeAlive - The length of time the player stayed alive as a string
    /// @param popUpsClosed - The amount of pop ups that have been closed so far
    /// @param currentLevel - the level that the player is on
    void updateLabels(int catsDodged, string timeAlive, int popUpsClosed, int currentLevel);

    /// @brief This changes the maximum amount of time the cat can take to spawn, and tells the World to change level
    /// @param newMaxCatWait - new Maximum time for a cat to spawn
    void tellWorldLevelUp(int newMaxCatWait);

public slots:
    /// @brief Starts the timer to track play time
    void startGame();

    /// @brief Used to record final stats and send a signal to switch the view to the game over screen
    void processDeath();

    /// @brief Used to calculate the amount of seconds passed and will pass that information to the view
    void calculateStats();

    /// @brief Starts the timer to track time from last pop up and sends a signal to the view
    ///         to draw a new pop up.
    void generatePopUp();

    /// @brief Incremements popUpsClosed every time the player closes a pop up
    void updatePopUpsClosed();

    /// @brief Increments catsDodged every time the player dodges a cat
    void updateCatsDodged();

private:
    QTimer *popUpFrequency  = new QTimer(this);
    QTimer *oneSecond       = new QTimer(this);
    QTimer *levelUpper      = new QTimer(this);

    QElapsedTimer popUpToDeath;
    QElapsedTimer playTimeStopwatch;
    int catsDodged;
    int popUpsClosed;
    int level;

    // time in milliseconds
    int currentPopUpFrequency;
    int currentCatSpawnMaxWait;

    /// @brief Sets the game level and therefore the frequency of pop ups based on the amount of time
    ///         the player has been playing. Every 30 seconds, the level increases.
    void levelUp();

    /// @brief Converts the number of milliseconds elapsed to a string of mm:ss format
    /// @param millisecondsElapsed is the amount of ms since the player started playing
    /// @return a string of the form mm:ss
    string millisecondsToMinAndSec(qint64 millisecondsElapsed);

    /// @brief Constants of time in Millisenconds
    enum levelTimes
    {
        twoMinThirtySeconds = 150000,
        twoMin              = 120000,
        oneMinThirtySeconds = 90000,
        oneMin              = 60000,
        thirtySeconds       = 30000
    };
};

#endif // STATSMODEL_H
