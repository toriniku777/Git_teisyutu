#include "CollisionManeger.h"
#include "../../lib//Collision/collision.h"

void CollisionManeger::CheckHitShotToEnemy(ShotManeger& shot,
	EnemyManeger& enemy)
{
	//敵の数だけループ
	for (int shotID = 0; shotID < PL_SHOT_NUM; shotID++)
	{
		//弾１発分の情報を取得し、生存確認
		Shot& oneShot = shot.GetShot(shotID);
		if (oneShot.isActive() == false) continue;

		//敵の数だけループ
		for (int enemyID = 0; enemyID < ENEMY_NUM; enemyID++)
		{
			//敵１人の情報を取得し、生存確認
			Enemy& oneEnemy = enemy.GetEnemy(enemyID);
			if (oneEnemy.isActive() == false) continue;

			//それぞれの座標と半径を取得
			VECTOR shotPos = oneShot.GetCenter();
			float shotRadius = oneShot.GetRadius();
			VECTOR enemyPos = oneEnemy.GetCenter();
			float enemyRadius = oneEnemy.GetRadius();

			//当たり判定開始
			bool isHit = Collision::CheckHitSphereToSphere(
				shotPos, shotRadius, enemyPos, enemyRadius
			);

			if (isHit == true)
			{
				oneShot.HitCalc();
				oneEnemy.HitCalc();

			}
		}

	}
}

void CollisionManeger::CheckHitPlayerToEnemy(Player& player,
	EnemyManeger& enemy)
{
	if (player.isActive() == false)return;

	//敵の数だけループ
	for (int enemyID = 0; enemyID < ENEMY_NUM; enemyID++)
	{
		//敵１人の情報を取得し、生存確認
		Enemy& oneEnemy = enemy.GetEnemy(enemyID);
		if (oneEnemy.isActive() == false) continue;

		//それぞれの座標と半径を取得
		VECTOR playerPos = player.GetCenter();
		float playerRadius = player.GetRadius();
		VECTOR enemyPos = oneEnemy.GetCenter();
		float enemyRadius = oneEnemy.GetRadius();

		//当たり判定開始
		bool isHit = Collision::CheckHitSphereToSphere(
			playerPos, playerRadius, enemyPos, enemyRadius
		);
		if (isHit == true)
		{
			player.HitCalc();
			oneEnemy.HitCalc();

		}
	}
}

void CollisionManeger::CheckHitPlayerToField(Player& player, BackGround& field)
{
	const int ITERATION = 3;//繰り返し回数
	

	for (int objectID = 0; objectID < OBJECT_NUM; objectID++)
	{
		if (SKY == 1)continue;
		//それぞれの座標と半径を取得
		VECTOR playerPos = player.GetPosition();
		float playerRadius = player.GetRadius();


		for(int iter=0;iter<ITERATION;++iter)
		{
			VECTOR p_pos = player.GetCenter();
			VECTOR out = { 0.0f };
			MV1_COLL_RESULT_POLY_DIM res;		//当たり判定が格納される構造体
			res = MV1CollCheck_Sphere(field.GetHndl(objectID), -1, p_pos, playerRadius);

			if (res.HitNum == 0)
			{
				MV1CollResultPolyDimTerminate(res);
				break;
			}

			float maxLen = 0.0f;
			VECTOR bestPush = { 0.0f,0.0f,0.0f };


				//最も深く当たっているポリゴンに基づいて押し戻し処理
				for (int i = 0; i < res.HitNum; ++i)
				{
					VECTOR Norm = res.Dim[i].Normal;

					//ヒットしたポリゴンとヒットした物体のめり込んだ距離を求める
					VECTOR sub = VSub(res.Dim[i].HitPosition, p_pos);
					float len = VSize(sub);
					len = playerRadius - len;

					if (len <= 0.0f)continue;
					//一番深いものだけ選ぶ
					if (len > maxLen)
					{
						maxLen = len;
						bestPush = VScale(Norm, len);
					}
					
				}
				//めり込んだ距離だけ外に押し出す　押し出す方向は法線の方向
				playerPos = VAdd(playerPos, bestPush);
				player.SetPosition(playerPos);

				MV1CollResultPolyDimTerminate(res);

				//ほぼ押し出し終わったら終了
				if(maxLen<0.001f)break;
				//player.SetPosition(VAdd(player.GetPosition(), out));
				
		}
		
		
	
	}
	
 }
