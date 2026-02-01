#include "push_swap.h"

/** @brief Swaps the values of the 2 first nodes of the list
 * and prints the command or not accordingly to the flag.
 * @param stack
 * Pointer of the linked list.
 * @param flag
 * Tells the name of the list, or nothing if isn't supposed to write.
 * @return
 * Amount of chars writted to stdout. 0 in case nothing
 * needs to be written or exist. -1 in case of error. */
int swap(t_stacks *stack, char flag)
{
	int	tmp;

	if (!stack->next)
		return (0);
	tmp = stack->nbr;
	stack->nbr = stack->next->nbr;
	stack->next->nbr = tmp;
	if (flag == 'a')
		return (ft_putendl_fd("sa", 1));
	if (flag == 'b')
		return (ft_putendl_fd("sb", 1));
	return (0);
}

/** @brief Pushes the first node of the list from to to.
 * @param stack_from Pointer to first node of the list to remove from.
 * @param stack_to	Pointer to first node of the list to add to.
 * @param flag	Id of the stack that the node is coming from.
 * @return Amout of chars written. 0 if list doesn't exist.
 * -1 in case of error. */
int	push(t_stacks **stack_from, t_stacks **stack_to, char flag)
{
	t_stacks	*tmp;
	if (!stack_from)
		return (0);
	tmp = *stack_from;
	stack_from = &(*stack_from)->next;
	tmp->next = NULL;
	if (*stack_to)
		tmp->next = *stack_to;
	stack_to = &tmp;
	if (flag == 'a')
		return (ft_putendl_fd("pb", 1));
	return (ft_putendl_fd("pa", 1));
}

/** @brief Rotates the stack passing first element to be the last.
 * @param stack	Pointer to the first node of list to rotate.
 * @param flag	Flag with the name of the stack to print the move.
 * Or NULL if nothing has to be printed (rr case).
 * @return	Amount of chars writted to stdout. 0 in case nothing
 * needs to be written or exist. -1 in case of error. */
int	rotate(t_stacks **stack, char flag)
{
	t_stacks	*tmp;

	if (!(*stack)->next)
		return (0);
	tmp = *stack;
	stack = &(*stack)->next;
	tmp->next = NULL;
	ft_lstlast(stack)->next = tmp;
	if (flag == 'a')
		return (ft_putendl_fd("ra", 1));
	if (flag == 'b')
		return (ft_putendl_fd("rb", 1));
	return (0);
}
/** @brief Reverse rotates the stack passing last element to be the first.
 * @param stack	Pointer to the first node of list to rotate.
 * @param flag	Flag with the name of the stack to print the move.
 * Or NULL if nothing has to be printed (rr case).
 * @return	Amount of chars writted to stdout. 0 in case nothing
 * needs to be written or exist. -1 in case of error. */
int	rev_rotate(t_stacks **stack, char flag)
{
	t_stacks	*tmp;

	if (!(*stack)->next)
		return (0);
	tmp = *stack;
	stack = tmp->next;
	ft_lstlast(stack)->next = tmp;
	tmp->next = NULL;
	if (flag == 'a')
		return (ft_putendl_fd("rra", 1));
	if (flag == 'b')
		return (ft_putendl_fd("rrb", 1));
	return (0);
}
