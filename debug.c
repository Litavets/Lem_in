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
//		printf("{%s|%d]-", adj->dest, adj->dst);
		printf("{%s|%d]-", adj->link->name, adj->link->num);
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
		printf("name: {%s}\n", cur->name);
		printf("num : [%d]\n", cur->num);
		printf(">> x:%d y:%d\n", cur->x, cur->y);
		printf(">> flag: %d\n", cur->flag);
		printf(">> ant: %d\n", cur->ant);
		printf(">> fire: %d\n", cur->fire);
		printf(">> count: %d\n", cur->count);
		if (cur->from)
			printf(">> from: %s\n", cur->from->name);
		print_adjlist(cur->adj);
		cur = cur->next;
	}
}

void		print_struct_lemin(t_lemin *l)
{
	printf("\n☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎\n");
	printf(">> l->ants: %zd\n", l->ants);
	printf(">> l->nrooms: %zd\n", l->nrooms);
	if (l->start->name)
		printf(">> l->start: {%s|%d]\n", l->start->name, l->start->num);
	if (l->end->name)
		printf(">> l->end: {%s|%d]\n", l->end->name, l->end->num);
}