#include "push_swap.h"

/** @brief Checks if the arg only has spaces.
 * If so, ends the program.
 * @param arg Argument to be checked. */
static void	empty_arg(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (!ft_isspace(arg[i]))
			return;
	error_msg(INVALID_ARGS);
}

/** @brief Checks if argument recieved has only digits,
 * signal (with space behind) or spaces.
 * @param args Pointer to matrix of string to be checked.
 * @return True if only those things were found. False if not. */
static t_bool	valid_args(char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i])
	{
		j = 0;
		empty_arg(*args);
		while (args[i][j])
		{
			if (args[i][j] == '+' || args[i][j] == '-')
			{
				if (!args[i][j+1] || (j > 0 && (!ft_isspace(args[i][j-1]) || !ft_isdigit(args[i][j+1]))))
					error_msg(INVALID_ARGS);
				j++;
			}
			while (ft_isdigit(args[i][j]))
				j++;
			while (ft_isspace(args[i][j]))
				j++;
			if (args[i][j] && (!ft_isdigit(args[i][j]) && args[i][j] != '-' && args[i][j] != '+'))
				error_msg(INVALID_ARGS);
		}
	}
	return (TRUE);
}

/** @brief Passes the number (or first number) on str to the nbr at node.
 * And jumps to the end of string, or next value.
 * @param str String where the number is at.
 * @param node The node to receive the value.
 * @return True if number was passed, False if number exceeds int min or max.
 */
static t_bool	get_number(char **str, t_stacks *node)
{
	ssize_t	nbr;
	int		i;
	int		decimal;

	nbr = ft_atoi(**str);
	while (ft_isdigit(**str) || **str == '-' || **str == '+')
		**str++;
	i = 0;
	decimal = 10;
	while (nbr % decimal)
	{
		if (*str[--i] - '0' != (nbr % decimal) / (decimal / 10))
			return (FALSE);
		decimal *= 10;
	}
	while (ft_isspace(**str))
		**str++;
	return (TRUE);
}

/** @brief Check if any number is duplicated.
 * If so, exists safely the program.
 * @param nbr Number on first node to compared with others.
 * @param stack Second node of the stack, to compare from it, to the end.*/
static void	duplicate_check(int nbr, t_stacks *stack)
{
	t_stacks	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (nbr == tmp->nbr)
			end_all(nbr, NULL, DUPLICATED);
		tmp = tmp->next;
	}
}

/** @brief Passes arg to a node, and link it to head
 * and check if it's value is duplicated.
 * @param head Head of the stack that will receive new node.
 * @param arg String with number or numbers to be added.
 * @return True if everything went fine, False if any error occured. */
static void	stack_init(t_stacks **head, char *arg)
{
	t_stacks	*new;

	while (*arg)
	{
		new = ft_calloc(1, sizeof(t_stacks));
		if (!new)
			end_all(*head, NULL, ALLOCATION_ERROR);
		new->next = NULL;
		if (head)
			(ft_lstlast(*head))->next = new;
		else
			head = &new;
		if (!get_number(&arg, new))
			end_all(*head, NULL, INT_OVERFLOW);
		duplicate_check(new->nbr, new->next);
	}
}

/** @brief Check if content of args are valid, and if so,
 * parse the arg to the stack linked list.
 * @param args List of arguments received by the program.
 * @return The head of the linked list generated, or NULL if any error occurs. */
t_stacks	*parsing(char **args)
{
	t_stacks	*head;
	int			i;

	if (!args || !*args)
		error_msg(INVALID_ARGS);
	valid_args(args);
	head = NULL;
	i = -1;
	while (args[++i])
		stack_init(&head, args[i]);
	return (head);
}
