#include <iostream>
#include <functions.h>
#include <log.h>

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

extern void ui_main () {
	logi(LOG_TAG,"Entered ui_main!");
	int choice = 0;
	while(choice != 3) {
		clrscr();
		banner();
		cout << "1. Play QUIZ\n2. Help\n3. Exit\nYour choice (1-3) : "; 
		cin >> choice;
		if(choice == 1) {
			
		} else if(choice == 2) {
			ui_help();
		} else if(choice != 3 ) {
			cout << "Invalid input. Try again!!";
			getch();
		}
	}
	logi(LOG_TAG,"Exiting from UI");
}