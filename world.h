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

public slots:
    /// @brief Steps the world, and calls update() to paint again. Called periodically by the worldCycle timer.
    void updateWorld();
    /// @brief Moves the mouse to the left when left arrow is pressed.
    void moveLeft();
    /// @brief Moves the mouse to the right when right arrow is pressed.
    void moveRight();
    /// @brief Sets our max spawn wait time.
    void setCatSpawnMaxWait(int newMax);

    /// @brief When a cat hits the ground, it is marked for deletion
    /// @param catID is the identifier of the cat
    void markCatsForDeath(qint64 catID);

    /// @brief The player has been hit by the cat, this begins the singal-slot sequence for game over
    void playerHitByCat();
private:
    const float width = 691.0f;
    const float height = 601.0f;
    
    b2World world;
    qint64 catData = 2;

    int catSpawnMaxWait = 5000;
    QTimer worldCycle;

    b2Body* mouseBody;
    QImage mouseImg;
    map<qint64, b2Body*> catBodies;
    map<qint64, b2Body*> deadCats;
    QImage catImg;

    /// @brief Spawns a cat in thw world that we follow to paint in catbodies.
    void SpawnNewCat();

    /// @brief Deletes all cats that have been marked for deletion. Must be done outside the world step.
    void deleteCats();
};

#endif // WORLD_H
