/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:05:43 by mfirdous          #+#    #+#             */
/*   Updated: 2022/10/13 18:05:43 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// returns the index of the smallest element in the stack
int	find_min_chunk(t_stack *s, int size)
{
	int	i;
	int	min_index;

	i = -1;
	min_index = s->top;
	while (++i < size)
		if (s->stack[s->top - i] < s->stack[min_index])
			min_index = s->top - i;
	return (min_index);
}

void	sort(t_stack *a, t_stack *b)
{
	int	min;
	int	i;

	i = -1;
	while (a->top != -1)
	{
		while (++i < CHUNK_SIZE)
		{
			min = find_min_chunk(a, CHUNK_SIZE - i);
			printf("CHUNKSIZE - i = %d\n", CHUNK_SIZE - i);
			printf("min = %d, %d\n", min, a->stack[min]);
			if (min - a->top == 1)
				sa(a);
			else if (min >= a->top - CHUNK_SIZE / 2)
				while (++min <= a->top)
					ra(a);
			else if (min < a->top - CHUNK_SIZE / 2)
				while (--min >= -1)
					rra(a);
			pb(a, b);
			print_stack(a, b);
		}
	}
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(a->top + 1);
	print_stack(a, b);
	sort(a, b);
	print_stack(a, b);
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
