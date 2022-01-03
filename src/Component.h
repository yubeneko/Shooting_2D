#pragma once

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const struct InputState& keyState) {}
	virtual void OnUpdateWorldTransform() {}

	class Actor* GetOwner() { return mOwner; }
	int GetUpdateOrder() const { return mUpdateOrder; }

	bool GetEnabled() const { return mEnabled; }
	void SetEnabled(bool value) { mEnabled = value; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;

private:
	// コンポーネントの有効と無効を切り替える
	// これが false だとコンポーネントの如何なる処理も行わない
	bool mEnabled;
};