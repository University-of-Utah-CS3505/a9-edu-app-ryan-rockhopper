#ifndef WORLD_H
#define WORLD_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include "gamecollisionlistener.h"
using std::vector;

class World : public QWidget
{
    Q_OBJECT
public:
    explicit World(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void updateWorld();
    void moveLeft();
    void moveRight();

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

#endif // WORLD_H
