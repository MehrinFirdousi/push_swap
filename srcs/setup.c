/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:03:18 by mfirdous          #+#    #+#             */
/*   Updated: 2022/10/14 16:03:18 by mfirdous         ###   ########.fr       */
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

// exits from the program after freeing everything and displaying "Error"
int	exit_err(t_stack *a)
{
	free(a->stack);
	free(a);
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

// um yea literally just parses the args
char	**parse_args(char **argv, int *count)
{
	char	*nums_str;
	char	*temp;
	char	**nums;
	int		i;

	nums_str = ft_strdup(argv[0]);
	i = 0;
	while (argv[++i])
	{
		temp = ft_strjoin(nums_str, " ");
		free(nums_str);
		nums_str = temp;
		temp = ft_strjoin(nums_str, argv[i]);
		free(nums_str);
		nums_str = temp;
	}
	nums = ft_split(nums_str, ' ');
	free(nums_str);
	i = -1;
	while (nums[++i])
		;
	*count = i - 1;
	return (nums);
}

// creates stack a with the top element at the end of the array 
t_stack	*create_stack_a(char **argv)
{
	t_stack	*a;
	char	**nums;
	int		i;
	int		j;
	int		count;

	nums = parse_args(argv + 1, &count);
	a = (t_stack *)ft_malloc(sizeof(t_stack));
	a->stack = (int *)ft_malloc(sizeof(int) * (count + 1));
	i = -1;
	while (nums[++i])
	{
		a->stack[i] = ft_atoi_ofd(nums[count - i]);
		if (a->stack[i] == 0 && nums[count - i][0] != '0')
			exit_err(a);
		j = -1;
		while (++j < i)
			if (a->stack[i] == a->stack[j])
				exit_err(a);
		free(nums[count - i]);
	}
	a->top = count;
	free(nums);
	return (a);
}

t_stack	*init_stack(int len)
{
	t_stack	*s;

	s = (t_stack *)ft_malloc(sizeof(t_stack));
	s->stack = (int *)ft_malloc(sizeof(int) * len);
	s->top = -1;
	return (s);
}

// remove
void	print_stack(t_stack *a, t_stack *b)
{
	int	i;
	int	top_a;
	int	top_b;

	top_a = (!a? -1 : a->top);
	top_b = (!b? -1 : b->top);
	i = (top_a >= top_b? top_a : top_b) + 1;
	printf("-----------------\n");
	while (--i >= 0)
	{
		printf("%d\t", i);
		if (i <= top_a)
			printf("%d", a->stack[i]);
		printf("\t");
		if (i <= top_b)
			printf("%d", b->stack[i]);
		printf("\n");
	}
	printf("_\t_\t_\n");
	printf("i\ta\tb\n");
	printf("-----------------\n");
}