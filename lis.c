#include "push_swap.h"

/** @brief Sees if the nbr_b fits on the position before nbr_a, on the array.
 * @param nbr_a Number on the array that will be compared.
 * @param nbr_b Number that will try to fit before the nbr_a.
 * @param lis Array of int that will see on it if nbr_b fits before nbr_a.
 * @param size Size of the array passed as parameter.
 * @return True if number fits there. False if not. */
static t_bool	on_lis_pos(int nbr_a, int nbr_b, int *lis, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (nbr_a == lis[i])
			break ;
	if (nbr_b < nbr_a && (i == 0 || nbr_b > lis[i - 1]))
		return (TRUE);
	return (FALSE);
}

//Prevents extra pushes for numbers that are easy to put in place.
/** @brief Swap the args to fix it's order or fix normally if size of stack = 3.
 * @param stk Pointer to the first node of the stack to swap if possible.
 * @param error Other stack to handle in case of an error.
 * @param lis Array with LIS numbers.
 * @param lis_size Size of lis.
 * @return True if swap or fix was done. False if not. */
static t_bool	can_swap(t_stk **stk, t_stk *error, int *lis, int lis_size)
{
	int		highest;
	int		last_n;
	t_stk	*nxt_lis;

	if (ft_lstsize((t_list *)*stk) == 3)
	{
		sort_three(stk, &error, FALSE);
		return (TRUE);
	}
	get_highest(*stk, &highest, NULL);
	last_n = stack_last(*stk)->nbr;
	nxt_lis = (*stk)->next;
	while (nxt_lis->next && is_on_lis(nxt_lis->nbr, lis, lis_size) == FALSE)
		nxt_lis = nxt_lis->next;
	if (is_on_lis((*stk)->next->nbr, lis, lis_size) == TRUE
		&& (*stk)->nbr > (*stk)->next->nbr
		&& (*stk)->nbr < nxt_lis->nbr
		&& (highest == last_n || ((*stk)->next->nbr > last_n
				&& is_on_lis(last_n, lis, lis_size))))
	{
		swap(*stk, 'a', error);
		rotate_amount(stk, 2, 'a', error);
		return (TRUE);
	}
	return (FALSE);
}

/** @brief Pushes all the numbers that aren't on lis, from a to b.
 * @param a Pointer to the first node of the list to look for.
 * @param b Pointer to the first node of the list to push for.
 * @param lis Array of int not to be pushed.
 * @param size Size of array of ints. */
void	push_lis(t_stk **a, t_stk **b, int *lis, int size)
{
	int	a_size;
	int	pushes;

	a_size = ft_lstsize((t_list *)*a);
	pushes = a_size - size;
	while (a_size--)
	{
		if (is_on_lis((*a)->nbr, lis, size))
		{
			if (*b && on_lis_pos((*a)->nbr, (*b)->nbr, lis, size))
			{
				push(b, a, 'b');
				rotate(a, 'a', *b);
			}
			rotate(a, 'a', *b);
		}
		else
		{
			pushes--;
			if (!can_swap(a, *b, lis, size))
				push(a, b, 'a');
		}
		if (!pushes)
			break ;
	}
}

/** @brief Finds the LIS starting on a given node,
 * saving on lis, all the numbers that are part of it.
 * @param a Current node of a linked list to find it's LIS.
 * @param lis Array of int to save the numbers that are in sequence. 
 * @param head The head of the linked list.
 * @return The size of the array created with the LIS numbers. */
static int	lis_per_node(t_stk *a, int *lis, t_stk *head)
{
	int		last_low;
	int		first;
	int		i;
	t_stk	*tmp;

	i = -1;
	tmp = a->next;
	if (!tmp)
		tmp = head;
	first = a->nbr;
	lis[++i] = first;
	last_low = first;
	while (tmp->nbr != first)
	{
		if (tmp->nbr > last_low && !next_better(tmp, last_low, a, first))
		{
			lis[++i] = tmp->nbr;
			last_low = tmp->nbr;
		}
		tmp = tmp->next;
		if (!tmp)
			tmp = head;
	}
	return (i + 1);
}

/** @brief Finds the best Longest Increasing Subsequence on linked list.
 * Searches for the LIS starting on each node to see wich one will have
 * a bigger list.
 * @param a Linked list to search for the LIS.
 * @param lis Array of int to save the numbers that are in sequence. 
 * @return The size of the array created with the LIS numbers. */
int	get_lis(t_stk *a, int *lis)
{
	t_stk	*tmp;
	t_stk	*best_node;
	int		longest_lis;
	int		lis_size;

	if (!a)
		return (0);
	longest_lis = 0;
	tmp = a;
	while (tmp)
	{
		lis_size = lis_per_node(tmp, lis, a);
		if (lis_size > longest_lis)
		{
			longest_lis = lis_size;
			best_node = tmp;
		}
		tmp = tmp->next;
	}
	return (lis_per_node(best_node, lis, a));
}
