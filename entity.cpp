#include "entity.hpp"
#include "game.hpp"
#include <QGraphicsScene>
#include <QDebug>

Entity::Entity(Game *game, double x, double y, double w, double h,
               QPointF velocity, QObject *parent) :
    QObject(parent), QGraphicsRectItem(x, y, w, h), mGame{game},
    mVelocity{velocity}
{
    this->setPos(x,y);
    this->setRect(0, 0, w, h);
    connect(this, SIGNAL(outOfSceneBounds()), this, SLOT(destroy()));
}

Entity::Entity(Game *game, double x, double y, double w, double h, double vx,
               double vy, QObject *parent):
    Entity(game, x,y,w,h,QPointF(vx,vy), parent)
{}

void Entity::move()
{
    this->moveBy(mVelocity.x(), mVelocity.y());

    if(right() < 0 || bottom() < 0 ||
       left() > Game::WINDOW_WIDTH || top() > Game::WINDOW_HEIGHT)
    {
        //qDebug() << "Entity is out of bounds";
        emit outOfSceneBounds();
    }
}

void Entity::destroy()
{
    this->scene()->removeItem(this);
    delete this;
}
