#ifndef WORLD_H
#define WORLD_H

#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QRandomGenerator>
#include <map>
#include <QPainter>
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

    /// @brief This stops the mouse from moving when the left arrow is released
    void stopMoveLeft();

    /// @brief This stops the mouse from moving when the right arrow is released
    void stopMoveRight();

    /// @brief this handles the consequences of leveling up in the world
    /// @param newMaxCatWait - new Maximum time for a cat to spawn
    void levelUpWorld(int newMaxCatWait);

    /// @brief When a cat hits the ground, it is marked for deletion
    /// @param catID is the identifier of the cat
    void markCatsForDeath(qint64 catID);

    /// @brief The player has been hit by the cat, this begins the singal-slot sequence for game over
    void playerHitByCat();

private:
    float currentMoveVelocity;
    float currentStopVelocity;
    void changePhysics(int level);
    const float width   = 691.0f;
    const float height  = 601.0f;
    bool gameStarted    = false;
    bool applyBounce    = false;
    b2World world;
    qint64 catData      = 2;

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

    vector<QPixmap> worldBackgrounds
    {
        QPixmap (":/grass_template.png"),
        QPixmap (":/ice_template.png"),     // lowers friction (ice lvl)
        QPixmap (":/sand_template.png"),    // increase friction (sand lvl)
        QPixmap (":/bouncy_template.png")   // increase bounciness/restitution (bouncy castle lvl)
    };

    QPixmap currentBackground = worldBackgrounds.at(0);
};

#endif // WORLD_H
