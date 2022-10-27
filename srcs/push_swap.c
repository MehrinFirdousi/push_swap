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

/**
 * @brief TODO
 * 
 * 1. make push_chunk_a return the number of elements pushed to b
 * 2. change param of push_chunk_a to chunk_size itself instead
 * 
 * 
 *  
 */
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
int	find_mid(t_stack *s, int start, int end)
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
		if (count_bigger == count_smaller - ((s->top - end) & 1)) // (top & 1) will be 0 when stack has odd number of elements
			break ;										  // (top & 1) will be 1 when stack has even number of elements
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
		if (s->stack[i] > s->stack[i - 1]) // for now checks asc order
			return (i);
	return (0);
}

// returns the index of the element from where the list is unsorted till the top
int check_sorted_from(t_stack *s, int i)
{
	while (++i <= s->top)
		if (s->stack[i] > s->stack[i - 1])
			return (i);
	return (i);
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
		mid = find_mid(a, a->top, chunk_end);
		remain = (a->top + chunk_end) / 2;
		// chunk_size = a->top - remain;
		// printf("mid = %d, chunk_size = %d\n", mid, chunk_size);
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

void	push_chunk_a(t_stack *a, t_stack* b, int chunk_end)
{
	int chunk_size;
	int	remain;
	int	mid;
	int top;

	chunk_size = a->top - chunk_end + 1;
	top = 1;
	while (chunk_size > 2)
	{
		if (top)
		{
			remain = a->top - chunk_size / 2;
			mid = find_mid(a, a->top, a->top - chunk_size + 1);
			printf("top: chunk_size = %d, remain = %d, mid = %d\n", chunk_size, remain, mid);
			printf("\tstart = %d, end = %d\n", a->top, a->top - chunk_size + 1);
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
			mid = find_mid(a, chunk_size - 1, 0);
			printf("bottom: chunk_size = %d, remain = %d, mid = %d\n", chunk_size, remain, mid);
			printf("\tstart = %d, end = %d\n", chunk_size - 1, 0);
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
}

void	push_chunks_ba(t_stack *a, t_stack *b, int old_top)
{
	int chunk_size;
	int mid;
	int remain;
	int i;

	if (old_top > 1)
	{
		chunk_size = old_top - old_top / 2;
		push_chunks_ba(a, b, old_top / 2);
		remain = b->top - chunk_size / 2;
		mid = find_mid(b, 0, chunk_size);
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
		push_chunk_a(a, b, check_sorted_from(a, a->top - chunk_size / 2));
		// i = 0;
		// while (i < chunk_size - chunk_size / 2)
		// {
		// 	if (b->stack[0] )
		// }
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
	push_chunks_ba(a, b, a->top + b->top + 1);
	// sort_stack_desc(a, b);
	// print_stack(a, b);
	// printf("is sorted = %d\n", is_sorted(a));
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

