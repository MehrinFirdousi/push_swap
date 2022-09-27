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
	int	i;
	int	sum;
	int	sign;

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
		printf("sum = %d\n", sum);
		if (sum <= 0) // overflow has occurred except for when the number is INT_MIN
		 	return (0);
	}
	return (sign * sum);
}

// int *create_stack_a(int len, char **argv)
// {
// 	int	*a;
// 	int	i;
// 	int	j;

// 	a = (int *)malloc(sizeof(int) * len);
// 	if (!a)
// 		return (NULL);
// 	i = -1;
// 	while (argv[++i])
// 	{
// 		a[i] = ft_atoi(argv[i]);
// 		if (a[i] == 0 && argv[i][0] != '0') // not an integer
// 		{
// 			free(a);
// 			ft_printf("Error\n");
// 			return (NULL);
// 		}
// 		j = -1;
// 		while (++j < i) // duplicate exists
// 			if (a[i] == a[j])
// 			{
// 				free(a);
// 				ft_printf("Error\n");
// 				return (NULL);
// 			}


// 	}
// 	return (a);
// }

int main(int argc, char **argv)
{
	// int *a;
	// int *b;

	if (argc == 1)
		return (0);
	//a = create_stack_a(argc - 1, argv + 1);
	printf("%d\n", ft_atoi_ofd(argv[1]));
	return (0);
}

/*
	errors:
	1. no args - just return 
	2. args aren't integers
	3. > INT_MAX or < INT_MIN
	4. there are duplicates
*/