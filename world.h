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

public slots:
    /// @brief Steps the world, and calls update() to paint again. Called periodically by the worldCycle timer.
    void updateWorld();
    /// @brief Moves the mouse to the left when left arrow is pressed.
    void moveLeft();
    /// @brief Moves the mouse to the right when right arrow is pressed.
    void moveRight();

private:
    const float width = 691.0f;
    const float height = 601.0f;
    GameCollisionListener listener;
    b2World world;

    int catSpawnMaxWait = 5000;
    QTimer worldCycle;

    b2Body* mouseBody;
    QImage mouseImg;
    vector<b2Body*> catBodies;
    QImage catImg;

    /// @brief Spawns a cat in thw world that we follow to paint in catbodies.
    void SpawnNewCat();
};

#endif // WORLD_H
