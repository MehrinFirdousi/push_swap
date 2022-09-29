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

int	*create_stack_a(int len, char **argv)
{
	int	*a;
	int	i;
	int	j;

	a = (int *)malloc(sizeof(int) * len);
	if (!a)
		return (NULL);
	i = -1;
	while (argv[++i])
	{
		a[i] = ft_atoi_ofd(argv[i]);
		if (a[i] == 0 && argv[i][0] != '0')
		{
			free(a);
			return (NULL);
		}
		j = -1;
		while (++j < i)
			if (a[i] == a[j])
			{
				free(a);
				return (NULL);
			}
	}
	return (a);
}

int	main(int argc, char **argv)
{
	int	*a;
	int	*b;
	int	i;

	if (argc == 1)
		return (0);
	a = create_stack_a(argc - 1, argv + 1);
	if (!a)
	{
		ft_printf("Error\n");
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < argc -1)
		printf("%d\n", a[i]);
	b = (int *)malloc(sizeof(int) * argc - 1);
	free(a);
	free(b);
	return (0);
}
