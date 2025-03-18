#include "BRButton.h"
#include "../Scene.h"

void C_BRButton::ButtonInit()
{
	buttonHit = false;
	Once = false;

	m_message.transparent = 0.0f;
	fading = false;
	//音量初期値
	//vol = 0.4f; //MAXは1.0f

	//SE
	//①メモリ領域の確保
	se = std::make_shared<KdSoundEffect>();

	//②音データの読み込み
	se->Load("Sound/Gimic/anvilhammer.WAV");

	//③スピーカーのメモリ確保＆音データを渡す
	seInst = se->CreateInstance(false);
	//seInst->SetVolume(vol); //ボリューム調整(セッターで音を流す)
}

void C_BRButton::ButtonUpdate()
{
	C_MapBase* map = m_owner->GetMap();
	Scene& scene = SCENE;

	if (nextStage) {
		if (!EffectOnce) {
			scene.GetEffectManager()->SetTechSquareEffect(m_button.pos.x, m_button.pos.y, true);
			EffectOnce = true;
		}
		if (buttonHit && !Once) {
			scene.GetEffectManager()->GetTechSquareEffect()->Init();
			Once = true;
			m_owner->GetGimicMgr()->GetBCButton()->SetEffect(true);
		}

		static int frame = 0;

		if (buttonHit) {
			if (frame % 4 == 0) // 4フレームごとに1つのマップデータを変更
			{
				static int i = 0;
				static int j = 0;

				map->ChangeMapData(42 + i, 61 + j, '0');

				j++;
				if (j >= 3)
				{
					j = 0;
					i++;
				}

				if (i >= 6)
				{
					i = 0;
				}
			}
			frame++;

			if (!fading) {
				m_message.transparent += 0.1f;
				if (m_message.transparent >= 1.0f) {
					m_message.transparent = 1.0f;
					fading = true; 
				}
			}
			else if(frame >= 120){
				m_message.transparent -= 0.01f;
				if (m_message.transparent <= 0.0f) {
					m_message.transparent = 0.0f;
				}
			}
		}

		m_message.scaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 1.0f);
		m_message.transMat = Math::Matrix::CreateTranslation(0, 0, 0);
		m_message.mat = m_message.scaleMat * m_message.transMat;
	}
}

void C_BRButton::ButtonDraw()
{
	if (nextStage) {
		SHADER.m_spriteShader.SetMatrix(m_message.mat);
		SHADER.m_spriteShader.DrawTex(&m_messageTex, Math::Rectangle(0, 0, 1280, 720), m_message.transparent);
	}
}

void C_BRButton::PlaySE()
{
	seInst->Play(); //ループ再生オフ
}

void C_BRButton::Load()
{
	m_messageTex.Load("Texture/Gimic/messagewall.png");
}

void C_BRButton::Release()
{
	m_messageTex.Release();
}

//void C_BRButton::SELoad()
//{
//}
