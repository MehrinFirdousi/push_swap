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
	ra(a);
	ra(b);
}

// rra and rrb at the same time
void	rrr(t_stack *a, t_stack *b)
{
	rra(a);
	rra(b);
}