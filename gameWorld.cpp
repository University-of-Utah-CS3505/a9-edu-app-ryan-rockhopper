#include "gameWorld.h"
#include <QPainter>
#include <QDebug>

GameWorld::GameWorld(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 20.0f)),//b2Vec2(0.0f, 10.0f)),
    worldCycle(this),
    mouseImg(":/mouse.png"),
    catImg(":/cat.png")
{
    width = 691.0f;
    height = 601.0f;
    float xMidpoint = width / 2.0f;
    world.SetContactListener(&listener);

    qDebug() << "set Listener";
    // Define the ground body.
    b2BodyDef groundBodyDef;
//    b2Vec2 groundPosition(xMidpoint, parent->height());
//    qDebug() << "groundPostion" << groundPosition.x << "," << groundPosition.y;
    groundBodyDef.position.Set(xMidpoint, height);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;
    groundBox.SetAsBox(width, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define dynamic body. We set its position and call the body factory.
    b2BodyDef mouseBodyDef;
    mouseBodyDef.angularDamping = 1000; // keeps mouse from rotating and making collision weird
    mouseBodyDef.type = b2_dynamicBody;
    mouseBodyDef.position.Set(xMidpoint, 511.0f);//0.0f, 4.0f);
    mouseBody = world.CreateBody(&mouseBodyDef);
    int mouseData = 1;
    mouseBody->SetUserData((void*) mouseData);
    qDebug() << mouseBody->GetUserData();

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(25.0f, 25.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;

    // Add the shape to the body.
    mouseBody->CreateFixture(&fixtureDef);
    qDebug() << "Init world";

    connect(&worldCycle, &QTimer::timeout, this, &GameWorld::updateWorld);
    worldCycle.start(10);

    SpawnNewCat();
}

void GameWorld::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    b2Vec2 position = mouseBody->GetPosition();
    float angle = mouseBody->GetAngle();

    qDebug() << position.x << "," << position.y;//, angle);
    painter.drawImage(position.x - 25.0f, position.y - 25.0f, mouseImg);
    for(b2Body* body : catBodies)
    {
        b2Vec2 position = body->GetPosition();
        painter.drawImage(position.x - 41.0f, position.y - 50.0f, catImg);
    }

    painter.end();
}

void GameWorld::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}

void GameWorld::SpawnNewCat()
{
    b2BodyDef catBodyDef;
    catBodyDef.angularDamping = 1000; //this keeps the cat from rotating and making the collision weird
    catBodyDef.type = b2_dynamicBody;
    catBodyDef.position.Set(rand() % (int)width, -80.0f);//0.0f, 4.0f);
    int catData = 2;
    b2Body* cat = world.CreateBody(&catBodyDef);
    cat->SetUserData((void*) catData);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(41.0f, 50.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;


    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.9;
    cat->CreateFixture(&fixtureDef);
    catBodies.push_back(cat);
    QTimer::singleShot(rand() % catSpawnMaxWait, Qt::PreciseTimer, this, [this](){SpawnNewCat();});
}
