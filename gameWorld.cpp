#include "gameWorld.h"
#include <QPainter>
#include <QDebug>

GameWorld::GameWorld(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 20.0f)),//b2Vec2(0.0f, 10.0f)),
    worldCycle(this)//,
    //mouse(":/sprites/mouse.png"),
    //cat(":/sprites/mouse.png")
{
    width = 691.0f;
    height = 601.0f;
    float xMidpoint = width / 2.0f;

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
    mouseBodyDef.type = b2_dynamicBody;
    mouseBodyDef.position.Set(xMidpoint, height / 2.0f);//0.0f, 4.0f);
    mouseBody = world.CreateBody(&mouseBodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10.0f, 10.0f);
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
}

void GameWorld::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    b2Vec2 position = mouseBody->GetPosition();
    float angle = mouseBody->GetAngle();

    //qDebug() << position.x << "," << position.y;//, angle);

    painter.fillRect(position.x, position.y, 20, 20, Qt::blue);
//    painter.drawImage((int)(position.x*20), (int)(position.y*20), mouse);
//    painter.drawImage(200, 200, mouse);
    //    qDebug() << image;

    QPen pen(Qt::black);
    int penWidth =  2;
    pen.setWidth(penWidth);
    painter.setPen(pen);

    QRect paintingFrame(0, 0, width, height);
    painter.drawRect(paintingFrame);

    painter.end();
}

void GameWorld::updateWorld() {
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
}
