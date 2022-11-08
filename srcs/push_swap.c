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

/**
 * @todo
 * 
 * optimization ideas - 
 * 		when doing rb if b[top] <= mid, only rb if an upcoming element requires a pb, which would need it to be at the top
 * 		check for unsorted elements in a as soon has half of a chunk is pushed
 * 		when pushing to b for the first time, only push unsorted elements from the top because sometimes the bottom of the stack may already be sorted
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

	// printf("start = %d, end = %d\nnums: ", start, end);
	// for (int i = start; i >= end; i--)
	// 	printf("%d, ", s->stack[i]);
	// printf("\n");
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

// returns the count of unsorted elements from the top 
int count_unsorted(t_stack *s, int i)
{
    while (++i <= s->top)
        if (s->stack[i] > s->stack[i - 1])
            return (s->top - i + 2);
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
	
	while (a->top > chunk_end + 1)
	{
		mid = find_mid(a, a->top, chunk_end, 1);
		remain = (a->top + chunk_end) / 2;
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

// pushing one chunk from a to b
int	push_chunk_a(t_stack *a, t_stack* b, int chunk_size)
{
	int count_pushed;
	int	count_rotated;
	int	remain;
	int	mid;

	count_pushed = 0;
	if (chunk_size > 2)
		count_pushed = chunk_size - 2;
	count_rotated = 0;
	while (chunk_size > 1)
	{
		remain = a->top - chunk_size / 2;
		mid = find_mid(a, a->top, a->top - chunk_size + 1, 1);
		// printf("chunk_size in a = %d, mid = %d\n", chunk_size, mid);
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
		// else
		// {
		// 	remain = a->top - chunk_size / 2;
		// 	mid = find_mid(a, chunk_size - 1, 0, 1);
		// 	while (a->top > remain)
		// 	{
		// 		rra(a);
		// 		if (a->stack[a->top] < mid)
		// 			pb(a, b);
		// 	}
		// 	top = 1;
		// }
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

	count_rotated = 0;
	old_top =  a->top + b->top + 1;
	last_chunk_size =  old_top - old_top / 2;
	while (chunk_size > 1)
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
			}
			// if (b->stack[0] > mid)
			// {
			// 	rrb(b);
			// 	pa(a, b);
			// }
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
        unsorted_c = count_unsorted(a, a->top - chunk_size + 1);
		// printf("for chunk %d,, unsorted = %d\n", chunk_size, unsorted_c);
		// push_chunk_a(a, b, count_unsorted);
        while (unsorted_c > 0)
        {
            unsorted_c = push_chunk_a(a, b, unsorted_c); // pushes 1 chunk from a to b
            push_chunk_b(a, b, unsorted_c); // pushes that chunk back to a
			// printf("for chunk %d, ", unsorted_c);
            unsorted_c = count_unsorted(a, a->top - unsorted_c + 1);
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

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(a->top + 1);
	
	for (int i = a->top; i >= 0; i--)
		printf("%d ", a->stack[i]);
	printf("\n");
	push_chunks_ab(a, b, 0);
	push_chunks_ba(a, b, a->top + b->top + 1);
	printf("is_sorted?  %d\n", is_sorted(a));
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

