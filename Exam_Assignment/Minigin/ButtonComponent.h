#pragma once
#include "BaseComponent.h"
#include "TextRenderComponent.h"
#include <functional>

	class ButtonComponent final : public BaseComponent
	{
	public:
		ButtonComponent(std::string text, std::shared_ptr<dae::Font> font, SDL_Color color, std::function<void()> function);
		~ButtonComponent() = default;

		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void SetTransform(float x, float y, float z) override;

		void HooverOver(const SDL_Color& color);
		void ExecuteButton() const { m_Function(); }
		void ResetColor() const;

	private:
		std::shared_ptr<TextRenderComponent> m_Button;
		std::function<void()> m_Function;
		SDL_Color m_Color;
	};
