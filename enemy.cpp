#include "enemy.hpp"
#include <QGraphicsScene>
#include <QTimer>
#include <cstdlib>
#include <QDebug>

Enemy::Enemy(double w, double h, double vy, QObject *parent):
    Entity(rand() % 700,0,w,h,0,vy, parent)
{
    mTimer = new QTimer();
    //connect
    connect(mTimer, SIGNAL(timeout()), this, SLOT(move()));
    mTimer->start(TIMER_DELAY);
}

void Enemy::destroy()
{
    qDebug() << "Enemy has been destoyed";
    Entity::destroy();
}
