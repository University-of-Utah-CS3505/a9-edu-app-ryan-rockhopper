#include "gamecollisionlistener.h"
#include <QDebug>
GameCollisionListener::GameCollisionListener()
{

}
void GameCollisionListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
}

void GameCollisionListener::EndContact(b2Contact* contact)
{
}

