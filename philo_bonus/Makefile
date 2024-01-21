NAME 			= philo

CC 				= gcc

BONUS			= philo_bonus

INCLUDES		= includes/

FILES 			= 	philo_bonus			\
					utils_bonus			\
					parsing_bonus		\
					routine_bonus		\
					sem_handling_bonus	\
					monitor_bonus

SRCS 			= $(addsuffix .c, $(addprefix sources/, $(FILES)))

OBJS 			= ${SRCS:.c=.o}

CFLAGS 			= -Wall -Wextra -Werror -lpthread -pthread

# CURSOR MOVEMENTS
MOV_U			= \033[1A
MOV_D			= \033[1B
MOV_F			= \033[1C
MOV_B			= \033[1D

ERASE_ALL		= \033[0J

# COLORS 
YELLOW 	= \033[0;33m
GREEN 	= \033[0;32m
BLUE 	= \033[0;34m
RED		= \033[0;31m
PURPLE 	= \033[0;35m
CYAN 	= \033[0;36m
BLACK 	= \033[0;30
WHITE 	= \033[0;37m

RESET	= \033[0m

${NAME} : 	${OBJS}
		@echo "${GREEN} Compiling... ${RESET}"
		@${CC} ${CFLAGS} -I ${INCLUDES} ${SRCS} -o ${NAME}
		@echo "${MOV_U}${ERASE_ALL}${RED} Done ${RESET}"

%.o 	: %.c
		@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

all 	: 	${NAME}

clean 	:
		@rm -rf ${OBJS} ${BOBJS}
		@echo "${BLUE} Cleaned ${RESET}"

bonus: all
		@mv $(NAME) $(BONUS)

fclean	: clean
		@rm -rf ${NAME}
		@rm -rf ${BONUS}

re		: fclean all

.PHONY	: all clean fclean re ${NAME}