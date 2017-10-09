#pragma once

#include <QObject>
#include <QGraphicsRectItem>

class Game;

class Entity : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Entity(Game* game, double x, double y, double w, double h,
                    double vx, double vy, QObject *parent = nullptr);
    explicit Entity(Game *game, double x, double y, double w, double h,
                    QPointF velocity, QObject *parent = nullptr);
    inline auto left() const noexcept { return pos().x(); }
    inline auto top() const noexcept { return pos().y(); }
    inline auto right() const noexcept { return left() + rect().width(); }
    inline auto bottom() const noexcept { return top() + rect().height(); }
    inline auto width() const noexcept { return rect().width(); }
    inline auto height() const noexcept { return rect().height(); }
signals:
    void outOfSceneBounds();
public slots:
    virtual void move();
    virtual void destroy();
protected:
    Game* mGame;
    QPointF mVelocity;
};
