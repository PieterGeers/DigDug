#pragma once
class GameObject;
class TransformComponent;
class BaseComponent
{
	friend class GameObject;
public:
	BaseComponent();
	virtual ~BaseComponent() = default;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render() = 0;
	virtual void SetTransform(float x, float y, float z) = 0;

	GameObject* GetGameObject() const { return m_pGameObject; }
	std::shared_ptr<TransformComponent> GetTransform() const;
protected:
	GameObject* m_pGameObject;

};

