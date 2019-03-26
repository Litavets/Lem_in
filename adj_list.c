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

#include "lem_in.h"

static int			get_room_num(t_lemin *l, char *dest)
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
	adj = cur->adj;
	newadj->next = NULL;
	newadj->dest = ft_strdup(dest);
//		printf(">> adj->dest: %s\n", newadj->dest); //
	newadj->dst = get_room_num(l, newadj->dest);
//		printf(">> adj->dst: %d\n", newadj->dst);
	newadj->link = NULL;
	if (cur->adj == NULL)
		cur->adj = newadj;
	else
	{
		while (adj->next)
			adj = adj->next;
		adj->next = newadj;
	}

}

void		addlink(t_lemin *l, char *line)
{
	char		**split;
	t_room		*cur;

//		printf("We're adding link, yo! %s\n", line);  //
	split = ft_strsplit(line, '-');
	cur = l->rooms;
	while (cur)
	{
		if (!ft_strcmp(cur->name, split[0]))
		{
			add_to_adjlist(l, cur, split[1]);
			break ;
		}
		cur = cur->next;
	}
	del_arr(split);
}

int			validate_link(char *line)
{
	char	**split;

	if (!ft_strchr(line, '-') || ft_strchr(line, ' ') || ft_strchr(line, '	'))
		return (0);
	split = ft_strsplit(line, '-');
	if (split[2] != NULL)
		return (0);
	del_arr(split);
	return (1);
}
