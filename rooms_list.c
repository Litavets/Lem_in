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

#include "lem_in.h"

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

static char		*get_room_name(char *line)
{
	char	*ptr;
	char	*name;

	ptr = ft_strchr(line, ' ');
	name = ft_strsub(line, 0, ptr - line);
	return(name);
}

static void		get_room_coord(t_room *new, char *line)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	new->x = ft_atoi(split[1]);
	new->y = ft_atoi(split[2]);
	del_arr(split);
}

static t_room		*newroom(t_lemin *l, char *line, int flag)
{
	t_room		*new;
	static int	num = 0;

	new = (t_room *)malloc(sizeof(t_room));
	new->name = get_room_name(line);
//		printf(">> new->name: %s\n", new->name);
	new->num = num++;
	get_room_coord(new, line);
//		printf(">> new->x: %d y: %d\n", new->xy[0], new->xy[1]);
		new->flag = flag;
//		printf(">> new->flag: %d\n", new->flag);
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
	return(new);
}

void		addroom(t_lemin *l, char *line, int flag)
{
	t_room		*room;
	
//		printf("We're adding room[%d]: %s\n", flag, line);  //
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

int			validate_room(char *line)
{
	int		i;
	int		j;

	if (line[0] == 'L')
		error("Invalid room name.");
	i = 0;
	while(line[i] && line[i] != ' ')
		i++;
	if (i == 0 || line[i] == '\0')
		return (0);
	j = i;
	while (ft_isdigit(line[++i]))
		;
	if (i == j + 1 || line[i] != ' ')
		return (0);
	j = i;
	while (ft_isdigit(line[++i]))
		;
	if (i == j + 1 || line[i] != '\0')
		return (0);
	return (1);
}
