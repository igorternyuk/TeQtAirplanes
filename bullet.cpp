#include "bullet.hpp"
#include "enemy.hpp"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QDebug>

Bullet::Bullet(double x, double y, double w, double h, double vx, double vy,
               QObject *parent):
    Entity(x,y,w,h,vx,vy, parent)
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
            if(typeid(*e) != typeid(Bullet) && typeid(*e) == typeid(Enemy))
            {
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
