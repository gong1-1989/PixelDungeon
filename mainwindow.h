#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include "GameTime.h"
#include "GameBase.h"
#include "gameinput.h"
#include "configmanager.h"
#include "playerentity.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void keyPressEvent(QKeyEvent *event)override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void GameFrameUpdate();
private:
    Ui::MainWindow *ui;
    QTimer* m_gameTimer=nullptr;
    GameState m_currState=GameState::MainMenu;
    QVector<AABB> m_walls;
    bool CheckAndResolveCollision(PlayerEntity& player,const QVector<AABB>&walls);
    bool LoadLevel(const QString& path,LevelData& outLevel);
};

#endif // MAINWINDOW_H
