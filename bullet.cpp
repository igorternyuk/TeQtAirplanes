#include "bullet.hpp"
#include "game.hpp"
#include "enemy.hpp"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <typeinfo>
#include <QDebug>

Bullet::Bullet(Game* game, double x, double y, const QPixmap &image,
               double vx, double vy, QObject *parent):
    Entity(game, x, y, image, vx, vy, parent)
{
    mExplosionSound = new QMediaPlayer;
    mExplosionSound->setMedia(QUrl("qrc:/sounds/Explosion.wav"));
    mTimer = new QTimer();
    //connect
    connect(mTimer, SIGNAL(timeout()), this, SLOT(move()));
    mTimer->start(TIMER_DELAY);
}

void Bullet::move()
{
    if((mGame->getState() == Game::State::PLAY) &&
            !hasCollisionWithEnemies())
        Entity::move();
}

void Bullet::destroy()
{
    //qDebug() << "Bullet has been destroyed";
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
            if(typeid(*e) == typeid(Enemy))
            {
                mGame->increaseScore();
                if(mExplosionSound->state() == QMediaPlayer::PlayingState)
                    mExplosionSound->setPosition(0);
                mExplosionSound->play();
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
