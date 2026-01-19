NAME		= minitalk

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

HDR			= minitalk.h

SRCS_CLIENT	= client.c utils.c
SRCS_SERVER	= server.c utils.c

OBJS_CLIENT	= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER	= $(SRCS_SERVER:.c=.o)

all: $(NAME)

$(NAME): client server

client: $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $@

server: $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $@

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	rm -f client server

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
