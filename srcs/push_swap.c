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

// pushes all elements of a to b at the start
void	push_ab(t_stack *a, t_stack *b, t_chunk *c)
{
	int	rb_flag;

	rb_flag = 0;
	find_pivot(a, 0, c);
	// printf("remain = %d\n", c->remain);
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
// returns number of elements that were pushed
// remove chunk_end
void	push_chunks(t_stack *a, t_stack *b) // chunk_end is the end index of the chunk we're pushing
{
	t_chunk c;

	if (a->top > 1)
	{
		push_ab(a, b, &c);
		push_chunks(a, b);
		// printf("p sp ct cb %d %d %d %d\n", c.pivot, c.sub_pivot, c.count_top, c.count_bottom);
		// one recursive iteration handles both the top and bottom set
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
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

// ********************* does full sort in desc *************
void	sort_stack_desc_full(t_stack *a, t_stack *b)
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
	
	// for (int i = a->top; i >= 0; i--)
	// 	printf("%d ", a->stack[i]);
	// printf("\n");
	push_chunks(a, b);
	sort_stack_desc_full(a, b);

	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
