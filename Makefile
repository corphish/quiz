all:	
	@make quiz
	
quiz: source/quiz_main.cpp
	@g++ -o intermediates/quiz.obj source/quiz_main.cpp
	
