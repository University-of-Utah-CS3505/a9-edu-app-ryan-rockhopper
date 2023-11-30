#ifndef GAMECOLLISIONLISTENER_H
#define GAMECOLLISIONLISTENER_H
#include <Box2D/Box2D.h>
#include <QObject>


class GameCollisionListener :public QObject, public b2ContactListener
{
    Q_OBJECT
public:
    explicit GameCollisionListener(QObject *parent = nullptr);
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

signals:
    void catHitsFloor(qint64 catID);
    void catHitsMouse();
};

#endif // GAMECOLLISIONLISTENER_H
