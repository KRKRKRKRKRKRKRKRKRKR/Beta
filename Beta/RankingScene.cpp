#include "RankingScene.h"
#include <Novice.h>

RankingScene::RankingScene(SceneManager* manager)
	: sceneManager(manager)
{
}

void RankingScene::Update(char* keys, char* preKeys)
{
	if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
	{
		sceneManager->ChangeScene(SceneType::Title);
	}
}

void RankingScene::Draw()
{
	Novice::ScreenPrintf(100, 100, "Ranking Scene");
}