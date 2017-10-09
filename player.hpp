#pragma once

#include "entity.hpp"
#include <QKeyEvent>
#include <QMediaPlayer>

class Game;

class Player : public Entity
{
public:
    explicit Player(Game *game, double x, double y, const QPixmap &image,
                    double vx, QObject *parent = nullptr);
protected:
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    enum { BULLET_VELOCITY = -30 };
    QMediaPlayer* mBulletSound;
    void fireBullet();
};

