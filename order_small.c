#include "push_swap.h"

/** @brief Sort numbers when stack is size of 3, and they need more
 * than just rotate, wich leaves only 3 options.
 * @param a Stack to sort numbers.
 * @param b Stack to rotate together, or NULL if only one stack exists.
 * @param rotate_b Flag to see if b needs rotation */
void	sort_three(t_stk **a, t_stk **b, t_bool rotate_b)
{
	if ((*a)->nbr > (*a)->next->nbr && (*a)->nbr < (*a)->next->next->nbr)
	{
		swap(*a, 'a', *b);
		if (rotate_b)
			rotate(b, 'b', *a);
	}
	else if ((*a)->nbr < (*a)->next->nbr && (*a)->nbr < (*a)->next->next->nbr)
	{
		swap(*a, 'a', *b);
		if (rotate_b)
			double_rotation(a, b, TRUE);
		else
			rotate(a, 'a', *b);
	}
	else if ((*a)->nbr > (*a)->next->nbr && (*a)->nbr > (*a)->next->next->nbr)
	{
		if (rotate_b)
			double_rotation(a, b, TRUE);
		else
			rotate(a, 'a', *b);
		swap(*a, 'a', *b);
	}
}

/** @brief Returns the amount of rotation or reverse rotation (the closest one)
 * needed to get to a number on the top of a stack.
 * @param stack Stack to find number on it.
 * @param nbr	Number you're looking to be at top of stack.
 * @return 		Amount of rotation needed to put nbr on top. */
static int	rotation_amount(t_stk *stack, int nbr)
{
	int		i;
	int		size;
	t_stk	*tmp;

	i = 0;
	tmp = stack;
	size = ft_lstsize((t_list *)stack);
	while (tmp)
	{
		if (stack->nbr == nbr)
		{
			if (i > size / 2)
				i = size - i;
			return (i);
		}
		tmp = tmp->next;
		++i;
	}
	return (i);
}

/*to order five we need to push 2 lowest numbers to the other side,
if they are in crescent order there, we need to rotate,
better to do double rotation to reduce one move,
order the 3 left (if !in_order() -> sort_three()) and push the 2 back */

/** @brief Sort list of 4 or 5 numbers by passing the 1 or 2 lower
 * to stack b, performing in_order or sort_three, and pushing back from
 * b to a.
 * @param a Pointer to stack a with all the numbers.
 * @param b Pointer to empty stack to receive numbers. */
void	sort_five(t_stk **a, t_stk **b, int size)
{
	t_bool	rotate_b;
	int		lower1;
	int		lower2;

	rotate_b = FALSE;
	get_lowest(*a, &lower1, &lower2);
	if (size == 5 && rotation_amount(*a, lower1) > rotation_amount(*a, lower2))
	{
		rotate_b = TRUE;
		ft_intswap(&lower1, &lower2);
	}
	best_rotation(a, lower1, 'a', *b);
	push(a, b, 'a');
	if (size == 5)
	{
		best_rotation(a, lower2, 'a', *b);
		push(a, b, 'a');
	}
	if (!in_order(a, 'a', *b))
		sort_three(a, b, rotate_b);
	push(b, a, 'b');
	if (size == 5)
		push(b, a, 'b');
}
