#include "push_swap.h"

/** @brief Passes the number (or first number) on str to the nbr at node.
 * And jumps to the end of string, or next value.
 * @param str String where the number is at.
 * @param node The node to receive the value.
 * @return True if number was passed, False if number exceeds int min or max. */
static t_bool	get_number(char **str, t_stk *node)
{
	int		nbr;

	if (ft_atoi_overflow(*str))
		return (FALSE);
	nbr = ft_atoi(*str);
	node->nbr = nbr;
	while (**str == '-' || **str == '+')
		(*str)++;
	while (ft_isdigit(**str))
		(*str)++;
	while (ft_isspace(**str))
		(*str)++;
	return (TRUE);
}

/** @brief Passes args to nodes, checking if it's value is duplicated
 * and return the head of linked list.
 * @param arg String with number or numbers to be added.
 * @return Head of the linked list created. */
static t_stk	*stack_init(char *arg)
{
	t_stk	*head;
	t_stk	*new;

	head = NULL;
	while (*arg)
	{
		new = ft_calloc(1, sizeof(t_stk));
		if (!new)
			end_all(head, NULL, ALLOCATION_ERROR);
		new->next = NULL;
		if (head)
			(stack_last(head))->next = new;
		else
			head = new;
		if (!get_number(&arg, new))
			end_all(head, NULL, INT_OVERFLOW);
		duplicate_check(new->nbr, head);
	}
	return (head);
}

/** @brief Check if content of args are valid, and if so,
 * parse the arg to the stack linked list.
 * @param args List of arguments received by the program.
 * @return The head of the linked list generated,
 * or NULL if any error occurs. */
t_stk	*parsing(char **args)
{
	t_stk	*head;
	int		i;

	if (!args || !*args)
		error_msg(INVALID_ARGS);
	empty_arg(args);
	valid_args(args);
	head = stack_init(args[0]);
	i = 0;
	while (args[++i])
		stack_last(head)->next = stack_init(args[i]);
	return (head);
}
