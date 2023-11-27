#ifndef GAMECOLLISIONLISTENER_H
#define GAMECOLLISIONLISTENER_H
#include <Box2D/Box2D.h>


class GameCollisionListener : public b2ContactListener
{
public:
    GameCollisionListener();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};

#endif // GAMECOLLISIONLISTENER_H
