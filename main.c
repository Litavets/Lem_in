/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 18:59:47 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/21 18:59:48 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			parse_ants(void)
{
	char	*line;
	int		i;
	int		ants;

	ants = 0;
	get_next_line(0, &line);
	i = 0;
	while(line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != '\n')
		{
			ft_strdel(&line);
			error("Invalid ants number.");
		}
		i++;
	}
	ants = ft_atoi(line);
	if (ants <= 0) 
	{
		ft_strdel(&line);
		error("Invalid ants number.");
	}
	ft_putendl(line);
	ft_strdel(&line);
	return ((size_t)ants);	
}

t_lemin		*init_lemin(void)
{
	t_lemin		*l;

	if (!(l = (t_lemin *)malloc(sizeof(t_lemin))))
		return (NULL);
	l->ants = 0;

	return(l);
}

int			main(void)
{
	char		*line;
	t_lemin		*l;

	l = init_lemin();
	l->ants = parse_ants();
	while (get_next_line(0, &line))
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
		printf(">> ants: %zd\n", l->ants);   //
	free(l);
	return (0);
}
