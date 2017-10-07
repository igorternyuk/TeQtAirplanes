#pragma once

#include "entity.hpp"

class QTimer;

class Bullet : public Entity
{
public:
    explicit Bullet(double x, double y, double w, double h,
                    double vx, double vy, QObject *parent = nullptr);
public slots:
    virtual void move() override;
    virtual void destroy() override;
private:
    enum { TIMER_DELAY = 50 };
    QTimer *mTimer;
    bool hasCollisionWithEnemies();
};

