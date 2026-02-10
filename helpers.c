#include "push_swap.h"

/** @brief Search for the 2 lowest numbers on the stack.
 * @param stack Stack to search on.
 * @param l1 Pointer to attribute the lowest number.
 * @param l2 Pointer to attribute the 2nd lowest.
 * NULL if you only need the lowest. */
void	get_lowest(t_stacks *stack, int *l1, int *l2)
{
	t_stacks	*tmp;

	tmp = stack;
	*l1 = tmp->nbr;
	if (l2)
		*l2 = INT_MAX;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (*l1 > tmp->nbr)
		{
			if (*l2)
				*l2 = *l1;
			*l1 = tmp->nbr;
		}
		else if (l2 && (*l2 > tmp->nbr || *l2 == *l1))
			*l2 = tmp->nbr;
	}
}

/** @brief Search for the 2 highest numbers on the stack.
 * @param stack Stack to search on.
 * @param h1 Pointer to attribute the highest number.
 * @param h2 Pointer to attribute the 2nd highest. NULL if you only want one */
void	get_highest(t_stacks *stack, int *h1, int *h2)
{
	t_stacks	*tmp;

	tmp = stack;
	*h1 = tmp->nbr;
	if (h2)
		*h2 = INT_MIN;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (*h1 < tmp->nbr)
		{
			if (h2)
				*h2 = *h1;
			*h1 = tmp->nbr;
		}
		else if (h2 && (*h2 < tmp->nbr || *h2 == *h1))
			*h2 = tmp->nbr;
	}
}

/** @brief Return the index of the node that has the given number.
 * @param stack Linked list to search on.
 * @param nbr	Number you're looking for.
 * @return Index of the node that number was found. */
int	get_index(t_stacks *stack, int nbr)
{
	int			i;
	t_stacks	*tmp;

	if (!stack)
		return (0);
	i = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->nbr == nbr)
			return (i);
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/** @brief Takes a Stack and a number that it has, choose wich rotation will use
 * less moves to put the number at first, and rotate that way.
 * @param stack	Pointer to the first node of the list.
 * @param nbr	Number we will put at first.
 * @param id	Flag telling if it's stack a or b. */
void	best_rotation(t_stacks **stack, int nbr, char id, t_stacks *error)
{
	int			i;
	int			size;

	size = ft_lstsize(*stack);
	i = get_index(*stack, nbr);
	if (!i || !size)
		return ;
	if (i <= size)
		while (i--)
			rotate(stack, id, error);
	else
		while (i++ < size)
			rev_rotate(stack, id, error);
}

/** @brief Checks if all the numbers on the stack are in crescent order.
 * If it's in order but need only rotation, already call function to do it.
 * @param stack Linked list to be checked.
 * @param error If existing, the other linked list to handle errors in write.
 * If not, send NULL.
 * @return True if is or was put in order, False if not. */
t_bool	in_order(t_stacks **stack, char id, t_stacks *error)
{
	t_stacks	*tmp;
	int			high;

	tmp = *stack;
	get_highest(*stack, &high, NULL);
	while (tmp->next)
	{
		if (tmp->nbr != high && tmp->nbr > tmp->next->nbr)
			return (FALSE);
	}
	if (((t_stacks *)ft_lstlast(*stack))->nbr != high)
		best_rotation(stack, high, id, error);
	return (TRUE);
}
