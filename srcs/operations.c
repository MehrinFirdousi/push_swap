/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:21:35 by mfirdous          #+#    #+#             */
/*   Updated: 2022/09/28 12:21:35 by mfirdous         ###   ########.fr       */
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
}

// sa and sb at the same time
void	ss(t_stack *a, t_stack *b)
{
	sa(a);
	sa(b);
}

// Take the first element at the top of b and put it at the top of a
void	pa(t_stack *a, t_stack *b)
{
	printf("1.top = %d, 2.top = %d\n", a->top, b->top);
	if (b->top != -1)
		a->stack[++a->top] = b->stack[b->top--];
	printf("1.top = %d, 2.top = %d\n", a->top, b->top);
}

//  Shift up all elements of stack a by 1
void	ra(t_stack *a)
{
	int	old_top;
	int	i;

	if (a->top != -1)
	{
		old_top = a->stack[a->top];
		i = a->top;
		while (--i > 0)
			a->stack[i] = a->stack[i - 1];
		a->stack[0] = old_top;
	}
}

// ra and rb at the same time
void	rr(t_stack *a, t_stack *b)
{
	ra(a);
	ra(b);
}

//  Shift down all elements of stack a by 1
void	rra(t_stack *a)
{
	int	old_last;
	int	i;

	if (a->top != -1)
	{
		old_last = a->stack[0];
		i = -1;
		while (++i < a->top)
			a->stack[i] = a->stack[i + 1];
		a->stack[a->top] = old_last;
	}
}

// rra and rrb at the same time
void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rra(b);
}

/* TODO:
	1.	./push_swap 2 3 5 1 0 6 4 9
		2 should be at the top of the stack and the stack will 
		grow from the right, so fill the stack array starting from
		end of args
		a->stack = {9, 4, 6, 0, 1, 5, 3, 2}
				0  1  2  3  4  5  6  7	8
*/