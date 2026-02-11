#include "push_swap.h"

/** @brief Swaps the values of the 2 first nodes of the list
 * and prints the command or not accordingly to the id.
 * @param stack Pointer of the linked list.
 * @param id Id of the list, or nothing if isn't supposed to write.
 * @param error If existing, the other stack is sent to handle errors in write.
 * If not, send NULL.
 * @return Amount of chars writted to stdout. 0 in case nothing
 * needs to be written or exist. -1 in case of error. */
void	swap(t_stacks *stack, char id, t_stacks *error)
{
	int	tmp;

	if (!stack->next)
		return ;
	tmp = stack->nbr;
	stack->nbr = stack->next->nbr;
	stack->next->nbr = tmp;
	if (id == 'a')
		if (ft_putendl_fd("sa", 1) == -1)
			end_all(stack, error, WRITE_ERROR);
	if (id == 'b')
		if (ft_putendl_fd("sb", 1) == -1)
			end_all(stack, error, WRITE_ERROR);
}

/** @brief Pushes the first node of the list from to to.
 * @param stack_from Pointer to first node of the list to remove from.
 * @param stack_to	Pointer to first node of the list to add to.
 * @param id	Flag of the stack that the node is coming from.
 * @return Amout of chars written. 0 if list doesn't exist.
 * -1 in case of error. */
void	push(t_stacks **stack_from, t_stacks **stack_to, char id)
{
	t_stacks	*tmp;

	if (!*stack_from)
		return ;
	tmp = *stack_from;
	*stack_from = (*stack_from)->next;
	tmp->next = NULL;
	if (*stack_to)
		tmp->next = *stack_to;
	*stack_to = tmp;
	if (id == 'a')
		if (ft_putendl_fd("pb", 1) == -1)
			end_all(*stack_from, *stack_to, WRITE_ERROR);
	if (ft_putendl_fd("pa", 1) == -1)
		end_all(*stack_from, *stack_to, WRITE_ERROR);
}

/** @brief Rotates the stack passing first element to be the last.
 * @param stack	Pointer to the first node of list to rotate.
 * @param id	Flag with the name of the stack to print the move.
 * Or NULL if nothing has to be printed (rr case).
 * @param error If existing, the other stack is sent to handle errors in write.
 * If not, send NULL.
 * @return	Amount of chars writted to stdout. 0 in case nothing
 * needs to be written or exist. -1 in case of error. */
void	rotate(t_stacks **stack, char id, t_stacks *error)
{
	t_stacks	*tmp;

	if (!(*stack)->next)
		return ;
	tmp = *stack;
	*stack = (*stack)->next;
	tmp->next = NULL;
	stack_last(*stack)->next = tmp;
	if (id == 'a')
		if (ft_putendl_fd("ra", 1) == -1)
			end_all(*stack, error, WRITE_ERROR);
	if (id == 'b')
		if (ft_putendl_fd("rb", 1) == -1)
			end_all(*stack, error, WRITE_ERROR);
}

/** @brief Reverse rotates the stack passing last element to be the first.
 * @param stack	Pointer to the first node of list to rotate.
 * @param id	Flag with the name of the stack to print the move.
 * Or NULL if nothing has to be printed (rr case).
 * @param error If existing, the other stack is sent to handle errors in write.
 * If not, send NULL.
 * @return	Amount of chars writted to stdout. 0 in case nothing
 * needs to be written or exist. -1 in case of error. */
void	rev_rotate(t_stacks **stack, char id, t_stacks *error)
{
	t_stacks	*tmp;
	t_stacks	*last;

	if (!(*stack)->next)
		return ;
	last = stack_last(*stack);
	tmp = *stack;
	while (tmp->next != last)
		tmp = tmp->next;
	last->next = *stack;
	*stack = last;
	tmp->next = NULL;
	if (id == 'a')
		if (ft_putendl_fd("rra", 1) == -1)
			end_all(*stack, error, WRITE_ERROR);
	if (id == 'b')
		if (ft_putendl_fd("rrb", 1) == -1)
			end_all(*stack, error, WRITE_ERROR);
}

/** @brief Do the double rotation to the side decided by the id.
 * @param a Pointer to linked list a.
 * @param b Pointer to linked list b.
 * @param way TRUE if is normal rotation, FALSE if is reverse. */
void	double_rotation(t_stacks **a, t_stacks **b, t_bool way)
{
	if (!*a || !*b)
		return ;
	if (way)
	{
		rotate(a, (char)0, *b);
		rotate(b, (char)0, *a);
		if (ft_putendl_fd("rr", 2) == -1)
			end_all(*a, *b, WRITE_ERROR);
	}
	else
	{
		rev_rotate(a, (char)0, *b);
		rev_rotate(b, (char)0, *a);
		if (ft_putendl_fd("rrr", 2) == -1)
			end_all(*a, *b, WRITE_ERROR);
	}
}
