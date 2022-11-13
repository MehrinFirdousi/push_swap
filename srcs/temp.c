/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:45:25 by mfirdous          #+#    #+#             */
/*   Updated: 2022/11/13 13:20:09 by mfirdous         ###   ########.fr       */
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

// or find average of min and max element and use it as a measure
/**
 * @brief finding the index of the mid value of the stack, i.e., the mid index value if the array was sorted 
 * 
 * @param s stack a or b
 * @param start index of element to start the search from
 * @param end index of the element to search till
 * @param asc enter 1 for ascending order, 0 for descending order
 * @return returns the median of values in the given range
 */
int	find_mid(t_stack *s, int start, int end, int asc)
{
	int	count_bigger;
	int	count_smaller;
	int	i;
	int	j;

	i = start;
	while (i >= end)
	{
		count_bigger = 0;
		count_smaller = 0;
		j = start;	
		while (j >= end)
		{
			if (s->stack[j] > s->stack[i])
				count_bigger++; 
			else if (s->stack[j] < s->stack[i])
				count_smaller++;
			j--;
		}
		// printf("%d num: %d, cb = %d, cs = %d\n", i, s->stack[i], count_bigger, count_smaller);
		if (asc)
		{
			if (count_bigger == count_smaller - ((s->top - end) & 1)) // (top & 1) will be 0 when stack has odd number of elements
				break ;										  // (top & 1) will be 1 when stack has even number of elements
		}	
		else
		{
			if (count_smaller == count_bigger - ((s->top - end) & 1))
				break;
		}	
		i--;
	}
	return (s->stack[i]);
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

// pushing one chunk from a to b
int	push_chunk_a(t_stack *a, t_stack* b, int chunk_size)
{
	int count_pushed;
	int	count_rotated;
	int	remain;
	int	mid;
	int test;

	count_pushed = 0;
	if (chunk_size > 2)
		count_pushed = chunk_size - 2;
	count_rotated = 0;
	while (chunk_size > 1)
	{
		remain = a->top - chunk_size / 2;
		mid = find_pivot(a, a->top - chunk_size + 1, &test, &test);
		while (a->top > remain)
		{
			if (a->stack[a->top] < mid)
			{
				pb(a, b);
				if (b->stack[b->top] < b->stack[b->top - 1])
					sb(b);
			}	
			else
			{
				ra(a);
				count_rotated++;
			}
		}
		while (--count_rotated >= 0) // restoring the chunk
			rra(a);
		count_rotated = 0;
		chunk_size = chunk_size - chunk_size / 2;
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
	return (count_pushed);
}

// pushes top chunk from b to a 
void	push_chunk_b(t_stack *a, t_stack *b, int chunk_size)
{
	int	remain;
	int	mid;
	int	count_rotated;
	int	last_chunk_size;
	int old_top;
	int test;

	count_rotated = 0;
	old_top =  a->top + b->top + 1;
	last_chunk_size =  old_top - old_top / 2;
	while (chunk_size > 1)
	{
		remain = b->top - chunk_size / 2;
		mid = find_pivot(b, b->top - chunk_size + 1, &test, &test);
		while (b->top > remain)
		{
			if (b->stack[b->top] > mid)
			{
				pa(a, b);
				if (a->stack[a->top] > a->stack[a->top - 1]) // search for pa sa in output file to see if this was ever useful
					sa(a);
			}
			else
			{
				rb(b);
				count_rotated++;
			}
		}
		if (b->top >= last_chunk_size)
			while (--count_rotated >= 0)
				rrb(b);
		count_rotated = 0;
		chunk_size = chunk_size - chunk_size / 2;
	}
	if (chunk_size == 1)
	{
		pa(a, b);
		if (a->stack[a->top] > a->stack[a->top - 1]) // search for pa sa in output file to see if this was ever useful
			sa(a);
	}
}

void	push_chunks_ba(t_stack *a, t_stack *b, int old_top)
{
	int chunk_size;
	int unsorted_c;
    // int mid;
    // int remain;

	if (old_top > 1)
    {
        chunk_size = old_top - old_top / 2;
        push_chunks_ba(a, b, old_top / 2);
		push_chunk_b(a, b, chunk_size);
        unsorted_c = count_unsorted(a, 0);
		// printf("for chunk %d,, unsorted = %d\n", chunk_size, unsorted_c);
		// push_chunk_a(a, b, count_unsorted);
        while (unsorted_c > 0)
        {
            unsorted_c = push_chunk_a(a, b, unsorted_c); // pushes 1 chunk from a to b
            push_chunk_b(a, b, unsorted_c); // pushes that chunk back to a
			// printf("for chunk %d, ", unsorted_c);
            unsorted_c = count_unsorted(a, 0);
			// printf("unsorted = %d\n", unsorted_c);
		}
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
	int	half;

	half = (b->top + a->top) / 2;
	while (b->top > half)
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
	while (b->top > half)
		pa(a, b);
}

