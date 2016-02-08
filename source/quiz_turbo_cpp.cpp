#include <iostream.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <process.h>


#define LOG_TAG "Quiz"
char log_msg[128];

// from log.cpp
void log(char log_type[], char log_tag[], char message[]) {
	FILE *log_file;
	log_file = fopen("log.txt","a");
	fprintf(log_file,"%s/%s : %s\n", log_type, log_tag, message);
	fclose(log_file);
}

void logv(char log_tag[], char message[]) {
	log("V",log_tag,message);
}

void loge(char log_tag[], char message[]) {
	log("E",log_tag,message);
}

void logi(char log_tag[], char message[]) {
	log("I",log_tag,message);
}

// from quiz.h
class quiz {
	//class variables
	char question[512];
	char options[4][128];
	int key;
	int difficulty;
	public:
	//function definitions
	char* get_question();
	char* get_options(int);
	int check_answer(int);
	int get_difficulty();
	void print_round();
	
	//for input from user
	int get_answer_from_user();
	
	//for write operation by the host
	void set_question(char*);
	void set_option(char*, int);
	void set_key(int);
	void set_difficulty(int);
	
	//for file IO
	int number_of_elements();
	
};

// from quiz_main.cpp
char* quiz::get_question() {
	logi(LOG_TAG,"get_question()!!");
	return question;
}

char* quiz::get_options(int index) {
	logi(LOG_TAG,"get_options()!!");
	return options[index];
}

int quiz::check_answer(int user_key) {	
	logi(LOG_TAG,"check_answer()!!");
	if(key == user_key) 
		return 1;
	return 0;
}

int quiz::get_difficulty() {
	logi(LOG_TAG,"get_difficulty()!!");
	return difficulty;
}

int quiz::number_of_elements() {
		return 4;
	}

int quiz::get_answer_from_user() {
	char c;
	
	logi(LOG_TAG,"get_answer_from_user!!");
	cout << "Your choice (A/B/C/D) :";
	cin >> c;
	if(check_answer((int)(c - 64))) {
		cout << "Correct Answer!\n";
		return 1;
	} else {
		cout << "Wrong Answer!\n";
		return 0;
	}
}

void quiz::print_round() {
	logi(LOG_TAG,"print_round!!");
	cout << get_question() << endl << "A. "<< get_options(0) << "\nB. " << get_options(1) <<  "\nC. " << get_options(2) << "\nD. "<< get_options(3) << endl;
}

void quiz::set_question(char c[]) {
	strcpy(question,c);
}

void quiz::set_option(char c[], int index) {
	strcpy(options[index],c);
}

void quiz::set_key(int k) {
	key = k;
}

void quiz::set_difficulty(int d) {
	difficulty = d;
}

// from game.cpp
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

int check_and_set_difficulty (int new_difficulty) {
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


int update_score(int type) {
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

int return_round() {
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

void destroy_game() {
	logi(LOG_TAG,"Destroy!");
	used_id_count = 0;
	temp_count = 0;
	game_score = 0;
	used_q_count = 0;
}

int get_game_difficulty() {
	return game_difficulty;
}

int get_score() {
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

void get_question() {
	quiz q;
	static int got_valid_round = 0, count = 1;
	FILE *qfile;
	qfile = fopen("qfile.bin","r");
	while(!got_valid_round) {
		fread(&q,sizeof(q),q.number_of_elements(),qfile);
	}
}

int game_init() {
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

// from ui.cpp
void banner () {
	cout << "***********************" << endl;
	cout << "*         QUIZ        *" << endl;
	cout << "***********************" << endl;
}

void ui_help() {
	logi(LOG_TAG,"Entered ui_help!");
	clrscr();
	banner();
	cout << "HELP:\n\tYou will be prompted on what you need to press.\n\tAll you need to do is press vaild key and press enter.";
	getch();
}

void ui_error() {
	logi(LOG_TAG,"Entered ui_error!");
	clrscr();
	banner();
	cout << "ERROR:\n\tFatal error. Could not start up the game. Exiting.";
	getch();
}

void ui_score() {
	logi(LOG_TAG,"Entered ui_score!");
	clrscr();
	banner();
	cout << "Game Over :\n\tYour score - " << get_score() <<"\n\nPress any key to continue...";
	getch();
}

void ui_set_difficulty() {
	logi(LOG_TAG,"Entered ui_set_difficulty!");
	int choice = 0;
	clrscr();
	banner();
	cout<< "Choose Difficulty :\n1. Easy\n2. Medium\n3. Hard\nYour choice (1-3) : ";
	cin >> choice;
	if(check_and_set_difficulty(choice))
		cout << "Invalid input! Setting difficulty to easy. Good Luck!!";
	else
		cout << "Good luck!";
	getch();
}

void ui_main () {
	int choice = 0;
	while(choice != 3) {
		logi(LOG_TAG,"Entered ui_main!");
		clrscr();
		banner();
		cout << "1. Play QUIZ\n2. Help\n3. Exit\nYour choice (1-3) : "; 
		cin >> choice;
		if(choice == 1) {
			ui_set_difficulty();
			clrscr();
			banner();
			while(return_round()) {
				getch();
				clrscr();
				banner();
			}
			ui_score();
			destroy_game();
		} else if(choice == 2) {
			ui_help();
		} else if(choice != 3 ) {
			loge(LOG_TAG,"main: Invalid user input.");
			cout << "Invalid input. Try again!!";
			getch();
		}
	}
	logi(LOG_TAG,"Exiting from UI");
}

int check_for_qfile() {
	FILE *f;
	f = fopen("qfile.bin", "rb");
	if(!f)
		return 1;
	fclose(f);
	return 0;
}

void init() {
	logi(LOG_TAG,"Deleting old log file!");
	if(remove("log.txt"))
		loge(LOG_TAG,"No log file! First start?");
	else
		logi(LOG_TAG,"Succesfully deleted log file");
	logi(LOG_TAG,"Welcome to QUIZ");
	logi(LOG_TAG,"Starting up init process!");
	logi(LOG_TAG,"Checking for qfile!");
	if (check_for_qfile()) {
			ui_error();
			loge(LOG_TAG,"qfile not found! Exiting");
			exit(0);
	} else 
		logi(LOG_TAG,"qfile found!");
	if(game_init()) exit(0);	
	logi(LOG_TAG,"Starting up UI");
	ui_main();
	
}

int main() {
	init();
	return 0;
}