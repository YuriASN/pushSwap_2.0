#include "push_swap.h"

/** @brief Returns the last node of the stack list.
 * @param stack Head of the linked list to find the last node.
 * @return Pointer to the last node of given list. */
t_stacks	*stack_last(t_stacks *stack)
{
	t_stacks	*tmp;

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
void	rotate_amount(t_stacks **stack, int roll, char id, t_stacks *error)
{
		if (roll > 0)
			while (roll--)
				rotate(stack, id, error);
		else
			while (roll++)
				rev_rotate(stack, id, error);
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
	if ((stack_last(*stack))->nbr != high)
		best_rotation(stack, high, id, error);
	return (TRUE);
}
