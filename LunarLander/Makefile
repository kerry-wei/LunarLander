all:
	@echo "Compiling..."
	#g++ -o $(NAME) main.cpp EventLoopManager.cpp XInfo.cpp Utilities.cpp -I/usr/X11R6/include -L/usr/X11R6/lib -lX11 -lstdc++
	g++ -o LunarLander main.cpp GameContext.cpp GameStateAbstract.cpp GameStateNotStarted.cpp GameStateNotStartedSmallWindow.cpp GameStateStarted.cpp GameStatePausedSmallWindow.cpp GameStateGameOver.cpp GameStateGameOverSmallWindow.cpp GameStateLandingSucceed.cpp GameStateLandingSucceedSmallWindow.cpp CongratulationLayer.cpp GameOverLayer.cpp TerrainSegment.cpp LandingPad.cpp CollisionDetector.cpp WelcomeLayer.cpp TerrainPoint.cpp TerrainManager.cpp TerrainRenderer.cpp TerrainGenerator.cpp GameSceneManager.cpp GameState.cpp GameObjectManager.cpp EventLoopManager.cpp XInfo.cpp Utilities.cpp DrawableObject.cpp Spaceship.cpp -L/usr/X11R6/lib -lX11 -lstdc++

run: all
	@echo "Running..."
	./LunarLander
