/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:41:47 by mfirdous          #+#    #+#             */
/*   Updated: 2022/09/26 21:41:47 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# ifdef _WIN32
#  define EXIT_SUCCESS 0
#  define EXIT_FAILURE 1
# else
#  include <unistd.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

# define CHUNK_SIZE 5

typedef struct s_stack
{
	int	*stack;
	int	top;
}	t_stack;

void	print_stack(t_stack *a, t_stack *b);
void	sa(t_stack *a);
void	sb(t_stack *a);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

void	ra(t_stack *a);
void	rb(t_stack *a);
void	rra(t_stack *a);
void	rrb(t_stack *a);

void	ss(t_stack *a, t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rrr(t_stack *a, t_stack *b);

#endif