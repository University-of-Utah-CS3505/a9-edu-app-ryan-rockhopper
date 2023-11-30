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
    GameCollisionListener listener;
signals:

public slots:
    void updateWorld();
    void moveLeft();
    void moveRight();

    /// @brief When a cat hits the ground, it is marked for deletion
    /// @param catID is the identifier of the cat
    void markCatsForDeath(qint64 catID);

    /// @brief The player has been hit by the cat, this begins the singal-slot sequence for game over
    void playerHitByCat();
private:
    float width;
    float height;
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

    /// @brief Deletes all cats that have been marked for deletion. Must be done outside the world step.
    void deleteCats();
};

#endif // WORLD_H
