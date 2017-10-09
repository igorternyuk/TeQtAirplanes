#pragma once

#include <QObject>
#include <QString>
#include "texItem.hpp"
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Player;
class Score;
class QTimer;
class QGraphicsScene;
class QGraphicsView;

class Game: public QObject
{
    Q_OBJECT
public:
    enum
    {
        WINDOW_WIDTH = 800,
        WINDOW_HEIGHT = 600
    };
    enum class State
    {
        PLAY,
        PAUSE,
        GAME_OVER
    };

    enum class SoundID
    {
        FIRE_BULLET,
        EXPLOSION
    };
    explicit Game();
    void run();
    inline auto getState() const noexcept { return mState; }
signals:
    void scoreChanged();
    void healthChanged();
public slots:
    void increaseScore();
    void decreaseHealth();
    void prepareNewGame();
    void togglePause();
    void updateStatus();

private slots:
    void createEnemy();

private:
    enum
    {
        PLAYER_WIDTH = 100,
        PLAYER_HEIGHT = 100,
        PLAYER_VELOCITY = 10,
        PLAYER_HEALTH = 3,
        ENEMY_TIMER_DELAY_MS = 2000
    };

    const QString mWindowTitle{"TeQtAirplanes"};
    State mState{State::PLAY};
    QGraphicsScene *mScene;
    QGraphicsView *mView;
    Player *mPlayer;
    TextItem<int> *mScore;
    TextItem<int> *mHealth;
    QGraphicsTextItem *mStatusLabel;
    QTimer *mTimer;
    QMediaPlaylist *mPlaylist;
    QMediaPlayer *mBGM;

    void centralizeView();
};
