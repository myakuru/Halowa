#include "MouseInput.h"
#include <Application/main.h>

bool C_MouseInput::GetMousePosition(POINT& mousePos)
{
    // �}�E�X�̌��݂̈ʒu���擾
    GetCursorPos(&mousePos);

    // �E�B���h�E���W���N���C�A���g���W�ɕϊ�
    ScreenToClient(APP.m_window.GetWndHandle(), &mousePos);

    return true;
}

bool C_MouseInput::IsLeftButtonPressed()
{
    return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
}
