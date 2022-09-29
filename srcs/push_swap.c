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

int	check_error(int )
{

}

int	*create_stack_a(int len, char **argv)
{
	int	*a;
	int	i;
	int	j;

	a = (int *)ft_malloc(sizeof(int) * len);
	i = -1;
	while ((len - ++i) > 0)
	{
		a[i] = ft_atoi_ofd(argv[len - i]);
		if (a[i] == 0 && argv[len - i][0] != '0')
		{
			free(a);
			ft_printf("Error\n");
			return (NULL);
		}
		j = -1;
		while (++j < i)
		{
			if (a[i] == a[j])
			{
				free(a);
				ft_printf("Error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (a);
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	int		i;

	if (argc == 1)
		return (0);
	a.stack = create_stack_a(argc - 1, argv);
	a.top = argc - 1;
	i = -1;
	while (++i < argc -1)
		printf("%d\n", a.stack[i]);
	b.stack = (int *)ft_malloc(sizeof(int) * argc - 1);
	b.top = -1;
	free(a.stack);
	free(b.stack);
	return (0);
}
