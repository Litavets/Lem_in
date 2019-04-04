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

static void		remove_adj_node(t_lemin *l, t_adjlist **adj, int f)
{
	t_adjlist	*tmp;
	t_adjlist	*nxt;

	tmp = *adj;
	if (f)
	{
		*adj = (*adj)->next;
		ft_strdel(&tmp->dest);
		ft_bzero((void *)tmp, sizeof(tmp));
		free(tmp);
		(f == 1) ? (l->start->adj = *adj) : (l->end->adj = *adj);
	}
	else
	{
		nxt = tmp->next->next;
		ft_strdel(&tmp->next->dest);
		ft_bzero((void *)tmp->next, sizeof(tmp->next));
		free(tmp->next);
		(*adj)->next = nxt;
	}
}

void			delete_1step_way(t_lemin *l)
{
	t_adjlist	*adj;

	adj = l->start->adj;
	if (adj->dst == l->end->num)
		remove_adj_node(l, &adj, 1);
	else
	{
		while (adj && adj->next)
		{
			if (adj->next->dst == l->end->num)
			{
				remove_adj_node(l, &adj, 0);
				break ;
			}
			adj = adj->next;
		}
	}
	adj = l->end->adj;
	if (adj->dst == l->start->num)
		remove_adj_node(l, &adj, 2);
	else
	{
		while (adj && adj->next)
		{
			if (adj->next->dst == l->start->num)
			{
				remove_adj_node(l, &adj, 0);
				break ;
			}
			adj = adj->next;
		}
	}
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
		if (adj->dst == newadj->dst)
				error("ERROR: Duplicate links.");
		while (adj->next)
		{
			if (adj->dst == newadj->dst)
				error("ERROR: Duplicate links.");
			adj = adj->next;
		}
		adj->next = newadj;
	}
}

void			addlink(t_lemin *l, char *line)
{
	char				**split;
	t_room				*cur;
	static uintmax_t	links;

	split = ft_strsplit(line, '-');
	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(cur->name, split[0]))
			add_to_adjlist(l, cur, split[1]);
		if (!ft_strcmp(cur->name, split[1]))
			add_to_adjlist(l, cur, split[0]);
		cur = cur->next;
	}
	del_arr(split);
	links = 0;
	links++;
	l->links_num = links;
}

int				validate_link(t_lemin *l, char *line)
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
		(!ft_strcmp(split[0], cur->name)) ? (rooms_found[0] = 1) : 0;
		(!ft_strcmp(split[1], cur->name)) ? (rooms_found[1] = 1) : 0;
		cur = cur->next;
	}
	if (!ft_strcmp(split[0], split[1]))
	{
		del_arr(split);
		error("ERROR: Don't link rooms with themselves, you pervert!");
	}
	del_arr(split);
	if (rooms_found[0] == 0 || rooms_found[1] == 0)
		error("ERROR: link to a non-existent room.");
	return (1);
}
