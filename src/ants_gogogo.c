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

#include "../inc/lem_in.h"

int				is_good_way(t_lemin *l, int y)
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
	if ((uintmax_t)l->start->ant >= moves)
		return (1);
	else
		return (0);
}

void			move_along(t_lemin *l, t_ants *a)
{
	while (a)
	{
		if (a->y >= 0)
		{
			a->x++;
			if (l->paths[a->y][a->x] == l->end->num)
			{
				print_move(l, a, 'F');
				a->y = -2;
				l->end->ant++;
			}
			else
				print_move(l, a, 'M');
		}
		a = a->next;
	}
}

void			move_from_start2(t_lemin *l, t_ants **a, int *moved, int *y)
{
	(*a)->y = *y;
	(*a)->x++;
	if (l->paths[(*a)->y][(*a)->x] == l->end->num)
	{
		print_move(l, (*a), '1');
		(*a)->y = -2;
		l->end->ant++;
	}
	else
		print_move(l, (*a), 'S');
	(*moved)++;
	l->start->ant--;
	(*a) = (*a)->next;
}

void			move_from_start(t_lemin *l, t_ants *a)
{
	int		y;
	int		ways;
	int		moved;

	ways = 0;
	while (l->paths[ways] && l->paths[ways][1] != -1)
		ways++;
	while (a->next && (a->y == -2 || a->y > -1))
		a = a->next;
	moved = 0;
	y = 0;
	while (y < ways && moved < ways && a && l->start->ant)
	{
		if (is_good_way(l, y))
			move_from_start2(l, &a, &moved, &y);
		y++;
	}
}

void			ants_gogogo(t_lemin *l)
{
	t_ants		*a;

	a = make_ants_list(l);
	ft_putchar('\n');
	while (l->end->ant < l->ants)
	{
		ft_printf("{cyan}[%lu]>{-} ", l->move_count + 1);
		if (l->move_count)
			move_along(l, a);
		if (l->start->ant > 0)
			move_from_start(l, a);
		ft_putchar('\n');
		l->move_count++;
	}
	if (!l->options[1])
		print_moves_count(l);
	kill_all_the_ants(a);
}
