/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 19:03:47 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/21 19:03:48 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "./libft/includes/libft.h"


typedef struct 			s_adjlist
{
	int						dest;
	struct s_adjlist		*next;
}							t_adjlist;

typedef struct 				s_room
{
	char					*name;
	int						num;
	int						*xy;
	enum {no, start, end}	flag;
	char					ant;
	struct s_adjlist		*adjlist;
	struct s_room			*next;
}							t_room;

/*
**	doors[0] - start; [1] - end;
*/
typedef struct 				s_lemin
{
	size_t					ants;
	size_t					nrooms;
	char					doors[2];
	t_room					*rooms;

}							t_lemin;

void						error(char *str);
void						del_arr(char **arr);

//	DEBUG
void						print_rooms_list(t_room *rooms);

#endif