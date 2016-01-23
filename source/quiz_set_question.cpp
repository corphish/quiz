#include <stdio.h>
#include <log.h>
#include <quiz.h>

using namespace std;

/* Questions will be set to a binary file.
	Write questions and various other stuff with a separate executable.*/
	
void write_to_file(quiz new_quiz_input) {
	FILE *qfile;
	qfile = fopen("qfile.bin","ab");
	fwrite(&new_quiz_input,sizeof(new_quiz_input),new_quiz_input.number_of_elements(),qfile);
	fclose(qfile);
	
}

int main() {
	
	return 0;
}