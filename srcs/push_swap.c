/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:48:36 by mfirdous          #+#    #+#             */
/*   Updated: 2022/09/26 21:48:36 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_stack_full(t_stack *a, t_stack *b)
{
	int	max;
	int	max2;
	int	max_dist;
	int	max2_dist;

	while (b->top > 0)
	{
		max = find_closest(b, &max_dist, 0);
		max2 = find_closest(b, &max2_dist, 1);
		if (max2_dist < max_dist)
		{
			push_max(a, b, max2);
			max = get_index(b, find_kth_smallest(b, b->top));
			push_max(a, b, max);
			sa(a);
		}
		else
			push_max(a, b, max);
	}
	while (b->top > -1)
		pa(a, b);
}

void	push_ab(t_stack *a, t_stack *b, int split)
{
	t_chunk	c;
	int		rb_flag;

	rb_flag = 0;
	find_median(a, &c, split);
	while (a->top > c.remain)
	{
		if (a->stack[a->top] < c.pivot || a->stack[0] < c.pivot)
		{
			if (rb_flag)
				rb(b);
			rb_flag = 0;
			if (a->stack[0] < c.pivot && a->stack[a->top] >= c.pivot)
				rra(a);
			pb(a, b);
			if (b->stack[b->top] < c.sub_pivot)
				rb_flag = 1;
		}
		else if (a->stack[a->top] >= c.pivot)
			rotate(a, b, &rb_flag);
	}
}

int	find_limit(t_stack *a)
{
	int	limit;

	limit = 2;
	while ((a->top + 1) / limit > 75)
		limit *= 2;
	return (limit);
}

void	push_chunks(t_stack *a, t_stack *b)
{
	int	limit;
	int	i;

	while (a->top > 1)
	{
		limit = find_limit(a);
		i = -1;
		while (++i < limit / 2)
			push_ab(a, b, limit);
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(a->top + 1);
	if (is_sorted(a) == 0)
		exit(0);
	if (a->top == 2)
		sort_3(a);
	else
	{
		push_chunks(a, b);
		sort_stack_full(a, b);
		if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
			sa(a);
	}
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
