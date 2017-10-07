#pragma once
#include "enemy.hpp"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QString>

class Player;

class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game();
    void run();
private slots:
    void createEnemy();
private:
    enum
    {
        WINDOW_WIDTH = 800,
        WINDOW_HEIGHT = 600,
        PLAYER_WIDTH = 100,
        PLAYER_HEIGHT = 100,
        PLAYER_VELOCITY = 10,
        ENEMY_TIMER_DELAY_MS = 2000
    };
    const QString mWindowTitle{"TeQtAirplanes"};
    QGraphicsScene *mScene;
    QGraphicsView *mView;
    Player *mPlayer;
    QTimer *mTimer;
    void centralizeView();
};
