/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kth-smallest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 00:04:31 by mfirdous          #+#    #+#             */
/*   Updated: 2022/11/12 00:04:31 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	partition(int *arr, int l, int r)
{
	int	x;
	int	i;
	int	j;
	int	temp;

	x = arr[r];
	i = l;
	j = l;
	while (j <= r - 1)
	{
		if (arr[j] <= x)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
		j++;
	}
	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;
	return (i);
}

int	kth_smallest(int *arr, int l, int r, int k)
{
	int	index;

	if (k > 0 && k <= r - l + 1)
	{
		index = partition(arr, l, r);
		if (index - l == k - 1)
			return (arr[index]);
		if (index - l > k - 1)
			return (kth_smallest(arr, l, index - 1, k));
		return (kth_smallest(arr, index + 1, r, k - index + l - 1));
	}
	return (0);
}

int	find_kth_smallest(t_stack *s, int k)
{
	int	i;
	int	*dup_arr;
	int	target;

	dup_arr = (int *)malloc((s->top + 1) * sizeof(int));
	i = -1;
	while (++i <= s->top)
		dup_arr[i] = s->stack[i];
	target = kth_smallest(dup_arr, 0, s->top, ++k);
	free(dup_arr);
	return (target);
}

int	find_closest(t_stack *b, int *max_dist, int pos)
{
	int	max;

	max = get_index(b, find_kth_smallest(b, b->top - pos));
	if (max >= b->top / 2)
		*max_dist = b->top - max;
	else
		*max_dist = max + 1;
	return (max);
}

void	find_median(t_stack *s, t_chunk *c, int split)
{
	int	median_pos;
	int	sub_chunk_size;
	int	i;

	median_pos = (s->top + 1) / split;
	c->pivot = find_kth_smallest(s, median_pos);
	sub_chunk_size = median_pos + !((s->top + 1) & 1);
	c->sub_pivot = find_kth_smallest(s, sub_chunk_size / 2);
	c->remain = -1;
	i = -1;
	while (++i <= s->top)
		if (s->stack[i] >= c->pivot)
			c->remain++;
}
