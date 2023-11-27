#include "gamecollisionlistener.h"
#include <QDebug>
GameCollisionListener::GameCollisionListener()
{

}
void GameCollisionListener::BeginContact(b2Contact* contact)
{
    qDebug() << "begun";
}

void GameCollisionListener::EndContact(b2Contact* contact)
{
    qDebug() << "ended";
}

