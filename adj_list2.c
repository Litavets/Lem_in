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

void			create_paths_arr_and_q(t_lemin *l)
{
	size_t		y;
	size_t		x;
	size_t		ways;

	if (!(l->q = (t_room **)malloc(sizeof(t_room *) * l->nrooms + 1)))
		return ;
	y = 0;
	while (y < l->nrooms + 1)
		l->q[y++] = NULL;
	ways = (l->start->count <= l->end->count) ? l->start->count : l->end->count;
	if (!(l->paths = (int **)malloc(sizeof(int *) * ways + 1)))
		return ;
	y = 0;
	while (y < ways)
	{
		l->paths[y] = (int *)malloc(sizeof(int *) * l->nrooms + 2);
		while (x < l->nrooms + 2)
		{
			l->paths[y][x] = -1;
			x++;
		}
		x = 0;
		y++;
	}
	l->paths[y] = NULL;
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
