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
 */

/**
 * @todo 
 * 
 * sort 3
 * check is_sorted before sorting
 * leak check
 * norm
 * 
 */

void	find_median(t_stack *s, int chunk_size, t_chunk *c, int split)
{
	int end;
	int median_pos;
	int sub_chunk_size;
	int sub_median_pos;
	int *arr;

	arr = d_array(s->stack, s->top);
	end = s->top - chunk_size + 1;
	median_pos = chunk_size / split + 1;
	c->pivot = kthSmallest(arr, end, s->top, median_pos);

	sub_chunk_size = median_pos + !(chunk_size & 1);
	sub_median_pos = sub_chunk_size / 2 + 1;
	c->sub_pivot = kthSmallest(arr, end, s->top, sub_median_pos);
	
	chunk_size = 0;
	while (end <= s->top)
		if (s->stack[end++] < c->pivot)
			chunk_size++;
	c->remain = s->top - chunk_size;
	free(arr);
}

// pushes all elements of a to b at the start, t_chunk c info is set here
void	push_ab(t_stack *a, t_stack *b, int split)
{
	t_chunk	c;
	int		rb_flag;

	rb_flag = 0;
	find_median(a, a->top + 1, &c, split);
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

int	find_limit(t_stack *a)
{
	int	limit;

	limit = 2;
	while ((a->top + 1) / limit > 75)
		limit *= 2;
	return (limit);
}

void	push_chunks(t_stack *a, t_stack *b) // chunk_end is the end index of the chunk we're pushing
{
	int limit;
	int i;

	while (a->top > 1)
	{
		limit = find_limit(a);
		i = -1;
		while (++i < limit / 2)
			push_ab(a, b, limit);
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
	push_chunks(a, b);
	sort_stack_full(a, b);
	if (a->top > 0 && a->stack[a->top] > a->stack[a->top - 1])
		sa(a);
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}

// for (int i = a->top; i >= 0; i--)
	// 	printf("%d ", a->stack[i]);
	// printf("\n");