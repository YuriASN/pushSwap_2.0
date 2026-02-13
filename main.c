#include "push_swap.h"

/** @brief Checks if numbers are organized, and if not,
 * choose the best algorithm to work with the list size. 
 * @param a Pointer to stack with numbers received by the program.
 * @param b	Pointer to empty stack. */
static void	sort_stk(t_stk **a, t_stk **b)
{
	int	size;

	size = ft_lstsize((t_list *)*a);
	if (size <= 3)
		sort_three(a, b, FALSE);
	else if (size <= 5)
		sort_five(a, b, size);
	else
		sort_big(a, b);
}

int	main(int argc, char **argv)
{
	t_stk	*stack_a;
	t_stk	*stack_b;

	if (argc < 2)
		return (0);
	if (!argv[1][0])
		error_msg(NO_ARG);
	stack_a = parsing(&argv[1]);
	stack_b = NULL;
	if (!in_order(&stack_a, 'a', NULL))
		sort_stk(&stack_a, &stack_b);
	end_all(stack_a, stack_b, 0);
	return (0);
}
