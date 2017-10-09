#include "enemy.hpp"
#include "game.hpp"
#include <QGraphicsScene>
#include <QTimer>
#include <cstdlib>
#include <QDebug>

Enemy::Enemy(Game *game, const QPixmap &image, double vy, QObject *parent):
    Entity(game, (image.width() / 2 + rand() % int(Game::WINDOW_WIDTH - image.width())),
           0, image, 0, vy, parent)
{
    this->setPixmap(image);
    this->setTransformOriginPoint(width() / 2, height() / 2);
    this->setRotation(180);
    mTimer = new QTimer();
    qDebug() << "New enemy x = " << this->x();
    //connect
    connect(mTimer, SIGNAL(timeout()), this, SLOT(move()));
    mTimer->start(TIMER_DELAY);
}

void Enemy::move()
{
    if(mGame->getState() == Game::State::PLAY)
    {
        if(bottom() >= Game::WINDOW_HEIGHT && !isBottomLineReached)
        {
            emit bottomLineReached();
            isBottomLineReached = true;
        }
        Entity::move();
    }    
}

void Enemy::destroy()
{
    //qDebug() << "Enemy has been destoyed";
    //disconnect(this, SIGNAL(bottomLineReached()), mGame, SLOT(decreaseHealth()));
    Entity::destroy();
}
