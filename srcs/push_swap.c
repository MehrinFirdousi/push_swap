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
 * @test
 * 
 * ARG=`ruby -e "puts (-49..50).to_a.shuffle.join(' ')"`; ./push_swap $ARG > output && < output ./checker_linux $ARG && < output wc -l
 * 
 */

/**
 * @todo
 * 
 * optimization ideas - 
 * 		when doing rb if b[top] <= mid, only rb if an upcoming element requires a pb, which would need it to be at the top
 * 		check for unsorted elements in a as soon has half of a chunk is pushed
 * 		when pushing to b for the first time, only push unsorted elements from the top because sometimes the bottom of the stack may already be sorted
 */

// sub_pivot and remain are by-products of calculating the pivot
void	find_pivot(t_stack *s, int end, t_chunk *c)
{
	int	i;
	int	min;
	int	max;

	max = s->stack[s->top];
	i = s->top;
	while (--i >= end)
		if (max < s->stack[i])
			max = s->stack[i];
	min = s->stack[s->top];
	i = s->top;
	while (--i >= end)
		if (min > s->stack[i])
			min = s->stack[i];
	c->pivot = (max + min) / 2;
	c->sub_pivot = (min + c->pivot) / 2;
	// printf("pivot = %d, %d\n", c->pivot, c->sub_pivot);
	c->count_top = 0;
	c->count_bottom = 0;
	i = s->top + 1;
	while (--i >= end)
		if (s->stack[i] < c->pivot && s->stack[i] >= c->sub_pivot)
			(c->count_top)++;
	i = s->top + 1;
	while (--i >= end)
		if (s->stack[i] < c->sub_pivot)
			(c->count_bottom)++;
	c->remain = s->top - (c->count_top + c->count_bottom);
}

int *d_array(int arr[], int r)
{
	int i;
	int *dup_arr;
	
	dup_arr = (int *)malloc((r + 1) * sizeof(int));
	i = -1;
	while (++i <= r)
		dup_arr[i] = arr[i];
	return (dup_arr);
}

void	find_median(t_stack *s, int end, t_chunk *c)
{
	int chunk_size;
	int median_pos;
	int sub_chunk_size;
	int sub_median_pos;
	int i;
	int *arr;

	arr = d_array(s->stack, s->top);
	chunk_size = s->top - end + 1;
	median_pos = chunk_size / 2 + 1;
	c->pivot = kthSmallest(arr, end, s->top, median_pos);
	// printf("chunksize %d, median_pos %d, pivot %d\n", chunk_size, median_pos, c->pivot);

	// might fail because arr was modified by kthsmallest call above
	sub_chunk_size = chunk_size - median_pos + !(chunk_size & 1);
	sub_median_pos = sub_chunk_size / 2 + 1;
	c->sub_pivot = kthSmallest(arr, end, s->top, sub_median_pos);
	// printf("sub_chunksize %d, sub_median_pos %d, sub_pivot %d\n", sub_chunk_size, sub_median_pos, c->sub_pivot);
	
	c->count_top = 0;
	c->count_bottom = 0;
	i = s->top + 1;
	while (--i >= end)
		if (s->stack[i] < c->pivot && s->stack[i] >= c->sub_pivot)
			(c->count_top)++;
	i = s->top + 1;
	while (--i >= end)
		if (s->stack[i] < c->sub_pivot)
			(c->count_bottom)++;
	c->remain = s->top - (c->count_top + c->count_bottom);
	free(arr);
}

// returns the count of unsorted elements from the top 
int	count_unsorted(t_stack *s, int i)
{
    while (++i <= s->top)
        if (s->stack[i] > s->stack[i - 1])
            return (s->top - i + 2);
    return (0);
}

// pushes all elements of a to b at the start
void	push_ab(t_stack *a, t_stack *b, t_chunk *c)
{
	int	rb_flag;

	rb_flag = 0;
	find_median(a, 0, c);
	// printf("%d %d\n", c->pivot, c->sub_pivot);

	while (a->top > c->remain)
	{
		if (a->stack[a->top] < c->pivot || a->stack[0] < c->pivot)
		{
			if (rb_flag)
				rb(b);
			rb_flag = 0;
			if (a->stack[0] < c->pivot && a->stack[a->top] >= c->pivot)
				rra(a);
			pb(a, b);
			if (b->stack[b->top] < c->sub_pivot)
				rb_flag = 1;
			// else if (b->stack[b->top] < b->stack[b->top - 1])
			// 	sb(b);
		}
		else if (a->stack[a->top] >= c->pivot)
		{
			if (rb_flag)
				rr(a, b);
			else
				ra(a);
			rb_flag = 0;
		}
	}
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

// returns the index of the second largest element in the stack
int find_second_max(t_stack *s)
{
	int i;
	int j;
	int	count_big;

	i = -1;
	while (++i <= s->top)
	{
		j = -1;
		count_big = 0;
		while (++j <= s->top)
			if (s->stack[i] < s->stack[j])
				count_big++;
		if (count_big == 1)
			return (i);
	}
	return (0);
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
	if (is_sorted(b) == 0)
		return (1);
	pa(a, b);
	return (0);
}

void	sort_stack_half(t_stack *a, t_stack *b)
{
	int	max;
	int max2;
	int	max_dist;
	int max2_dist;
	int	half;

	half = (b->top + a->top) / 2;
	while (b->top > half)
	{
		max = find_max(b);
		if (max >= b->top / 2)
			max_dist = b->top - max;
		else
			max_dist = max + 1;
	
		max2 = find_second_max(b);
		if (max2 >= b->top / 2)
			max2_dist = b->top - max2;
		else
			max2_dist = max2 + 1;
		if (max2_dist < max_dist)
		{
			if (push_max(a, b, max2)) // returns 1 if the list got sorted while rotating
				break;
			max = find_max(b); // find max again because the elements moved
			if (push_max(a, b, max)) // returns 1 if the list got sorted while rotating
				break;
			sa(a);
		}
		else
			if (push_max(a, b, max)) // returns 1 if the list got sorted while rotating
				break;
	}
	while (b->top > half)
		pa(a, b);
}

// returns number of elements that were pushed
// remove chunk_end
void	push_chunks(t_stack *a, t_stack *b) // chunk_end is the end index of the chunk we're pushing
{
	t_chunk cb;

	if (a->top > 1)
	{
		push_ab(a, b, &cb);
		push_chunks(a, b);
		printf("p sp ct cb r %d %d %d %d %d\n", cb.pivot, cb.sub_pivot, cb.count_top, cb.count_bottom, cb.remain);
	}
	if (cb.remain <= (a->top + b->top + 2) / 2)
	{
		if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
			sa(a);
		sort_stack_half(a, b);
	} 
}

// ********************* does full sort in desc *************
void	sort_stack_desc_full(t_stack *a, t_stack *b)
{
	int	max;
	int max2;
	int	max_dist;
	int max2_dist;

	while (b->top > 0)
	{
		max = find_max(b);
		if (max >= b->top / 2)
			max_dist = b->top - max;
		else
			max_dist = max + 1;
	
		max2 = find_second_max(b);
		if (max2 >= b->top / 2)
			max2_dist = b->top - max2;
		else
			max2_dist = max2 + 1;
		if (max2_dist < max_dist)
		{
			if (push_max(a, b, max2)) // returns 1 if the list got sorted while rotating
				break;
			max = find_max(b); // find max again because the elements moved
			if (push_max(a, b, max)) // returns 1 if the list got sorted while rotating
				break;
			sa(a);
		}
		else
			if (push_max(a, b, max)) // returns 1 if the list got sorted while rotating
				break;
	}
	while (b->top != -1)
		pa(a, b);
}

void	test(t_stack *a, t_stack *b, t_chunk *c)
{
	find_median(a, 0, c);
	printf("remain = %d\n", c->remain);
	printf("%d %d\n", c->count_top, c->count_bottom);
	(void)b;
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
	
	if (is_sorted(a) == 0)
		exit(0);
	push_chunks(a, b);
	printf("tops %d %d\n", a->top, b->top);
	print_stack(a, b);
	// sort_stack_desc_full(a, b);
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
	printf("is_sorted = %d\n", is_sorted(a));
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
