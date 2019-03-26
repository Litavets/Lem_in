/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:03:33 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/26 16:03:34 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


t_room		*get_link(t_lemin *l, int rnum)
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

void		link_adjlist(t_lemin *l)
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

int			is_in_q(t_room **q, t_room *r)
{
	int		i;

	i = 0;
	while (q[i])
		if (q[i++]->num == r->num)
			return (1);
	return (0);
}

void		bfs(t_lemin *l)
{
	size_t		i;
	size_t		j;
	t_adjlist	*adj;

	if (!(l->q = (t_room **)malloc(sizeof(t_room *) * l->nrooms)))
		return ;
	i = 0;
	while (i < l->nrooms)
		l->q[i++] = NULL;
	i = 0;
	j = 0;
	l->q[0] = l->start;
	while (l->q[j])
	{
		adj = l->q[j]->adj;
		while (adj)
		{
			if (!is_in_q(l->q, adj->link) && !adj->link->fire)
			{
				l->q[++i] = adj->link;
					printf("->{%s|%d]", l->q[i]->name, l->q[i]->num);
			}
			adj = adj->next;
		}

//		for (int j = 0; j < cur->count; j++)
/*		int j = 0;
		while (l->q[j])
		{
			printf(">>>>cur{%s|%d] = {%s|%d]\n", cur->name, cur->num, l->q[j]->name, l->q[j]->num);
			j++;
		}
*/
		l->q[j]->fire = 1;
		l->q[j] = NULL;
		j++;
	}
/*
		int j = 0;
		while (l->q[j])
		{
			printf("->{%s|%d]", l->q[j]->name, l->q[j]->num);
			j++;
		}
*/
}
