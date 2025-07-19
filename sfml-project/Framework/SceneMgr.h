#pragma once
class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	~SceneMgr() = default;

	std::unordered_map<SceneIds, Scene*> scenes;

	SceneIds startScene = SceneIds::Stage;
	SceneIds currentScene = SceneIds::None;
	SceneIds nextScene = SceneIds::None;

	int stageSelect = 0;
	int stageCleared = 1;

public:
	void Init();
	void Release();

	Scene* GetCurrentScene() { return scenes[currentScene]; }
	SceneIds GetCurrentSceneId() const { return currentScene; }
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void SetStageSelect(int select) { stageSelect = select; }
	int GetStageSelect() const { return stageSelect; }
	void SetStageCleared(int clear) { stageCleared = clear; }
	int GetStageCleared() const { return stageCleared; }
};

#define SCENE_MGR (SceneMgr::Instance())

