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

// atoi with overflow detection
int	ft_atoi_ofd(const char *nptr)
{
	long long int	sum;
	int				i;
	int				sign;

	i = 0;
	sum = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		sum = (sum * 10) + (nptr[i++] - 48);
		if ((sign == 1 && sum > INT32_MAX) || (sign == -1 && sum > 2147483648))
			return (0);
	}
	if (nptr[i] && !ft_isdigit(nptr[i]))
		return (0);
	return (sign * sum);
}

int	exit_err(t_stack *a)
{
	free(a->stack);
	free(a);
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

t_stack	*create_stack_a(int len, char **argv)
{
	t_stack	*a;
	int	i;
	int	j;

	a = (t_stack *)ft_malloc(sizeof(t_stack));
	a->stack = (int *)ft_malloc(sizeof(int) * len);
	i = -1;
	while ((len - ++i) > 0)
	{
		a->stack[i] = ft_atoi_ofd(argv[len - i]);
		if (a->stack[i] == 0 && argv[len - i][0] != '0')
			exit_err(a);
		j = -1;
		while (++j < i)
			if (a->stack[i] == a->stack[j])
				exit_err(a);
	}
	a->top = len - 1;
	return (a);
}

void	print_stack(t_stack *s)
{
	int	i;

	i = s->top + 1;
	printf("stack top = %d\n", s->top);
	while (--i >= 0)
		printf("%d\n", s->stack[i]);
}

t_stack	*init_stack(int len)
{
	t_stack *s;

	s = (t_stack *)ft_malloc(sizeof(t_stack));
	s->stack = (int *)ft_malloc(sizeof(int) * len);
	s->top = -1;
	return (s);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argc - 1, argv);
	print_stack(a);
	sa(a);

	b = init_stack(argc - 1);
	print_stack(b);

	pa(b, a);
	print_stack(b);
	pa(a, b);
	print_stack(a);

	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
