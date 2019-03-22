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

void		print_rooms_list(t_room *rooms)
{
	t_room *cur;

	cur = rooms;
	while (cur)
	{
		printf("==============================\n");
		printf(">> cur->name: %s\n", cur->name);
		printf(">> cur->num: %d\n", cur->num);
		printf(">> cur->x: %d y: %d\n", cur->xy[0], cur->xy[1]);
		printf(">> cur->flag: %d\n", cur->flag);
		printf(">> cur->ant: %d\n", cur->ant);
		cur = cur->next;
	}
}
