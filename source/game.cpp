/*Function definitions for stuff specific to 'game', for example, scoring, setting difficulty*/

#include <log.h>

#define LOG_TAG "Game"

extern int game_difficulty;
extern int game_score;

extern int check_and_set_difficulty (int new_difficulty) {
	if(new_difficulty == 1) {
		logi(LOG_TAG,"Setting difficulty to easy");
		game_difficulty = new_difficulty;
		return 0;
	} else if(new_difficulty == 2) {
		logi(LOG_TAG,"Setting difficulty to medium");
		game_difficulty = new_difficulty;
		return 0;
	} else if(new_difficulty == 3) {
		logi(LOG_TAG,"Setting difficulty to hard");
		game_difficulty = new_difficulty;
		return 0;
	} else {
		game_difficulty = 1;
		loge(LOG_TAG,"Invalid difficulty setting! Using default");
		return 1;
	}
}