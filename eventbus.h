#ifndef EVENTBUS_H
#define EVENTBUS_H
//事件总线
#include <QObject>
#include <QVariant>
#include "basetype.h"

enum class GameEventType{
    //场景控制
    Event_ChangeGameState,
    Event_PauseGame,
    Event_ResumeGame,
    //游戏逻辑
    Event_LoadLevel,
    Event_PlayerMove,
    Event_OpenBag,
    Event_SaveGame,
    Event_LoadSave
};

//通用事件结构体
struct  GameEvent
{
    GameEventType type;
    QVariant data;
    GameEvent(GameEventType t,QVariant d={}) :type(t),data(d) {}
};
//事件总线：单例+Qt信号槽
class EventBus: public QObject
{
    Q_OBJECT
public:
    static EventBus& instance();
    //发送事件
    void sendEvent(const GameEvent& event);
    //全局暂停开关
    void setPause(bool pause);
    bool isPaused()const;
signals:
    //事件广播信号
    void onGameEvent(const GameEvent&state);
private:
    explicit EventBus(QObject *parent=nullptr);
    ~EventBus() override=default;
    EventBus(const EventBus&)=delete;
    EventBus& operator =(const EventBus&)=delete;
    bool m_isPaused=false;
};

#endif // EVENTBUS_H
