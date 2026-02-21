#include "push_swap.h"

/** @brief Returns the last node of the stack list.
 * @param stack Head of the linked list to find the last node.
 * @return Pointer to the last node of given list. */
t_stk	*stack_last(t_stk *stack)
{
	t_stk	*tmp;

	if (!stack)
		return (NULL);
	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/** @brief Rotates the stack the amount of times of roll.
 * Rotating reverse if roll is a negative number.
 * @param stack Pointer to linked list to rotate.
 * @param roll Amount of rotations need to be done.
 * @param id Id of the stack being rotated.
 * @param error The other linked list to work with it in case of error. */
void	rotate_amount(t_stk **stack, int roll, char id, t_stk *error)
{
	if (!roll)
		return ;
	if (roll > 0)
		while (roll--)
			rotate(stack, id, error);
	else
		while (roll++)
			rev_rotate(stack, id, error);
}

/** @brief Takes a Stack and a number that it has, choose wich rotation will use
 * less moves to put the number at first, return the amount of rotations needed.
 * @param stack	Pointer to the first node of the list.
 * @param nbr	Number we will put at first.
 * @return Amount of rotation or rev rotation (negative) needed. */
int	best_rotation(t_stk *stack, int nbr)
{
	int			i;
	int			size;

	size = ft_lstsize((t_list *)stack);
	i = get_index(stack, nbr);
	if (!i || !size)
		return (0);
	if (i <= size / 2)
		return (i);
	else
		return (i - size);
}

/** @brief Checks if all the numbers on the stack are in crescent order.
 * If it's in order but need only rotation, already call function to do it.
 * @param stack Linked list to be checked.
 * @param error If existing, the other linked list to handle errors in write.
 * If not, send NULL.
 * @return True if is or was put in order, False if not. */
t_bool	in_order(t_stk **stack, char id, t_stk *error)
{
	t_stk	*tmp;
	int		high;
	int		low;

	tmp = *stack;
	get_highest(*stack, &high, NULL);
	get_lowest(*stack, &low, NULL);
	while (tmp->next)
	{
		if (tmp->nbr != high && tmp->nbr > tmp->next->nbr)
			return (FALSE);
		tmp = tmp->next;
	}
	if (tmp->nbr != high && tmp->nbr > (*stack)->nbr)
		return (FALSE);
	if ((stack_last(*stack))->nbr != high)
		rotate_amount(stack, best_rotation(*stack, low), id, error);
	return (TRUE);
}

/** @brief Checks if number is on the array of int.
 * @param nbr Number to be searched for.
 * @param lis Array of int to search on.
 * @param size Size of the array.
 * @return True if number is found, False if not. */
t_bool	is_on_lis(int nbr, int *lis, int size)
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
