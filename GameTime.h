#ifndef GAMETIME_H
#define GAMETIME_H
//全局统一时间管理器【禁止插件化】
#include <qelapsedtimer.h>
#include "GameBase.h"
class GameTime{
public:
    static GameTime& getInstance(){
        static GameTime ins;
        return ins;
    }
    void Init(){
        m_timer.start();
        m_lastTime=0;
    }
    void Update(){
        qint64 now=m_timer.elapsed();
        m_deltaTime=(now-m_lastTime)/1000.0;
        m_lastTime=now;
    }
qreal GetDeltaTime()const{
    return m_deltaTime;
    }

private:
    GameTime()=default;
    QElapsedTimer m_timer;
    qint64 m_lastTime=0;
    qreal m_deltaTime=0.0f;
};

#endif // GAMETIME_H
