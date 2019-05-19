#pragma once
#include "Singleton.h"
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, SDL_Rect dst, double angle, SDL_Point center) const;
		void RenderTexture(const Texture2D& texture, SDL_Rect dst, SDL_Rect src, double angle, SDL_Point center) const;
		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

