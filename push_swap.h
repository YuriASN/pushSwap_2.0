#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include <limits.h>
# define TRUE 1
# define FALSE 0

//Exit status
# define NO_ARG 1
# define ALLOCATION_ERROR 2
# define INT_OVERFLOW 3
# define DUPLICATED 4
# define INVALID_ARGS 5
# define EMPTY_ARGS 6
# define WRITE_ERROR 7

typedef int		t_bool;
typedef struct	s_stacks
{
	//char			id;
	int				nbr;
	//struct s_stacks	*prev;
	struct s_stacks	*next;
}		t_stacks;


//PARSE

t_stacks	*parsing(char **args);

//Argument checkers

void		empty_arg(char **args);
void		valid_args(char **args);
void		duplicate_check(int nbr, t_stacks *stack);

//Commands

void		swap(t_stacks *stack, char id, t_stacks *error);
void		push(t_stacks **stack_from, t_stacks **stack_to, char id);
void		rotate(t_stacks **stack, char id, t_stacks *error);
void		rev_rotate(t_stacks **stack, char id, t_stacks *error);
void		double_rotation(t_stacks **a, t_stacks **b, t_bool way);

//End program

void		error_msg(int err_no);
void		end_all(t_stacks *a, t_stacks *b, int err_no);

// Getters
void		get_lowest(t_stacks *stack, int *l1, int *l2);
void		get_highest(t_stacks *stack, int *h1, int *h2);
int			get_index(t_stacks *stack, int nbr);
int			get_rotation(t_stacks *stack, int nbr);

//Helpers

t_stacks	*stack_last(t_stacks *stack);
void		rotate_amount(t_stacks **stack, int roll, char id, t_stacks *error);
void		best_rotation(t_stacks **stack, int nbr, char id, t_stacks *error);
t_bool		in_order(t_stacks **stack, char id, t_stacks *error);

//Order

void		sort_three(t_stacks **a, t_stacks **b, t_bool rotate_b);
void		sort_five(t_stacks **a, t_stacks **b, int size);
void		sort_big(t_stacks **a, t_stacks **b);

#endif