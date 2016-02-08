// Contains declarations specific for 'Quiz'

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
	
	//for input from user
	int get_answer_from_user();
	
	//for write operation by the host
	void set_question(char*);
	void set_option(char*, int);
	void set_key(int);
	void set_difficulty(int);
	
	//for file IO
	int number_of_elements();
	
};
