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

char	**parse_args(char **argv, int *count)
{
	char	*nums_str;
	char	*temp;
	char	**nums;
	int		i;

	nums_str = argv[0];
	i = 0;
	while (argv[++i])
	{
		temp = nums_str;
		nums_str = ft_strjoin(nums_str, " ");
		free(temp);
		temp = nums_str;
		nums_str = ft_strjoin(nums_str, argv[i]);
		free(temp);
	}
	nums = ft_split(nums_str, ' ');
	i = -1;
	while(nums[++i])
		printf("nums[%d] = %s\n", i, nums[i]);
		
	*count = i;
	return (nums);
}

t_stack	*create_stack_a(char **argv)
{
	t_stack	*a;
	char	**nums;
	int		i;
	int		j;
	int		count;

	nums = parse_args(argv + 1, &count);
	a = (t_stack *)ft_malloc(sizeof(t_stack));
	a->stack = (int *)ft_malloc(sizeof(int) * count);
	count -= 1;
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
		free(nums[i]);
	}
	a->top = count;
	free(nums);
	return (a);
}

void	print_stack(t_stack *a, t_stack *b)
{
	int	i;
	int	top_a;
	int	top_b;

	top_a = (!a? -1 : a->top);
	top_b = (!b? -1 : b->top);
	// printf("top_a = %d, top_b = %d\n", top_a, top_b);
	i = (top_a >= top_b? top_a : top_b) + 1;
	// printf("big stack top = %d\n", i - 1);
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

t_stack	*init_stack(int len)
{
	t_stack	*s;

	s = (t_stack *)ft_malloc(sizeof(t_stack));
	s->stack = (int *)ft_malloc(sizeof(int) * len);
	s->top = -1;
	return (s);
}

// returns the index of the smallest element in the stack
int	find_min(t_stack *s)
{
	int	i;
	int	min_index;

	i = s->top + 1;
	min_index = s->top;
	while (--i >= 0)
		if (s->stack[i] < s->stack[min_index])
			min_index = i;
	return (min_index);
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

void	sort_stack(t_stack *a, t_stack *b)
{
	int	min;

	while (a->top > 0)
	{
		if (is_sorted(a) == 0)
			break ;
		min = find_min(a);
		if (a->top - min == 1)
			sa(a);
		else if (min >= a->top / 2)
			while (++min <= a->top)
				ra(a);
		else if (min < a->top / 2)
			while (--min >= -1)
				rra(a);
		pb(a, b);
	}
	while (b->top != -1)
		pa(a, b);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc == 1)
		return (0);
	a = create_stack_a(argv);
	b = init_stack(argc - 1);
	// print_stack(a, b);
	//printf("is sorted till: %d\n", is_sorted(a));
	//printf("min = %d\n", find_min(a));
	sort_stack(a, b);
	// print_stack(a, b);
	free(a->stack);
	free(a);
	free(b->stack);
	free(b);
	return (0);
}
