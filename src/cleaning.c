/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:22:02 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/31 16:22:08 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			del_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		ft_memdel((void **)&arr);
	}
}

void			kill_all_the_ants(t_ants *a)
{
	t_ants		*c;
	t_ants		*n;

	c = a;
	while (c)
	{
		n = c->next;
		free(c);
		c = n;
	}
}

void			clean_lemin_struct(t_lemin *l)
{
	t_room		**cur;
	int			i;

	l->rooms = NULL;
	cur = l->q;
	i = 0;
	free(l->q);
	l->q = NULL;
	i = 0;
	while (l->paths[i])
		free(l->paths[i++]);
	free(l->paths[i]);
	free(l->paths);
}

static void		clean_adjlists(t_adjlist *adj)
{
	t_adjlist	*cura;
	t_adjlist	*nexa;

	cura = adj;
	while (cura != NULL)
	{
		nexa = cura->next;
		ft_strdel(&cura->dest);
		free(cura);
		cura = nexa;
	}
	adj = NULL;
}

void			clean_rooms(t_lemin *l)
{
	t_room	*curr;
	t_room	*nexr;

	curr = l->rooms;
	while (curr != NULL)
	{
		nexr = curr->next;
		ft_strdel(&curr->name);
		clean_adjlists(curr->adj);
		curr->from = NULL;
		free(curr);
		curr = nexr;
	}
	l->rooms = NULL;
	free(l);
}
