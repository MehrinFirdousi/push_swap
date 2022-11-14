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

B_NAME	=	checker

SRCS	=	srcs/push_swap.c	srcs/parsing.c	srcs/push_swap_utils.c	srcs/kth_smallest.c \
			operations/op_ps.c	operations/op_r.c \

B_SRCS	=	bonus/checker_bonus.c \
			bonus/op_ps_bonus.c	bonus/op_r_bonus.c	bonus/op_both_bonus.c \
			srcs/parsing.c \

OBJS	=	${SRCS:.c=.o}

B_OBJS	=	${B_SRCS:.c=.o}

HEADER	=	include

LIBFT	=	libft/libft.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I ${HEADER}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${LIBFT} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${B_NAME}:	${LIBFT} ${B_OBJS}
			${CC} ${CFLAGS} ${B_OBJS} ${LIBFT} -o ${B_NAME}

${LIBFT}:	
			${MAKE} -C libft

all:		${NAME}

bonus:		${B_NAME}

clean:		
			rm -f ${OBJS}
			rm -f ${B_OBJS}
			${MAKE} -C libft clean

fclean:		clean
			rm -f ${NAME} 
			rm -f ${B_NAME} 
			${MAKE} -C libft fclean

re:			fclean all

.PHONY:		all clean fclean re bonus
