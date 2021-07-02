# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mspinnet <mspinnet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/20 13:14:06 by mspinnet          #+#    #+#              #
#    Updated: 2021/03/26 17:56:42 by mspinnet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	parser.c utils.c exec_env.c exec_exp.c exec_main.c exec_unset.c redir.c make_num_arg.c \
			make_args.c make_clear_str.c if_dollar.c del_pip.c prov_line.c delitel.c if_cov.c exec_cd_echo.c \
			exec_sys_funct.c pipes.c exec_utils.c redir2.c term.c term_utils.c term_utils2.c redir3.c\

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

GCC		= gcc

CFLAGS	= -Wall -Wextra -Werror -I. -g
RM		= rm -f

ARRC	= ar rc

LIBFT 	= make -C ./libft/

FT_H	= header.h

LIB		= libft.a

all:	${NAME}

.c.o:
		${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS} header.h
		${LIBFT}
		cp ./libft/libft.a .
		${GCC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} -ltermcap

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}
		${RM} history
		make fclean -C ./libft/
		
bonus:	all

re:		fclean all
