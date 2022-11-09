/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ab                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:35:09 by mfirdous          #+#    #+#             */
/*   Updated: 2022/10/01 11:35:09 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// sa and sb at the same time
void	ss(t_stack *a, t_stack *b)
{
	sa(a);
	sa(b);
}

// ra and rb at the same time
void	rr(t_stack *a, t_stack *b)
{
	int	old_top;
	int	i;

	if (a->top != -1)
	{
		old_top = a->stack[a->top];
		i = a->top + 1;
		while (--i > 0)
			a->stack[i] = a->stack[i - 1];
		a->stack[0] = old_top;
	}
	if (b->top != -1)
	{
		old_top = b->stack[b->top];
		i = b->top + 1;
		while (--i > 0)
			b->stack[i] = b->stack[i - 1];
		b->stack[0] = old_top;
	}
	ft_printf("rr\n");
}

// rra and rrb at the same time
void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rra(b);
}