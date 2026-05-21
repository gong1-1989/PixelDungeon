#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QJsonObject globalCfg;
    qreal playerSpd=180.0;
    if(ConfigManager::GetInstance().LoadJson(":/Config/GameGlobal.json",globalCfg)){
        QJsonObject obj=globalCfg["Game"].toObject();
        int w=obj["WindowWidth"].toInt(1280);
        int h=obj["WindowHeight"].toInt(720);
        QString title=obj["Title"].toString("PixelDungeon");
        this->setWindowTitle(title);
        this->resize(w,h);
        playerSpd=obj["Physics"].toObject()["PlayerSpeed"].toInt(20);
    }
    PlayerEntity::GetInstance().Init(playerSpd);
    LevelData level;
    if(LoadLevel(":/Config/Level_01.json",level)){
        PlayerEntity::GetInstance().SetPos(level.playerStart);
        m_walls=level.walls;
    }
    GameTime::getInstance().Init();
    m_gameTimer=new QTimer(this);
    m_gameTimer->setInterval(16);
    connect(m_gameTimer,&QTimer::timeout,this,&MainWindow::GameFrameUpdate);
    m_gameTimer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GameFrameUpdate(){
    GameInput::GetInstance().FrameClear();
    GameTime::getInstance().Update();
    //后续所有物理、移动、渲染、逻辑全部在这里分层写入
    PlayerEntity::GetInstance().Update();
    if(CheckAndResolveCollision(PlayerEntity::GetInstance(),m_walls)) qDebug()<<"撞到墙体，无法通行";
   // qDebug()<<PlayerEntity::GetInstance().GetPos().x<<","<<PlayerEntity::GetInstance().GetPos().y;
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    GameInput::GetInstance().OnKeyPress(event->key());
    QMainWindow::keyPressEvent(event);
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    GameInput::GetInstance().OnKeyRelease(event->key());
    QMainWindow::keyReleaseEvent(event);
}
bool MainWindow::CheckAndResolveCollision(PlayerEntity &player, const QVector<AABB> &walls){
    bool collided=false;
    AABB playerBox=player.GetCollisionBox();
    for(const AABB&wall:walls){
        if(playerBox.intersect(wall)){
            collided=true;
            player.SetPos(player.GetPrevPos());
            break;
        }
    }
    return collided;
}
bool MainWindow::LoadLevel(const QString &path, LevelData &outLevel){
    QJsonObject root;
    if(!ConfigManager::GetInstance().LoadJson(path,root)){
        qWarning()<<"关卡配置加载失败"<<path;
        return false;
    }
    outLevel.levelName=root["levelName"].toString("未知关卡");
    QJsonObject startObj=root["playerStrat"].toObject();
    outLevel.playerStart.x=startObj["x"].toDouble(200.0);
    outLevel.playerStart.y=startObj["y"].toDouble(200.0);
    outLevel.walls.clear();
    QJsonArray tiles=root["tiles"].toArray();
    for(const QJsonValue& tileval:tiles){
        QJsonObject tileObj=tileval.toObject();
        if(tileObj["type"].toString()=="wall"){
            AABB wall;
            wall.pos.x=tileObj["x"].toDouble();
            wall.pos.y=tileObj["y"].toDouble();
            wall.width=tileObj["width"].toDouble();
            wall.height=tileObj["height"].toDouble();
            outLevel.walls.append(wall);
        }
    }
    qDebug()<<"成功加载关卡："<<outLevel.levelName<<",墙体数量："<<outLevel.walls.size()
             <<",玩家初始坐标："<<outLevel.playerStart.x<<"，"<<outLevel.playerStart.y;
    return true;
}