NAME = philo
CC = gcc
CFLAGS = -pthread -Wall -Wextra -Werror -g

src =	main.c\
		philo_utils.c
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(src:.c=.o))
REMOVE = rm -f

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;30m
NC = \033[0m

${NAME}:$(OBJ_DIR) ${OBJS}
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@printf "\r${GREEN}Compilation complete.\n"


all:${NAME}

$(OBJ_DIR)/%.o: %.c
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