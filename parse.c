/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:35:08 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/31 14:35:10 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int				validate_room(t_lemin *l, char *line)
{
	int		i;
	int		j;

	if (line[0] == 'L')
		error("Invalid room name.");
	i = 0;
	while (line[i] && line[i] != ' ')
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
	check_duplicates(l, line);
	return (1);
}

int				validate_ants(t_lemin *l, char *line)
{
	int		i;

	i = 0;
	if (ft_isdigit(line[0]) && !ft_strchr(line, ' ') && !ft_strchr(line, '-')
		&& l->rooms == NULL)
	{
		while (ft_isdigit(line[i]))
			i++;
		if (line[i] == '\0')
			return (1);
	}
	return (0);
}

int				parse_ants(t_lemin *l, char *line)
{
	int			i;
	intmax_t	ants;

	ants = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != '\n')
		{
			ft_strdel(&line);
			error("ERROR: Invalid ants number.");
		}
		i++;
	}
	ants = ft_atoi(line);
	if (ants <= 0 || ants > INT_MAX)
	{
		ft_strdel(&line);
		error("ERROR: Invalid ants number.");
	}
	if (l->ants != 0)
		error("ERROR: Multiple ants input. Shame on you!");
	return ((size_t)ants);
}

void			parse_comment(t_lemin *l, char **line)
{
	int		flag;
	
	flag = 0;
	if (!ft_strcmp(*line, "##start"))
		flag = 1;
	else if (!ft_strcmp(*line, "##end"))
		flag = 2;
	if (flag)
	{
		while (*line[0] == '#')
		{
			ft_putendl(*line);
			ft_strdel(*&line);
			get_next_line(0, *&line);
			((!ft_strcmp(*line, "##start")) || (!ft_strcmp(*line, "##end")))
				? error("ERROR: Start/end flags are messed up!") : 0;
		}
		(validate_room(l, *line)) ? addroom(l, *line, flag) :
			error("ERROR: Invalid room input. Ants hate this!");
	}
}
