#include "push_swap.h"

/** @brief Writes on stdout the Error message,
 * and exit the program with the error number received as parameter.
 * @param err_no Number of the error that occured. */
void	error_msg(int err_no)
{
	ft_putendl_fd("Error", 2);
	exit(err_no);
}

/** @brief Free both stacks and in case of error exits with err_no.
 * @param a Linked list a to be freed.
 * @param b	Linked List b to be freed.
 * @param err_no Error number to be exited or 0 if no error is found. */
void	end_all(t_stacks *a, t_stacks *b, int err_no)
{
	t_stacks	*tmp;

	while (a)
	{
		tmp = a->next;
		free(a);
		a = tmp;
	}
	while (b)
	{
		tmp = b->next;
		free(b);
		b = tmp;
	}
	if (err_no)
		error_msg(err_no);
}

/** @brief Checks if all the numbers on the stack are in crescent order.
 * @param stack Linked list to be checked.
 * @return True if is in order, False if not. */
t_bool	in_order(t_stacks *stack)
{
	t_stacks	*tmp;
	t_stacks	*check;

	tmp = stack;
	while (tmp->next)
	{
		check = tmp->next;
		while (check)
		{
			if (tmp->nbr < check->nbr)
				return (FALSE);
			check = check->next;
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
