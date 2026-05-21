#ifndef EVENTBUS_H
#define EVENTBUS_H
//极简全局事件总线
#include <functional>
#include <QMap>
#include <QVector>
//自定义事件ID
enum GameEventID{
    EVENT_SWITCH_SCENE,     //切换场景
    EVENT_GAME_PAUSE,       //游戏暂停
    EVENT_GAME_RESUME       //游戏继续
};
using EventFunc=std::function<void(void*)>;
class EventBus{
public:
    static EventBus&GetInstance(){
        static EventBus ins;
        return ins;
    }
    void Register(int eventId,EventFunc func){
        m_eventMap[eventId].push_back(func);
    }
    void Dispatch(int eventId,void* param=nullptr){
        if(!m_eventMap.contains(eventId)) return;
        for(auto& f:m_eventMap[eventId]){
            f(param);
        }
    }

private:
    EventBus()=default;
    QMap<int,QVector<EventFunc>> m_eventMap;
};

#endif // EVENTBUS_H
