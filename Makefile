CC = g++
CFLAGS = -Iinclude -c -g -w

all:	
	@make quiz
	@make exe
	@make question_set_full
	
quiz: source/quiz_main.cpp source/log.cpp source/main.cpp
	@$(CC) $(CFLAGS) -o intermediates/main.obj source/main.cpp	
	@$(CC) $(CFLAGS) -o intermediates/game.obj source/game.cpp
	@$(CC) $(CFLAGS) -o intermediates/log.obj source/log.cpp
	@$(CC) $(CFLAGS) -o intermediates/quiz.obj source/quiz_main.cpp
	@$(CC) $(CFLAGS) -o intermediates/ui.obj source/ui.cpp
	@$(CC) $(CFLAGS) -o intermediates/functions.obj source/function_ports.cpp


exe: intermediates/quiz.obj intermediates/log.obj intermediates/main.obj
	@$(CC) -o output/quiz.exe intermediates/quiz.obj intermediates/log.obj intermediates/main.obj intermediates/functions.obj intermediates/ui.obj intermediates/game.obj
	
	
question_set_full: source/quiz_set_question.cpp intermediates/log.obj intermediates/quiz.obj
	@$(CC) -Iinclude -c -g -o intermediates/quiz_set_question.obj source/quiz_set_question.cpp
	@$(CC) -o output/quiz_set_question.exe intermediates/quiz_set_question.obj intermediates/log.obj intermediates/quiz.obj 