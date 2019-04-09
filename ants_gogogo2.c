/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_gogogo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:56:07 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/31 15:56:09 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	char c == [S - start, F - Finsih, 1 - finish in 1 step, M - Midway]
*/

void				print_move(t_lemin *l, t_ants *a, char c)
{
	char	*name;

	name = get_room_name(l, l->paths[a->y][a->x]);
	if (c == 'S')
		ft_printf("{green}{b}L%ld{yellow}-%s{0}{-} ", a->ant, name);
	else if (c == 'F')
		ft_printf("{yellow}{b}L%ld{magenta}-%s{0}{-} ", a->ant, name);
	else if (c == '1')
		ft_printf("{green}{b}L%ld{magenta}-%s{0}{-} ", a->ant, name);
	else
		ft_printf("{yellow}L%ld{yellow}-%s{-} ", a->ant, name);
}

static t_ants		*new_ant(void)
{
	t_ants				*new;
	static int			num = 0;

	new = (t_ants *)malloc(sizeof(t_ants));
	new->ant = ++num;
	new->y = -1;
	new->x = 1;
	new->next = NULL;
	return (new);
}

t_ants				*make_ants_list(t_lemin *l)
{
	t_ants		*ants;
	t_ants		*cur;
	int			num;

	ants = new_ant();
	cur = ants;
	num = 1;
	while (num < l->ants)
	{
		cur->next = new_ant();
		cur = cur->next;
		num++;
	}
	return (ants);
}

char				*get_room_name(t_lemin *l, int num)
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
