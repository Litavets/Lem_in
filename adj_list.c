/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:59:14 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/23 17:59:19 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int			get_room_num(t_lemin *l, char *dest)
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

static void		add_to_adjlist(t_lemin *l, t_room *cur, char *dest)
{
	t_adjlist	*adj;
	t_adjlist	*newadj;

	newadj = (t_adjlist *)malloc(sizeof(t_adjlist));
	adj = cur->adj;
	newadj->next = NULL;
	newadj->dest = ft_strdup(dest);
//		printf(">> adj->dest: %s\n", newadj->dest); //
	newadj->dst = get_room_num(l, newadj->dest);
//		printf(">> adj->dst: %d\n", newadj->dst);
	newadj->link = NULL;
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
	char				**split;
	t_room				*cur;
	static uintmax_t	links;

//		printf("We're adding link, yo! %s\n", line);  //
	split = ft_strsplit(line, '-');
	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(cur->name, split[0]))
			add_to_adjlist(l, cur, split[1]);
		else if (!ft_strcmp(cur->name, split[1]))
			add_to_adjlist(l, cur, split[0]);
		cur = cur->next;
	}
	del_arr(split);
	links = 0;
	links++;
	l->links_num = links;
}

int			validate_link(t_lemin *l, char *line)
{
	char		**split;
	t_room		*cur;
	int			rooms_found[2];
	
	if (!ft_strchr(line, '-') || ft_strchr(line, ' ') || ft_strchr(line, '	'))
		return (0);
	split = ft_strsplit(line, '-');
	if (split[2] != NULL)
	{
		del_arr(split);
		return (0);
	}
	cur = l->rooms;
	rooms_found[0] = 0;
	rooms_found[1] = 0;
	while (cur)
	{
		if (!ft_strcmp(split[0], cur->name))
			rooms_found[0] = 1;
		if (!ft_strcmp(split[1], cur->name))
			rooms_found[1] = 1;
		cur = cur->next;
	}
	del_arr(split);
	if (rooms_found[0] == 0 || rooms_found[1] == 0)
		error("ERROR: link to a non-existent room.");
	return (1);
}
