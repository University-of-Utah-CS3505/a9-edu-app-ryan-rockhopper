#ifndef WORLD_H
#define WORLD_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <map>
#include "gamecollisionlistener.h"

using std::map;
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
    void markCatsForDeath(qint64 catID);

private:
    float width;
    float height;
    GameCollisionListener listener;
    b2World world;
    qint64 catData = 2;

    int catSpawnMaxWait = 5000;
    QTimer worldCycle;

    b2Body* mouseBody;
    QImage mouseImg;
    map<qint64, b2Body*> catBodies;
    map<qint64, b2Body*> deadCats;
    QImage catImg;

    void SpawnNewCat();
    void deleteCats();
};

#endif // WORLD_H
