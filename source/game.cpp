/*Function definitions for stuff specific to 'game', for example, scoring, setting difficulty*/

#include <log.h>
#include <quiz.h>
#include <stdio.h>
#include <fstream>

using namespace std;

#define LOG_TAG "Game"
char log_msg[128];

int game_difficulty = 1;
int game_score = 0;

int total_questions;
int used_ids[100];

quiz game_quiz[60];

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

int get_game_difficulty() {
	return game_difficulty;
}

int get_score() {
	return game_score;
}

int update_score(int type) {
	/*type - Determines whether user has given correct answer or not, then update score accordingly.
			 0 - Wrong Answer
			 1 - Correct Answer*/
	if(type)
		game_score += 25;
	else
		game_score -= 10;
}

int load_questions() {
	int count = 0;
	ifstream f("qfile.bin",ios::binary);
	while(f.read((char*)&game_quiz[count],sizeof(quiz))) {
		count++;
	}
	return count;
}

extern void get_question() {
	quiz q;
	static int got_valid_round = 0, count = 1;
	FILE *qfile;
	qfile = fopen("qfile.bin","r");
	while(!got_valid_round) {
		fread(&q,sizeof(q),q.number_of_elements(),qfile);
	}
}

extern int game_init() {
	logi(LOG_TAG,"Initializing game");
	if(total_questions = load_questions()) {
		sprintf(log_msg,"Total no. of quiz questions : %d",total_questions);
		logi(LOG_TAG,log_msg);
	} else {
		loge(LOG_TAG,"Empty/Corrupted qfile. Exiting!!");
		return 1;
	}
	logi(LOG_TAG,"Successfull initialization");
	return 0;
}

