#pragma once

#include "entity.hpp"

class QTimer;
class Enemy : public Entity
{
    Q_OBJECT
public:
    explicit Enemy(Game* game, double w, double h, double vy,
                   QObject *parent = nullptr);
signals:
    void bottomLineReached();
public slots:
    virtual void move() override;
    virtual void destroy() override;
private:
    enum { TIMER_DELAY = 100 };
    QTimer *mTimer;
    bool isBottomLineReached{false};
};
