#include "push_swap.h"

/** @brief Find the number in B that can be pushed to A with the less.
 * amount of moves in between them all.
 * @param a Pointer to linked list with stack a.
 * @param b Pointer to linked list with stack b. */
static void	best_push(t_stacks **a, t_stacks **b)
{
	t_stacks	*tmp;
	int			nbr;
	int			i;
	int			moves;
	int			lowest_move;

	lowest_move = INT_MAX;
	tmp = *b;
	i = 0;
	while (tmp)
	{
		moves = ft_abs(get_rotation(*a, tmp->nbr)) + i;
		if (moves < lowest_move)
		{
			lowest_move = moves;
			nbr = tmp->nbr;
		}
		tmp = tmp->next;
		++i;
	}
	best_rotation(b, nbr, 'b', *a);
	rotate_amount(a, get_rotation(*a, nbr), 'a', *b);
	push(b, a, 'b');
}

/** @brief Pushes all the numbers on non_lis, from a to b.
 * @param a Pointer to the first node of the list to look for.
 * @param b Pointer to the first node of the list to push for.
 * @param non_lis Array of ints to be pushed from a to b. */
static void	push_lis(t_stacks **a, t_stacks **b, int *non_lis, int lis_size)
{
	int	i;

	while (lis_size)
	{
		i = -1;
		while (++i < lis_size)
		{
			if ((*a)->nbr == non_lis[i])
			{
				push(a, b, 'a');//need to figure out non_lis free in case commands fail (-1 on write)
				ft_memmove(&non_lis[i], &non_lis[i + 1], lis_size - i);
				lis_size--;
				break ;
			}
		}
		if (i == lis_size)
			rotate(a, 'a', *b);
	}
}

/** @brief Finds the Longest Increasing Subsequence on stack a, 
 * saving on non_lis, all the numbers that aren't part of it.
 * @param a Linked list to search for the LIS.
 * @param non_lis Array of int to save the numbers that aren't in sequence. 
 * @return The size of the array created with the non-lis numbers. */
static int	get_lis(t_stacks *a, int *non_lis)
{
	int			last_low;
	int			lowest;
	int			i;
	t_stacks	*tmp;

	i = -1;
	get_lowest(a, &lowest, NULL);
	tmp = a;
	while (tmp->nbr != lowest)
		tmp = tmp->next;
	last_low = lowest;
	tmp = tmp->next;
	if (!tmp)
		tmp = a;
	while (tmp->nbr != lowest)
	{
		if (tmp->nbr < last_low)
			non_lis[++i] = tmp->nbr;
		else
			last_low = tmp->nbr;
		tmp = tmp->next;
		if (!tmp)
			tmp = a;
	}
	return (i + 1);
}

/** @brief Sort big stacks by find the numbers that are in order, starting from
 * the lowest. Push all the numbers that aren't to stack b.
 * And call helper to push them back in order.
 * @param a Pointer to first node of stack A.
 * @param b Pointer to first node of stack B. */
void	sort_big(t_stacks **a, t_stacks **b)
{
	int	*non_lis;
	int	lis_size;

	non_lis = ft_calloc((size_t)ft_lstsize((t_list *)*a), sizeof(int *));
	lis_size = get_lis(*a, non_lis);
	push_lis(a, b, non_lis, lis_size);
	free(non_lis);
	while (*b)
		best_push(a, b);
}
