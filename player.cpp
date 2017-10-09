#include "player.hpp"
#include "game.hpp"
#include "bullet.hpp"
#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

Player::Player(Game *game, double x, double y, const QPixmap &image,
               double vx, QObject *parent):
    Entity(game, x,y,image,vx,0.f,parent)
{
    mBulletSound = new QMediaPlayer;
    mBulletSound->setMedia(QUrl("qrc:/sounds/bullet.wav"));
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
        mVelocity.setX(-fabs(mVelocity.x()));
        if(mGame->getState() == Game::State::PLAY &&
                left() >= fabs(mVelocity.x()))
            move();
        break;
    case Qt::Key_Right:
        mVelocity.setX(+fabs(mVelocity.x()));
        if(mGame->getState() == Game::State::PLAY &&
                right() <= this->scene()->width() - fabs(mVelocity.x()))
            move();
        break;
    case Qt::Key_F:
        if(mGame->getState() == Game::State::PLAY)
            fireBullet();
        break;
    case Qt::Key_N:
        mGame->prepareNewGame();
        break;
    case Qt::Key_Space:
        mGame->togglePause();
        break;
    default:
        break;
    }
}

void Player::fireBullet()
{
    if(mBulletSound->state() == QMediaPlayer::PlayingState)
        mBulletSound->setPosition(0);
    mBulletSound->play();
    QPixmap img(":/gfx/Bullet.png");
    Bullet *bullet = new Bullet(mGame, 0, 0, img, 0.f,
                                BULLET_VELOCITY);
    bullet->setPos(x() + (this->width() - bullet->width()) / 2, y() -
                          bullet->height() - 3);
    scene()->addItem(bullet);
}
