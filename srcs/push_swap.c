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
// optimization idea - when doing rb if b[top] <= mid, only rb if an upcoming element requires a pb, which would need it to be at the top

int count = 0;

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

// returns the index of element till where it is sorted
int	is_sorted(t_stack *s) 
{
	int	i;

	i = s->top + 1;
	while (--i > 0)
		if (s->stack[i] > s->stack[i - 1]) // checks asc order
			return (i);
	return (0);
}

// returns the index of the element from where the list is unsorted till the top
int check_sorted_from(t_stack *s, int i)
{
    while (++i <= s->top)
        if (s->stack[i] > s->stack[i - 1])
            return (s->top - i + 1);
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

// returns number of elements that were pushed
// remove chunk_end
void	push_chunks_ab(t_stack *a, t_stack *b, int chunk_end) // chunk_end is the end index of the chunk we're pushing
{
	int	mid;
	int	remain;
	int chunk_size;
	
	while (a->top > chunk_end + 1)
	{
		mid = find_mid(a, a->top, chunk_end, 1);
		remain = (a->top + chunk_end) / 2;
		chunk_size = a->top - remain;
		printf("mid = %d, chunk_size = %d\n", mid, chunk_size);
		(void)chunk_size;
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
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
}

int	push_chunk_a(t_stack *a, t_stack* b, int chunk_size)
{
	int count_pushed;
	int	remain;
	int	mid;
	int top;

	top = 1;
	count_pushed = 0;
	if (chunk_size > 2)
		count_pushed = chunk_size - 2;
	while (chunk_size > 2)
	{
		if (top)
		{
			remain = a->top - chunk_size / 2;
			mid = find_mid(a, a->top, a->top - chunk_size + 1, 1);
			while (a->top > remain)
			{
				if (a->stack[a->top] < mid)
					pb(a, b);
				else
					ra(a);
			}
			top = 0;
		}
		else
		{
			remain = a->top - chunk_size / 2;
			mid = find_mid(a, chunk_size - 1, 0, 1);
			while (a->top > remain)
			{
				rra(a);
				if (a->stack[a->top] < mid)
					pb(a, b);
			}
			top = 1;
		}
		chunk_size = chunk_size - chunk_size / 2;
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
	return (count_pushed);
}

// b to a
int	push_chunk_b(t_stack *a, t_stack *b, int chunk_size)
{
	int count_pushed;
	int	remain;
	int	mid;
	int top;

	top = 1;
	count_pushed = chunk_size;
	
	while (chunk_size > 1)
	{
		if (top)
		{
			remain = b->top - chunk_size / 2;
			mid = find_mid(b, b->top, b->top - chunk_size + 1, 0);
			while (b->top > remain)
			{
				if (b->stack[b->top] > mid)
				{
					pa(a, b);
					if (a->stack[a->top] > a->stack[a->top - 1]) // search for pa sa in output file to see if this was ever useful
						sa(a);
					count++;
				}	
				else
					rb(b);
			}
			top = 0;
		}
		else
		{
			remain = b->top - chunk_size / 2;
			mid = find_mid(b, chunk_size - 1, 0, 0);
			while (b->top > remain)
			{
				rrb(b);
				if (b->stack[b->top] > mid)
				{
					pa(a, b);
					if (a->stack[a->top] > a->stack[a->top - 1]) // search for pa sa in output file to see if this was ever useful
						sa(a);
					count++;
				}
			}
			top = 1;
		}
		chunk_size = chunk_size - chunk_size / 2;
	}
	if (chunk_size == 1)
	{
		pa(a, b);
		if (a->stack[a->top] > a->stack[a->top - 1]) // search for pa sa in output file to see if this was ever useful
			sa(a);
		count++;
	}	
	if (b->top > 0 && b->stack[b->top] < b->stack[b->top - 1])
		sb(b);
	return (count_pushed);
}

void	push_chunks_ba(t_stack *a, t_stack *b, int old_top)
{
	int chunk_size;
	int count_unsorted;
    int mid;
    int remain;
    int i;

	if (old_top > 1)
    {
        chunk_size = old_top - old_top / 2;
        push_chunks_ba(a, b, old_top / 2);
        remain = b->top - chunk_size / 2;
        mid = find_mid(b, 0, chunk_size, 0);
        i = 0;
        while (b->top > remain && i < 100)
        {
            if (b->stack[b->top] > mid)
            {
                pa(a, b);
                if (a->stack[a->top] > a->stack[a->top - 1]) // search for pa sa in output file to see if this was ever useful
                    sa(a);
            }
            else
                rb(b);
            i++;
        }
        count_unsorted = check_sorted_from(a, a->top - chunk_size / 2);
		//push_chunk_a(a, b, count_unsorted);
		i = -1;
        while (count_unsorted > 0 && ++i < 100)
        {
            count_unsorted = push_chunk_a(a, b, count_unsorted); // pushes 1 chunk from a to b
            count_unsorted = push_chunk_b(a, b, count_unsorted); // pushes that chunk back to a
            count_unsorted = check_sorted_from(a, a->top - count_unsorted);
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

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(a->top + 1);
	
	push_chunks_ab(a, b, 0);
	push_chunk_b(a, b, 1);
	push_chunk_b(a, b, 3);
	push_chunk_b(a, b, 5);
	push_chunk_b(a, b, 11);
	// push_chunks_ba(a, b, a->top + b->top + 1);
	printf("pa count = %d\n", count);
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}

// ********************* does full sort in desc *************
// void	sort_stack_desc(t_stack *a, t_stack *b)
// {
// 	int	max;

// 	while (b->top > 0)
// 	{
// 		max = find_max(b);
// 		if (b->top - max == 1)
// 			sb(b);
// 		else if (max >= b->top / 2)
// 			while (++max <= b->top)
// 				rb(b);
// 		else if (max < b->top / 2)
// 			while (--max >= -1)
// 				rrb(b);
// 		if (is_sorted(b) == 0)
// 			break ;
// 		pa(a, b);
// 	}
// 	while (b->top != -1)
// 		pa(a, b);
// }

