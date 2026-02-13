#include "push_swap.h"

/** @brief Checks if number is on the array of int.
 * @param nbr Number to be searched for.
 * @param lis Array of int to search on.
 * @param size Size of the array.
 * @return True if number is found, False if not. */
static t_bool	is_on_lis(int nbr, int *lis, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (nbr == lis[i])
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
			rotate(a, 'a', *b);
		else
		{
			pushes--;
			push(a, b, 'a');
		}
		if (!pushes)
			break ;
	}
}

/** @brief Checks if next number on the stack is a better option for LIS.
 * If it is lower than the current, but higher than the last saved.
 * @param curr Current node of the stack.
 * @param last_low Value of last LIS number.
 * @param head First node of the stack.
 * @param first Value of first node that was searched on.
 * @return True if next number is a better option, False if not. */
static t_bool	next_better(t_stk *curr, int last_low, t_stk *head, int first)
{
	int	curr_nbr;
	int	next_number;

	curr_nbr = curr->nbr;
	if (!curr->next)
		next_number = head->nbr;
	else
		next_number = curr->next->nbr;
	if (next_number == first)
		return (FALSE);
	if (next_number < curr_nbr && next_number > last_low)
		return (TRUE);
	return (FALSE);
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
