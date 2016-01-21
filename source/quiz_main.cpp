#include <iostream>
#include <log.h>

using namespace std;

#define LOG_TAG "quiz_main"

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
	
	void get_answer_from_user();
	
	void set_question(char*);
	void set_option(char*, int);
	void set_key(int);
	void set_difficulty(int);
	
};

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