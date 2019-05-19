#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
	if (mRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	SceneManager::GetInstance().Render();

	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect dst, double angle, SDL_Point center) const
{
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_NONE);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect dst, SDL_Rect src, double angle,
	SDL_Point center) const
{
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, angle, &center, SDL_FLIP_NONE);
}