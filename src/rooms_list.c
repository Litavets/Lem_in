/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:52:25 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/23 17:52:29 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			count_rooms(t_lemin *l)
{
	int			how_many_rooms_we_are_going_to_burn;
	t_room		*cur;

	how_many_rooms_we_are_going_to_burn = 0;
	cur = l->rooms;
	while (cur)
	{
		cur = cur->next;
		how_many_rooms_we_are_going_to_burn++;
	}
	l->nrooms = how_many_rooms_we_are_going_to_burn;
}

static char		*parse_room_name(char *line)
{
	char	*ptr;
	char	*name;

	ptr = ft_strchr(line, ' ');
	name = ft_strsub(line, 0, ptr - line);
	return (name);
}

static void		get_room_coord(t_room *new, char *line)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	new->x = ft_atoi(split[1]);
	new->y = ft_atoi(split[2]);
	del_arr(split);
}

static t_room	*newroom(t_lemin *l, char *line, int flag)
{
	t_room		*new;
	static int	num = 0;

	new = (t_room *)malloc(sizeof(t_room));
	new->name = parse_room_name(line);
	new->num = num++;
	get_room_coord(new, line);
	new->flag = flag;
	new->ant = (flag == 1) ? l->ants : 0;
	if (flag == 1)
		l->start = new;
	else if (flag == 2)
		l->end = new;
	new->adj = NULL;
	new->fire = 0;
	new->count = 0;
	new->from = NULL;
	new->next = NULL;
	return (new);
}

void			addroom(t_lemin *l, char *line, int flag)
{
	t_room		*room;

	if ((flag == 1 && l->start) || (flag == 2 && l->end))
		error("ERROR: Multiple start/end rooms make me sad :(");
	if (l->ants == 0)
		error("ERROR: Nice try. Give me ants first!");
	if (l->rooms == NULL)
		l->rooms = newroom(l, line, flag);
	else
	{
		room = l->rooms;
		while (room->next)
			room = room->next;
		room->next = newroom(l, line, flag);
	}
}
