#include "push_swap.h"

/** @brief Find the number in B that can be pushed to A with the less.
 * amount of moves in between them all.
 * @param a Pointer to linked list with stack a.
 * @param b Pointer to linked list with stack b. */
static void	best_push(t_stk **a, t_stk **b)
{
	t_stk	*tmp;
	int		nbr;
	int		i;
	int		moves;
	int		lowest_move;

	lowest_move = INT_MAX;
	tmp = *b;
	i = 0;
	while (tmp)
	{
		moves = (int)ft_abs(get_rotation(*a, tmp->nbr)) + i;
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

/** @brief Sort big stacks by find the numbers that are in order, starting from
 * the lowest. Push all the numbers that aren't to stack b.
 * And call helper to push them back in order.
 * @param a Pointer to first node of stack A.
 * @param b Pointer to first node of stack B. */
void	sort_big(t_stk **a, t_stk **b)
{
	int	*lis;
	int	lis_size;

	lis = ft_calloc((size_t)ft_lstsize((t_list *)*a), sizeof(int *));
	lis_size = get_lis(*a, lis);
	push_lis(a, b, lis, lis_size);
	free(lis);
	while (*b)
		best_push(a, b);
	in_order(a, 'a', *b);
}
