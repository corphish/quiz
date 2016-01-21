all:	
	@make quiz
	@make exe
	
quiz: source/quiz_main.cpp source/log.cpp
	@g++ -Iinclude -c -g -o intermediates/log.obj source/log.cpp
	@g++ -Iinclude -c -g -o intermediates/quiz.obj source/quiz_main.cpp

	
exe: intermediates/*.obj
	@g++ -o output/quiz.exe intermediates/*.obj