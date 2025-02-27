#pragma once
#include <chrono>
#include "sre/Camera.hpp"
#include "sre/SpriteAtlas.hpp"
#include "SDL.h"
#include "GameObject.h"
#include "../../Asteroids/Game/GameManager/GameManager.h"

class GameObject;

namespace MyEngine {

	class Engine {
	private:

		static Engine* _instance;
	public:
		static Engine* GetInstance() { return _instance; }
	public:
        ~Engine();
        std::shared_ptr<GameManager> gameManager;
		const glm::vec2 WIN_SIZE = glm::vec2(2000, 1200);
        std::shared_ptr<sre::SpriteAtlas> atlas;
		const std::chrono::duration<double> MAX_FRAME_TIME = std::chrono::duration<double>(1 / 60.0);
		Engine();
		void Init();
        void RestartGame();
		void ProcessEvents(SDL_Event& event);
		void Update(float);
		void Render();
        std::shared_ptr<GameManager> GetGameManager();

		float GetFPS() const { return 1.0 / time_elapsed.count(); }
		float GetTimeElapsedMs() const { return 1000 * time_elapsed.count(); }
		float GetTimeComputationMs() const { return 1000 * time_computation.count(); }

		glm::vec2 GetScreenSize() const;

		int GetFrame() const { return frame; }
		float GetTime() const { return time; }

		std::shared_ptr<MyEngine::GameObject> CreateGameObject(std::string name);
        void RemoveObject(std::shared_ptr<MyEngine::GameObject>);
        std::vector<std::shared_ptr<MyEngine::GameObject>> gameObjects = {};
	private:
		std::chrono::time_point<std::chrono::steady_clock>	time_start;
		std::chrono::time_point<std::chrono::steady_clock>	time_end;
		std::chrono::time_point<std::chrono::steady_clock>	time_end_computation;
		std::chrono::duration<double>						time_elapsed;
		std::chrono::duration<double>						time_computation;
		int frame;
		float time;

		unsigned char input = -1;
		bool b_show_debug_window = false;

		sre::Camera _camera;
	};
}