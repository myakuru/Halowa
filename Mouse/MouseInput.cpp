#include "MouseInput.h"
#include <Application/main.h>

bool C_MouseInput::GetMousePosition(POINT& mousePos)
{
    // マウスの現在の位置を取得
    GetCursorPos(&mousePos);

    // ウィンドウ座標をクライアント座標に変換
    ScreenToClient(APP.m_window.GetWndHandle(), &mousePos);

    return true;
}

bool C_MouseInput::IsLeftButtonPressed()
{
    return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
}
