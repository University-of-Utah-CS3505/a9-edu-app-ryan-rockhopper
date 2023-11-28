#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <QElapsedTimer>
#include <QObject>

class gameModel : public QObject
{
    Q_OBJECT
public:
    gameModel();

signals:
    void spawnPopUp();
    void deathScreen(int catsDodged, qint64 timeAlive, qint64 timeSincePopUp, int popUpsClosed);
public slots:
    void processDeath();
    void startGame();
private:
    QElapsedTimer popUpToDeath;
    QElapsedTimer timer;
    int catsDodged;
    int popUpsClosed;

};

#endif // GAMEMODEL_H
