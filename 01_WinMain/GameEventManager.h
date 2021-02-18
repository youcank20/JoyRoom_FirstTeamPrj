#pragma once

class IEvent;
class GameEventManager
{
	Singleton(GameEventManager)
private:
	//�� queue��� �ڷᱸ�� �����ؼ� queue�� �ٲ����
	queue<IEvent*> mEventQueue;
public:
	GameEventManager();
	~GameEventManager();

	void RemoveAllEvent();
	void Update();

	void PushEvent(class IEvent* event);
};