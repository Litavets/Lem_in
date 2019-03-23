/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freexit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 20:35:45 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/21 20:35:46 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		error(char *str)
{
	ft_putendl(str);
	exit(0);
}

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

void		clean_rooms(t_lemin *l)
{
	t_room	*curr;
	t_room	*nexr;

	curr = l->rooms;
	while (curr != NULL)
	{
		nexr = curr->next;
		ft_strdel(&curr->name);
		clean_adjlists(curr->adj);
		free(curr);
		curr = nexr;
	}
	l->rooms = NULL;
	free(l);
}