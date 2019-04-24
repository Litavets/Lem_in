/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 16:25:57 by dstepane          #+#    #+#             */
/*   Updated: 2019/04/09 16:25:59 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			error(char *str)
{
	ft_printf("{red}{b}%s{0}\n", str);
	exit(0);
}

static void		check_duplicates(t_lemin *l, char *line)
{
	t_room		*r;
	char		**split;
	int			x;
	int			y;

	split = ft_strsplit(line, ' ');
	r = l->rooms;
	x = ft_atoi(split[1]);
	y = ft_atoi(split[2]);
	while (r)
	{
		if (!ft_strcmp(split[0], r->name))
			error("ERROR: Rooms with the same name.");
		if (r->x == x && r->y == y)
			error("ERROR: Rooms with the same coordinates.");
		r = r->next;
	}
	del_arr(split);
}

static int		validate_room2(t_lemin *l, char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
	{
		if (!l->options[4])
			error("ERROR: Negative coordinates.\n[Option -n to allow]");
		i++;
		if (!str[i])
			return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

static int		count_spaces(char *line)
{
	int			i;
	int			sp;

	i = 0;
	sp = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			sp++;
		i++;
	}
	if (sp != 2)
		return (0);
	return (1);
}

int				validate_room(t_lemin *l, char *line)
{
	char		**split;

	if (!l->ants)
		return (0);
	if (line[0] == 'L')
		error("Invalid room name.");
	if (!count_spaces(line))
		return (0);
	split = ft_strsplit(line, ' ');
	if (!split[0] || !split[1] || !split[2] || split[3]
		|| ft_strchr(split[0], '-'))
	{
		del_arr(split);
		return (0);
	}
	if (!validate_room2(l, split[1]) || !validate_room2(l, split[2]))
	{
		del_arr(split);
		return (0);
	}
	del_arr(split);
	check_duplicates(l, line);
	return (1);
}
