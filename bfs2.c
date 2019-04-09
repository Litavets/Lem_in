/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:06:08 by dstepane          #+#    #+#             */
/*   Updated: 2019/04/09 17:06:09 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			create_q(t_lemin *l)
{
	size_t		i;

	if (!(l->q = (t_room **)malloc(sizeof(t_room *) * l->nrooms + 1)))
		return ;
	i = 0;
	while (i < l->nrooms + 1)
		l->q[i++] = NULL;
}

void			create_paths_arr(t_lemin *l)
{
	size_t		y;
	size_t		x;
	size_t		ways;

	ways = (l->start->count <= l->end->count) ? l->start->count : l->end->count;
	if (!ways)
		error("ERROR: Start/end room has no links.");
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
