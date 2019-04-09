/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:23:48 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/31 16:23:49 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		print_border(int i)
{
	if (i == 1)
		write(1, "\n", 1);
	ft_printf("{blue}{u}[# # # # # # # # # # # # # # # # # # # # ");
	ft_printf("{0}{blue}>>{-}\n");
}

static void		print_paths2(t_lemin *l, t_room *cur)
{
	if (cur->num == l->start->num)
		ft_printf("{b}{green}[%d/%s}-->{-}{0}", cur->num, cur->name);
	else if (cur->num == l->end->num)
		ft_printf("{b}{magenta}[%d/%s}{-}{0}", cur->num, cur->name);
	else
		ft_printf("{yellow}[%d/%s}-->{-}", cur->num, cur->name);
}

void			print_paths(t_lemin *l)
{
	size_t		y;
	size_t		x;
	t_room		*cur;

	y = 0;
	x = 1;
	print_border(1);
	while (l->paths[y] && l->paths[y][1] != -1)
	{
		ft_printf("{b}{I}{cyan}(%lu)>>{0}{-} ", y + 1);
		while (l->paths[y][x] != -1)
		{
			cur = l->rooms;
			while (cur)
			{
				(cur->num == l->paths[y][x]) ? print_paths2(l, cur) : 0;
				cur = cur->next;
			}
			x++;
		}
		x = 1;
		y++;
		ft_putchar('\n');
	}
	print_border(0);
}
