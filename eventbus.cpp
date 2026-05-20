#include "eventbus.h"
#include <QDebug>
EventBus&EventBus::instance(){
    static EventBus ins;
    return ins;
}

EventBus::EventBus(QObject *parent) :QObject(parent) {}
void EventBus::sendEvent(const GameEvent &event){
    //暂停时，仅允许暂停/恢复事件通过
    if(m_isPaused){
        if(event.type!=GameEventType::Event_PauseGame&&event.type!=GameEventType::Event_ResumeGame) return;
    }
    emit onGameEvent(event);
    qDebug()<<"发送事件："<<static_cast<int>(event.type);
}
void EventBus::setPause(bool pause){
    m_isPaused=pause;
}
bool EventBus::isPaused()const{
    return m_isPaused;
}