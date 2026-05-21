#include "playerentity.h"

PlayerEntity& PlayerEntity::GetInstance() {
    static PlayerEntity ins;
    return ins;
}
void PlayerEntity::Init(qreal moveSpeed){
    m_moveSpeed=moveSpeed;
    m_pos=Vector2D(100,100);
    m_baseAttr.maxHp=100;
    m_baseAttr.attack=10;
    m_baseAttr.defense=5;
}
void PlayerEntity::Update(){
    qreal dt=GameTime::getInstance().GetDeltaTime();
    Vector2D dir(0,0);
    if(GameInput::GetInstance().IsKeyHold(KEY_W)) dir.y=-1;
    if(GameInput::GetInstance().IsKeyHold(KEY_S)) dir.y=1;
    if(GameInput::GetInstance().IsKeyHold(KEY_A)) dir.x=-1;
    if(GameInput::GetInstance().IsKeyHold(KEY_D)) dir.x=1;
    //归一化，防止斜向加速
    qreal len=qSqrt(dir.x*dir.x+dir.y*dir.y);
    if(len>0){
        dir.x/=len;
        dir.y/=len;
    }
    m_prevPos=m_pos;
    m_pos.x+=dir.x*m_moveSpeed*dt;
    m_pos.y+=dir.y*m_moveSpeed*dt;
}
Vector2D PlayerEntity::GetPos()const{
    return m_pos;
}
Vector2D PlayerEntity::GetPrevPos()const{
    return m_prevPos;
}
void PlayerEntity::SetPos(const Vector2D &pos){
    m_pos=pos;
    m_prevPos=pos;
}
PlayerBaseAttr& PlayerEntity::getBaseAttr(){
    return m_baseAttr;
}
AABB PlayerEntity::GetCollisionBox()const{
    AABB box;
    box.pos.x=m_pos.x-m_size/2.0;
    box.pos.y=m_pos.y-m_size/2.0;
    box.width=m_size;
    box.height=m_size;
    return box;
}
