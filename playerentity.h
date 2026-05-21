#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H
#include "gamebase.h"
#include "gametime.h"
#include "gameinput.h"

//玩家固定属性（不可升级，后续仅靠装备加成）
struct PlayerBaseAttr{
    qreal maxHp=100.0;
    qreal attack=10.0;
    qreal defense=5.0;
};

class PlayerEntity
{
public:
    static PlayerEntity& GetInstance();
    void Init(qreal moveSpeed);
    void Update();
    Vector2D GetPos()const;
    Vector2D GetPrevPos()const;
    void SetPos(const Vector2D& pos);
    PlayerBaseAttr& getBaseAttr();
    PlayerEntity()=default;
    Vector2D m_pos;
    Vector2D m_prevPos;
    qreal m_moveSpeed=180.0;
    PlayerBaseAttr m_baseAttr;
    AABB GetCollisionBox()const;
    qreal m_size=32.0;
};

#endif // PLAYERENTITY_H
