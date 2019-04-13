/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:59:14 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/23 17:59:19 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int		get_room_num(t_lemin *l, char *dest)
{
	t_room		*cur;

	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(dest, cur->name))
			return (cur->num);
		cur = cur->next;
	}
	return (-1);
}

static void		add_to_adjlist(t_lemin *l, t_room *cur, char *dest)
{
	t_adjlist	*adj;
	t_adjlist	*newadj;

	newadj = (t_adjlist *)malloc(sizeof(t_adjlist));
	newadj->next = NULL;
	newadj->dest = ft_strdup(dest);
	newadj->dst = get_room_num(l, newadj->dest);
	newadj->link = NULL;
	adj = cur->adj;
	if (cur->adj == NULL)
		cur->adj = newadj;
	else
	{
		if ((adj->dst == newadj->dst) && !l->options[2])
			error("ERROR: Duplicate links.\n[Allow with -d option]");
		while (adj->next)
		{
			if ((adj->dst == newadj->dst) && !l->options[2])
				error("ERROR: Duplicate links.\n[Allow with -d option]");
			adj = adj->next;
		}
		adj->next = newadj;
	}
}

void			addlink(t_lemin *l, char *line)
{
	char				**split;
	t_room				*cur;

	if (!l->ants || !l->rooms)
		error("ERROR. Right order: 1)ants 2)rooms 3)links.");
	split = ft_strsplit(line, '-');
	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(cur->name, split[0]))
			add_to_adjlist(l, cur, split[1]);
		if (ft_strcmp(split[0], split[1]) && !ft_strcmp(cur->name, split[1]))
			add_to_adjlist(l, cur, split[0]);
		cur = cur->next;
	}
	del_arr(split);
	if (!l->links_flag)
		l->links_flag++;
}

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
