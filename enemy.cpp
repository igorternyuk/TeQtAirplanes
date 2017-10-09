#include "enemy.hpp"
#include "game.hpp"
#include <QGraphicsScene>
#include <QTimer>
#include <cstdlib>
#include <QDebug>

Enemy::Enemy(Game *game, double w, double h, double vy, QObject *parent):
    Entity(game, rand() % int(Game::WINDOW_WIDTH - w),0,w,h,0,vy, parent)
{
    mTimer = new QTimer();
    //connect
    connect(mTimer, SIGNAL(timeout()), this, SLOT(move()));
    mTimer->start(TIMER_DELAY);
}

void Enemy::move()
{
    if(bottom() >= Game::WINDOW_HEIGHT && !isBottomLineReached)
    {
        //qDebug() << "bottomLineReached";
        emit bottomLineReached();
        isBottomLineReached = true;
    }
    Entity::move();
}

void Enemy::destroy()
{
    //qDebug() << "Enemy has been destoyed";
    //disconnect(this, SIGNAL(bottomLineReached()), mGame, SLOT(decreaseHealth()));
    Entity::destroy();
}
