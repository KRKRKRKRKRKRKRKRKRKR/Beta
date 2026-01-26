#include "CreditScene.h"
#include <Novice.h>

CreditScene::CreditScene(SceneManager* manager)
	: sceneManager(manager)
{
}
void CreditScene::Update(char* keys, char* preKeys)
{
	if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
	{
		sceneManager->ChangeScene(SceneType::Title);
	}
}
void CreditScene::Draw()
{
	Novice::ScreenPrintf(100, 100, "Credit Scene");
}