#pragma once
#include "../Enemy/EnemyManeger.h"
#include "../Enemy/Enemy.h"
#include "../shot/ShotManeger.h"
#include "../player/player.h"
#include "../BackGround/BackGround.h"

//“–‚½‚è”»’è‘S‘Ì‚ğŠÇ—‚·‚éƒNƒ‰ƒX
class CollisionManeger
{
public:
	static void CheckHitShotToEnemy(ShotManeger& shot, 
										EnemyManeger& enemy);


	static void CheckHitPlayerToEnemy(Player& player,
		EnemyManeger& enemy);


	static void CheckHitPlayerToField(Player& player, BackGround& field);


	static void CheckHitEnemyToField(EnemyManeger& enemy, BackGround& field);
};
