#include "Sence.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "CreditScene.h"
#include "RankingScene.h"

SceneManager::SceneManager()
	: currentScene(nullptr), currentType(SceneType::Title)
{
	ChangeScene(SceneType::Title);
}

SceneManager::~SceneManager()
{
	if (currentScene)
	{
		delete currentScene;
	}
}

void SceneManager::ChangeScene(SceneType newType)
{
	if (currentScene)
	{
		delete currentScene;
		currentScene = nullptr;
		currentType = newType;
	}
	switch (newType)
	{
	case SceneType::Title:
		currentScene = new TitleScene();
		break;
	case SceneType::Play:
		currentScene = new PlayScene();
		break;
	case SceneType::Credit:
		currentScene = new CreditScene();
		break;
	case SceneType::Ranking:
		currentScene = new RankingScene();
		break;
	}
}

void SceneManager::UpdateCurrentScene()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::DrawCurrentScene()
{
	if (currentScene)
	{
		currentScene->Draw();
	}
}