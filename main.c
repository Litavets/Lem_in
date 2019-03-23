/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:59:47 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/21 18:59:48 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parse_ants(void)
{
	char	*line;
	int		i;
	int		ants;

	ants = 0;
	get_next_line(0, &line);
	i = 0;
	while(line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != '\n')
		{
			ft_strdel(&line);
			error("Invalid ants number.");
		}
		i++;
	}
	ants = ft_atoi(line);
	if (ants <= 0) 
	{
		ft_strdel(&line);
		error("Invalid ants number.");
	}
	ft_putendl(line);
	ft_strdel(&line);
	return ((size_t)ants);	
}

void		parse_comment(t_lemin *l, char *line)
{
	if (!ft_strcmp(line, "##start"))
	{
		ft_putendl(line);
		ft_strdel(&line);
		get_next_line(0, &line);
		if (validate_room(line))
		{
			l->doors[0] = 1;
			addroom(l, line, 1);
		}
		else
			error("Invalid room parameters input.");
	}
	else if (!ft_strcmp(line, "##end"))
	{
		ft_putendl(line);
		ft_strdel(&line);
		get_next_line(0, &line);
		if (validate_room(line))
		{
			l->doors[1] = 1;
			addroom(l, line, 2);
		}
		else
			error("Invalid room parameters input.");
	}
}

t_lemin		*init_lemin(void)
{
	t_lemin		*l;

	if (!(l = (t_lemin *)malloc(sizeof(t_lemin))))
		return (NULL);
	l->ants = 0;
	l->nrooms = 0;
	ft_bzero(l->doors, 2);
	l->rooms = NULL;

	return(l);
}

int			main(void)
{
		FILE 	*fp = freopen("./sub1a", "r", stdin);  //
	
	char		*line;
	t_lemin		*l;

	l = init_lemin();
	l->ants = parse_ants();
	while (get_next_line(0, &line) > 0)
	{
		if (line && line[0] == '#')
			parse_comment(l, line);
		else if (validate_room(line))
			addroom(l, line, 0);
		else if (validate_link(line))
			addlink(l, line);
		else if (*line)
			error("Invalid input.");
		ft_putendl(line);
		ft_strdel(&line);
	}
		print_struct_lemin(l); //
		print_rooms_list(l->rooms); //
	clean_rooms(l);
		fclose(fp);  //

//	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
//	system("leaks -q lem-in");
	return (0);
}
