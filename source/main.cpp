#include <stdio.h>
#include <stdlib.h>

#include <ui.h>
#include <log.h>
#include <game.h>

#define LOG_TAG "Main"

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
	logi(LOG_TAG,"Starting up UI");
	game_init();
	ui_main();
	
}

int main() {
	init();
	return 0;
}