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

int		partition(int *arr, int l, int r);
int		kth_smallest(int arr[], int l, int r, int k);
int		find_kth_smallest(t_stack *s, int k);
int		find_closest(t_stack *b, int *max_dist, int pos);
void	find_median(t_stack *s, t_chunk *c, int split);

int		get_index(t_stack *s, int num);
int		is_sorted(t_stack *s);
void	rotate(t_stack *a, t_stack *b, int *rb_flag);
int		push_max(t_stack *a, t_stack *b, int max);
void	sort_3(t_stack *a);

void	sort_stack_full(t_stack *a, t_stack *b);
void	push_ab(t_stack *a, t_stack *b, int split);
int		find_limit(t_stack *a);
void	push_chunks(t_stack *a, t_stack *b);

// operations
void	sa(t_stack *a);
void	sb(t_stack *a);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *a);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *a);
void	rrr(t_stack *a, t_stack *b);

#endif