#include "entity.hpp"
#include "game.hpp"
#include <QGraphicsScene>
#include <QDebug>

Entity::Entity(Game *game, double x, double y, const QPixmap &image,
               QPointF velocity, QObject *parent) :
    QObject(parent), QGraphicsPixmapItem(), mGame{game},
    mVelocity{velocity}
{
    this->setPos(x, y);
    this->setPixmap(image);
    connect(this, SIGNAL(outOfSceneBounds()), this, SLOT(destroy()));
}

Entity::Entity(Game* game, double x, double y, const QPixmap &image,
               double vx, double vy, QObject *parent):
    Entity(game, x,y,image,QPointF(vx,vy), parent)
{}

void Entity::move()
{
    this->moveBy(mVelocity.x(), mVelocity.y());

    if(right() < 0 || bottom() < 0 ||
       left() > Game::WINDOW_WIDTH || top() > Game::WINDOW_HEIGHT)
    {
        emit outOfSceneBounds();
    }
}

void Entity::destroy()
{
    this->scene()->removeItem(this);
    delete this;
}
