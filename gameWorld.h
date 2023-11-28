#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include "gamecollisionlistener.h"
using std::vector;

class GameWorld : public QWidget
{
    Q_OBJECT
public:
    explicit GameWorld(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void updateWorld();

private:
    float width;
    float height;
    GameCollisionListener listener;
    b2World world;

    int catSpawnMaxWait = 5000;
    QTimer worldCycle;

    b2Body* mouseBody;
    QImage mouseImg;
    vector<b2Body*> catBodies;
    QImage catImg;

    void SpawnNewCat();
};

#endif // GAMEWORLD_H
