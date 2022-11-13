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

void	find_median(t_stack *s, int chunk_size, t_chunk *c, int split)
{
	// int chunk_size;
	int end;
	int median_pos;
	int sub_chunk_size;
	int sub_median_pos;
	int i;
	int *arr;

	arr = d_array(s->stack, s->top);
	end = s->top - chunk_size + 1;
	median_pos = chunk_size / split + 1;
	c->pivot = kthSmallest(arr, end, s->top, median_pos);
	// printf("chunksize %d, median_pos %d, pivot %d\n", chunk_size, median_pos, c->pivot);

	// might fail because arr was modified by kthsmallest call above
	sub_chunk_size = median_pos + !(chunk_size & 1);
	sub_median_pos = sub_chunk_size / 2 + 1;
	c->sub_pivot = kthSmallest(arr, end, s->top, sub_median_pos);
	// printf("sub_chunksize %d, sub_median_pos %d, sub_pivot %d\n", sub_chunk_size, sub_median_pos, c->sub_pivot);
	
	chunk_size = 0;
	i = s->top + 1;
	while (--i >= end)
		if (s->stack[i] < c->pivot)
			chunk_size++;
	// i = s->top + 1;
	// while (--i >= end)
	// 	if (s->stack[i] < c->sub_pivot)
	// 		(c->count_bottom)++;
	c->remain = s->top - chunk_size;
	free(arr);
}

int	find_limit(t_stack *a)
{
	int chunk_size;
	int	limit;

	chunk_size = a->top + 1;
	limit = 2;
	while (chunk_size / limit > 65)
		limit *= 2;
	return (limit);
}

// pushes all elements of a to b at the start, t_chunk c info is set here
void	push_ab(t_stack *a, t_stack *b, int split)
{
	t_chunk	c;
	int		rb_flag;

	rb_flag = 0;
	printf("limit for %d nums = %d\n", a->top + 1, find_limit(a));
	find_median(a, a->top + 1, &c, split);
	printf("%d %d %d\n", c.pivot, c.sub_pivot, c.remain);
	while (a->top > c.remain)
	{
		if (a->stack[a->top] < c.pivot || a->stack[0] < c.pivot)
		{
			if (rb_flag)
				rb(b);
			rb_flag = 0;
			if (a->stack[0] < c.pivot && a->stack[a->top] >= c.pivot)
				rra(a);
			pb(a, b);
			if (b->stack[b->top] < c.sub_pivot)
				rb_flag = 1;
			// else if (b->stack[b->top] < b->stack[b->top - 1])
			// 	sb(b);
		}
		else if (a->stack[a->top] >= c.pivot)
		{
			if (rb_flag)
				rr(a, b);
			else
				ra(a);
			rb_flag = 0;
		}
	}
}

// one chunk b to a
void	push_chunks(t_stack *a, t_stack *b) // chunk_end is the end index of the chunk we're pushing
{
	while (a->top > 1)
	{
		push_ab(a, b, 2);
	}
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(a->top + 1);
	if (is_sorted(a) == 0)
		exit(0);
	for (int i = a->top; i >= 0; i--)
		printf("%d ", a->stack[i]);
	printf("\n");

	if (a->top + b->top > 200)
	{
		push_ab(a, b, 8); // 62
		push_ab(a, b, 8); // 62
		push_ab(a, b, 8); // 62
		push_ab(a, b, 8); // 62 - 250 - 1st chunk - half of stack
		push_ab(a, b, 4); // 125
		push_ab(a, b, 4); //
		push_ab(a, b, 4);
		push_ab(a, b, 4);
	}
	push_chunks(a, b);
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
	sort_stack_full(a, b);
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
