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

#include "../inc/lem_in.h"

static	t_lemin		*init_lemin(void)
{
	t_lemin		*l;

	if (!(l = (t_lemin *)malloc(sizeof(t_lemin))))
		return (NULL);
	ft_bzero(l->options, 5);
	l->ants = 0;
	l->nrooms = 0;
	l->rooms = NULL;
	l->start = NULL;
	l->end = NULL;
	l->q = NULL;
	l->paths = NULL;
	l->move_count = 0;
	return (l);
}

static void			solve(t_lemin *l)
{
	link_adjlist(l);
	create_paths_arr(l);
	create_q(l);
	bfs(l);
	if (!l->options[0])
		print_paths(l);
	ants_gogogo(l);
	clean_rooms(l);
	clean_lemin_struct(l);
}

static void			more_errors(t_lemin *l, int ret)
{
	if (ret < 0)
		error("ERROR: Can't read the file.");
	count_rooms(l);
	if (l->nrooms == 0)
		error("ERROR: Make some rooms for those lovely little ants!");
	if (!l->start || !l->end)
		error("ERROR: No start or end room.");
	if (!l->ants)
		error("ERROR: No ants - no fun!");
	if (l->links_num == 0)
		error("ERROR: Are you kidding? No links, dude.");
}

void				options(t_lemin *l, int ac, char *av[])
{
	int			i;

	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-p"))
			l->options[0] = 'p';
		else if (!ft_strcmp(av[i], "-c"))
			l->options[1] = 'c';
		else if (!ft_strcmp(av[i], "-d"))
			l->options[2] = 'd';
		else if (!ft_strcmp(av[i], "-s"))
			l->options[3] = 's';
		else if (!ft_strcmp(av[i], "-n"))
			l->options[4] = 'n';
		else
		{
			ft_printf("{I}OPTIONS:{0}\n-p	hide discovered paths\n");
			ft_printf("-c	hide moves count\n-d	allow duplicate links\n");
			ft_printf("-s	allow self-links\n");
			ft_printf("-n	allow negative coordinates\n");
			error("ERROR: invalid option.");
		}
		i++;
	}
}

//int					main(void)
int					main(int ac, char *av[])
{
		FILE 	*fp = freopen("./test", "r", stdin);  //
	char		*line;
	t_lemin		*l;
	int			ret;

	l = init_lemin();
	if (ac > 1)
		options(l, ac, av);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (validate_ants(l, line))
			l->ants = parse_ants(l, line);
		else if (line && line[0] == '#')
			parse_comment(l, &line);
		else if (validate_room(l, line))
			addroom(l, line, 0);
		else if (validate_link(l, line))
			addlink(l, line);
		else if (*line || (!*line && ret > 0))
			error("ERROR: Invalid input.");
		ft_putendl(line);
		ft_strdel(&line);
	}
	more_errors(l, ret);
	solve(l);
		fclose(fp);  //
		printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
		system("leaks -q lem-in");
	return (0);
}
