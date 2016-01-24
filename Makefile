all:	
	@make quiz
	@make exe
	@make question_set_full
	
quiz: source/quiz_main.cpp source/log.cpp source/main.cpp
	@g++ -Iinclude -c -g -o intermediates/main.obj source/main.cpp
	@g++ -Iinclude -c -g -o intermediates/log.obj source/log.cpp
	@g++ -Iinclude -c -g -o intermediates/quiz.obj source/quiz_main.cpp
	@g++ -Iinclude -c -g -o intermediates/functions.obj source/function_ports.cpp


exe: intermediates/quiz.obj intermediates/log.obj intermediates/main.obj
	@g++ -o output/quiz.exe intermediates/quiz.obj intermediates/log.obj intermediates/main.obj intermediates/functions.obj
	
	
question_set_full: source/quiz_set_question.cpp intermediates/log.obj intermediates/quiz.obj
	@g++ -Iinclude -c -g -o intermediates/quiz_set_question.obj source/quiz_set_question.cpp
	@g++ -o output/quiz_set_question.exe intermediates/quiz_set_question.obj intermediates/log.obj intermediates/quiz.obj 