/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kth-smallest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 00:04:31 by mfirdous          #+#    #+#             */
/*   Updated: 2022/11/12 00:04:31 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int partition(int arr[], int l, int r)
{
	int x;
	int i;
	int j;
	int temp;

	x = arr[r];
	i = l;
	j = l; 
	while(j <= r - 1)
	{
		if (arr[j] <= x) 
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
		}
		j++;
	}
	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;
	return (i);
}

int *d_array(int arr[], int r)
{
	int i;
	int *dup_arr;
	
	dup_arr = (int *)malloc((r + 1) * sizeof(int));
	i = -1;
	while (++i <= r)
		dup_arr[i] = arr[i];
	return (dup_arr);
}

int kthSmallest(int arr[], int l, int r, int k)
{
	int index;

	if (k > 0 && k <= r - l + 1) 
	{
		index = partition(arr, l, r);
		if (index - l == k - 1)
			return arr[index];
		if (index - l > k - 1)
			return (kthSmallest(arr, l, index - 1, k));
		return (kthSmallest(arr, index + 1, r, k - index + l - 1));
	}
	return (0);
}

// // Driver program to test above methods
// int main(int argc, char **argv)
// {
// 	//			  0   1  2  3  4  5   6   7   8   9
// 	//			  4   5  6  8  10 11  26
// 	int arr[] = { 10, 4, 5, 8, 6, 11, 26, 32, -3, 99 };
// 	int n = sizeof(arr) / sizeof(arr[0]);
// 	int k = ft_atoi(argv[1]);
// 	int top = n - 1;
// 	int median_index = top / 2 + 1;
// 	printf("%d-th smallest element is %d\n", median_index, kthSmallest(arr, 5, n - 1, median_index));
// 	return 0;
// }
