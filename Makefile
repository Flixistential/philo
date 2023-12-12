NAME = philo
CC = gcc
#CFLAGS = -pthread -Wall -Wextra -Werror -fsanitize=thread -g
CFLAGS = -pthread -Wall -Wextra -Werror -g

src =	./src/main.c\
		./src/philo_utils.c\
		./src/time.c\
		./src/init_philo.c\
		./src/parse.c\
		./src/monitoring.c\
		./src/exit.c
OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(src)))
REMOVE = rm -f

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;30m
NC = \033[0m

${NAME}:$(OBJ_DIR) ${OBJS}
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@printf "\r${GREEN}Compilation complete.\n"


all:${NAME}

$(OBJ_DIR)/%.o: src/%.c
	@printf "${GREEN}Compiling: ${YELLOW}$(CC) $(CFLAGS) -c $< -o $@"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\r\033[K"  # Clear the line

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
clean :
		@${REMOVE} ${OBJS}
		@echo "${RED}Object files removed."
	

fclean :clean
		@${REMOVE} ${NAME}
		@echo "${RED}Executable removed."
re:fclean all
 
.PHONY: all clean fclean re