NAME		=	minishell

HEADER		=	./includes/

LIBFT		=	libft/libft.a

CC			=	gcc

FLAGS		=	-Werror -Wall -Wextra -I $(HEADER) #-fsanitize=address

SRCS		=	srcs/main.c \
				srcs/parsing/sep.c \
				srcs/parsing/pip.c \
				srcs/parsing/cmdargs.c \
				srcs/parsing/protec.c \
				srcs/parsing/redir.c \
				srcs/parsing/varenv.c \
				srcs/parsing/error.c \
				srcs/shell/pipe.c \
				srcs/shell/exec.c \
				srcs/shell/execution.c \
				srcs/shell/env.c \
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
				$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all
