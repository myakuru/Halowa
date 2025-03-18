#include "EnemyAttackHit.h"
#include "../Scene.h"

C_EnemyAtkHit::C_EnemyAtkHit() : m_hOwner(nullptr), m_hPlayer(nullptr), m_hEnemyMgr(nullptr) {};

void C_EnemyAtkHit::Player_EnemyHit()
{
    //無敵ならリターン
    if (m_hPlayer->GetInvincible())return;

    const size_t allEnemiesNum = m_hEnemyMgr->GetAllEnemies().size();

    for (size_t i = 0; i < allEnemiesNum; i++)
    {
        C_EnemyBase* enemy = m_hEnemyMgr->GetAllEnemies()[i];

        if (enemy->GetDead()) continue;

        Math::Vector2 enemyPos = enemy->GetPos();
        const float enemyRadius = enemy->GetHitWidth() * 0.8;//判定を甘くするための補正値×0.8

        switch (enemy->GetEnemyType())
        {
        case EnemyType::Robot:
        case EnemyType::Frog:
        case EnemyType::Ghost:
        case EnemyType::Gremlin:
        case EnemyType::BossRobot:
        case EnemyType::Skull:
            if (!enemy->GetAttackHit())
            {
                //当たり判定チェック
                if (PlayerHitCircle(enemyPos.x, enemyPos.y, enemyRadius))
                {
                    //プレイヤーのノックバック
                    const Math::Vector2 enemyPos = enemy->GetPos();
                    const float hitKnockForce = enemy->GetHitKnockForce();
                    Knockback(enemyPos, hitKnockForce);

                    //ダメージを与える
                    m_hPlayer->SetEnemyDamage(enemy->GetHitDamage());
                    return;
                }
            }
            break;
        }

    }
}

void C_EnemyAtkHit::AllEnemiesAttack()
{
    //ロボットの攻撃判定
    RobotAttackHit();
    //グレムリンの攻撃判定
    GremlinAttackHit();
    //ボスロボットの攻撃判定
    BossRobotAttackHit();
    //スカルの攻撃判定
    SkullAttackHit();
    //煙の当たり判定
    SmokeHit();
    //魔法の当たり判定
    SpellHit();
    //火の玉の当たり判定
    FireballHit();
    //焚火の当たり判定
    BonfireHit();
}

void C_EnemyAtkHit::RobotAttackHit()
{
    const size_t robotNum = m_hEnemyMgr->GetRobot().size();

    for (size_t i = 0; i < robotNum; i++)
    {
        C_Robot* robot = m_hEnemyMgr->GetRobot()[i];

        if (!robot->GetAttackHit()) continue;
        if (robot->GetDead()) continue;

        const Math::Vector2 attackPos = robot->GetAttackPos();
        const float attackRadius = robot->GetAttackRadius();

        //プレイヤーが攻撃判定のある場所にいたら
        if (PlayerHitCircle(attackPos.x, attackPos.y, attackRadius))
        {
            //ノックバック
            const Math::Vector2 robotPos = robot->GetPos();
            const float hitKnockForce = robot->GetHitKnockForce();
            Knockback(robotPos, hitKnockForce);

            //ダメージを与える
            const int attackDamage = robot->GetAttackDamage();
            m_hPlayer->SetEnemyDamage(attackDamage);
        }
    }
}

void C_EnemyAtkHit::GremlinAttackHit()
{
    const size_t gremlinNum = m_hEnemyMgr->GetGremlin().size();

    for (size_t i = 0; i < gremlinNum; i++)
    {
        C_Gremlin* gremlin = m_hEnemyMgr->GetGremlin()[i];

        if (!gremlin->GetAttackHit()) continue;
        if (gremlin->GetDead()) continue;

        const Math::Vector2 gremlinPos = gremlin->GetPos();
        const float attackRadius = gremlin->GetAttackRadius();

        //プレイヤーが攻撃判定のある場所にいたら
        if (PlayerHitCircle(gremlinPos.x, gremlinPos.y, attackRadius))
        {
            //ノックバック
            const float hitKnockForce = gremlin->GetHitKnockForce();
            Knockback(gremlinPos, hitKnockForce);

            //ダメージを与える
            const int attackDamage = gremlin->GetAttackDamage();
            m_hPlayer->SetEnemyDamage(attackDamage);
        }
    }
}

void C_EnemyAtkHit::BossRobotAttackHit()
{
    const size_t bossRobotNum = m_hEnemyMgr->GetBossRobot().size();

    for (size_t i = 0; i < bossRobotNum; i++)
    {
        C_BossRobot* bossRobot = m_hEnemyMgr->GetBossRobot()[i];

        if (!bossRobot->GetAttackHit()) continue;
        if (bossRobot->GetDead()) continue;

        const Math::Vector2 attackPos = bossRobot->GetAttackPos();
        const float attackRadius = bossRobot->GetAttackRadius();

        //プレイヤーが攻撃判定のある場所にいたら
        if (PlayerHitCircle(attackPos.x, attackPos.y, attackRadius))
        {
            //ノックバック
            const Math::Vector2 bossRobotPos = bossRobot->GetPos();
            const float hitKnockForce = bossRobot->GetHitKnockForce();
            Knockback(bossRobotPos, hitKnockForce);

            //ダメージを与える
            const int attackDamage = bossRobot->GetAttackDamage();
            m_hPlayer->SetEnemyDamage(attackDamage);
        }
    }
}

void C_EnemyAtkHit::SkullAttackHit()
{
    const size_t skullNum = m_hEnemyMgr->GetSkull().size();

    for (size_t i = 0; i < skullNum; i++)
    {
        C_Skull* skull = m_hEnemyMgr->GetSkull()[i];

        if (!skull->GetAttackHit()) continue;
        if (skull->GetDead()) continue;

        const Math::Vector2 skullPos = skull->GetPos();
        const float attackRadius = skull->GetAttackRadius();

        //プレイヤーが攻撃判定のある場所にいたら
        if (PlayerHitCircle(skullPos.x, skullPos.y, attackRadius))
        {
            //ノックバック
            const float hitKnockForce = skull->GetHitKnockForce();
            Knockback(skullPos, hitKnockForce);

            //ダメージを与える
            const int attackDamage = skull->GetAttackDamage();
            m_hPlayer->SetEnemyDamage(attackDamage);
        }
    }
}

void C_EnemyAtkHit::SmokeHit()
{
    const size_t bossRobotNum = m_hEnemyMgr->GetBossRobot().size();

    if (bossRobotNum < 1)return;

    const Math::Vector2 playerPos = m_hPlayer->GetPos();

    for (size_t i = 0; i < bossRobotNum; i++)
    {
        C_BossRobot* bossRobot = m_hEnemyMgr->GetBossRobot()[i];
        const C_Smoke* smoke = bossRobot->GetSmoke();

        if (smoke == nullptr)continue;
        if (!smoke->GetAlive())continue;
        if (!smoke->GetHitCnk())continue;

        const Math::Vector2 smokePos = smoke->GetPos();
        const float smokeHitWidth = smoke->GetHitWidth();
        const float smokeHitHeight = smoke->GetHitHeight();

        const float distanceX = fabsf(smokePos.x - playerPos.x);
        const float distanceY = fabsf(smokePos.y - playerPos.y);

        if (distanceX < m_hPlayer->GetWidth() + smokeHitWidth &&
            distanceY < m_hPlayer->GetHeight() + smokeHitHeight)
        {
            //ノックバック
            const float hitKnockForce = smoke->GetKnockForce();
            Knockback(smokePos, hitKnockForce);

            //ダメージを与える
            const int smokeDamage = smoke->GetDamage();
            m_hPlayer->SetEnemyDamage(smokeDamage);
        }
    }
}

void C_EnemyAtkHit::SpellHit()
{
    const size_t frogNum = m_hEnemyMgr->GetFrog().size();

    if (frogNum < 1)return;

    const Math::Vector2 playerPos = m_hPlayer->GetPos();
    const float playerRadius = m_hPlayer->GetWidth();

    for (size_t i = 0; i < frogNum; i++)
    {
        C_Frog* frog = m_hEnemyMgr->GetFrog()[i];
        const C_Spell* spell = frog->GetSpell();

        if (spell == nullptr)continue;
        if (!spell->GetAlive())continue;

        const Math::Vector2 spellPos = spell->GetPos();
        const float spellRadius = spell->GetHitWidth();

        const float a = playerPos.x - spellPos.x;
        const float b = playerPos.y - spellPos.y;
        const float c = sqrt(a * a + b * b);

        if (c < playerRadius + spellRadius)
        {
            //ノックバック
            const float hitKnockForce = spell->GetKnockForce();
            Knockback(spellPos, hitKnockForce);

            //ダメージを与える
            const int spellDamage = spell->GetDamage();
            m_hPlayer->SetEnemyDamage(spellDamage);
        }
    }
}

void C_EnemyAtkHit::FireballHit()
{
    const size_t skullNum = m_hEnemyMgr->GetSkull().size();

    if (skullNum < 1)return;

    const Math::Vector2 playerPos = m_hPlayer->GetPos();
    const float playerRadius = m_hPlayer->GetWidth();

    for (size_t i = 0; i < skullNum; i++)
    {
        C_Skull* skull = m_hEnemyMgr->GetSkull()[i];

        const size_t fireballNum = skull->GetFireball().size();

        for (size_t i = 0; i < fireballNum; i++)
        {
            const C_Fireball* fireball = skull->GetFireball()[i];

            if (!fireball->GetAlive())continue;
            if (fireball->GetGroundHit())continue;

            const Math::Vector2 fireballPos = fireball->GetPos();
            const float fireballRadius = fireball->GetHitWidth();

            const float a = playerPos.x - fireballPos.x;
            const float b = playerPos.y - fireballPos.y;
            const float c = sqrt(a * a + b * b);

            if (c < playerRadius + fireballRadius)
            {
                //ノックバック
                const float hitKnockForce = fireball->GetKnockForce();
                Knockback(fireballPos, hitKnockForce);

                //ダメージを与える
                const int fireballDamage = fireball->GetDamage();
                m_hPlayer->SetEnemyDamage(fireballDamage);
            }
        }
    }
}

void C_EnemyAtkHit::BonfireHit()
{
    const size_t skullNum = m_hEnemyMgr->GetSkull().size();

    if (skullNum < 1)return;

    const Math::Vector2 playerPos = m_hPlayer->GetPos();

    for (size_t i = 0; i < skullNum; i++)
    {
        C_Skull* skull = m_hEnemyMgr->GetSkull()[i];

        const size_t bonfireNum = skull->GetBonfire().size();

        for (size_t i = 0; i < bonfireNum; i++)
        {
            const C_Bonfire* bonfire = skull->GetBonfire()[i];

            if (!bonfire->GetAlive())continue;
            if (!bonfire->GetActive())continue;
            if (!bonfire->GetHitCnk())continue;

            const Math::Vector2 bonfirePos = bonfire->GetPos();
            const float bonfireHitWidth = bonfire->GetHitWidth();
            const float bonfireHitHeight = bonfire->GetHitHeight();

            const float distanceX = fabsf(bonfirePos.x - playerPos.x);
            const float distanceY = fabsf(bonfirePos.y - playerPos.y);

            if (distanceX < m_hPlayer->GetWidth() + bonfireHitWidth &&
                distanceY < m_hPlayer->GetHeight() + bonfireHitHeight)
            {
                //ノックバック
                const float hitKnockForce = bonfire->GetKnockForce();
                Knockback(bonfirePos, hitKnockForce);

                //ダメージを与える
                const int bonfireDamage = bonfire->GetDamage();
                m_hPlayer->SetEnemyDamage(bonfireDamage);
            }
        }
    }
}

bool C_EnemyAtkHit::PlayerHitCircle(float circleX, float circleY, float circleRadius)
{
    const Math::Vector2 playerPos = m_hPlayer->GetPos();
    const float playerRadius = m_hPlayer->GetWidth();


    const float a = playerPos.x - circleX;
    const float b = playerPos.y - circleY;
    const float c = sqrt(a * a + b * b);

    if (c < playerRadius + circleRadius)
    {
        return true;
    }
    return false;
}

void C_EnemyAtkHit::Knockback(Math::Vector2 a_srcPos, float a_knockForce)
{
    const Math::Vector2 playerPos = m_hPlayer->GetPos();

    const float a = playerPos.x - a_srcPos.x;
    const float b = playerPos.y - a_srcPos.y;
    const float angle = atan2(b, a);

    Knockback(a_srcPos, a_knockForce, angle);
}

void C_EnemyAtkHit::Knockback(Math::Vector2 a_srcPos, float a_knockForce, float a_knockAngle)
{
    float moveX = cos(a_knockAngle) * a_knockForce;
    float moveY = fabsf(sin(a_knockAngle) * a_knockForce);
    //moveY最低保証
    if (moveY < 3.0f)
    {
        moveY = 3.0f;
    }

    m_hPlayer->SetHurtMove(false, a_srcPos.x, { moveX,moveY });
}
