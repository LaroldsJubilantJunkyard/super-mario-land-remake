#ifndef GAME_STATE_MANAGER
#define GAME_STATE_MANAGER __EDG_SIZE_TYPE__

typedef enum GameStates{GameState_FirstLoad,GameState_SplashScreen,GameState_StartScreen,GameState_Gameplay} GameStates;

extern GameStates  currentGameState, nextGameState;


void UpdateGameStateManager(void)BANKED;
void InitializeGameStateManager(void) BANKED;

#endif