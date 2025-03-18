#pragma once
#include<fstream>
#include<string>
#include<map>
#include"LightningPar.h"
#include"../Enum/SceneTypeEnum.h"
#include"../Enum/ItemAndCollectEnum.h"
#include"../Enum/AvoidTypeEnum.h"
class Scene;    //前方宣言
class C_Chara {
private:

    //オーナー
    Scene* m_owner;


    //画像配列管理用
    enum Charatype {
        Idle,           //待機(0)
        Run,            //ダッシュ(1)
        RunEnd,         //ダッシュ終了(2)
        Jump,           //ジャンプ(3)
        Fall,           //落下(4)
        AttackStd,      //立ち攻撃(5)
        AttackAir,      //空中攻撃(6)
        Hurt,           //ダメージ(7)
        CharatypeMax
    };

    //SE管理
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


    

    //パーティクル用
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

    
   

    // プレイヤーに関する変数をまとめた構造体
    struct Player {
        int m_MaxHp;                     //最大HP
        int m_NowHp;                      //HP
        bool m_HPUP[5];                     //HP強化フラグ
        int m_MaxMp;                      //最大MP
        int m_NowMp;                      //MP
        bool m_MPUP[5];                     //MP強化フラグ
        int m_HaveItemAll = 0;                //所持アイテム総数
        bool m_IsPoison;                        //毒状態フラグ
        bool m_FuseBlows;                 //ヒューズ切断フラグ
        int m_FuseCnt;                    //ヒューズ切断カウント
        Math::Vector2 m_pos;              //座標
        Math::Vector2 m_move;            //移動量
        Math::Vector2 m_hurtMove;        //被弾移動量
        Math::Matrix m_mat;              //行列
        Math::Matrix m_scaleMat;         //拡縮行列
        Math::Matrix m_transMat;          //移動行列
        Math::Vector2 m_scale;             //拡縮度
        Math::Vector2 m_scroll;            //スクロール
        bool m_Events=false;               //イベント行動不能フラグ
        bool m_isJump;                     //ジャンプフラグ
        bool m_DoubleJumpFlg;               //二段ジャンプフラグ
        bool m_IsFall;                      //落下フラグ
        bool m_isRun;                      //ダッシュフラグ
        bool m_isRunEnd;                   //ダッシュエンドフラグ
        bool m_isAvoid;                   //回避フラグ
        bool m_AvoidKey;                  //回避キーフラグ
        bool m_DebugKey;
        bool m_isAttackStd;                //地上攻撃フラグ
        bool m_AttackStdCha;            //ため攻撃
        bool m_AtkKeyFlg;               //ため攻撃フラグ
        Math::Vector2 m_AtkFirstPos;    //ため攻撃の移動前の地点
        Math::Vector2 m_AtkEndPos;      //ため攻撃の移動後の地点
        int AttackChargeCnt;             //ため攻撃カウント
        bool m_ChargeAtkStart;             //ため攻撃攻撃判定開始
        bool m_isAttackAir;              //空中攻撃フラグ
        bool m_bAttackKey;                  //攻撃キーフラグ
        int m_AtkPow;                       //攻撃力
        bool m_AtkUp[5];                    //攻撃強化フラグ
        bool m_ItemUsing=false;
        bool m_ItemUseKeyFlg = false;
        bool m_bAvoidChangeKey;          //回避切り替えフラグ
        bool m_AttackHit;                //攻撃判定出現フラグ
        bool m_isHurt;                  //被弾モーションフラグ
        bool m_isInvincible;            //無敵状態フラグ
        bool m_isHurtInvincible=false;  //被弾無敵状態フラグ
        int m_InvincibleCnt;             //無敵時間カウント
        bool m_isAlive;                   //生存フラグ
        AvoidType NowAvoidType;            //現在の回避種
        Math::Color m_color;               //色
    } m_player;

    bool m_TabKeyFlg;
    bool m_EscapeKeyFlg;

    //雷に関する変数をまとめた構造体
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

    // アニメーションに関する変数をまとめた構造体
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

    //アニメーション関数内で扱う変数をまとめた構造体
    struct s_AnimeFunction {
        int m_fFrameCnt = 0;
        int m_fTexNum = 0;
    };
    s_AnimeFunction LoopAni, OneAni;

    //当たり判定可視化
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

    //エフェクト
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

    // コンストラクタとデストラクタの宣言
    C_Chara();           
    ~C_Chara(){}

	//初期化・更新・描画
	void Init();
    void Update();
    void PlayerAnimeUpdate();
    void ThunUpdate();
    void Draw();
    //HP・MPの最大値の更新、枯渇処理
    void HPMPUpdate();
    //アイテムの使用
    void ItemUse();
    //被弾モーション・無敵処理
    void HurtUpdate();
    //攻撃更新
    void AttackUpdate();
    void AttackAction();
    //SE更新
    void SEUpdate();
    void SEPlay(int a_num);
    //攻撃当たり判定
    void TestUpdate();
    void TestDraw();
    void TestInit();
    //セーブ・ロード
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
    int Animation(int a_changeframe,int a_changemax,s_Animation& a_Anitype);       //アニメーション
    int OneAnimation(int a_changeframe, int a_changemax,int a_Charatype);
    int NeoAnimation(int a_chageframe, int a_changemax, s_Animation& a_Anitype);
    void LoadTexture();     //画像ロード
    void ReleaseTexture();  //画像開放
    void LoadSE();          //SEロード
    float GetAngle(Math::Vector2 a_srcPos,Math::Vector2 a_destPos);
    float Rnd() { return rand() / (float)RAND_MAX; }

    
    void ImGuiUpdate();
	
    //ゲッター============================================

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

    //セッター=============================================

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

	// マップとプレイヤーの処理
    void MapHitX(Math::Vector2 Pos, float moveX);

    void SampleMapHitX(float x, float movex);

    void MapHitY(Math::Vector2 Pos, float moveY, bool Jump,bool a_bOne,bool a_Hurt);

    void SetEnter(bool enter) { EnterFlag = enter; }

    //オーナー
    void SetOwner(Scene* owner) { m_owner = owner; };

    bool IsJumping() const {
        return m_player.m_isJump;
    }

private:

    // その他のメンバー変数
    KdTexture m_Texture[CharatypeMax][24];     // プレイヤーテクスチャ
    char strp[100];

    KdTexture m_ThunderTexture;                  //雷テクスチャ
   

    Math::Color m_color;                 // 色
    const float CharaWidth = 30.0f;     // キャラクターの半径
    const float CharaHeight = 60.0f;    // キャラクターの半径
	const float Gravity = 1.0f;		  // 重力

    const Math::Vector2 NormalAtkHalf = { 96,16 };
    
    //画像枚数
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

    float ThuderAngle=0;            //雷画像角度
    float AngleAdjust = 270;        //雷角度調整
    bool m_bThunDirectX;            //向き true:右 false:左
    bool m_bThunDirectRi;           //右入力
    bool m_bThunDirectLe;           //左入力
    bool m_bThunDirectUp;           //上入力
    bool m_bThunDirectDw;           //下入力

    //HP、MP
    int level1 = 1000;
    int level2 = 1200;
    int level3 = 1400;
    int level4 = 1600;
    int level5 = 1800;

    //攻撃力
    int AttackPowLevel[5] = { 7,14,21,28,35 };

    //消費MP、デバック用に仮の値
    /*int NorMp = 300;
    int LongMp = 600;
    int OverMp = 1200;*/

   /* int NorMp = 200;
    int LongMp = 400;
    int OverMp = 1000;*/

    int NorMp = 1;
    int LongMp = 1;
    int OverMp = 1;


    //与える電撃値
    int NorValue = 50;
    int LongValue = 40;
    int OverValue = 80;

    //電撃のダメージ
    int OverDamage = 60;

    //回復量
    int HealValue = 500;

    bool TestKeyFlg;

    bool EnterFlag = false;

    bool ShopdebugFlg=false;

};
