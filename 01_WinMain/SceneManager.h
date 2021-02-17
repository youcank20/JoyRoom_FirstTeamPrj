#pragma once
/*
Scene을 관리하는 녀석
*/

/*
로딩 구현해오기!!
- 컴파일하면 로딩씬이 나옴
- 리소스 로딩만(사운드랑, 이미지)
- 프로그래스 바 있었으면 좋겠음
- 로딩이 끝나면 스페이스를 누르세요 라는 글이 나옴
- 스페이스 누르면 다음씬으로 넘어감
*/

class Scene;
class SceneManager
{
	Singleton(SceneManager)
private:
	/*
	key 값으로 value를 찾을때 매우 빠르다
	*/
	map<wstring, Scene*> mSceneList;
	Scene* mCurrentScene;						//현재 씬
	typedef map<wstring, Scene*>::iterator SceneIter;
public:
	SceneManager();
	~SceneManager();

	void Update();
	void Render(HDC hdc);

	void AddScene(const wstring& sceneName,Scene* scene);
	void LoadScene(const wstring& sceneName);

	bool CompareWithCurrentScene(const wstring& sceneName);
	Scene* GetCurrentScene() const { return mCurrentScene; }
};