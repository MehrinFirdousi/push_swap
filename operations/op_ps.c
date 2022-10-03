/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:36:41 by mfirdous          #+#    #+#             */
/*   Updated: 2022/10/01 11:36:41 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Swap the first 2 elements at the top of stack a
void	sa(t_stack *a)
{
	int	temp;
	int	top;

	top = a->top;
	if (a->top > -1)
	{
		temp = a->stack[top];
		a->stack[top] = a->stack[top - 1];
		a->stack[top - 1] = temp;
	}
	ft_printf("sa\n");
}

// Swap the first 2 elements at the top of stack b
void	sb(t_stack *b)
{
	int	temp;
	int	top;

	top = b->top;
	if (b->top > -1)
	{
		temp = b->stack[top];
		b->stack[top] = b->stack[top - 1];
		b->stack[top - 1] = temp;
	}
	ft_printf("sb\n");
}

// Take the first element at the top of b and put it at the top of a
void	pa(t_stack *a, t_stack *b)
{
	if (b->top != -1)
		a->stack[++a->top] = b->stack[b->top--];
	ft_printf("pa\n");
}

// Take the first element at the top of a and put it at the top of b
void	pb(t_stack *a, t_stack *b)
{
	if (a->top != -1)
		b->stack[++b->top] = a->stack[a->top--];
	ft_printf("pb\n");
}

/* TODO:
	1.	./push_swap 2 3 5 1 0 6 4 9
		2 should be at the top of the stack and the stack will 
		grow from the right, so fill the stack array starting from
		end of args
		a->stack = {9, 4, 6, 0, 1, 5, 3, 2}
				0  1  2  3  4  5  6  7	8
*/