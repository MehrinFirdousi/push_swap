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

// finding the index of the mid value of the stack, i.e., the mid index value if the array was sorted 
// INEFFICIENT O(n^2) - use quick sort approach instead to find mid so average case is O(n)
int	find_mid(t_stack *s, int chunk_size)
{
	int	count_bigger;
	int	count_smaller;
	int	i;
	int	j;

	i = s->top;
	while (i >= chunk_size)
	{
		count_bigger = 0;
		count_smaller = 0;
		j = s->top;
		while (j >= chunk_size)
		{
			if (s->stack[j] > s->stack[i])
				count_bigger++; 
			else if (s->stack[j] < s->stack[i])
				count_smaller++;
			j--;
		}
		// printf("%d num: %d, cb = %d, cs = %d\n", i, s->stack[i], count_bigger, count_smaller);
		if (count_bigger == count_smaller - ((s->top - chunk_size) & 1)) // (top & 1) will be 0 when stack has odd number of elements
			break ;										  // (top & 1) will be 1 when stack has even number of elements
		i--;
	}
	return (s->stack[i]);
}

int	is_sorted(t_stack *s) 
{
	int	i;

	i = s->top + 1;
	while (--i > 0)
		if (s->stack[i] > s->stack[i - 1]) // for now checks asc order
			return (i);
	return (0);
}

int	is_sorted_desc(t_stack *s) 
{
	int	i;

	i = s->top + 1;
	while (--i > 0)
		if (s->stack[i] < s->stack[i - 1]) // for now checks desc order
			return (i);
	return (0);
}

void	push_chunks_ab(t_stack *a, t_stack *b)
{
	int	mid;
	int	remain;
	int chunk_size;

	while (a->top > 1)
	{
		mid = find_mid(a, 0);
		remain = a->top / 2;
		chunk_size = a->top - remain;
		// printf("mid = %d, chunk_size = %d\n", mid, chunk_size);
		while (a->top > remain)
		{
			if (a->stack[a->top] < mid)
				pb(a, b);
			else if (a->stack[0] < mid)
			{
				rra(a);
				pb(a, b);
			}
			else if (a->stack[a->top] >= mid)
				ra(a);
		}
		// print_stack(a, b);
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
}

void	push_chunks_ba(t_stack *a, t_stack *b, int old_top) // when calling, must call with  (a->top + b->top + 1) as chunk_size
{
	int	chunk_size;
	// int count_top;
	// int count_bottom;
	// int i;
	int	mid;

	if (old_top > 1)
	{
		chunk_size = old_top - old_top / 2;
		mid = find_mid(b, chunk_size - 1);
		push_chunks_ba(a, b, old_top / 2);
		printf("oldtop = %d, mid = %d, chunk_size = %d\n", old_top, mid, chunk_size);
		// while (b->top > chunk_size)
		// {
		// 	if (b->stack[b->top] > mid)
		// 		pa(a, b);
		// 	else if (b->stack[chunk_size - 1] > mid)
		// 		;
		// }
		// count_top = 0;
		// count_bottom = 0;
		// i = a->top;
		// while (--chunk_size >= 0)
		// {
		// 	while (b->stack[b->top] > a->stack[i])
		// }
	}
	else
	{
		// while ()
	}
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

void	sort_stack_desc(t_stack *a, t_stack *b)
{
	int	max;

	while (b->top > 0)
	{
		max = find_max(b);
		if (b->top - max == 1)
			sb(b);
		else if (max >= b->top / 2)
			while (++max <= b->top)
				rb(b);
		else if (max < b->top / 2)
			while (--max >= -1)
				rrb(b);
		if (is_sorted(b) == 0)
			break ;
		pa(a, b);
	}
	while (b->top != -1)
		pa(a, b);
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
	push_chunks_ab(a, b);
	// push_chunks_ba(a, b, a->top + b->top + 1);
	// sort_stack_desc(a, b);
	// sort_stack(a, b);
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}

// int is_sorted_chunk(t_stack *s, int start)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < CHUNK_SIZE - 1)
// 		if (s->stack[start - i] > s->stack[start - i - 1])
// 			return (i);
// 	return (0);
// }

// void	sort_with_chunks(t_stack *a, t_stack *b)
// {
// 	int	i;
// 	int	max;

// 	i = a->top + 1;
// 	while (i >= 0)
// 	{
// 		if (is_sorted_chunk(a, a->top) != 0) // if chunk is not sorted
// 			while (i - a->top < CHUNK_SIZE)
// 				pb(a, b);
// 		i = a->top;
// 		while (b->top != -1)
// 		{
// 			max = find_max(b);
// 			if (b->top - max == 1)
// 				sb(a);
// 			else if (max >= b->top / 2)
// 				while (++max < b->top)
// 					rb(b);
// 			else if (max < b->top / 2)
// 				while (--max >= -1)
// 					rrb(b);
// 			if (is_sorted(b) == 0)
// 				break ;
// 			pa(a, b);
// 		}
// 		while (b->top != -1)
// 		{
// 			pa(a, b);
// 			ra(a);
// 		}
// 	}
// }

