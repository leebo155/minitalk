CC = cc
CFLAGS = -Wall -Wextra -Werror
LD = ar
LDFLAGS = rcs
INC = -Iinclude
NAME = server client
SRCS = src/server_main.c \
	   src/client_main.c
BONUS_SRCS = src/server_main_bonus.c \
			 src/client_main_bonus.c
LIBFT = lib/libft.a
FT_PRINTF = lib/libftprintf.a
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
ALL_DONE = src/.all.tmp
BONUS_DONE = src/.bonus.tmp

.PHONY: all clean fclean re bonus

all: $(ALL_DONE)

bonus: $(BONUS_DONE)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(ALL_DONE) $(BONUS_DONE)

re: fclean
	$(MAKE) all

$(NAME):

$(ALL_DONE): $(LIBFT) $(FT_PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(INC) src/server_main.o $(LIBFT) $(FT_PRINTF) -o server
	$(CC) $(CFLAGS) $(INC) src/client_main.o $(LIBFT) $(FT_PRINTF) -o client
	rm -f $(BONUS_DONE)
	touch $@

$(BONUS_DONE): $(LIBFT) $(FT_PRINTF) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(INC) src/server_main_bonus.o $(LIBFT) $(FT_PRINTF) -o server
	$(CC) $(CFLAGS) $(INC) src/client_main_bonus.o $(LIBFT) $(FT_PRINTF) -o client
	rm -f $(ALL_DONE)
	touch $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^
