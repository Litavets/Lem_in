/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:49:58 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/22 21:49:59 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_adjlist(t_adjlist *adj)
{
	while (adj)
	{
		printf("[%s|%d]-", adj->dest, adj->dst);
		adj = adj->next;
	}
	printf("\n");
}

void		print_rooms_list(t_room *rooms)
{
	t_room *cur;

	cur = rooms;
	while (cur)
	{
		printf("==============================\n");
		printf(">> cur->name: %s\n", cur->name);
		printf(">> cur->num: %d\n", cur->num);
		printf(">> cur->x: %d y: %d\n", cur->x, cur->y);
		printf(">> cur->flag: %d\n", cur->flag);
		printf(">> cur->ant: %d\n", cur->ant);
		print_adjlist(cur->adj);
		cur = cur->next;
	}
}

void		print_struct_lemin(t_lemin *l)
{
	printf("☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎\n");
	printf(">> l->ants: %zd\n", l->ants);
	printf(">> l->nrooms: %zd\n", l->nrooms);
	printf(">> l->doors: start:%d end:%d\n", l->doors[0], l->doors[1]);
}