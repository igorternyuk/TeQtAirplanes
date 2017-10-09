#pragma once

#include "entity.hpp"
#include <QMediaPlayer>

class QTimer;

class Bullet : public Entity
{
public:
    explicit Bullet(Game *game, double x, double y, const QPixmap& image,
                    double vx, double vy, QObject *parent = nullptr);
public slots:
    virtual void move() override;
    virtual void destroy() override;
private:
    enum { TIMER_DELAY = 50 };
    QTimer *mTimer;
    QMediaPlayer *mExplosionSound;
    bool hasCollisionWithEnemies();
};

