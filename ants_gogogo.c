/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_gogogo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:19:07 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/27 20:19:08 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_ants		*new_ant(void)
{
	t_ants		*new;
	static int	num = 0;

	new = (t_ants *)malloc(sizeof(t_ants));
	new->ant = ++num;
	new->y = -1;
	new->x = 1;
	new->in = NULL;
	new->next = NULL;
	return (new);
}

t_ants		*make_ants_list(t_lemin *l)
{
	t_ants		*ants;
	t_ants		*cur;
	uintmax_t	num;

	ants = new_ant();
	cur = ants;
	num = 1;
	while (num < l->ants)
	{
		cur->next = new_ant();
		cur = cur->next;
		num++;
	}
	return(ants);
}

char		*get_room_name(t_lemin *l, int num)
{
	t_room		*r;
	
	r = l->rooms;
	while (r)
	{
		if (r->num == num)
			return (r->name);
		r = r->next;
	}
	return (NULL);
}

/*
**	char c == [S - start, F - Finsih, M - Midway]
*/
void		print_move(t_lemin *l, t_ants *a, char c)
{
	char	*name;

	name = get_room_name(l, l->paths[a->y][a->x]);
	if (c == 'S')
		ft_printf("{green}{b}L%ld-%s{0}{-} ", a->ant, name);
	else if (c == 'F')
		ft_printf("{magenta}{b}L%ld-%s{0}{-} ", a->ant, name);
	else
		ft_printf("{yellow}L%ld{yellow}-%s{-} ", a->ant, name);
	
}

int			is_good_way(t_lemin *l, int y)
{
	int			y1;
	uintmax_t	moves;
	
	if (y == 0)
		return (1);
	y1 = y - 1;
	moves = 0;
	while (y1 >= 0)
	{
		moves += l->paths[y][0] - l->paths[y1][0];
		y1--;
	}
//		printf("\n> moves: %ju\n", moves);
	if (l->start->ant > moves)
		return (1);
	else 
		return (0); 
}

void			move_along(t_lemin *l, t_ants *a)
{
	while (a && a->y != -1)
	{
		while (a->y == -2)
			a = a->next;
		a->x++;
		if (!l->paths[a->y][a->x + 1] || l->paths[a->y][a->x + 1] == -1)
		{
			print_move(l, a, 'F');
			a->y = -2;
			l->end->ant++;
		}
		else
			print_move(l, a, 'M');
		a = a->next;
	}
}

void			move_from_start(t_lemin *l, t_ants *a)
{
	int		y;
	int		ways;
	int		moved;
	
	ways = 0;
	while (l->paths[ways] && l->paths[ways][1] != -1)
			ways++;
	while (a->next && a->y != -1)
			a = a->next;
	moved = 0;
	y = 0;
	while (y < ways && moved < ways && a && l->start->ant)
	{
		if (is_good_way(l, y))
		{
			a->y = y;
			a->x++;
			print_move(l, a, 'S');
			moved++;
			l->start->ant--;
			a = a->next;
		}
		y++;
	}

}

void		ants_gogogo(t_lemin *l)
{
	t_ants		*a;
	
	a = make_ants_list(l);
//		print_ants(a);			//
	while (l->end->ant < l->ants)
	{
		move_along(l, a);
		if (l->start->ant > 0)
			move_from_start(l, a);
		ft_putchar('\n');
		l->move_count++;
	}
	ft_printf("\n{red}>> MOVES COUNT: {b}%lu{-}{0}\n", l->move_count);

//		print_ants(a);			//
//		printf(">> Start_ants: %lu, End_ants: %lu\n", l->start->ant, l->end->ant);		//

}


