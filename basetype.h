#ifndef BASETYPE_H
#define BASETYPE_H
//基础数据类型
#include <QPointF>
#include <QRectF>

//游戏场景状态枚举
enum class EventType{
    SwitchScene,
    GamePause,
    GameResume,
    SaveGame,
    LoadGame
};
//2D向量（封装Qt QpointF）
struct Vector2D
{
    qreal x=0.0;
    qreal y=0.0;
    Vector2D()=default;
    Vector2D(qreal x_,qreal y_):x(x_),y(y_){}
    Vector2D(const QPointF& p):x(p.x()),y(p.y()){}
    QPointF tiPointF()const{return QPointF(x,y);}
};
//AABB碰撞包围盒（封装Qt QRectF）
struct AABB
{
    Vector2D pos;
    qreal width=0.0;
    qreal height=0.0;
    AABB()=default;
    QRectF toRectF()const{
        return QRectF(pos.x,pos.y,width,height);
    }
    //AABB碰撞检测
    bool intersect(const AABB& other)const{
        return toRectF().intersects(other.toRectF());
    }
};

#endif // BASETYPE_H
