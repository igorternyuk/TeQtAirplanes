#include "game.hpp"
#include <QApplication>
#include <QDesktopWidget>
#include "player.hpp"
#include "bullet.hpp"
#include "enemy.hpp"

Game::Game()
{
    mScene = new QGraphicsScene();
    mView = new QGraphicsView(mScene);
    mView->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    mView->setWindowTitle(mWindowTitle);
    mScene->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mPlayer = new Player((WINDOW_WIDTH - PLAYER_WIDTH) / 2,
                         WINDOW_HEIGHT - PLAYER_HEIGHT,
                         PLAYER_WIDTH, PLAYER_HEIGHT,
                         PLAYER_VELOCITY);
    mPlayer->setFlag(QGraphicsItem::ItemIsFocusable);
    mPlayer->setFocus();
    mScene->addItem(mPlayer);
    mTimer = new QTimer();

    connect(mTimer, SIGNAL(timeout()), this, SLOT(createEnemy()));
    mTimer->start(ENEMY_TIMER_DELAY_MS);
}

void Game::run()
{
    //Centralize window
    centralizeView();
    mView->show();
}

void Game::createEnemy()
{
    Enemy *enemy = new Enemy(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_VELOCITY);
    mScene->addItem(enemy);
}

void Game::centralizeView()
{
    QRect myScreenGeometry = QApplication::desktop()->geometry() ;
    int dx = (myScreenGeometry.width() - mView->width()) / 2;
    int dy = (myScreenGeometry.height() - mView->height()) / 2;
    mView->move(dx, dy);
}
