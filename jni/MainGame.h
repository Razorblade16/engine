#pragma once

#include "defines.h"

namespace star
{
	struct Context;

	class SceneManager;
	class BaseScene;
	class TestScene;

	class MainGame
	{
	public:
		MainGame();
		~MainGame() {}

		status Initialize();
		status Run(const Context& context);
		status End();
	
	private:
		SceneManager* mSceneManager;
		TestScene* mTestScene;

		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		MainGame(const MainGame& t);
		MainGame& operator=(const MainGame& t);

	};
}
