#include "push_swap.h"

/** @brief Checks if any of the args only has spaces.
 * If so, ends the program.
 * @param arg Argument to be checked. */
void	empty_arg(char **args)
{
	int	i;
	int	j;

	j = -1;
	while (args[++j])
	{
		i = 0;
		while (args[j][i] && ft_isspace(args[j][i]))
				++i ;
		if (!args[j][i])
			error_msg(EMPTY_ARGS);
	}
}

/** @brief Checks if argument recieved has only digits,
 * signal (with space behind) or spaces.
 * @param args Pointer to matrix of string to be checked.*/
void	valid_args(char **args)
{
	int	i;
	int	j;

	i = -1;
	while (args[++i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '+' || args[i][j] == '-')
			{
				if (!args[i][j + 1] || (j > 0 && (!ft_isspace(args[i][j - 1])
					|| !ft_isdigit(args[i][j + 1]))))
					error_msg(INVALID_ARGS);
				j++;
			}
			while (ft_isdigit(args[i][j]))
				j++;
			while (ft_isspace(args[i][j]))
				j++;
			if (args[i][j] && (!ft_isdigit(args[i][j]) && args[i][j] != '-'
				&& args[i][j] != '+'))
				error_msg(INVALID_ARGS);
		}
	}
}

/** @brief Check if any number is duplicated, without checking the last,
 * as it's where nbr comes from. If so, exists safely the program.
 * @param nbr Number on first node to compared with others.
 * @param stack Second node of the stack, to compare from it, to the end.*/
void	duplicate_check(int nbr, t_stacks *stack)
{
	t_stacks	*tmp;

	tmp = stack;
	while (tmp->next)
	{
		if (nbr == tmp->nbr)
			end_all(stack, NULL, DUPLICATED);
		tmp = tmp->next;
	}
}
