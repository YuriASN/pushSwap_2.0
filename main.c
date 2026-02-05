#include "push_swap.h"

/** @brief Checks if numbers are organized, and if not,
 * choose the best algorithm to work with the list size. 
 * @param a Pointer to stack with numbers received by the program.
 * @param b	Pointer to empty stack. */
static void	sort_stacks(t_stacks **a, t_stacks **b)
{
	int	size;

	size = ft_lstsize(*a);
	if (size == 2)
		ft_putendl_fd("sa", 1);
	else if (size < 3)
		sort_three(a);
	else if (size <= 5)
		sort_five(a, b);
	else
		sort_big(a, b);
}

int	main(int argc, char **argv)
{
	t_stacks	*stack_a;
	t_stacks	*stack_b;

	if (argc < 2 || !argv[1][0])
		error_msg(NO_ARG);
	stack_a = parsing(&argv[1]);
	stack_b = NULL;
	if (!in_order(stack_a, 'a', NULL))
		sort_stacks(&stack_a, &stack_b);
	end_all(stack_a, stack_b, 0);
	return (0);
}
