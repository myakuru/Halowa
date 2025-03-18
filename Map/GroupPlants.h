#pragma once
//�O���錾
class Scene;

class C_GroupPlants
{
public:
	C_GroupPlants();
	~C_GroupPlants();
	void InitPlants();
	void DrawPlants();
	void UpdatePlants();
	void LoadTexture();
	void ReleaseTexture();

	//���̈ʒu�̃Z�b�^�[	
	void SetPlantsPos(int num, float posX,float posY) { Plants[num].m_pos.x = posX, Plants[num].m_pos.y=posY; }

	//���̐F�̃Z�b�^�[
	void SetPlantsColor(Math::Color color) { this->color = color; }

	//�I�[�i�[�̐ݒ�
	void SetOwner(Scene* owner) { m_mOwner = owner; }

private:
	struct s_Plants {
		Math::Vector2 m_pos;
		Math::Matrix m_mat;
		Math::Matrix m_scaleMat;
		Math::Matrix m_transMat;
	};

	struct s_AnimeFunction {
		int m_fFrameCnt = 0;
		int m_fTexNum = 0;
	}Animetion;

	static const int TextureMax = 44;	//�A���̍ő吔
	static const int PlantsMax = 2;	//�A���̍ő吔
	KdTexture Tex[TextureMax][PlantsMax];//�A���̃e�N�X�`��
	char str[100] = {0};				//�e�N�X�`���̃p�X
	Math::Color color = { 1,1,1,1 };	//�F

	s_Plants Plants[PlantsMax];				//�A���̍\����

	Scene* m_mOwner = nullptr;


};