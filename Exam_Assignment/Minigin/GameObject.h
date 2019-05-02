#pragma once
#include <memory>

#include "SceneObject.h"
#include "TransformComponent.h"

class BaseComponent;
class GameObject final : public SceneObject
{
public:
	void Update() override;
	void FixedUpdate() override;
	void Render() const override;

	GameObject() = default;
	virtual ~GameObject();
	
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Translate(float x, float y, float z) const;
	void SetPosition(float x, float y, float z) const;
	void AddComponent(std::shared_ptr<BaseComponent> pComp);
	const std::shared_ptr<TransformComponent>& GetTransform() const { return m_Transform; }
	void RemoveComponent(std::shared_ptr<BaseComponent> pComp); 

	template <class T>
	std::shared_ptr<T> GetComponent()
	{
		const type_info& ti = typeid(T);
		for (const auto component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				return std::static_pointer_cast<T>(component);
		}
		return nullptr;
	}

	template <class T>
	bool HasComponent()
	{
		return GetComponent<T>() != nullptr;
	}

private:
	std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
	std::shared_ptr<TransformComponent> m_Transform = std::make_shared<TransformComponent>();;
	void SetComponentTransform() const;

};
