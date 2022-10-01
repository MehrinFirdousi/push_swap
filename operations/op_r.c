/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:31:55 by mfirdous          #+#    #+#             */
/*   Updated: 2022/10/01 11:31:55 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Shift up all elements of stack a by 1
void	ra(t_stack *a)
{
	int	old_top;
	int	i;

	if (a->top != -1)
	{
		old_top = a->stack[a->top];
		i = a->top + 1;
		while (--i > 0)
			a->stack[i] = a->stack[i - 1];
		a->stack[0] = old_top;
	}
	ft_printf("ra\n");
}

// Shift up all elements of stack b by 1
void	rb(t_stack *b)
{
	int	old_top;
	int	i;

	if (b->top != -1)
	{
		old_top = b->stack[b->top];
		i = b->top + 1;
		while (--i > 0)
			b->stack[i] = b->stack[i - 1];
		b->stack[0] = old_top;
	}
	ft_printf("rb\n");
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
	ft_printf("rra\n");
}

// Shift down all elements of stack b by 1
void	rrb(t_stack *b)
{
	int	old_last;
	int	i;

	if (b->top != -1)
	{
		old_last = b->stack[0];
		i = -1;
		while (++i < b->top)
			b->stack[i] = b->stack[i + 1];
		b->stack[b->top] = old_last;
	}
	ft_printf("rrb\n");
}