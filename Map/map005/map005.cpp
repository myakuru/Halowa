#include "map005.h"
#include "../../Constants.h"
#include "../../Scene.h"

C_map005::C_map005() :
    C_MapBase(50, 100)
{
}

C_map005::~C_map005()
{
}

void C_map005::InitMap()
{
    C_MapBase::InitMap();
}

void C_map005::DrawMap()
{
    // �X�N���[���͈̔͂��`
    float screenLeft = scrollX - (SCREEN_WIDTH / 2);
    float screenRight = scrollX + (SCREEN_WIDTH / 2);
    float screenTop = scrollY - (SCREEN_HEIGHT / 2);
    float screenBottom = scrollY + (SCREEN_HEIGHT / 2);

    // �}�b�v�f�[�^�̕`��
    Math::Rectangle rect;
    for (int h = 0; h < MapHeight; h++) {
        for (int w = 0; w < MapWidth; w++) {
            // �^�C���̈ʒu���v�Z
            float tileX = m_mapChip[h][w].pos.x;
            float tileY = m_mapChip[h][w].pos.y;

            if (m_mapChip[h][w].data != 'F' && m_mapChip[h][w].data != 'G' &&
                m_mapChip[h][w].data != 'J') {
                // �J�����O�����F�X�N���[���͈͓̔��ɂ��邩�ǂ������`�F�b�N
                if (tileX + 64 < screenLeft || tileX - 64 > screenRight ||
                    tileY + 64 < screenTop || tileY - 64 > screenBottom) {
                    continue; // �X�N���[���͈̔͊O�Ȃ�`�悵�Ȃ�
                }
            }

            switch (m_mapChip[h][w].data) {
            case '0':
                rect = { 0, 0, 0, 0 };
                break;
            case '1':
                rect = { 0, 370, 64, 64 };
                break;
            case '2':
                rect = { 64, 370, 64, 64 };
                break;
            case '3':
                rect = { 128, 370, 64, 64 };
                break;
            case '4':
                rect = { 192, 370, 64, 64 };
                break;
            case '5':
                rect = { 256, 370, 64, 64 };
                break;
            case '6':
                rect = { 256 + 64, 370, 64, 64 };
                break;
            case 'a':
                rect = { 0, 370 + 64, 64, 64 };
                break;
            case 'b':
                rect = { 64, 370 + 64, 64, 64 };
                break;
            case 'c':
                rect = { 128, 370 + 64, 64, 64 };
                break;
            case 'd':
                rect = { 192, 370 + 64, 64, 64 };
                break;
            case 'e':
                rect = { 256, 370 + 64, 64, 64 };
                break;
            case 'f':
                rect = { 256 + 64, 370 + 64, 64, 64 };
                break;
            case 'g':
                rect = { 0, 370 + 146, 64, 64 };
                break;
            case 'h':
                rect = { 64, 370 + 146, 64, 64 };
                break;
            case 'i':
                rect = { 128, 370 + 146, 64, 64 };
                break;
            case 'j':
                rect = { 192, 370 + 146, 64, 64 };
                break;
            case 'k':
                rect = { 256, 370 + 146, 64, 64 };
                break;
            case 'l':
                rect = { 256 + 64, 370 + 146, 64, 64 };
                break;
            case 'm':
                rect = { 1152, 512, 64, 64 };
                break;
            case 'n':
                rect = { 1282, 385, 64, 64 };
                break;
            case 'o':
                rect = { 1344, 385, 64, 64 };
                break;
            case 'p':
                rect = { 1218, 385 + 64, 64, 64 };
                break;
            case 'q':
                rect = { 1282, 385 + 64, 64, 64 };
                break;
            case 'r':
                rect = { 1346, 385 + 64, 64, 64 };
                break;
            case 's':  //�n�ʂ̒[�̕���
                rect = { 256 + 128, 370 + 64, 64, 64 };
                break;
            case 't':
                rect = { 256 + 192, 370 + 64, 64, 64 };
                break;
            case 'u':
                rect = { 256 + 128, 370 + 128, 64, 64 };
                break;
            case 'v':
                rect = { 256 + 190, 370 + 128, 64, 64 };
                break;
            case 'w':
                rect = { 1170,720, 64, 64 };
                break;
            case 'B':
                rect = { 448 - 64, 64, 64, 64 };
                break;
            case 'E':
                rect = { 199, 1600, 60, 64 };
                break;
            case 'D':
                rect = { 640, 1664, 64, 64 };
                break;
            case 'C':
                rect = { 640 + 64, 1664, 64, 64 };
                break;
            case 'F':
                rect = { 0, 1850, 640, 400 };
                break;
            case 'G':
                rect = { 700, 1860, 450, 400 };
                break;
            case 'H':
                rect = { 900, 1474, 124, 256 };
                break;
            case 'I':   //��
                rect = { 454, 1086, 56, 64 };
                break;
            case 'J':   //��_3
                rect = { 1024, 1310, 450, 560 };
            case 'W':
                rect = { 448, 64, 64, 64 };
                break;
            default:
                break;
            }
            SHADER.m_spriteShader.SetMatrix(m_mapChip[h][w].mat);
            SHADER.m_spriteShader.DrawTex(m_mapChipTex, rect, 1.0f);
        }
    }
}

void C_map005::ScrollUpdate()
{  // �X�N���[������
    C_Chara* chara = m_mOwner->GetChara();

    float targetScrollX = chara->GetPos().x;
    float targetScrollY = chara->GetPos().y;

    if (targetScrollX < scrollXMin) targetScrollX = scrollXMin;
    if (targetScrollX > scrollXMax) targetScrollX = scrollXMax;

    if (targetScrollY < scrollYMin) targetScrollY = scrollYMin;
    if (targetScrollY > scrollYMax) targetScrollY = scrollYMax;


    // x���W�̃X�N���[������
    scrollX += (targetScrollX - scrollX) * 0.1f; // ���X�ɃX�N���[��
    // y���W�̃X�N���[������
    scrollY += (targetScrollY - scrollY) * 0.1f; // ���X�ɃX�N���[��
}

void C_map005::DrawBackGround() const
{
    // �w�i�̕`��
    Math::Rectangle srcRect = { 0, 0, 1280, 720 };
    Math::Color color = { 1, 1, 1, 1 };
    // �e���C���[�̕`��
    for (int i = 4; i > 0; i--) {
        SHADER.m_spriteShader.SetMatrix(m_backgroundTransform[i].mat); // �s��Z�b�g
        for (float j = 0; j < 5; j += 2) {
            SHADER.m_spriteShader.DrawTex(m_backGroundTex + i, 640 * j, 0, &srcRect, &color);
        }
    }
}

void C_map005::UpdateBackGround()
{
    //==================�w�i�̍X�V===============================//

// �e���C���[�̃X�N���[�����x��ݒ�
    float scrollSpeeds[] = { 0.6f, 0.5f, 0.4f, 0.3f };

    for (int i = 0; i < 4; ++i) {
        m_backgroundTransform[i].transMat = Math::Matrix::CreateTranslation
        (m_backgroundTransform[i].pos.x - (scrollX * scrollSpeeds[i]) - 20, m_backgroundTransform[i].pos.y, 1);

        m_backgroundTransform[i].scaleMat = Math::Matrix::CreateScale(1, 1, 1);
        m_backgroundTransform[i].mat = m_backgroundTransform[i].scaleMat * m_backgroundTransform[i].transMat;
    }
}

void C_map005::StageMove()
{
    if (m_mOwner->GetChara()->GetPos().x > 5709 &&
        m_mOwner->GetChara()->GetPos().y < -1500
        && WarpFlg == false)
    {
        WarpFlg = true;
        m_mapBeforeFlg = true;
        m_mOwner->GetSceneChange()->Init_D(map004);
    }
}

void C_map005::StageGimmickUpdate()
{
    C_MapBase* map = m_mOwner->GetMap();
    C_Chara* player = m_mOwner->GetChara();

    static bool Once = false;

    if (player->GetPos().x < 700 && player->GetPos().y < -1950) {
        trapTrigger = true;
    }

    if (trapTrigger) {
        for (int w = 22; w < 23; w++) {
            for (int h = 32; h < 36; h++) {
                map->ChangeMapData(h, w, 'B');
            }
        }
        if (!Once) {
            enemyNum[0] = m_mOwner->GetEnemyMgr()->SpawnFrog(-400, -2000);
            enemyNum[1] = m_mOwner->GetEnemyMgr()->SpawnFrog(-300, -2000);
            enemyNum[2] = m_mOwner->GetEnemyMgr()->SpawnFrog(-200, -2000);
            enemyNum[3] = m_mOwner->GetEnemyMgr()->SpawnGremlin(-50, -2000);
            enemyNum[4] = m_mOwner->GetEnemyMgr()->SpawnGremlin(100, -2000);
            enemyNum[5] = m_mOwner->GetEnemyMgr()->SpawnGremlin(200, -2000);
            Once = true;
        }
    }
}
