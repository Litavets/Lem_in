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

int				is_in_q(t_room **q, t_room *r)
{
	int		i;

	i = 0;
	while (q[i])
		if (q[i++]->num == r->num)
			return (1);
	return (0);
}

void			save_path(t_lemin *l)
{
	t_room		*cur;
	size_t		y;
	size_t		x;

	cur = l->end;
	x = 0;
	while (cur)
	{
		x++;
		cur = cur->from;
	}
	cur = l->end;
	y = 0;
	while (l->paths[y + 1] && l->paths[y][0] != -1)
		y++;
	while (cur)
	{
		l->paths[y][x--] = cur->num;
		l->paths[y][0]++;
		cur->fire = -1;
		cur = cur->from;
	}
}

void			reset_bfs(t_lemin *l)
{
	size_t		i;
	t_room		*cur;

	i = 0;
	while (i < l->nrooms)
		l->q[i++] = NULL;
	cur = l->rooms;
	while (cur)
	{
		if (cur->fire != -1)
			cur->fire = 0;
		cur = cur->next;
	}
	l->start->fire = 0;
	l->end->fire = 0;
}

static void		bfs2(t_lemin *l, size_t j)
{
	static int	toggle = 0;

	if (l->q[j] && l->q[j]->flag == end)
	{
		save_path(l);
//			print_paths_nums(l);	////
		if (l->paths[0][2] == l->end->num && !toggle)
		{
			delete_1step_way(l);
			toggle = 1;
		}
		reset_bfs(l);
		bfs(l);
	}
	else if (!*l->paths || l->paths[0][1] == -1)
		error("ERROR: There's no path from start to end.");
	else
		return ;
}

void			bfs(t_lemin *l)
{
	size_t		i;
	size_t		j;
	t_adjlist	*adj;

	i = 0;
	j = 0;
	l->q[0] = l->start;
	while (l->q[j])
	{
		adj = l->q[j]->adj;
		while (adj)
		{
			if (!adj->link->fire && !is_in_q(l->q, adj->link))
			{
				l->q[++i] = adj->link;
				l->q[i]->from = l->q[j];
			}
			adj = adj->next;
		}
		l->q[j]->fire = 1;
		if (l->q[j]->flag == end)
			break ;
		j++;
	}
	bfs2(l, j);
}
