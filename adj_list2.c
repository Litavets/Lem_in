/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:41:56 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/31 15:41:58 by dstepane         ###   ########.fr       */
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
		(f == 1) ? (l->start->adj = *adj) :
			(l->end->adj = *adj);
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

static void		delete_1step_way2(t_lemin *l)
{
	t_adjlist	*adj;

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
	delete_1step_way2(l);
}

static t_room	*get_link(t_lemin *l, int rnum)
{
	t_room		*cur;

	cur = l->rooms;
	while (cur)
	{
		if (cur->num == rnum)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

void			link_adjlist(t_lemin *l)
{
	t_room		*cur;
	t_adjlist	*adj;

	cur = l->rooms;
	while (cur)
	{
		adj = cur->adj;
		while (adj)
		{
			adj->link = get_link(l, adj->dst);
			cur->count++;
			adj = adj->next;
		}
		cur = cur->next;
	}
}
