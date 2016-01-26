// Contains variables and function definitions related 'game'

// global variables
/* Difficulty:
				1 - Easy (default)
				2 - Medium
				3 - Hard
*/
int game_difficulty;

/* Score : Scoring is done on the basis of difficulty. 
		   score = difficulty * 25 */
int game_score;

/* Function to check and set difficulty*/
int check_and_set_difficulty(int new_difficulty);