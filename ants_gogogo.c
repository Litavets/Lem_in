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

void		print_move(t_lemin *l, t_ants *a)
{
	char	*name;

	name = get_room_name(l, l->paths[a->y][a->x]);
	ft_printf("L%ld-%s ", a->ant, name);
}

int			is_good_way(t_lemin *l, t_ants *a, int y)
{

	l = NULL;
	a = NULL;
	y = 0;

	return (1);
}

void			move_from_start(t_lemin *l, t_ants *a)
{
	int		y = 0;
	int				ways;
	
	ways = 0;
	while (l->paths[ways])
			ways++;
	while (a->next && a->y != -1)
			a = a->next;
	while (y < ways && a)
	{
		if (is_good_way(l, a, y))
		{
			a->y = y;
			a->x++;
			print_move(l, a);
			l->start->ant--;
			a = a->next;
		}
		y++;
//		y = l->paths[y + 1] ? ++y : 0;
	}

}

void		ants_gogogo(t_lemin *l)
{
	t_ants		*a;
	
	a = make_ants_list(l);
//		print_ants(a);			//
	while (l->end->ant < l->ants)
	{
		move_from_start(l, a);
		l->end->ant++;
	}

		print_ants(a);			//
}


