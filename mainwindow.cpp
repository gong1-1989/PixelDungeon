#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "baseType.h"
#include "configmanager.h"
#include "eventbus.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool loadOk = ConfigManager::instance().loadConfig(":/Config/GameGlobal.json");
    if (!loadOk) {
        qCritical() << "全局配置加载失败，程序退出！";
    }
    //=========测试代码========
    //读取配置文件
    int fps = ConfigManager::instance().getValue<int>({"Game", "FPS"}, 60);
    int w = ConfigManager::instance().getValue<int>({"Game", "WindowWidth"}, 800);
    int h = ConfigManager::instance().getValue<int>({"Game", "WindowHeight"}, 600);
    QString title = ConfigManager::instance().getValue<QString>({"Game", "Title"}, "PixelDungeon");
    qreal speed = ConfigManager::instance().getValue<qreal>({"Physics", "PlayerSpeed"}, 2.5);
    qInfo() << "FPS:" << fps;
    qInfo() << "窗口尺寸：" << w << "×" << h;
    qInfo() << "玩家移动速度：" << speed;
    this->setWindowTitle(title);
    this->resize(w,h);
    //========测试暂停拦截========
    connect(&EventBus::instance(),&EventBus::instance().onGameEvent,[](const GameEvent& e){
        if(e.type==GameEventType::Event_ChangeGameState){
            GameState state=e.data.value<GameState>();
            qInfo()<<"场景切换至："<<static_cast<int>(state);
        }
    });
    //发送场景切换事件（从主菜单进入游戏）
    EventBus::instance().sendEvent(GameEvent(GameEventType::Event_ChangeGameState,QVariant::fromValue(GameState::InGame)));
    EventBus::instance().setPause(false);
    //====================================
}

MainWindow::~MainWindow()
{
    delete ui;
}
