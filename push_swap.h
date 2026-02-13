#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
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
}		t_stk;

//PARSE

t_stk	*parsing(char **args);

//Argument checkers

void	empty_arg(char **args);
void	valid_args(char **args);
void	duplicate_check(int nbr, t_stk *stack);

//Commands

void	swap(t_stk *stack, char id, t_stk *error);
void	push(t_stk **stack_from, t_stk **stack_to, char id);
void	rotate(t_stk **stack, char id, t_stk *error);
void	rev_rotate(t_stk **stack, char id, t_stk *error);
void	double_rotation(t_stk **a, t_stk **b, t_bool way);

//End program

void	error_msg(int err_no);
void	end_all(t_stk *a, t_stk *b, int err_no);

// Getters
void	get_lowest(t_stk *stack, int *l1, int *l2);
void	get_highest(t_stk *stack, int *h1, int *h2);
int		get_index(t_stk *stack, int nbr);
int		get_rotation(t_stk *stack, int nbr);

//Helpers

t_stk	*stack_last(t_stk *stack);
void	rotate_amount(t_stk **stack, int roll, char id, t_stk *error);
void	best_rotation(t_stk **stack, int nbr, char id, t_stk *error);
t_bool	in_order(t_stk **stack, char id, t_stk *error);

//Order

void	sort_three(t_stk **a, t_stk **b, t_bool rotate_b);
void	sort_five(t_stk **a, t_stk **b, int size);
void	sort_big(t_stk **a, t_stk **b);

//Longest Increasing Subsequence

int		get_lis(t_stk *a, int *lis);
void	push_lis(t_stk **a, t_stk **b, int *lis, int size);

#endif