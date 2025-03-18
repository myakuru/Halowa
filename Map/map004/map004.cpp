#include "map004.h"
#include "../../Constants.h"
#include "../../Scene.h"

C_map004::C_map004():
	C_MapBase(50, 100)
{
}

C_map004::~C_map004()
{
}

void C_map004::InitMap()
{
	C_MapBase::InitMap();
}

void C_map004::DrawMap()
{
    // スクリーンの範囲を定義
    float screenLeft = scrollX - (SCREEN_WIDTH / 2);
    float screenRight = scrollX + (SCREEN_WIDTH / 2);
    float screenTop = scrollY - (SCREEN_HEIGHT / 2);
    float screenBottom = scrollY + (SCREEN_HEIGHT / 2);

    // マップデータの描画
    Math::Rectangle rect;
    for (int h = 0; h < MapHeight; h++) {
        for (int w = 0; w < MapWidth; w++) {
            // タイルの位置を計算
            float tileX = m_mapChip[h][w].pos.x;
            float tileY = m_mapChip[h][w].pos.y;

            if (m_mapChip[h][w].data != 'F' && m_mapChip[h][w].data != 'G' &&
                m_mapChip[h][w].data != 'J') {
                // カリング処理：スクリーンの範囲内にあるかどうかをチェック
                if (tileX + 64 < screenLeft || tileX - 64 > screenRight ||
                    tileY + 64 < screenTop || tileY - 64 > screenBottom) {
                    continue; // スクリーンの範囲外なら描画しない
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
                //一段浮遊ブロック=======================
            case 'n':
                rect = { 897, 513, 64, 64 };
                break;
            case 'o':
                rect = { 897 + 64, 513, 64, 64 };
                break;
            case 'p':
                rect = { 897 + 128, 513, 64, 64 };
                break;
            case 'q':
                rect = { 897 + 192, 513, 64, 64 };
                break;
                //地中ブロック==========================
            case 'r':
                rect = { 1217 + 1,385, 64, 64 };
                break;
            case 's':
                rect = { 1217 + 64,385, 64, 64 };
                break;
            case 't':
                rect = { 1217 + 128 - 1,385, 64, 64 };
                break;
            case 'u':
                rect = { 1217,385 + 64, 64, 64 };
                break;
            case 'v':
                rect = { 1217 + 64,385 + 64, 64, 64 };
                break;
            case 'w':
                rect = { 1217 + 128,385 + 64, 64, 64 };
                break;
                //地中空白=============================
            case 'x':
                rect = { 1225,750,64,64 };
                break;
                //======================================
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
            case 'I':   //花
                rect = { 454, 1086, 56, 64 };
                break;
            case 'J':   //家_3
                rect = { 1024, 1310, 450, 560 };
            case 'W':
                rect = { 448, 64, 64, 64 };
                break;
                break;
            default:
                break;
            }
            SHADER.m_spriteShader.SetMatrix(m_mapChip[h][w].mat);
            SHADER.m_spriteShader.DrawTex(m_mapChipTex, rect, 1.0f);
        }
    }
}

void C_map004::ScrollUpdate()
{
    // スクロール処理
    C_Chara* chara = m_mOwner->GetChara();

    float targetScrollX = chara->GetPos().x;
    float targetScrollY = chara->GetPos().y;

    if (targetScrollX < scrollXMin) targetScrollX = scrollXMin;
    if (targetScrollX > scrollXMax) targetScrollX = scrollXMax;

    if (targetScrollY < scrollYMin) targetScrollY = scrollYMin;
    if (targetScrollY > scrollYMax) targetScrollY = scrollYMax;


    // x座標のスクロール処理
    scrollX += (targetScrollX - scrollX) * 0.1f; // 徐々にスクロール
    // y座標のスクロール処理
    scrollY += (targetScrollY - scrollY) * 0.1f; // 徐々にスクロール
}

void C_map004::DrawBackGround() const
{
    // 背景の描画
    Math::Rectangle srcRect = { 0, 0, 1280, 720 };
    Math::Color color = { 1, 1, 1, 1 };
    // 各レイヤーの描画
    for (int i = 4; i > 0; i--) {
        SHADER.m_spriteShader.SetMatrix(m_backgroundTransform[i].mat); // 行列セット
        for (float j = 0; j < 5; j += 2) {
            SHADER.m_spriteShader.DrawTex(m_backGroundTex + i, 640 * j, 0, &srcRect, &color);
        }
    }
}

void C_map004::UpdateBackGround()
{
    //==================背景の更新===============================//

// 各レイヤーのスクロール速度を設定
    float scrollSpeeds[] = { 0.6f, 0.5f, 0.4f, 0.3f };

    for (int i = 0; i < 4; ++i) {
        m_backgroundTransform[i].transMat = Math::Matrix::CreateTranslation
        (m_backgroundTransform[i].pos.x - (scrollX * scrollSpeeds[i]) - 20, m_backgroundTransform[i].pos.y, 1);

        m_backgroundTransform[i].scaleMat = Math::Matrix::CreateScale(1, 1, 1);
        m_backgroundTransform[i].mat = m_backgroundTransform[i].scaleMat * m_backgroundTransform[i].transMat;
    }
}

void C_map004::StageMove()
{
    if (m_mOwner->GetChara()->GetPos().x > 2814 && m_mOwner->GetChara()->GetPos().x < 3266 &&
        m_mOwner->GetChara()->GetPos().y < -2900
        && WarpFlg == false)
    {
        WarpFlg = true;
		m_mapBeforeFlg = true;
        m_mOwner->GetSceneChange()->Init_D(map003);
    }

    if (m_mOwner->GetChara()->GetPos().x < 2701 && m_mOwner->GetChara()->GetPos().y > -188 &&
        m_mOwner->GetChara()->GetPos().y < 200
        && WarpFlg == false)
    {
        WarpFlg = true;
		m_mapNextFlg = true;
        m_mOwner->GetSceneChange()->Init_L(map005);
    }

}

void C_map004::EnemyPos1()
{
    C_EnemyMgr* enemy = m_mOwner->GetEnemyMgr();
    enemy->SpawnFrog(4292, -2236);
    enemy->SpawnFrog(3722, -1852);
    enemy->SpawnRobot(3946, -1852);
    enemy->SpawnRobot(4086, -1852);
}
