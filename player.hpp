#pragma once

#include "entity.hpp"
#include <QKeyEvent>

class Game;

class Player : public Entity
{
public:
    explicit Player(Game* game, double x, double y, double w, double h,
                    double vx, QObject *parent = nullptr);
protected:
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    enum
    {
        BULLET_WIDTH = 10,
        BULLET_HEIGHT = 5 * BULLET_WIDTH,
        BULLET_VELOCITY = -20
    };
    void fireBullet();
};

