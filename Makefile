# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/26 21:18:38 by mfirdous          #+#    #+#              #
#    Updated: 2022/09/26 21:18:38 by mfirdous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	push_swap

SRCS	=	srcs/push_swap.c	srcs/setup.c \
			operations/op_ab.c	operations/op_ps.c	operations/op_r.c \
			srcs/kth-smallest.c

OBJS	=	${SRCS:.c=.o}

HEADER	=	include

LIBFT	=	libft/libft.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I ${HEADER}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${LIBFT} ${OBJS}
			${CC} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:	
			${MAKE} -C libft

all:		${NAME}

clean:		
			rm -f ${OBJS}
			${MAKE} -C libft clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

.PHONY:		all clean fclean re
