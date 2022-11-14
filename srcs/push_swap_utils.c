/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:49:29 by mfirdous          #+#    #+#             */
/*   Updated: 2022/11/14 16:55:18 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_index(t_stack *s, int num)
{
	int	i;

	i = s->top;
	while (s->stack[i] != num)
		i--;
	return (i);
}

int	is_sorted(t_stack *s)
{
	int	i;

	i = s->top + 1;
	while (--i > 0)
		if (s->stack[i] > s->stack[i - 1])
			return (i);
	return (0);
}

void	rotate(t_stack *a, t_stack *b, int *rb_flag)
{
	if (*rb_flag)
		rr(a, b);
	else
		ra(a);
	*rb_flag = 0;
}

int	push_max(t_stack *a, t_stack *b, int max)
{
	if (b->top - max == 1)
		sb(b);
	else if (max >= b->top / 2)
		while (++max <= b->top)
			rb(b);
	else if (max < b->top / 2)
		while (--max >= -1)
			rrb(b);
	pa(a, b);
	return (0);
}

void	sort_3(t_stack *a)
{
	int	*s;

	s = a->stack;
	if (s[2] > s[1] && s[1] < s[0] && s[0] > s[2])
		sa(a);
	else if (s[2] > s[1] && s[1] > s[0] && s[0] < s[2])
	{
		sa(a);
		rra(a);
	}
	else if (s[2] > s[1] && s[1] < s[0] && s[0] < s[2])
		ra(a);
	else if (s[2] < s[1] && s[1] > s[0] && s[0] > s[2])
	{
		sa(a);
		ra(a);
	}
	else if (s[2] < s[1] && s[1] > s[0] && s[0] < s[2])
		rra(a);
}
