#pragma once

#include "entity.hpp"
#include <QKeyEvent>

class Player : public Entity
{
public:
    explicit Player(double x, double y, double w, double h,
                    double vx, QObject *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    enum
    {
        BULLET_WIDTH = 10,
        BULLET_HEIGHT = 5 * BULLET_WIDTH,
        BULLET_VELOCITY = -10
    };
    void fireBullet();
};

