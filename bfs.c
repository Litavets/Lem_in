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

void		create_paths_arr_and_q(t_lemin *l)
{
	size_t		y;
	size_t		x;
	size_t		ways;

		if (!(l->q = (t_room **)malloc(sizeof(t_room *) * l->nrooms + 1)))		//NEED TO FREE!!!
			return ;
		y = 0;
		while (y < l->nrooms + 1)
			l->q[y++] = NULL;
	ways = (l->start->count >= l->end->count) ? l->start->count : l->end->count;
	if (!(l->paths = (int **)malloc(sizeof(int *) * ways + 1)))  // FREEEEEEE
		return ; 			
	y = 0;
	while (y < ways)
	{
		l->paths[y] = (int *)malloc(sizeof(int *) * l->nrooms + 2);  // FREEEEEEE
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

void		save_path(t_lemin *l)
{
	t_room		*cur;
	size_t		y;
	size_t		x;

	cur = l->end;
	x = 0;
//		printf("\n\n±±±±±±±±±±±\n");  //
	while (cur)
	{
//				printf("///{%s|%d]", cur->name, cur->num); //
		x++;
		cur = cur->from;
	}
//		printf("\n±±±±±±±±±±±\n");  //
	cur = l->end;
	y = 0;
	while (l->paths[y] && l->paths[y][0] != -1)
		y++;
	while (cur)
	{
		l->paths[y][x--] = cur->num;
		l->paths[y][0]++;
		cur->fire = -1;
		cur = cur->from;
	}
}

void		reset_bfs(t_lemin *l)
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

void		bfs(t_lemin *l)
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
			break;
		j++;
	}
//		printf("\n_____\nQUEUE: ");
//		for (int z = 0; l->q[z] != NULL; z++)
//			printf("->{%s|%d]", l->q[z]->name, l->q[z]->num);	//
	if (l->q[j] && l->q[j]->flag == end)
	{
			save_path(l);
			reset_bfs(l);
			if (l->nrooms == 2)
				return;
			bfs(l);
	}
	else if (l->paths[0][1] == -1)
		error("ERROR: There's no path from start to end.");
	else 
		return ;
}
