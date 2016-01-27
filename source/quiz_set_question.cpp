#include <stdio.h>
#include <iostream>
#include <log.h>
#include <quiz.h>

#define LOG_TAG "quiz_set_question"

using namespace std;

/* Questions will be set to a binary file.
	Write questions and various other stuff with a separate executable.*/
	
void write_to_file(quiz new_quiz_input) {
	FILE *qfile;
	if(!qfile) {
		loge(LOG_TAG,"Could not open file for writing. Exiting!");
		return;
	} else {
		logi(LOG_TAG,"Starting file write");
	}
	qfile = fopen("qfile.bin","ab");
	fwrite(&new_quiz_input,sizeof(new_quiz_input),new_quiz_input.number_of_elements(),qfile);
	fclose(qfile);	
}

quiz get_user_input() {
	quiz q;
	char character_stuff[512];
	int int_stuff, i;
	cout << "Question :\n";
	gets(character_stuff);
	gets(character_stuff); // IDK why but user input for question just skips :/
	q.set_question(character_stuff);
	for(i = 0;i < 4;i++) {
		cout << "Option : "<< i+1 <<"\n";
		gets(character_stuff);
		q.set_option(character_stuff,i);
	}
	cout << "Answer (1-4) :";
	cin >> int_stuff;
	q.set_key(int_stuff);
	cout << "Difficulty Rating : ";
	cin >> int_stuff;
	q.set_difficulty(int_stuff);
	cout<<"Summary :\n";
	q.print_round();
	return q;
}

void ui() {
	int no;
	cout << "Total number of entries for this session: ";
	cin >> no;
	while(no) {
		cout << "Entries remaining "<< no << "\n";
		write_to_file(get_user_input());
		no--;
	}
	
}

int main() {
	ui();
	return 0;
}