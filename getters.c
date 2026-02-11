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

/** @brief Calculates how many rotations need to be done for the nbr,
 * to get into the right place on stack.
 * @param stack Linked list with stack of numbers.
 * @param nbr	Number to be put on right location in stack.
 * @return Amount of rotation (or reverse) the stack had to do
 * to find the place. */
int	get_rotation(t_stacks *stack, int nbr)
{
	int			i;
	int			last;
	int			size;
	t_stacks	*tmp;

	tmp = stack;
	size = ft_lstsize(stack);
	i = 0;
	last = (stack_last(tmp))->nbr;
	while (tmp)
	{
		if ((nbr < tmp->nbr && nbr > last)
			|| (nbr < tmp->nbr && tmp->nbr > last && nbr > last))
			break ;
		last = tmp->nbr;
		tmp = tmp->next;
		i++;
	}
	if (i <= size / 2)
		return (i);
	return (i - size);
}
