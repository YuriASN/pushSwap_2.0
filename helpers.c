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

/** @brief Takes a Stack that is in order but need rotation,
 * chooses which way will rotate with less moves, and do it.
 * @param stack Pointer to the first node of the list.
 * @param id Flag telling if it's stack a or b. */
static void	best_rotation(t_stacks **stack, char id)
{
	int			i;
	int			count;
	int			high;
	int			size;
	t_stacks	*tmp;

	count = 0;
	high = (*stack)->nbr;
	tmp = (*stack)->next;
	size = ft_lstsize(*stack);
	while (tmp)
	{
		if (high < tmp->nbr)
		{
			i = count;			//salvo o index do maior número
			high = tmp->nbr;
		}
		++count;
	}
	if (i <= size)				//se p index estiver do meio pra baixo eu rodo
		while (i--)
			rotate(stack, id);
	else						//caso contrario rodo reverso
		while (i++ < size)
			rev_rotate(stack, id);
}

/** @brief Checks if all the numbers on the stack are in crescent order.
 * If it's in order but need only rotation, already call function to do it.
 * @param stack Linked list to be checked.
 * @return True if is or was put in order, False if not. */
t_bool	in_order(t_stacks **stack, char id)
{
	t_stacks	*tmp;
	int			high;
	int			prev;

	//descubro o maior valor
	tmp = (*stack)->next;
	high = (*stack)->nbr;
	while (tmp)
	{
		if (high < tmp->nbr)
			high = tmp->nbr;
		tmp = tmp->next;
	}
	/* rodo while conferindo se está em ordem exceto
	quando o maior está sendo comparado com o próximo */
	tmp = *stack;
	while (tmp->next)
	{
		if (tmp->nbr != high && tmp->nbr > tmp->next->nbr)
			return (FALSE);
	}
	if (((t_stacks *)ft_lstlast(*stack))->nbr != high)
		best_rotation(&stack, id);
	return (TRUE);
}
