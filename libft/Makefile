# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 10:38:51 by yviavant          #+#    #+#              #
#    Updated: 2020/03/06 22:11:45 by yviavant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CFLAGS		=	-Wall -Wextra -Werror -g

HEADER		=	libft.h

SRCS		=	ft_atoi.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_itoa.c \
				ft_itoa_base.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putnbr_base_fd.c \
				ft_putstr_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strcpy.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strcat.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strcmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strrev.c \
				get_next_line.c \
				ft_get_char_by_index.c \
				ft_free_array.c \
				ft_strequ.c \
				ft_minishell_split.c \
				ft_strip_extra_spaces.c \
				ft_only_spaces.c \
				ft_space_in_middle.c 
				
SRCS_BONUS	=	ft_lstnew_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c \

OBJ			=	${SRCS:.c=.o}

BONUS_OBJ	=	${SRCS_BONUS:.c=.o}

CC			= 	gcc

.c.o		:	${CC} ${CFLAGS} -c -I ${HEADER} $< -o ${<:.c=.o}

${NAME}		:	${OBJ} ${HEADER}
				ar rc ${NAME} ${OBJ}
				ranlib ${NAME}

all			:	${NAME}

bonus		:	${BONUS_OBJ} ${OBJ} ${HEADER}
				ar rc ${NAME} ${BONUS_OBJ} ${OBJ}
				ranlib ${NAME}

clean:
				rm -f ${OBJ} ${BONUS_OBJ}

fclean		:	clean
				rm -f ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean
