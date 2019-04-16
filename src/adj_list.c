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

#include "../inc/lem_in.h"

static int		duplicate_links(t_lemin *l, int link, int newlink)
{
	if (link == newlink)
	{
		if (!l->options[2])
			error("ERROR: Duplicate links.\n[Allow with -d option]");
		else
			return (1);
	}
	return (0);
}

static int		get_room_num(t_lemin *l, char *dest)
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
	newadj->next = NULL;
	newadj->dest = ft_strdup(dest);
	newadj->dst = get_room_num(l, newadj->dest);
	newadj->link = NULL;
	adj = cur->adj;
	if (cur->adj == NULL)
		cur->adj = newadj;
	else
	{
		if (duplicate_links(l, adj->dst, newadj->dst))
			return ;
		while (adj->next)
		{
			if (duplicate_links(l, adj->dst, newadj->dst))
				return ;
			adj = adj->next;
		}
		adj->next = newadj;
	}
}

void			addlink(t_lemin *l, char *line)
{
	char				**split;
	t_room				*cur;

	if (!l->ants || !l->rooms)
		error("ERROR. Right order: 1)ants 2)rooms 3)links.");
	split = ft_strsplit(line, '-');
	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(cur->name, split[0]))
			add_to_adjlist(l, cur, split[1]);
		if (ft_strcmp(split[0], split[1]) && !ft_strcmp(cur->name, split[1]))
			add_to_adjlist(l, cur, split[0]);
		cur = cur->next;
	}
	del_arr(split);
	if (!l->links_flag)
		l->links_flag++;
}
