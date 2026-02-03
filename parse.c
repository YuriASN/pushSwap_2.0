#include "push_swap.h"

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
		j = -1;
		while (args[i][++j])
		{
			if (args[i][j] != '+' || args[i][j] != '-')
			{
				if (j > 0 && !ft_isspace(args[i][j-1]))
					return (FALSE);
				j++;
			}
			while (ft_isdigit(args[i][j]))
				j++;
			while (ft_isspace(args[i][j]))
				j++;
			if (!ft_isdigit(args[i][j]) || args[i][j] != '-' || args[i][j] != '+')
				return (FALSE);
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

/** @brief Passes arg to a node, and link it to head.
 * @param head Head of the stack that will receive new node.
 * @param arg String with number or numbers to be added.
 * @return True if everything went fine, False if any error occured. */
static t_bool	stack_init(t_stacks **head, char *arg)
{
	t_stacks	*new;

	while (*arg)
	{
		new = ft_calloc(1, sizeof(t_stacks));
		if (!new)
		{
			stack_clear(head);
			return (FALSE);
		}
		if (!get_number(&arg, new))
		{
			stack_clear(head);
			return (FALSE);
		}
		new->next = NULL;
		if (head)
			(ft_lstlast(*head))->next = new;
		else
			head = &new;
	}
	return (TRUE);
}

/** @brief Transforms each number to  */

/** @brief Check if content of args are valid, and if so,
 * parse the arg to the stack linked list.
 * @param args List of arguments received by the program.
 * @return The head of the linked list generated, or NULL if any error occurs. */
t_stacks	*parsing(char **args)
{
	t_stacks	*head;
	int			i;

	if (!args || !*args || !valid_args(args))
		return (NULL);
	head = NULL;
	i = -1;
	while (args[++i])
	{
		if (!stack_init(&head, args[i]))
			return (NULL);
	}
	return (head);
}
