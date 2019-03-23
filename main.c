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

char		*get_room_name(char *line)
{
	char	*ptr;
	char	*name;

	ptr = ft_strchr(line, ' ');
	name = ft_strsub(line, 0, ptr - line);
	return(name);
}

void		get_room_coord(t_room *new, char *line)
{
	int		*xy;
	char	**split;

	xy = (int *)malloc(sizeof(int) * 2);
	split = ft_strsplit(line, ' ');
	new->x = ft_atoi(split[1]);
	new->y = ft_atoi(split[2]);
	del_arr(split);
}

t_room		*newroom(char *line, int flag)
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
	new->ant = 0;
	new->adj = NULL;
	new->next = NULL;
	return(new);
}

void		addroom(t_lemin *l, char *line, int flag)
{
	t_room		*room;
	
//		printf("We're adding room[%d]: %s\n", flag, line);  //
	if (l->rooms == NULL)
		l->rooms = newroom(line, flag);
	else 
	{
		room = l->rooms;
		while (room->next)
			room = room->next;
		room->next = newroom(line, flag);
	}
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

int			get_room_num(t_lemin *l, char *dest)
{
	t_room		*cur;

	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(dest, cur->name))
			return (cur->num);
		cur = cur->next;
	}
	return (-1);
}

void		add_to_adjlist(t_lemin *l, t_room *cur, char *dest)
{
	t_adjlist	*adj;
	t_adjlist	*newadj;

	newadj = (t_adjlist *)malloc(sizeof(t_adjlist));
	adj = cur->adj;
	newadj->next = NULL;
	newadj->dest = ft_strdup(dest);
		printf(">> adj->dest: %s\n", newadj->dest); //
	newadj->dst = get_room_num(l, newadj->dest);
		printf(">> adj->dst: %d\n", newadj->dst);
	if (cur->adj == NULL)
		cur->adj = newadj;
	else
	{
		while (adj->next)
			adj = adj->next;
		adj->next = newadj;
	}

}

void		addlink(t_lemin *l, char *line)
{
	char		**split;
	t_room		*cur;

		printf("We're adding link, yo! %s\n", line);  //
	split = ft_strsplit(line, '-');
	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(cur->name, split[0]))
		{
			add_to_adjlist(l, cur, split[1]);
			break ;
		}
		cur = cur->next;
	}
	del_arr(split);
}

int			validate_link(char *line)
{
	char	**split;

	if (!ft_strchr(line, '-') || ft_strchr(line, ' ') || ft_strchr(line, '	'))
		return (0);
	split = ft_strsplit(line, '-');
	if (split[2] != NULL)
		return (0);
	del_arr(split);
	return (1);
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
	free(l);
		fclose(fp);  //

//	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
//	system("leaks -q lem-in");
	return (0);
}
