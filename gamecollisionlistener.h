#ifndef GAMECOLLISIONLISTENER_H
#define GAMECOLLISIONLISTENER_H
#include <Box2D/Box2D.h>
#include <QObject>


class GameCollisionListener :public QObject, public b2ContactListener
{
    Q_OBJECT
public:
    /// @brief This is the constructor for our custom collision listener object
    explicit GameCollisionListener(QObject *parent = nullptr);
    /// @brief This is the method that should be called when two objects in the game world collide
    /// @param contact - the b2Contact Object passed in
    void BeginContact(b2Contact* contact);

signals:
    /// @brief This is the signal that gets sent out when a cat hits the floor object
    /// @param catID - the number from the userData field of the cat object
    void catHitsFloor(qint64 catID);
    /// @brief This is the signal that gets sent out when a cat and the mouse object collide, making a game-over
    void catHitsMouse();
};

#endif // GAMECOLLISIONLISTENER_H
