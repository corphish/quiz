#include <iostream>
#include <functions.h>
#include <log.h>
#include <game.h>

#define LOG_TAG "UI"

using namespace std;

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

extern void ui_error() {
	logi(LOG_TAG,"Entered ui_error!");
	clrscr();
	banner();
	cout << "ERROR:\n\tFatal error. Could not start up the game. Exiting.";
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

extern void ui_main () {
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