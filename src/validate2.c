/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:54:28 by dstepane          #+#    #+#             */
/*   Updated: 2019/04/16 18:54:30 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static void		validate_link2(t_lemin *l, char *split0, char *split1)
{
	t_room		*cur;
	int			rooms_found[2];

	cur = l->rooms;
	rooms_found[0] = 0;
	rooms_found[1] = 0;
	while (cur)
	{
		(!ft_strcmp(split0, cur->name)) ? (rooms_found[0] = 1) : 0;
		(!ft_strcmp(split1, cur->name)) ? (rooms_found[1] = 1) : 0;
		cur = cur->next;
	}
	if (rooms_found[0] == 0 || rooms_found[1] == 0)
		error("ERROR: link to a non-existent room.");
}

int				validate_link(t_lemin *l, char *line)
{
	char		**split;

	if (!l->ants || !l->rooms)
		return (0);
	if (!ft_strchr(line, '-') || ft_strchr(line, ' ') || ft_strchr(line, '	'))
		return (0);
	split = ft_strsplit(line, '-');
	if (split[2] != NULL)
	{
		del_arr(split);
		return (0);
	}
	validate_link2(l, split[0], split[1]);
	if (!ft_strcmp(split[0], split[1]) && !l->options[3])
	{
		ft_printf("{red}{b}ERROR: Don't link rooms with themselves,");
		ft_printf(" you pervert!{0}\n");
		error("[Allow with -s option]");
	}
	del_arr(split);
	return (1);
}
