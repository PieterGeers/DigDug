#pragma once
#include <memory>

#include "SceneObject.h"
#include "BaseComponent.h"

namespace dae
{
	class GameObject : public SceneObject
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

		void AddComponent(std::shared_ptr<BaseComponent> pComp);
		//void RemoveComponent(std::shared_ptr<BaseComponent> pComp); //add this when / if needed

		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

	private:
		//component based
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
	};
}
