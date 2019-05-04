#pragma once
#include "Structs.h"
#include <unordered_map>
#include "GameObject.h"
#include "BaseComponent.h"
#include "TextureRenderComponent.h"

class Animator final : public BaseComponent
{
public:
	Animator();
	~Animator() = default;

	void AddAnimation(const std::shared_ptr<Animation>& animation);
	void AddAnimation(const std::vector<std::shared_ptr<Animation>>& animationSet);
	void SetActiveAnimation(const std::string& name);
	void SetActiveAnimation(const std::string& name, const std::shared_ptr<TextureRenderComponent>& comp);

	void Update() override{}
	void FixedUpdate() override{}
	void Render() override{}
	void SetTransform(float , float , float ) override{}
private:
	std::unordered_map<std::string, std::shared_ptr<Animation>> m_Animation;
};

