#include "bullet.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <typeinfo>
#include <QDebug>

Bullet::Bullet(Game* game, double x, double y, double w, double h, double vx,
               double vy, QObject *parent):
    Entity(game, x,y,w,h,vx,vy, parent)
{
    mTimer = new QTimer();
    //connect
    connect(mTimer, SIGNAL(timeout()), this, SLOT(move()));
    mTimer->start(TIMER_DELAY);
}

void Bullet::move()
{
    if(!hasCollisionWithEnemies())
        Entity::move();
}

void Bullet::destroy()
{
    qDebug() << "Bullet has been destroyed";
    Entity::destroy();
}

bool Bullet::hasCollisionWithEnemies()
{
    bool hasCollisions{false};
    QList<QGraphicsItem*> collidingEntities = collidingItems();
    if(!collidingEntities.isEmpty())
    {
        for(auto &e: collidingEntities)
        {
            //typeof()
            if(typeid(*e) == typeid(Enemy))
            {
                mGame->increaseScore();
                mGame->playSound(Game::SoundID::EXPLOSION);
                qDebug() << "Collision was detected";
                scene()->removeItem(e);
                scene()->removeItem(this);
                delete e;
                delete this;
            }
        }
        hasCollisions = true;
    }
    return hasCollisions;
}
