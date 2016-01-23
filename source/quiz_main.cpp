#include <iostream>
#include <log.h>
#include <quiz.h>

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

void quiz::get_answer_from_user() {
	char c;
	
	logi(LOG_TAG,"get_answer_from_user!!");
	cout << "Your choice (A/B/C/D) :";
	cin >> c;
	check_answer((int)(c - 65));

}

void quiz::print_round() {
	logi(LOG_TAG,"print_round!!");
	cout << get_question() << endl << "A. "<< get_options(0) << " B. " << get_options(1) <<  " C. " << get_options(2) << " D. "<< get_options(3) << endl;
}

int main() {
	logi("quiz_main","start");
	return 0;
}