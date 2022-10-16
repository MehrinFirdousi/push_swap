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

// returns the index of the smallest element in the stack
int	find_min(t_stack *s)
{
	int	i;
	int	min_index;

	i = s->top + 1;
	min_index = s->top;
	while (--i >= 0)
		if (s->stack[i] < s->stack[min_index])
			min_index = i;
	return (min_index);
}

// returns the index of the largest element in the stack
int	find_max(t_stack *s)
{
	int	i;
	int	max_index;

	i = s->top + 1;
	max_index = s->top;
	while (--i >= 0)
		if (s->stack[i] > s->stack[max_index])
			max_index = i;
	return (max_index);
}

int	is_sorted(t_stack *s) 
{
	int	i;

	i = s->top + 1;
	while (--i > 0)
		if (s->stack[i] < s->stack[i - 1]) // for now checks desc order
			return (i);
	return (0);
}

int is_sorted_chunk(t_stack *s, int start)
{
	int	i;

	i = -1;
	while (++i < CHUNK_SIZE - 1)
		if (s->stack[start - i] > s->stack[start - i - 1])
			return (i);
	return (0);
}

void	sort_stack(t_stack *a, t_stack *b)
{
	int	min;

	while (a->top > 0)
	{
		min = find_min(a);
		if (a->top - min == 1)
			sa(a);
		else if (min >= a->top / 2)
			while (++min <= a->top)
				ra(a);
		else if (min < a->top / 2)
			while (--min >= -1)
				rra(a);
		if (is_sorted(a) == 0)
			break ;
		pb(a, b);
	}
	while (b->top != -1)
		pa(a, b);
}

void	sort_with_chunks(t_stack *a, t_stack *b)
{
	int	i;
	int	max;

	i = a->top + 1;
	while (i >= 0)
	{
		if (is_sorted_chunk(a, a->top) != 0) // chunk not sorted
			while (i - a->top < CHUNK_SIZE)
				pb(a, b);
		i = a->top;
		while (b->top != -1)
		{
			max = find_max(b);
			if (b->top - max == 1)
				sb(a);
			else if (max >= b->top / 2)
				while (++max <= b->top)
					rb(b);
			else if (max < a->top / 2)
				while (--max >= -1)
					rrb(b);
			if (is_sorted(b) == 0)
			{
				while (b->top != -1)
				{
					pa(a, b);
					ra(a);
				}
				break ;
			}	
			pa(a, b);
		}
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(a->top + 1);
	// print_stack(a, b);
	sort_stack(a, b);
	// print_stack(a, b);
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
