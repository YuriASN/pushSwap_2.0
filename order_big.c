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
	rotate_amount(a, rotate_a, 'a', *b);
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
static int	normal_move(int move1, int move1_size, int move2, int move2_size)
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

/** @brief Calculates alternatives for the rotation and reverse rotation,
 * to get stack on the position that move gets.
 * Then if compares the rotation, reverse rotation and rotation together to see,
 * what uses less moves.
 * @param move_a Best rotation on A to push a number from B.
 * @param a_size Size of stack A.
 * @param move_b Best rotation to put the number that will be pushed on top.
 * @param b_size Size of stack B.
 * @return The minimum amount of moves that it takes to get ready for the push.
 * */
static int	best_combo(int move_a, int a_size, int move_b, int b_size)
{
	int	rott;
	int	revs;

	if (move_a >= 0)
		rott = move_a;
	else
		rott = move_a + a_size;
	if (move_b >= 0)
		rott += move_b;
	else
		rott += move_b + b_size;
	if (move_a < 0)
		revs = move_a;
	else
		revs = move_a - a_size;
	if (move_b < 0)
		revs += move_b;
	else
		revs += move_b - b_size;
	revs = (int)ft_abs(revs);
	if (rott < normal_move(move_a, a_size, move_b, b_size) && rott < revs)
		return (rott);
	if (revs < normal_move(move_a, a_size, move_b, b_size) && revs < rott)
		return (revs * -1);
	return (normal_move(move_a, a_size, move_b, b_size));
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
		moves = best_combo(push_rotation(*a, tmp->nbr),
				ft_lstsize((t_list *)*a), best_rotation(*b, tmp->nbr), b_size);
		if (moves < lowest_move)
		{
			lowest_move = moves;
			nbr = tmp->nbr;
		}
		tmp = tmp->next;
		++i;
	}
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
	push_lis(a, b, lis, lis_size);
	free(lis);
	while (*b)
		best_push(a, b, ft_lstsize((t_list *)*b));
	in_order(a, 'a', *b);
}
