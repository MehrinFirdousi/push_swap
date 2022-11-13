/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:49:29 by mfirdous          #+#    #+#             */
/*   Updated: 2022/11/13 12:50:34 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

// returns the count of unsorted elements from the top 
int	count_unsorted(t_stack *s, int i)
{
    while (++i <= s->top)
        if (s->stack[i] > s->stack[i - 1])
            return (s->top - i + 2);
    return (0);
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

void	sort_stack_till(t_stack *a, t_stack *b, int limit)
{
	int	max;
	int max2;
	int	max_dist;
	int max2_dist;

	while (b->top > limit)
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
	while (b->top > limit)
		pa(a, b);
}

// ********************* does full sort in desc *************
void	sort_stack_full(t_stack *a, t_stack *b)
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