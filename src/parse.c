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

#include "../inc/lem_in.h"

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
		if (!ft_isdigit(line[i]))
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
	if (ants > 100000000 && !l->options[5])
	{
		ft_printf("{red}{b}ERROR: Life's too short for so many ants.\n");
		ft_printf("[100mln max. You can extend the limit with -a option.{0}");
		error("\nBut DON'T! Your mom wouldn't like it!]");
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
