#pragma once
class Scene;

class C_Death
{
public:

	C_Death();
	~C_Death();

	void Init();
	void Update();
	void Draw();
	void LoadTex();
	void ReleaseTex();

	void SetOwner(Scene* owner) { m_dOwner = owner; }

	int flame;

	void SetPos_Death(bool m_pos) { pos = m_pos; }
	bool GetPos_Death() { return pos; }



private:


	float m_blackalpha;
	
	bool pos = false;


	enum Death {
		gameover,
		back,
		restart,
		title,
		DeathtypeMax
	};

	Scene* m_dOwner;
	Scene* m_dmOwner;

	KdTexture m_GameoverTex;	//�Q�[���I�[�o�[
	KdTexture m_BackTex;		//�w�i
	KdTexture m_RestartTex;		//���X�^�[�g�I��
	KdTexture m_TitleTex;		//�^�C�g���ɖ߂�



	Math::Color m_color;

	struct object {
		Math::Vector2 pos;//���W
		Math::Vector2 move;//�ړ���
		Math::Matrix scalemat;//�g��s��
		Math::Matrix transmat;//�ړ��s��
		Math::Matrix mat;//�����s��
	};

	object m_death[DeathtypeMax];

};