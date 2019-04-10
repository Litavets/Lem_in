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

# include "../libft/includes/libft.h"

typedef struct				s_adjlist
{
	int						dst;
	char					*dest;
	struct s_room			*link;
	struct s_adjlist		*next;
}							t_adjlist;

typedef struct				s_room
{
	char					*name;
	int						num;
	int						x;
	int						y;
	enum {no, start, end}	flag;
	int						ant;
	int						fire;
	int						count;
	struct s_room			*from;
	struct s_adjlist		*adj;
	struct s_room			*next;
}							t_room;

/*
** options[0] -p hide discovered paths
** options[1] -c hide moves count
** options[2] -d allow duplicate links
** options[3] -s allow self-links
** options[4] -n allow negative coordinates
** options[5] -a extend ants limit to max int
*/

typedef struct				s_lemin
{
	char					options[6];
	int						ants;
	uintmax_t				nrooms;
	t_room					*rooms;
	t_room					*start;
	t_room					*end;
	t_room					**q;
	int						**paths;
	uintmax_t				move_count;
	uintmax_t				links_num;
}							t_lemin;

typedef struct				s_ants
{
	int						ant;
	int						y;
	int						x;
	struct s_ants			*next;
}							t_ants;

int							validate_ants(t_lemin *l, char	*line);
int							parse_ants(t_lemin *l, char *line);
void						parse_comment(t_lemin *l, char **line);

int							validate_room(t_lemin *l, char *line);
void						addroom(t_lemin *l, char *line, int flag);
int							validate_link(t_lemin *l, char *line);
void						addlink(t_lemin *l, char *line);

void						count_rooms(t_lemin *l);
void						link_adjlist(t_lemin *l);
void						create_paths_arr(t_lemin *l);
void						create_q(t_lemin *l);

void						bfs(t_lemin *l);
t_ants						*make_ants_list(t_lemin *l);
void						ants_gogogo(t_lemin *l);
char						*get_room_name(t_lemin *l, int num);
void						print_move(t_lemin *l, t_ants *a, char c);
void						print_paths(t_lemin *l);
void						delete_1step_way(t_lemin *l);

void						error(char *str);
void						del_arr(char **arr);
void						clean_rooms(t_lemin *l);
void						clean_lemin_struct(t_lemin *l);
void						kill_all_the_ants(t_ants *a);

#endif
