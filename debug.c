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

//	DEBUG
void						print_rooms_list(t_room *rooms);
void						print_struct_lemin(t_lemin *l);
void						print_paths_nums(t_lemin *l);
void						print_ants(t_ants	*a);

void		print_ants(t_ants	*a)
{
	t_ants		*cur;

	printf("\n:::::::::::::::::::::::::::::::::\n");
	cur = a;
	while (cur)
	{
		printf("(%d) ", cur->ant);
		printf("y:%d x:%d", cur->y, cur->x);
		printf("\n");
		cur = cur->next;
	}
	printf("\n:::::::::::::::::::::::::::::::::\n");
}

void		print_paths_nums(t_lemin *l)
{
	size_t		y = 0, x = 0;

	printf("\n.................................................\n");
	while (l->paths[y])
	{
		while (x < l->nrooms + 1)
		{
			printf(" % d|", l->paths[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

void		print_adjlist(t_adjlist *adj)
{
	while (adj)
	{
//		printf("{%s|%d]-", adj->dest, adj->dst);
		printf("[%d|%s}-", adj->link->num, adj->link->name);
		adj = adj->next;
	}
	printf("\n");
}

void		print_rooms_list(t_room *rooms)
{
	t_room		*cur;

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
	printf("\n\n☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎☀︎\n");
	printf(">> l->ants: %zd\n", l->ants);
	printf(">> l->nrooms: %zd\n", l->nrooms);
	if (l->start->name)
		printf(">> l->start: {%s|%d]\n", l->start->name, l->start->num);
	if (l->end->name)
		printf(">> l->end: {%s|%d]\n", l->end->name, l->end->num);
}