NAME		=	minishell

HEADER		=	./includes/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) #-fsanitize=address

SRCS		=	srcs/main.c \
				srcs/parsing/sep.c \
				srcs/parsing/pip.c \
				srcs/parsing/cmd.c \
				srcs/parsing/options.c \
				srcs/parsing/args.c \
				srcs/parsing/s_quote.c \
				srcs/parsing/d_quote.c \
				srcs/parsing/redir.c \
				srcs/parsing/redir_out.c \
				srcs/parsing/varenv.c \
				srcs/parsing/varenv_utils.c \
				srcs/parsing/error.c \
				srcs/parsing/free_parsing.c \
				srcs/parsing/syntax_error.c \
				srcs/shell/loop.c \
				srcs/shell/pipe.c \
				srcs/shell/exec/exec.c \
				srcs/shell/exec/additional.c \
				srcs/shell/execution.c \
				srcs/shell/env/env.c \
				srcs/shell/env/additional.c \
				srcs/shell/signal.c \
				srcs/builtin/cd.c \
				srcs/builtin/echo.c \
				srcs/builtin/unset.c \
				srcs/builtin/env.c \
				srcs/builtin/export/handler.c \
				srcs/builtin/export/print.c \
				srcs/builtin/exit.c \

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all
