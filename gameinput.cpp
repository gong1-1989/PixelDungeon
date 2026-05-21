#include "gameinput.h"

GameInput&GameInput::GetInstance() {
    static GameInput ins;
    return ins;
}
void GameInput::FrameClear(){
    m_downKeys.clear();
    m_upKeys.clear();
}
void GameInput::OnKeyPress(int key){
    if(!m_holdKeys.contains(key)){
        m_downKeys.insert(key);
    }
    m_holdKeys.insert(key);
}
void GameInput::OnKeyRelease(int key){
    m_upKeys.insert(key);
    m_holdKeys.remove(key);
}
bool GameInput::IsKeyDown(int key){
    return m_downKeys.contains(key);
}
bool GameInput::IsKeyHold(int key){
    return m_holdKeys.contains(key);
}
bool GameInput::IsKeyUp(int key){
    return m_upKeys.contains(key);
}