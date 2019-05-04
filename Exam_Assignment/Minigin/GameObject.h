#pragma once
#include <memory>

#include "SceneObject.h"
#include "TransformComponent.h"
#include <unordered_map>

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
	void RemoveComponent(std::shared_ptr<BaseComponent> pComp);

	void AddChild(const std::string& tag, std::shared_ptr<GameObject> child);
	void RemoveChild(const std::string& tag);
	std::shared_ptr<GameObject> GetChild(const std::string& tag);

	const std::shared_ptr<TransformComponent>& GetTransform() const { return m_Transform; }

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

	template <class T>
	bool HasComponentDerived()
	{
		for (const auto component : m_pComponents)
		{
			if (std::dynamic_pointer_cast<T>(component) != nullptr)
				return true;
		}
		return false;
	}

private:
	std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
	std::shared_ptr<TransformComponent> m_Transform = std::make_shared<TransformComponent>();;
	std::unordered_map<std::string, std::shared_ptr<GameObject>> m_Children;
	void SetComponentTransform() const;

};
