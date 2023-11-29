#include "gamecollisionlistener.h"
#include <QDebug>
GameCollisionListener::GameCollisionListener(QObject *parent) : QObject{parent}
{

}
void GameCollisionListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    qint64 fixtureA_ID = (qint64) fixtureA->GetBody()->GetUserData();
    qint64 fixtureB_ID = (qint64) fixtureB->GetBody()->GetUserData();

    //Floor is 0, Mouse is 1, Cat is > 1
    if(fixtureA_ID == 0 && fixtureB_ID > 1) //One is floor, the other is cat
        emit catHitsFloor(fixtureB_ID);
    else if(fixtureA_ID == 1 && fixtureB_ID > 1)
        emit catHitsMouse();

}

void GameCollisionListener::EndContact(b2Contact* contact)
{

}

