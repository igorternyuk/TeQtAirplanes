#pragma once

#include "entity.hpp"

class QTimer;
class Enemy : public Entity
{
public:
    explicit Enemy(double w, double h, double vy, QObject *parent = nullptr);
public slots:
    virtual void destroy() override;
private:
    enum { TIMER_DELAY = 100 };
    QTimer *mTimer;
};
