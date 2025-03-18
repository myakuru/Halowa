#pragma once
#include<fstream>
#include<string>
#include<map>
#include"LightningPar.h"
#include"../Enum/SceneTypeEnum.h"
#include"../Enum/ItemAndCollectEnum.h"
#include"../Enum/AvoidTypeEnum.h"
class Scene;    //�O���錾
class C_Chara {
private:

    //�I�[�i�[
    Scene* m_owner;


    //�摜�z��Ǘ��p
    enum Charatype {
        Idle,           //�ҋ@(0)
        Run,            //�_�b�V��(1)
        RunEnd,         //�_�b�V���I��(2)
        Jump,           //�W�����v(3)
        Fall,           //����(4)
        AttackStd,      //�����U��(5)
        AttackAir,      //�󒆍U��(6)
        Hurt,           //�_���[�W(7)
        CharatypeMax
    };

    //SE�Ǘ�
    enum PlayerSE {
        RunSE,
        HurtSE,
        AttackSE,
        ChargeAtkSEOne,
        ChargeAtkSETwo,
        ChargeAtkSEThree,
        ChargeSlashSE,
        SlashRushSE,
        AttackHitSe,
        LightningSE,
        HealSE,
        FuseBlowsSE,
        AvoidChargeSE,
        AvoidChangeSE,
        SEMAX
    };
    
    std::shared_ptr<KdSoundEffect> se[SEMAX];
    std::shared_ptr<KdSoundInstance> seInst[SEMAX];
    std::shared_ptr<KdSoundInstance> hitseInst[10];
    std::shared_ptr<KdSoundInstance> SlashRushInst[10];
    float vol=0.2;
    int RunCnt=0;


    

    //�p�[�e�B�N���p
    static const int LightNum= 10;
    static const int LiEffNum = 10;
    C_LightningPar Light;

    struct SaveData {
        SceneType m_SaveMap;
        Math::Vector2 m_SavePos;
        int m_NowCoin;
        HaveItems m_NowHaveItem;
        bool m_AvoidHaveFlg[AvoidMax];
        int m_HaveHPPotion;
        int m_HaveMPPotion;
        int m_HPBoostCnt=1;
        int m_MPBoostCnt=1;
        int m_AtkBoostCnt=1;
    };
    SaveData PlayerData;

    
   

    // �v���C���[�Ɋւ���ϐ����܂Ƃ߂��\����
    struct Player {
        int m_MaxHp;                     //�ő�HP
        int m_NowHp;                      //HP
        bool m_HPUP[5];                     //HP�����t���O
        int m_MaxMp;                      //�ő�MP
        int m_NowMp;                      //MP
        bool m_MPUP[5];                     //MP�����t���O
        int m_HaveItemAll = 0;                //�����A�C�e������
        bool m_IsPoison;                        //�ŏ�ԃt���O
        bool m_FuseBlows;                 //�q���[�Y�ؒf�t���O
        int m_FuseCnt;                    //�q���[�Y�ؒf�J�E���g
        Math::Vector2 m_pos;              //���W
        Math::Vector2 m_move;            //�ړ���
        Math::Vector2 m_hurtMove;        //��e�ړ���
        Math::Matrix m_mat;              //�s��
        Math::Matrix m_scaleMat;         //�g�k�s��
        Math::Matrix m_transMat;          //�ړ��s��
        Math::Vector2 m_scale;             //�g�k�x
        Math::Vector2 m_scroll;            //�X�N���[��
        bool m_Events=false;               //�C�x���g�s���s�\�t���O
        bool m_isJump;                     //�W�����v�t���O
        bool m_DoubleJumpFlg;               //��i�W�����v�t���O
        bool m_IsFall;                      //�����t���O
        bool m_isRun;                      //�_�b�V���t���O
        bool m_isRunEnd;                   //�_�b�V���G���h�t���O
        bool m_isAvoid;                   //����t���O
        bool m_AvoidKey;                  //����L�[�t���O
        bool m_DebugKey;
        bool m_isAttackStd;                //�n��U���t���O
        bool m_AttackStdCha;            //���ߍU��
        bool m_AtkKeyFlg;               //���ߍU���t���O
        Math::Vector2 m_AtkFirstPos;    //���ߍU���̈ړ��O�̒n�_
        Math::Vector2 m_AtkEndPos;      //���ߍU���̈ړ���̒n�_
        int AttackChargeCnt;             //���ߍU���J�E���g
        bool m_ChargeAtkStart;             //���ߍU���U������J�n
        bool m_isAttackAir;              //�󒆍U���t���O
        bool m_bAttackKey;                  //�U���L�[�t���O
        int m_AtkPow;                       //�U����
        bool m_AtkUp[5];                    //�U�������t���O
        bool m_ItemUsing=false;
        bool m_ItemUseKeyFlg = false;
        bool m_bAvoidChangeKey;          //���؂�ւ��t���O
        bool m_AttackHit;                //�U������o���t���O
        bool m_isHurt;                  //��e���[�V�����t���O
        bool m_isInvincible;            //���G��ԃt���O
        bool m_isHurtInvincible=false;  //��e���G��ԃt���O
        int m_InvincibleCnt;             //���G���ԃJ�E���g
        bool m_isAlive;                   //�����t���O
        AvoidType NowAvoidType;            //���݂̉����
        Math::Color m_color;               //�F
    } m_player;

    bool m_TabKeyFlg;
    bool m_EscapeKeyFlg;

    //���Ɋւ���ϐ����܂Ƃ߂��\����
    struct Thunder {
        Math::Vector2 m_pos = { 0,0 };
        Math::Vector2 m_move = { 0,0 };
        Math::Matrix m_mat;
        Math::Matrix m_scaleMat;
        Math::Matrix m_rotationMat;
        Math::Matrix m_transMat;
        Math::Vector2 m_scale = { 1,1 };
        int m_avoidChargeCnt;
        bool m_bAvoidCharge;
        bool m_bSelect=false;
        bool m_Flg = false;
        float m_PosAdjust=0;
    };

    Thunder m_Nor, m_Long, m_Over,m_Debug;

    // �A�j���[�V�����Ɋւ���ϐ����܂Ƃ߂��\����
    struct s_Animation {
        int m_Num = 0;
        int m_TexNum = 0;
        int m_FrameCnt = 0;
        bool m_bOne = false;
    };
    s_Animation IdleAni, RunAni, RunEndAni, JumpAni, FallAni,
                AttackStdAni,AttackAirAni,HurtAni,NorThunAni,
                ItemUsingAni,ChargeSlashAni,LightningChargeAni,
                DeathAni;

    //�A�j���[�V�����֐����ň����ϐ����܂Ƃ߂��\����
    struct s_AnimeFunction {
        int m_fFrameCnt = 0;
        int m_fTexNum = 0;
    };
    s_AnimeFunction LoopAni, OneAni;

    //�����蔻�����
    struct s_Test {
        Math::Vector2 m_pos = {0,0};
        Math::Matrix m_transMat;
        Math::Matrix m_mat;
        KdTexture Tex;
        Math::Rectangle rect;
        Math::Color m_color = {1,1,1,1};
        Math::Vector2 m_half;
        float m_width=96;
        float m_height=16;
    }Test;

    //�G�t�F�N�g
    struct S_Effect {
        Math::Vector2 m_pos;
        Math::Vector2 m_scale = { 1,1 };
        bool m_Alive;
        Math::Matrix m_transMat;
        Math::Matrix m_scaleMat;
        Math::Matrix m_mat;
        KdTexture m_tex;
        Math::Color m_color = { 1,1,1,1 };

    };

    S_Effect Danger,ItemUsing,ChargeSlash,LightningCharge,DeathEff;

    Math::Vector2 m_Shake;

public:

    // �R���X�g���N�^�ƃf�X�g���N�^�̐錾
    C_Chara();           
    ~C_Chara(){}

	//�������E�X�V�E�`��
	void Init();
    void Update();
    void PlayerAnimeUpdate();
    void ThunUpdate();
    void Draw();
    //HP�EMP�̍ő�l�̍X�V�A�͊�����
    void HPMPUpdate();
    //�A�C�e���̎g�p
    void ItemUse();
    //��e���[�V�����E���G����
    void HurtUpdate();
    //�U���X�V
    void AttackUpdate();
    void AttackAction();
    //SE�X�V
    void SEUpdate();
    void SEPlay(int a_num);
    //�U�������蔻��
    void TestUpdate();
    void TestDraw();
    void TestInit();
    //�Z�[�u�E���[�h
    void PlayerDataSave();
    void PlayerDataLoad();
    void PlayerDataDelete();

    bool ParseBool(const std::string& str) {
        if (str == "true"||str=="TRUE") return true;
        else return false;
    }
    std::string BoolToString(bool a_Bool) {
        if (a_Bool) return "TRUE";
        else return "FALSE";
    }

   
    C_LightningPar* GetLightning() { return &Light; }

    void Action();
    int Animation(int a_changeframe,int a_changemax,s_Animation& a_Anitype);       //�A�j���[�V����
    int OneAnimation(int a_changeframe, int a_changemax,int a_Charatype);
    int NeoAnimation(int a_chageframe, int a_changemax, s_Animation& a_Anitype);
    void LoadTexture();     //�摜���[�h
    void ReleaseTexture();  //�摜�J��
    void LoadSE();          //SE���[�h
    float GetAngle(Math::Vector2 a_srcPos,Math::Vector2 a_destPos);
    float Rnd() { return rand() / (float)RAND_MAX; }

    
    void ImGuiUpdate();
	
    //�Q�b�^�[============================================

	Math::Vector2 GetPos() { return m_player.m_pos; }
    Math::Vector2 GetMove() { return m_player.m_move; }
	Math::Vector2 GetFuturePos() { return m_player.m_pos + m_player.m_move; }
    float GetWidth() { return CharaWidth; }
    float GetHeight() { return CharaHeight; }
    bool GetisJump() { return m_player.m_isJump; }
    bool GetAlive() { return m_player.m_isAlive; }

    bool GetDirectX() { return m_bThunDirectX; }
    bool GetAtkHit() { return m_player.m_AttackHit; }
    Math::Vector2 GetAtkPos() { return Test.m_pos; }
    float GetAtkWidth() { return Test.m_width; }
    float GetAtkHeight() { return Test.m_height; }
    bool GetIsAtk() { return m_player.m_isAttackStd; }
    bool GetIsChaAtk() { return m_player.m_ChargeAtkStart; }
    int GetAtkAniNum() { return AttackStdAni.m_Num; }

    int GetMaxHp() { return m_player.m_MaxHp; }
    int GetNowHp() { return m_player.m_NowHp; }

    int GetMaxMp() { return m_player.m_MaxMp; }
    int GetNowMp() { return m_player.m_NowMp; }

    int GetAtkBoost() { return PlayerData.m_AtkBoostCnt; }

    int GetChageDamage() {
        switch (m_player.AttackChargeCnt / 40) {
        case 0:
            return m_player.m_AtkPow;
            break;
        case 1:
            return m_player.m_AtkPow/2;
            break;
        case 2:
            return m_player.m_AtkPow/2+m_player.m_AtkPow/3;
            break;
        default:
            return m_player.m_AtkPow;
        }
    }

    int GetChargeCnt() { return m_player.AttackChargeCnt / 40; }

    bool GetInvincible() { return m_player.m_isInvincible; }

    bool GetIsAvoid() { return m_player.m_isAvoid; }
    bool GetFuseBlows() { return m_player.m_FuseBlows; }
    int GetChargeFrame() { return m_player.AttackChargeCnt; }

    int GetThunderValue() {
        switch (m_player.NowAvoidType) {
        case NormalAvoid:
            return NorValue;
            break;
        case LongAvoid:
            return LongValue;
            break;
        case OverAvoid:
            return OverValue;
            break;
        }
    }

    int GetThunderDamage() {
        switch (m_player.NowAvoidType) {
        case OverAvoid:
            return OverDamage;
            break;
        default:
            return 0;
            break;
        }
    }

    int GetCoin() {return PlayerData.m_NowCoin; }
    int GetHaveItems(ItemsNum a_ItemsType){
        switch (a_ItemsType) {
        case HPPotionNum:
            return PlayerData.m_HaveHPPotion;
            break;
        case MPPotionNum:
            return PlayerData.m_HaveMPPotion;
            break;
        case AtkBoostNum:
            return PlayerData.m_AtkBoostCnt;
            break;
        case HPBoostNum:
            return PlayerData.m_HPBoostCnt;
            break;
        case MPBoostNum:
            return PlayerData.m_MPBoostCnt;
            break;
        default:
            break;
        }
    }

    int GetHaveItemAll() { return m_player.m_HaveItemAll; }

    int GetHaveHPPotion() { PlayerData.m_HaveHPPotion; }
    int GetHaveMPPotion() { PlayerData.m_HaveMPPotion; }

    bool GetHaveAvoid(AvoidType a_GetAvoid) {
        switch (a_GetAvoid) {
        case NormalAvoid:
            return PlayerData.m_AvoidHaveFlg[NormalAvoid];
            break;
        case LongAvoid:
            return PlayerData.m_AvoidHaveFlg[LongAvoid];
            break;
        case OverAvoid:
            return PlayerData.m_AvoidHaveFlg[OverAvoid];
            break;
        default:
            break;
        }
    }

    int GetAvoidMP(AvoidType a_AvoidType) {
        switch (a_AvoidType) {
        case NormalAvoid:
            return NorMp;
            break;
        case LongAvoid:
            return LongMp;
            break;
        case OverAvoid:
            return OverMp;
            break;
        default:
            break;
        }
    }

    int GetAvoidElectricPow(AvoidType a_AvoidType) {
        switch (a_AvoidType) {
        case NormalAvoid:
            return NorValue;
            break;
        case LongAvoid:
            return LongValue;
            break;
        case OverAvoid:
            return OverValue;
            break;
        default:
            break;
        }
    }

    int GetOverDamage() { return OverDamage; }

    bool GetTabKeyFlg() { return m_TabKeyFlg; }

    bool GetEscapeKeyFlg() { return m_EscapeKeyFlg; }

    HaveItems GetNowHaveItem() { return PlayerData.m_NowHaveItem; }

    AvoidType GetNowAvoidType() { return m_player.NowAvoidType; }

    SceneType GetSaveScene() { return PlayerData.m_SaveMap; }

    //=====================================================

    //�Z�b�^�[=============================================

    void SetPos(Math::Vector2 a_pos) { m_player.m_pos = a_pos; }
    void SampleMoveX(float movex) { m_player.m_move.x = movex; }
    void SetMoveX(float a_moveX) {
        m_player.m_move.x = a_moveX;
        if (m_player.m_move.x < 0) {
            m_player.m_isRun = true;
            m_player.m_isRunEnd = true;
            m_bThunDirectX = false;
            m_player.m_scale.x = -ScaleSize;
        }
        else if (m_player.m_move.x > 0) {
            m_player.m_isRun = true;
            m_player.m_isRunEnd = true;
            m_bThunDirectX = true;
            m_player.m_scale.x = ScaleSize;
        }
    }
    void SetMoveY(float a_moveY) {
        m_player.m_move.y = a_moveY;
    }
    void SetDirectX(bool direct) { m_bThunDirectX = direct; }
    void SetHurtMove(  bool a_bAuto=true, float a_EnemyPosX=0, Math::Vector2 a_hurtmove = {0,0}) {
        if (!m_player.m_isInvincible) {
            if (!a_bAuto) {
                if (m_player.m_pos.x <= a_EnemyPosX) m_bThunDirectX = true;
                else m_bThunDirectX = false;
                m_player.m_hurtMove = a_hurtmove;
            }
            else {
                if (m_bThunDirectX) m_player.m_hurtMove = { -5,5 };
                else m_player.m_hurtMove = { 5,5 };
            }
        }
    }
    void SetCoin(int a_coin) { PlayerData.m_NowCoin += a_coin; }
    void SetEnemyDamage(int a_damage);
    void SetPoison(bool a_Poison) {
        m_player.m_IsPoison = a_Poison;
    }
    void SetIsAvoid(bool a_isAvoid) { 
        m_player.m_isAvoid = a_isAvoid;
        LightningChargeAni.m_bOne = false;
    }
    void SetEvents(bool a_events) { m_player.m_Events = a_events; }
    void SetShake(Math::Vector2 a_shakepow) { m_Shake = a_shakepow; }

    void AddItems(ItemsNum a_ItemType,int a_AddNum) {
        switch (a_ItemType) {
        case HPPotionNum:
            PlayerData.m_HaveHPPotion += a_AddNum;
            m_player.m_HaveItemAll += a_AddNum;
            break;
        case MPPotionNum:
            PlayerData.m_HaveMPPotion += a_AddNum;
            m_player.m_HaveItemAll += a_AddNum;
            break;
        case AtkBoostNum:
            PlayerData.m_AtkBoostCnt += a_AddNum;
            break;
        case HPBoostNum:
            PlayerData.m_HPBoostCnt += a_AddNum;
            break;
        case MPBoostNum:
            PlayerData.m_MPBoostCnt += a_AddNum;
            break;
        default:
            break;
        }
    }

    void SetNowHaveItem(SetHaveItem a_SetHaveItem) {
        switch (a_SetHaveItem) {
        case SetHaveHPPotion:
            PlayerData.m_NowHaveItem = HaveHPPotion;
            break;
        case SetHaveMPPotion:
            PlayerData.m_NowHaveItem = HaveMPPotion;
            break;
        default:
            break;
        }
    }

    void SetTabKeyFlg(bool a_TabKeyFlg) { m_TabKeyFlg = a_TabKeyFlg; }
    void SetEscapeKeyFlg(bool a_EscapeKeyFlg) { m_EscapeKeyFlg = a_EscapeKeyFlg; }
    void SetMouseRightButtonKeyFlg(bool a_RightButtonKeyFlg) { m_player.m_AvoidKey = a_RightButtonKeyFlg; }

    void SetAlive() {
        m_player.m_isAlive = true;
        m_player.m_NowHp = m_player.m_MaxHp;
    }
    
    void SetAvoidFlg(AvoidType a_AvoidType) {
        PlayerData.m_AvoidHaveFlg[a_AvoidType] = true;
        m_player.NowAvoidType = a_AvoidType;
    }

    void SetVol(float a_Vol) {
        vol = 0.2 * a_Vol;
        for(int i = 0; i < SEMAX; i++) {
            seInst[i]->SetVolume(vol);
        }
        for (int i = 0; i < 10; i++) {
            hitseInst[i]->SetVolume(vol);
            SlashRushInst[i]->SetVolume(vol);
        }
    }

    void SetNowHP(int a_NowHP) { m_player.m_NowHp = a_NowHP; }

    //=====================================================

	// �}�b�v�ƃv���C���[�̏���
    void MapHitX(Math::Vector2 Pos, float moveX);

    void SampleMapHitX(float x, float movex);

    void MapHitY(Math::Vector2 Pos, float moveY, bool Jump,bool a_bOne,bool a_Hurt);

    void SetEnter(bool enter) { EnterFlag = enter; }

    //�I�[�i�[
    void SetOwner(Scene* owner) { m_owner = owner; };

    bool IsJumping() const {
        return m_player.m_isJump;
    }

private:

    // ���̑��̃����o�[�ϐ�
    KdTexture m_Texture[CharatypeMax][24];     // �v���C���[�e�N�X�`��
    char strp[100];

    KdTexture m_ThunderTexture;                  //���e�N�X�`��
   

    Math::Color m_color;                 // �F
    const float CharaWidth = 30.0f;     // �L�����N�^�[�̔��a
    const float CharaHeight = 60.0f;    // �L�����N�^�[�̔��a
	const float Gravity = 1.0f;		  // �d��

    const Math::Vector2 NormalAtkHalf = { 96,16 };
    
    //�摜����
    const int IdleMax = 15;
    const int RunMax = 24;
    const int RunEndMax = 15;
    const int JumpMax = 5;
    const int FallMax = 5;
    const int AttackStdMax = 7;
    const int AttackAirMax = 7;
    const int HurtMax = 5;
    const int NorThunMax = 16;

    const float ScaleSize = 0.3;
    const float RunPow = 7;
    const float JumpPow = 22;

    float ThuderAngle=0;            //���摜�p�x
    float AngleAdjust = 270;        //���p�x����
    bool m_bThunDirectX;            //���� true:�E false:��
    bool m_bThunDirectRi;           //�E����
    bool m_bThunDirectLe;           //������
    bool m_bThunDirectUp;           //�����
    bool m_bThunDirectDw;           //������

    //HP�AMP
    int level1 = 1000;
    int level2 = 1200;
    int level3 = 1400;
    int level4 = 1600;
    int level5 = 1800;

    //�U����
    int AttackPowLevel[5] = { 7,14,21,28,35 };

    //����MP�A�f�o�b�N�p�ɉ��̒l
    /*int NorMp = 300;
    int LongMp = 600;
    int OverMp = 1200;*/

   /* int NorMp = 200;
    int LongMp = 400;
    int OverMp = 1000;*/

    int NorMp = 1;
    int LongMp = 1;
    int OverMp = 1;


    //�^����d���l
    int NorValue = 50;
    int LongValue = 40;
    int OverValue = 80;

    //�d���̃_���[�W
    int OverDamage = 60;

    //�񕜗�
    int HealValue = 500;

    bool TestKeyFlg;

    bool EnterFlag = false;

    bool ShopdebugFlg=false;

};
