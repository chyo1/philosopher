RM=			rm -f
NAME=		philo
CC=			cc
CFLAGS=		-Wall -Wextra -Werror -g
SRCS_MAN=	main.c\
			init_info.c make_philo_thread.c\
			do_philo.c\
			do_eating.c do_sleeping.c do_thinking.c\
			print_error_n_exit.c
			
SRCS_BONUS= 
.PHONY : all bonus clean fclean re

all : $(NAME)

$(NAME) : LAST_ALL

LAST_ALL : $(SRCS_MAN)
	$(CC) $(CFLAGS) $(SRCS_MAN) -o $(NAME)
	touch LAST_ALL

bonus : LAST_BONUS

LAST_BONUS : $(SRCS_BONUS)
	$(CC) $(CFLAGS) $(SRCS_BONUS) -o $(NAME)
	touch LAST_BONUS

debug : $(SRCS_MAN)
		cc $(CFLAGS) -g -fsanitize=address -o debug $(SRCS_MAN)

clean :
	rm LAST_ALL
	rm LAST_BONUS

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all