#pragma once

#include <QObject>
#include <QString>
#include "texItem.hpp"
#include <SFML/Audio.hpp>
#include "ResourceManager.hpp"
#include <map>

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
    enum class SoundID
    {
        FIRE_BULLET,
        EXPLOSION
    };
    explicit Game();
    void run();
    void playSound(SoundID id);

public slots:
    void increaseScore();
    void decreaseHealth();

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
    QGraphicsScene *mScene;
    QGraphicsView *mView;
    Player *mPlayer;
    TextItem<int> *mScore;
    TextItem<int> *mHealth;
    QTimer *mTimer;
    sf::Music mBGM;
    ResourceManager<SoundID, sf::SoundBuffer> mSoundManager;
    std::map<SoundID, sf::Sound> mSounds;
    void centralizeView();
    void loadSounds();
};
