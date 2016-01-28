#include <iostream>
#include <string.h>
#include <log.h>
#include <quiz.h>
#include <game.h>

using namespace std;

#define LOG_TAG "quiz_main"

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

void quiz::get_answer_from_user() {
	char c;
	
	logi(LOG_TAG,"get_answer_from_user!!");
	cout << "Your choice (A/B/C/D) :";
	cin >> c;
	if(check_answer((int)(c - 64))) {
		cout << "Correct Answer!\n";
		//update_score(1);
	} else {
		cout << "Wrong Answer!\n";
		//update_score(0);
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