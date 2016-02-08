/*Function definitions for stuff specific to 'game', for example, scoring, setting difficulty*/

#include <log.h>
#include <quiz.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

#define LOG_TAG "Game"
char log_msg[128];

#define POINTS_ON_CORRECT_ANSWER	5
#define POINTS_ON_WRONG_ANSWER		-1 

int game_difficulty = 1;
int game_score = 0;

int temp_count = 0;

int total_questions, total_sorted_questions;
static int used_ids[60];
int used_id_count = 0, used_q_count = 0;

void sort_questions();

quiz game_quiz[60],new_quiz[60];

extern int check_and_set_difficulty (int new_difficulty) {
	if(new_difficulty == 1) {
		logi(LOG_TAG,"Setting difficulty to easy");
		game_difficulty = new_difficulty;
		sort_questions();
		return 0;
	} else if(new_difficulty == 2) {
		logi(LOG_TAG,"Setting difficulty to medium");
		game_difficulty = new_difficulty;
		sort_questions();
		return 0;
	} else if(new_difficulty == 3) {
		logi(LOG_TAG,"Setting difficulty to hard");
		game_difficulty = new_difficulty;
		sort_questions();
		return 0;
	} else {
		game_difficulty = 1;
		loge(LOG_TAG,"Invalid difficulty setting! Using default");
		sort_questions();
		return 1;
	}
	
}


extern int update_score(int type) {
	/*type - Determines whether user has given correct answer or not, then update score accordingly.
			 0 - Wrong Answer
			 1 - Correct Answer*/
	logi(LOG_TAG,"Updating Score");
	if(type)
		game_score += POINTS_ON_CORRECT_ANSWER;
	else
		game_score += POINTS_ON_WRONG_ANSWER;
}

void sort_questions() {
	logi(LOG_TAG,"Sorting questions based on difficulty");
	int i = 0,j = 0;
	for(i ; i < total_questions; i++) {
		if(game_quiz[i].get_difficulty() <= game_difficulty) {
			new_quiz[j] = game_quiz[i];
			j++;
		}
	}
	total_sorted_questions = j;
	sprintf(log_msg,"Sorted questions based on difficulty! New count : %d",total_sorted_questions);
	logi(LOG_TAG,log_msg);
}

unsigned int gen_rand_numbers() {
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	return rand()%total_questions;
}

int is_rand_available(int num) {
	int i;
	for(i = 0; i < used_id_count; i++) {
		if(used_ids[i] == num && temp_count < total_sorted_questions)
			return 1;		
	}
	return 0;
}

extern int return_round() {
	int temp;
	if(used_q_count == total_sorted_questions)
		return 0;
    temp = gen_rand_numbers();
	while(is_rand_available(temp)) {
		temp = gen_rand_numbers();
	}
	temp_count++;
	sprintf(log_msg,"Putting question no. %d", temp);
	logi(LOG_TAG,log_msg);
	used_q_count++;
	new_quiz[temp].print_round();
	if(new_quiz[temp].get_answer_from_user())
		update_score(1);
	else
		update_score(0);
	return 1;
}

extern void destroy_game() {
	logi(LOG_TAG,"Destroy!");
	used_id_count = 0;
	temp_count = 0;
	game_score = 0;
	used_q_count = 0;
}

int get_game_difficulty() {
	return game_difficulty;
}

extern int get_score() {
	return game_score;
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

