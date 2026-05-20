#include "MainWindow.h"
#include "configmanager.h"
#include "baseType.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool loadOk=ConfigManager::instance().loadConfig(":/Config/GameGlobal.json");
    if(!loadOk){
        qCritical()<<"全局配置加载失败，程序退出！";
        return -1;
    }
    //=========测试代码========
    //读取配置文件
    int fps=ConfigManager::instance().getValue<int>({"Game","FPS"},60);
    int w=ConfigManager::instance().getValue<int>({"Game","WindowWidth"},800);
    int h=ConfigManager::instance().getValue<int>({"Game","WindowHeight"},600);
    QString title=ConfigManager::instance().getValue<QString>({"Game","Title"},"PixelDungeon");
    qreal speed=ConfigManager::instance().getValue<qreal>({"Physics","PlayerSpeed"},2.5);
    qInfo()<<"FPS:"<<fps;
    qInfo()<<"窗口尺寸："<<w<<"×"<<h;
    qInfo()<<"玩家移动速度："<<speed;
    MainWindow win;
    win.setWindowTitle(title);
    win.resize(w,h);
    win.show();
    return a.exec();
}
