#include "PlayScene.h"

PlayScene::PlayScene(SceneManager* manager)
	: sceneManager(manager), gamePlay_()
{
}

void PlayScene::Update(char* keys, char* preKeys)
{
	gamePlay_.Update(keys, preKeys);

	if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
	{
		sceneManager->ChangeScene(SceneType::Ranking);
	}
}

void PlayScene::Draw()
{
	gamePlay_.Draw();
}	
