#include "game.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QTimer>
#include <QDebug>
//#include <QMediaPlayer>
#include "player.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "texItem.hpp"

Game::Game()
{
    mScene = new QGraphicsScene(this);
    //mScene->setBackgroundBrush(QBrush(Qt::cyan));
    mView = new QGraphicsView(mScene);
    mView->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    mView->setWindowTitle(mWindowTitle);
    mScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mPlayer = new Player(this, (WINDOW_WIDTH - PLAYER_WIDTH) / 2,
                         WINDOW_HEIGHT - PLAYER_HEIGHT,
                         PLAYER_WIDTH, PLAYER_HEIGHT,
                         PLAYER_VELOCITY, mView);
    mPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
    mPlayer->setFocus();
    mScene->addItem(mPlayer);

    mScore = new TextItem<int>(QString("SCORE"), 0, 0, 0, Qt::darkGreen);
    mHealth = new TextItem<int>(QString("HEALTH"), PLAYER_HEALTH, 0, 25,
                                Qt::darkRed);
    mScene->addItem(mScore);
    mScene->addItem(mHealth);

    loadSounds();

    mTimer = new QTimer();
    connect(mTimer, SIGNAL(timeout()), this, SLOT(createEnemy()));
    mTimer->start(ENEMY_TIMER_DELAY_MS);
    mBGM.play();
}

void Game::run()
{
    //Centralize window
    centralizeView();
    mView->show();
}

void Game::playSound(Game::SoundID id)
{
    qDebug() << "Boom!!!";
    mSounds[id].play();
}

void Game::increaseScore()
{
    mScore->increase(1);
}

void Game::decreaseHealth()
{
    mHealth->decrease(1);
}

void Game::createEnemy()
{
    Enemy *enemy = new Enemy(this, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_VELOCITY);
    connect(enemy, SIGNAL(bottomLineReached()), this, SLOT(decreaseHealth()));
    mScene->addItem(enemy);
}

void Game::centralizeView()
{
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int dx = (myScreenGeometry.width() - mView->width()) / 2;
    int dy = (myScreenGeometry.height() - mView->height()) / 2;
    mView->move(dx, dy);
}

void Game::loadSounds()
{
    mBGM.openFromFile("resources/sounds/bgm.ogg");
    mBGM.setLoop(true);
    mSoundManager.load(SoundID::FIRE_BULLET, "resources/sounds/bullet.wav");
    sf::Sound sBullet(mSoundManager.get(SoundID::FIRE_BULLET));
    mSounds.insert(std::make_pair(SoundID::FIRE_BULLET, sBullet));

    mSoundManager.load(SoundID::EXPLOSION, "resources/sounds/Explosion_02.wav");
    sf::Sound sExplosion(mSoundManager.get(SoundID::EXPLOSION));
    mSounds.insert(std::make_pair(SoundID::EXPLOSION, sExplosion));
}
