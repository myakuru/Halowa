#include "Fog.h"
#include"../Scene.h"

C_Fog::C_Fog(Math::Vector2 pos, float width, float height)
{
    m_fogTex.Load("Texture/Gimic/Fog.png");
    m_fog1Tex.Load("Texture/Gimic/Fog2.png");
    m_stencilTex.Load("Texture/Gimic/stencil4.png");
    m_stencil2Tex.Load("Texture/Gimic/stencil_negate4.png");
    m_backTex.Load("Texture/Gimic/background2.png");

    //レンダーターゲット用テクスチャ
    m_tmpTex.CreateRenderTarget(1280, 720);
    tmpStencilTex.CreateRenderTarget(1280, 720);
    tmpLastTex.CreateRenderTarget(1280, 720);

    m_fog.pos = pos;
    FogWidth = width;
    FogHeight = height;

    Init();
}

C_Fog::~C_Fog()
{
    Release();
}

void C_Fog::Init()
{
    m_tmp.pos = { 0,0 };

    m_stencil.scaleX = 9.0f;
    m_stencil.scaleY = 9.0;

    fogHit = false;
    fogLeave = false;
    fogFull = false;

    m_currentFrame = -1;
    m_frameTime = 4;
    m_elapsedFrames = 0;

    m_fog.scaleX = 2.5f;
    m_fog.scaleY = 2.5f;

    m_transparent = 0.0f;

    frame = 0;
}

void C_Fog::Update()
{
    C_MapBase* map = m_owner->GetMap();
    C_Chara* chara = m_owner->GetChara();

    const int spriteSheetColumns = 8;
    const int spriteSheetRows = 8;
    const int totalFrames = spriteSheetColumns * spriteSheetRows;

    m_owner->GetGimicMgr()->GetGimicHit()->Fog_Player();

    if (fogHit && !fogLeave) {
        m_stencil.scaleX -= 0.1f;
        m_stencil.scaleY -= 0.1f;
        fogFull = true;
        if (m_stencil.scaleX < 1.3f) {
            m_stencil.scaleX = 1.3f;
        }
        if (m_stencil.scaleY < 1.3f) {
            m_stencil.scaleY = 1.3f;
        }
    }

    if (fogLeave) {
        m_stencil.scaleX += 0.1f;
        m_stencil.scaleY += 0.1f;
        if (m_stencil.scaleX > 9.0f) { m_stencil.scaleX = 9.0f, fogHit = false; }
        if (m_stencil.scaleY > 9.0f) { m_stencil.scaleY = 9.0f, fogHit = false; }
        if (fogFull) {
            m_transparent = 0.0f;
            fogFull = false;
        }
    }

    if (fogFull) {
        m_transparent += 0.005f;
        if (m_transparent > 0.6f) {
            m_transparent = 0.6f;
        }
    }

    C_EnemyMgr* enemy = m_owner->GetEnemyMgr();

    if (fogHit) {
        if (frame % 600 == 0) {
            randomValueX = (rand() % 2 == 0) ? 300 : -300;
            randomValueY = (rand() % 2 == 0) ? rand() % 580 : -(rand() % 580);
            enemy->SpawnGhost(randomValueX, randomValueY);
        }
        frame++;
    }

    m_stencil.pos = chara->GetPos();

    m_stencil.scaleMat = Math::Matrix::CreateScale(m_stencil.scaleX, m_stencil.scaleY, 1.0f);
    m_stencil.transMat = Math::Matrix::CreateTranslation(m_stencil.pos.x - map->GetScrollX(), m_stencil.pos.y - map->GetScrollY(), 1.0f);
    m_stencil.mat = m_stencil.scaleMat * m_stencil.transMat;

    m_tmp.mat = Math::Matrix::CreateTranslation(m_tmp.pos.x, m_tmp.pos.y, 1.0f);
}

void C_Fog::Draw()
{
    C_MapBase* map = m_owner->GetMap();

    //SHADER.m_spriteShader.DrawTex(&m_fog1Tex, 0, 0, &Math::Rectangle{ m_currentRow * 512, m_currentColumn * 512, 512, 512 }, &Math::Color(1.0f, 1.0f, 1.0f, 0.7f));
    //SHADER.m_spriteShader.DrawTex(&m_fogTex, 0, 0, &Math::Rectangle{ m_currentRow * 512, m_currentColumn *512, 512, 512 }, &Math::Color(1.0f, 1.0f, 1.0f, 0.7f));

    if (fogHit) {
        DynamicDraw();

        //描画先をバックバッファに切り替え
        D3D.SetBackBuffer();

        //ブレンド方法の切り替え　→　ステンシル
        D3D.SetBlendState(BlendMode::Stencil);

        //tmpTex描画
        SHADER.m_spriteShader.SetMatrix(m_tmp.mat);
        SHADER.m_spriteShader.DrawTex(&m_tmpTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

        D3D.SetBlendState(BlendMode::Add);

        SHADER.m_spriteShader.SetMatrix(m_tmp.mat);
        SHADER.m_spriteShader.DrawTex(&tmpLastTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
        D3D.SetBlendState(BlendMode::Alpha);
    }
    //SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
    //SHADER.m_spriteShader.DrawBox(m_fog.pos.x - map->GetScrollX(), m_fog.pos.y - map->GetScrollY(), FogWidth, FogHeight, &Math::Color(1, 0, 0, 0.3f));
}

void C_Fog::DynamicDraw()
{
    if (fogHit) {
        D3D.SetBlendState(BlendMode::Alpha);

        //// 描画先のテクスチャを黒でクリア
        m_tmpTex.ClearRenerTarget(Math::Color(0.0f, 0.0f, 0.0f, 1.0f));

        m_tmpTex.SetRenderTarget();

        SHADER.m_spriteShader.SetMatrix(m_stencil.mat);
        SHADER.m_spriteShader.DrawTex(&m_stencilTex, Math::Rectangle(0, 0, 512*2, 512), 1.0f);


        // 描画先のテクスチャを白でクリア
        tmpStencilTex.ClearRenerTarget(Math::Color(1.0f, 1.0f, 1.0f, 1.0f));

        tmpStencilTex.SetRenderTarget();

        D3D.SetBlendState(BlendMode::Alpha);

        SHADER.m_spriteShader.SetMatrix(m_stencil.mat);
        SHADER.m_spriteShader.DrawTex(&m_stencil2Tex, Math::Rectangle(0, 0, 512*2, 512), 1.0f);

        //// 描画先のテクスチャを透明でクリア
        tmpLastTex.ClearRenerTarget(Math::Color(0.0f, 0.0f, 0.0f, 0.0f));

        //// 描画先をtmpStencilTexへ切り替え
        tmpLastTex.SetRenderTarget();

        // 背景
        SHADER.m_spriteShader.SetMatrix(m_tmp.mat);
        SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);

        D3D.SetBlendState(BlendMode::Stencil);

        SHADER.m_spriteShader.SetMatrix(m_tmp.mat);
        SHADER.m_spriteShader.DrawTex(&tmpStencilTex, Math::Rectangle(0, 0, 1280, 720), 1.0f);
    }
}

void C_Fog::DynamicPlayerDraw()
{
    SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
    SHADER.m_spriteShader.DrawBox(0, 0, 1280, 720, &Math::Color(1.0f, 1.0f, 1.0f, m_transparent));
}

void C_Fog::Release()
{
    m_fogTex.Release();
    m_fog1Tex.Release();
    m_stencilTex.Release();
    m_stencil2Tex.Release();
    m_backTex.Release();
    tmpStencilTex.Release();
    tmpLastTex.Release();
    m_tmpTex.Release();
}