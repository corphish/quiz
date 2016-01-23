#include <stdio.h>

void log(char log_type[], char log_tag[], char message[]) {
	FILE *log_file;
	log_file = fopen("log.txt","a");
	fprintf(log_file,"%s/%s : %s\n", log_type, log_tag, message);
	fclose(log_file);
}

extern void logv(char[] log_tag, char[] message) {
	log("V",log_tag,message);
}

extern void loge(char[] log_tag, char[] message) {
	log("E",log_tag,message);
}

extern void logi(char[] log_tag, char[] message) {
	log("I",log_tag,message);
}
