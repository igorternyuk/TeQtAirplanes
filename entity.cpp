#include "entity.hpp"
#include <QGraphicsScene>
#include <QDebug>

Entity::Entity(double x, double y, double w, double h,
               QPointF velocity, QObject *parent) :
    QObject(parent), QGraphicsRectItem(x, y, w, h), mVelocity{velocity}
{
    this->setPos(x,y);
    this->setRect(0, 0, w, h);
    connect(this, SIGNAL(outOfSceneBounds()), this, SLOT(destroy()));
}

Entity::Entity(double x, double y, double w, double h, double vx, double vy,
               QObject *parent):Entity(x,y,w,h,QPointF(vx,vy), parent)
{}

void Entity::move()
{
    this->moveBy(mVelocity.x(), mVelocity.y());
    auto sceneRect = sceneBoundingRect();
    if(right() < sceneRect.left() || bottom() < 0 ||
       left() > sceneRect.right() || top() > 800)
    {
        qDebug() << "Entity is out of bounds";
        emit outOfSceneBounds();
    }
}

void Entity::destroy()
{
    this->scene()->removeItem(this);
    delete this;
}
