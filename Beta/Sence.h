#pragma once

enum class SceneType
{
	Title,
	Play,
	Credit,
	Ranking
};

class Sence
{
public:
	virtual ~Sence() {}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

class SceneManager;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void ChangeScene(SceneType newType);
	void UpdateCurrentScene();
	void DrawCurrentScene();

	SceneType GetCurrentSceneType() const { return currentType; }

private:
	Sence* currentScene;
	SceneType currentType;
};


