#pragma once

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>

class Game;

class Entity : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Entity(Game* game, double x, double y, const QPixmap &image,
                    double vx, double vy, QObject *parent = nullptr);
    explicit Entity(Game *game, double x, double y, const QPixmap &image,
                    QPointF velocity, QObject *parent = nullptr);
    inline auto left() const noexcept { return pos().x(); }
    inline auto top() const noexcept { return pos().y(); }
    inline auto right() const noexcept { return left() + boundingRect().width(); }
    inline auto bottom() const noexcept { return top() + boundingRect().height(); }
    inline auto width() const noexcept { return boundingRect().width(); }
    inline auto height() const noexcept { return boundingRect().height(); }
signals:
    void outOfSceneBounds();
public slots:
    virtual void move();
    virtual void destroy();
protected:
    Game* mGame;
    QPointF mVelocity;
};
