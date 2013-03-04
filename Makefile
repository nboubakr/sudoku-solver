CC=gcc
OPT=-Wall
EXEC=sudoku

All:welcome_msg $(EXEC) quit_msg

welcome_msg:
	@clear
	@echo
	@echo " #############################"
	@echo " #                           #"
	@echo " #       SUDOKU SOLVER       #"
	@echo " #                           #"
	@echo " #############################"
	@echo

# Compile main.c
$(EXEC): main.c
	@echo
	@echo "---> Compiling and Linking Sudoku Solver..."
	@$(CC) main.c -o $(EXEC) #$(OPT)
	
quit_msg:
	@echo
	@echo "    All Done !"
	@echo
	@echo "Now, run: ./sudoku"
	@echo