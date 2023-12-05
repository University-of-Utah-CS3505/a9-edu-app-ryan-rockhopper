#include "world.h"

World::World(QWidget *parent) : QWidget(parent),
    world(b2Vec2(0.0f, 15.0f)),//b2Vec2(0.0f, 10.0f)),
    worldCycle(this),
    mouseImg(":/mouse.png"),
    catImg(":/cat.png")
{
    connect(&listener,
            &GameCollisionListener::catHitsFloor,
            this,
            &World::markCatsForDeath);
      
    float xMidpoint = width / 2.0f;
    world.SetContactListener(&listener);

    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(xMidpoint, height);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;
    groundBox.SetAsBox(width * 4, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define dynamic body. We set its position and call the body factory.
    b2BodyDef mouseBodyDef;
    mouseBodyDef.angularDamping = 1000; // keeps mouse from rotating and making collision weird
    mouseBodyDef.type = b2_dynamicBody;
    mouseBodyDef.position.Set(xMidpoint, 561.0f);
    mouseBody = world.CreateBody(&mouseBodyDef);
    int mouseData = 1;
    mouseBody->SetUserData((void*)mouseData);
    currentMoveVelocity = 120.0f;
    currentStopVelocity = 0.0f;

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(25.0f, 25.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    // Override the default friction.
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    // Add the shape to the body.
    mouseBody->CreateFixture(&fixtureDef);

    connect(&worldCycle, &QTimer::timeout, this, &World::updateWorld);
    worldCycle.start(10);

    SpawnNewCat();
}

void World::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    b2Vec2 position = mouseBody->GetPosition();

    painter.drawPixmap(0, 0, width, height, currentBackground);
    painter.drawImage(position.x - 25.0f, position.y - 25.0f, mouseImg);
    for(auto pair : catBodies)
    {
        b2Vec2 position = pair.second->GetPosition();
        painter.drawImage(position.x - 41.0f, position.y - 50.0f, catImg);
    }

    // add black border on the game
    QPen pen(Qt::black);
    int penWidth =  2;
    pen.setWidth(penWidth);
    painter.setPen(pen);
    QRect paintingFrame(0, 0, width, height);

    painter.drawRect(paintingFrame);
    painter.end();
}

void World::levelUpWorld(int newMaxCatWait)
{
    catSpawnMaxWait = newMaxCatWait;
    gameStarted = true;

    int currentBackgroundIndex = rand() % worldBackgrounds.size();
    changePhysics(currentBackgroundIndex);
    currentBackground = worldBackgrounds.at(currentBackgroundIndex);
}

void World::changePhysics(int level)
{
    switch(level)
    {
        case 0: //0 is the grass level, and physics should be default
           currentMoveVelocity = 120.0f;
           currentStopVelocity = 0.0f;
           applyBounce = false;
           break;
        case 1: //1 is the ice level, so we should slide around
           currentMoveVelocity = 120.0f;
           currentStopVelocity = 20.0f;
           applyBounce = false;
           break;
        case 2: //2 is the desert level, so we should move slower
           currentMoveVelocity = 80.0f;
           currentStopVelocity = 0.0f;
           applyBounce = false;
           break;
        case 3: //3 is the slime level so we
           currentMoveVelocity = 120.0f;
           currentStopVelocity = 0.0f;
           applyBounce = true;
           break;
    }
}

void World::updateWorld()
{
    // It is generally best to keep the time step and iterations fixed.
    world.Step(1.0/60.0, 6, 2);
    update();
    deleteCats();
    if(mouseBody->GetPosition().x > width - 20 || mouseBody->GetPosition().x < 20)
    {
        mouseBody->SetLinearVelocity(b2Vec2(0,0));
    }
    if(applyBounce && mouseBody->GetPosition().y  > 565)
    {
        mouseBody->ApplyLinearImpulse(b2Vec2(0, -80 * mouseBody->GetMass()), mouseBody->GetPosition(), true );
    }
}

void World::moveLeft()
{
    if (mouseBody->GetPosition().x > 20)
        mouseBody->SetLinearVelocity(b2Vec2(-currentMoveVelocity, mouseBody->GetLinearVelocity().y));
}

void World::moveRight()
{
    if (mouseBody->GetPosition().x < width - 20)
        mouseBody->SetLinearVelocity(b2Vec2(currentMoveVelocity,mouseBody->GetLinearVelocity().y));
}

void World::stopMoveLeft()
{
    mouseBody->SetLinearVelocity(b2Vec2(-currentStopVelocity,mouseBody->GetLinearVelocity().y));
}

void World::stopMoveRight()
{
    mouseBody->SetLinearVelocity(b2Vec2(currentStopVelocity,mouseBody->GetLinearVelocity().y));
}

void World::SpawnNewCat()
{
    if (gameStarted)
    {
        b2BodyDef catBodyDef;
        catBodyDef.angularDamping = 1000; //this keeps the cat from rotating and making the collision weird
        catBodyDef.type = b2_dynamicBody;
        catBodyDef.position.Set(rand() % (int)width, -80.0f);
        b2Body* cat = world.CreateBody(&catBodyDef);
        cat->SetUserData((void*) catData);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(41.0f, 50.0f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;

        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 1.0f;
        cat->CreateFixture(&fixtureDef);
        catBodies.insert(std::pair<qint64, b2Body*>(catData, cat));
        catData++;
    }
    QTimer::singleShot(rand() % catSpawnMaxWait, Qt::PreciseTimer, this, [this](){SpawnNewCat();});
}

void World::markCatsForDeath(qint64 catID)
{
    b2Body* cat = catBodies[catID];
    deadCats[catID] = cat;
}

void World::deleteCats()
{
    for(auto IDandCat : deadCats)
    {
        b2Body* cat = IDandCat.second;

        world.DestroyBody(cat);

        auto desiredCat = catBodies.find(IDandCat.first);
        catBodies.erase(desiredCat);
    }

    deadCats.clear();
}

void World::playerHitByCat()
{
    worldCycle.stop();
}
