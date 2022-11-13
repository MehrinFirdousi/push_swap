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
	t_chunk ca, cb;

	if (a->top > 1)
	{
		push_ab(a, b, &cb);
		push_chunks(a, b);
		// printf("p sp ct cb %d %d %d %d\n", cb.pivot, cb.sub_pivot, cb.count_top, cb.count_bottom);
		// one recursive iteration handles both the top and bottom set

		// while b.counttop > 1
		 ˙	// find pivot for the b.count_top elements in b
		:.	// push from b to a everything larger than pivot, separate in A according to sub_pivot
			 	// func ^ takes (a, b, &ca, &cb)
				// ca count_top and count_bottom are set
		:˙		// rrb everything that was rb'ed while pushing from b to a
				// update value of b.count_top -> b object still corresponds to the whole chunk that includes top and bottom
		:˙	// func(a, b, &ca) // to go back and forth until that set is sorted in a
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
}

func(a, b, a_chunk)
{
	t_chunk b_chunk;

:	// count unsorted in a starting from a.count_bottom elements till top (to skip the bottom elements)

	// if (count_unsorted > 0)
	//{
:	//		find pivot for unsorted (top) set in a
.:	//		do full chunk push a to b - (only top set) separate while pushing to b using pivot (as in push everything, not just whats on one side of the pivot, but separate it in b (so dont use subpivot)
	//		(push a to b (push the full unsorted set but split while pushing))
.˙	//		^ rrb everything that was rb'ed when splitting (combine top and bottom sets to make new top set)
.˙	//		^ update b.counttop according to what was pushed just now 
.˙	// 		find pivot for counttop set in b
:	//		do full chunk push b to a - (only top set) separate while pushing to a using pivot 
	//		^ rra everything that was ra'ed while pushing from b to a
	//		^ update a.counttop according to what was pushed just now 
	//		func(a, b, a_chunk)
	//}
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
