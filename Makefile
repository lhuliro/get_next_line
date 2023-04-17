NAME = getnextlinebonus.a
SRCS = get_next_line.c get_next_line_utils.c
SRCS_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS = $(SRCS:%.c=%.o)

OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

all: $(NAME)

$(NAME):
	gcc -c -Wall -Wextra -Werror -D BUFFER_SIZE=42 $(SRCS)
	ar rcs $(NAME) $(OBJS)

bonus:
	gcc -c -Wall -Wextra -Werror -D BUFFER_SIZE=42 $(SRCS_BONUS)
	ar rcs $(NAME) $(OBJS_BONUS)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all