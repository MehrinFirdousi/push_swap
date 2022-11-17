/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:17:51 by mfirdous          #+#    #+#             */
/*   Updated: 2022/11/15 11:35:13 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_operation(char *op, t_stack *a, t_stack *b)
{
	if (!ft_strncmp(op, "sa\n", 3))
		sa(a);
	else if (!ft_strncmp(op, "sb\n", 3))
		sb(b);
	else if (!ft_strncmp(op, "ss\n", 3))
		ss(a, b);
	else if (!ft_strncmp(op, "pa\n", 3))
		pa(a, b);
	else if (!ft_strncmp(op, "pb\n", 3))
		pb(a, b);
	else if (!ft_strncmp(op, "ra\n", 3))
		ra(a);
	else if (!ft_strncmp(op, "rb\n", 3))
		rb(b);
	else if (!ft_strncmp(op, "rr\n", 3))
		rr(a, b);
	else if (!ft_strncmp(op, "rra\n", 4))
		rra(a);
	else if (!ft_strncmp(op, "rrb\n", 4))
		rrb(b);
	else if (!ft_strncmp(op, "rrr\n", 4))
		rrr(a, b);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_sorted(t_stack *s)
{
	int	i;

	i = s->top + 1;
	while (--i > 0)
		if (s->stack[i] > s->stack[i - 1])
			return (i);
	return (0);
}

int	exit_free(t_stack *a, t_stack *b, char *op)
{
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	free(op);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	char	*op;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(a->top + 1);
	op = get_next_line(0);
	while (op)
	{
		if (check_operation(op, a, b) == EXIT_FAILURE)
			exit_free(a, b, op);
		free(op);
		op = get_next_line(0);
	}
	if (is_sorted(a) == 0 && b->top == -1)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
}
