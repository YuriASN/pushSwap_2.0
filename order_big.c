#include "push_swap.h"

/** @brief Sets both stacks on place for number to be pushed.
 * @param a Stack A that will receive the number.
 * @param b Stack B that will receive the number.
 * @param nbr Number in B that will go to A. */
static void	set_in_place(t_stk **a, t_stk **b, int nbr)
{
	int	rotate_a;
	int	rotate_b;

	rotate_b = best_rotation(*b, nbr);
	rotate_a = push_rotation(*a, nbr);
	if (rotate_a > 0 && rotate_b > 0)
	{
		while (rotate_a && rotate_b)
		{
			double_rotation(a, b, TRUE);
			rotate_a--;
			rotate_b--;
		}
	}
	else if (rotate_a < 0 && rotate_b < 0)
	{
		while (rotate_a && rotate_b)
		{
			double_rotation(a, b, FALSE);
			rotate_a++;
			rotate_b++;
		}
	}
	if (rotate_a)
		rotate_amount(a, rotate_a, 'a', *b);
	if (rotate_b)
		rotate_amount(b, rotate_b, 'b', *a);
}

/** @brief Calculate the amount of moves done if stacks can be moved together,
 * using rr or rrr. If not, returns sum of both amount of moves.Int overflow
 * wasn't take in account as moves can be maximmum of size of stack.
 * @param move1 Amount of moves of one stack.
 * @param move1_size Size of stack of move1.
 * @param move2 Amount of moves of other stack.
 * @param move2_size Size of stack of move2.
 * @return Amount of total moves. */
static int	move_together(int move1, int move1_size, int move2, int move2_size)
{
	if (!(move1_size % 2) && move1 == move1_size / 2)
	{
		if (move2 < 0)
			move1 *= -1;
	}
	else if (!(move2_size % 2) && move2 == move2_size / 2)
	{
		if (move1 < 0)
			move2 *= -1;
	}
	if ((move1 < 0 && move2 < 0) || (move1 >= 0 && move2 >= 0))
	{
		if (ft_abs(move1) >= ft_abs(move2))
			return ((int)ft_abs(move1));
		return ((int)ft_abs(move2));
	}
	return ((int)ft_abs(move1) + (int)ft_abs(move2));	
}
//Try many rotations. Use move together. both rotating and bot rev rotating. compare the 3 and decide the minimmum.
static int	best_combo(int move_a, int a_size, int move_b, int b_size)
{
	int	together;
	int	rotate_alt;
	int	rev_alt;

	together = move_together(move_a, a_size, move_b, b_size);
	if (move_a >= 0)
		rotate_alt = move_a;
	else
		rotate_alt = move_a + a_size;
	if (move_b >= 0)
		rotate_alt += move_b;
	else
		rotate_alt += move_b + b_size;
	if (move_a < 0)
		rev_alt = move_a;
	else
		rev_alt = move_a - a_size;
	if (move_b < 0)
		rev_alt += move_b;
	else
		rev_alt += move_b - b_size;
/*	if (move_a >= 0)
	{
		rotate_alt = move_a;
		rev_alt = move_a - a_size;
	}
	else
	{
		rev_alt = move_a;
	}
	if (move_b >= 0)
	{
		rotate_alt += move_b;
		rev_alt += move_b - b_size;
	}
	else
	{
		rotate_alt += move_b + b_size;
		rev_alt += move_b;
	}*/
	if (rotate_alt < ft_abs(together) && rotate_alt < ft_abs(rev_alt))
		return (rotate_alt);
	if (ft_abs(rev_alt) < ft_abs(together) && ft_abs(rev_alt) < rotate_alt)
		return (rev_alt * -1);
	return (together);
}


/** @brief Find the number in B that can be pushed to A with the less.
 * amount of moves in between them all.
 * @param a Pointer to linked list with stack a.
 * @param b Pointer to linked list with stack b. */
static void	best_push(t_stk **a, t_stk **b, int b_size)
{
	t_stk	*tmp;
	int		nbr;
	int		i;
	int		moves;
	int		lowest_move;

	lowest_move = INT_MAX;
	tmp = *b;
	i = 0;
	while (tmp)
	{
		moves = best_combo(push_rotation(*a, tmp->nbr), ft_lstsize((t_list *)*a), best_rotation(*b, tmp->nbr), b_size);
//		moves = push_rotation(*a, tmp->nbr);
//		moves = move_together(moves, i, b_size);
		if (moves < lowest_move)
		{
			lowest_move = moves;
			nbr = tmp->nbr;
		}
		tmp = tmp->next;
		++i;
	}
// implement double rotation for both lines. nbr is the one in
//	rotate_amount(b , best_rotation(*b, nbr), 'b', *a);
//	rotate_amount(a, push_rotation(*a, nbr), 'a', *b);
	set_in_place(a, b, nbr);
	push(b, a, 'b');
}

/** @brief Sort big stacks by find the numbers that are in order, starting from
 * the lowest. Push all the numbers that aren't to stack b.
 * And call helper to push them back in order.
 * @param a Pointer to first node of stack A.
 * @param b Pointer to first node of stack B. */
void	sort_big(t_stk **a, t_stk **b)
{
	int	*lis;
	int	lis_size;

	lis = ft_calloc((size_t)ft_lstsize((t_list *)*a), sizeof(int *));
	lis_size = get_lis(*a, lis);
//	print_int_array(lis, lis_size);	//
	push_lis(a, b, lis, lis_size);
	free(lis);
//	getchar();	//read_all(*a); read_all(*b);//
	while (*b)
		best_push(a, b, ft_lstsize((t_list *)*b));
	in_order(a, 'a', *b);
}
