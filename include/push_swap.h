/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:41:47 by mfirdous          #+#    #+#             */
/*   Updated: 2022/09/26 21:41:47 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# ifdef _WIN32
#  define EXIT_SUCCESS 0
#  define EXIT_FAILURE 1
# else
#  include <unistd.h>
# endif

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

typedef struct s_stack
{
	int	*stack;
	int	top;
}	t_stack;

typedef struct s_chunk
{
	int	pivot;
	int	sub_pivot;
	int	remain;
}	t_chunk;

int		ft_atoi_ofd(const char *nptr);
int		exit_err(t_stack *a);
char	**parse_args(char **argv, int *count);
t_stack	*create_stack_a(char **argv);
t_stack	*init_stack(int len);
void	print_stack(t_stack *a, t_stack *b);
int		kthSmallest(int arr[], int l, int r, int k);
int		*d_array(int arr[], int r);
void	find_pivot(t_stack *s, int end, t_chunk *c);
int		count_unsorted(t_stack *s, int i);
int		find_max(t_stack *s);
int		find_second_max(t_stack *s);
int		is_sorted(t_stack *s) ;
int		push_max(t_stack *a, t_stack *b, int max);
void	sort_stack_till(t_stack *a, t_stack *b, int limit);
void	sort_stack_full(t_stack *a, t_stack *b);

void	sa(t_stack *a);
void	sb(t_stack *a);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);

void	ra(t_stack *a);
void	rb(t_stack *a);
void	rra(t_stack *a);
void	rrb(t_stack *a);

void	ss(t_stack *a, t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rrr(t_stack *a, t_stack *b);

#endif