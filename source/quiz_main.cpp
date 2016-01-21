#include <iostream>

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
	
	void set_question(char*);
	void set_option(char*, int);
	void set_key(int);
	void set_difficulty(int);
	
};

char* quiz::get_question() {
	return question;
}

char* quiz::get_options(int index) {
	return options[index];
}

int quiz::check_answer(int user_key) {
	if(key == user_key) 
		return 1;
	return 0;
}

int quiz::get_difficulty() {
	return difficulty;
}

void quiz::print_round() {
	
}

int main() {
	return 0;
}