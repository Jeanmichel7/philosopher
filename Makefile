# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrasser <jrasser@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 16:18:36 by jrasser           #+#    #+#              #
#    Updated: 2023/09/01 21:35:49 by jrasser          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= srcs/main.c \
			srcs/checker.c \
			srcs/get_args.c \
			srcs/time.c \
			srcs/kill.c \
			srcs/manage_forks.c

OBJS 		= ${SRCS:.c=.o}
RM			= rm -f
NAME 		= philo
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-g3 -fsanitize=thread

${NAME}	:	${OBJS}
			gcc -o ${NAME} ${OBJS} -lpthread -D_REENTRANT ${CFLAGS}

all :	${NAME}

clean :
		${RM} ${OBJS}

fclean : clean
		${RM} ${NAME}

re : 	fclean all

.PHONY:	all clean fclean re
