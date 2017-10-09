#include "game.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QTimer>
#include <QImage>
#include <QDebug>
#include <QMediaPlayer>
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
    mScene->setBackgroundBrush(QBrush(QImage(":/gfx/background.png")));
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QPixmap img(":/gfx/player.png");
    mPlayer = new Player(this, (WINDOW_WIDTH - PLAYER_WIDTH) / 2,
                         WINDOW_HEIGHT - img.height(),
                         img, PLAYER_VELOCITY, mView);
    mPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
    mPlayer->setFocus();
    mScene->addItem(mPlayer);

    mScore = new TextItem<int>(QString("SCORE"), 0, 0, 0, QFont("times", 16),
                               Qt::darkGreen);
    mHealth = new TextItem<int>(QString("HEALTH"), PLAYER_HEALTH, 0, 25,
                                QFont("times", 16), Qt::darkRed);
    mStatusLabel = new QGraphicsTextItem;
    mStatusLabel->setFont(QFont("times", 80));
    mStatusLabel->setDefaultTextColor(Qt::transparent);
    mStatusLabel->setPlainText(QString(""));
    mStatusLabel->setPos((WINDOW_WIDTH - mStatusLabel->boundingRect().width()) / 2,
                         (WINDOW_HEIGHT - mStatusLabel->boundingRect().height()) / 2);

    mScene->addItem(mScore);
    mScene->addItem(mHealth);
    mScene->addItem(mStatusLabel);

    mTimer = new QTimer();
    connect(mTimer, SIGNAL(timeout()), this, SLOT(createEnemy()));
    mTimer->start(ENEMY_TIMER_DELAY_MS);

    mPlaylist = new QMediaPlaylist;
    mPlaylist->addMedia(QUrl("qrc:/sounds/bgm.ogg"));
    mPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    mBGM = new QMediaPlayer;
    mBGM->setPlaylist(mPlaylist);
    mBGM->setVolume(70);
    mBGM->play();

    connect(this, SIGNAL(healthChanged()), this, SLOT(updateStatus()));
}

void Game::run()
{
    //Centralize window
    centralizeView();
    mView->show();
}

void Game::increaseScore()
{
    mScore->increase(1);
    emit scoreChanged();
}

void Game::decreaseHealth()
{
    mHealth->decrease(1);
    emit healthChanged();
}

void Game::prepareNewGame()
{
    QList<QGraphicsItem*> items = mScene->items();
    for(auto &e: items)
        if(typeid(*e) == typeid(Enemy))
            delete e;
    mStatusLabel->setPlainText("");
    mStatusLabel->setDefaultTextColor(Qt::transparent);
    mState = State::PLAY;
    mScore->set(0);
    mHealth->set(PLAYER_HEALTH);
    mTimer->start(ENEMY_TIMER_DELAY_MS);
}

void Game::togglePause()
{
    if(mState == State::PLAY)
    {
        mState = State::PAUSE;
        mStatusLabel->setPlainText("PAUSE");
        mStatusLabel->setDefaultTextColor(Qt::darkGreen);
        mTimer->stop();
        mBGM->pause();
        mStatusLabel->setPos((WINDOW_WIDTH - mStatusLabel->boundingRect()
                              .width()) / 2,
                             (WINDOW_HEIGHT - mStatusLabel->boundingRect()
                              .height()) / 2);
    }
    else if(mState == State::PAUSE)
    {
        mStatusLabel->setPlainText("");
        mStatusLabel->setDefaultTextColor(Qt::transparent);
        mState = State::PLAY;
        mTimer->start(ENEMY_TIMER_DELAY_MS);
        mBGM->play();
        mStatusLabel->setPos((WINDOW_WIDTH - mStatusLabel->boundingRect()
                              .width()) / 2,
                             (WINDOW_HEIGHT - mStatusLabel->boundingRect()
                              .height()) / 2);
    }
}

void Game::updateStatus()
{
    if(mHealth->getValue() <= 0)
    {
        mState = State::GAME_OVER;
        mTimer->stop();
        mStatusLabel->setPlainText("GAME OVER");
        mStatusLabel->setDefaultTextColor(Qt::red);
        mStatusLabel->setPos((WINDOW_WIDTH - mStatusLabel->boundingRect()
                              .width()) / 2,
                             (WINDOW_HEIGHT - mStatusLabel->boundingRect()
                              .height()) / 2);
    }
}

void Game::createEnemy()
{
    QPixmap img(":/gfx/enemy.png");
    Enemy *enemy = new Enemy(this, img, PLAYER_VELOCITY);
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
