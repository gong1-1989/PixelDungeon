#ifndef GAMEINPUT_H
#define GAMEINPUT_H
//全局底层键盘输入管理器
#include <QKeyEvent>
#include <QSet>
#include <QMap>
class GameInput
{
public:
    //单例
    static GameInput& GetInstance();
    //帧开始清空瞬时状态
    void FrameClear();
    //键盘按下事件注入
    void OnKeyPress(int key);
    //键盘松开事件注入
    void OnKeyRelease(int key);
    //是否瞬时按下（仅按下那一帧生效）
    bool IsKeyDown(int key);
    //是否持续按下
    bool IsKeyHold(int key);
    // 是否瞬时松开
    bool IsKeyUp(int key);
private:
    GameInput()=default;
    QSet<int> m_holdKeys;
    QSet<int> m_downKeys;
    QSet<int> m_upKeys;
};
//游戏中常用按键宏定义
#define KEY_W       Qt::Key_W
#define KEY_S       Qt::Key_S
#define KEY_A       Qt::Key_A
#define KEY_D       Qt::Key_D
#define KEY_ESC     Qt::Key_Escape
#define KEY_SPACE   Qt::Key_Space
#define KEY_I       Qt::Key_I

#endif // GAMEINPUT_H
