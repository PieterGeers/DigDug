#pragma once

struct SDL_Window;

namespace dae
{
	class Minigin
	{
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
	public:
		void Initialize();
		virtual void LoadGame() const;
		void Cleanup();
		void Run();
	protected:
		int GetMs()const { return msPerFrame; }
	};
}