/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:07:19 by cjoaquin          #+#    #+#             */
/*   Updated: 2020/11/14 16:07:41 by cjoaquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <time.h>

# define START_POINT 1
# define END_POINT 2
# define CLOSE 1
# define INF 1000000

typedef struct		s_line
{
	char			*p_first;
	char			*p_next;
	int				num_first;
	int				num_next;
	struct s_line	*next;
}					t_line;

typedef struct		s_point
{
	int				num;
	int				snum;
	int				p;
	int				ant_num;
	char			*name;
	int				x;
	int				y;
	int				in_path;
	int				cost;
	struct s_point	*prev_room_path;
	struct s_point	*next;
}					t_point;

typedef struct		s_sline
{
	int				weight;
	int				close;
	t_point			*tmp_in;
	t_point			*in;
	t_point			*out;
	struct s_sline	*next;
}					t_sline;

typedef struct		s_loc
{
	int				i;
	char			*name;
	struct s_loc	*next;
}					t_loc;

typedef struct		s_data
{
	int				num_ants;
	int				num_of_edges;
	int				max_paths;
	int				ants_end;
	int				ants_count;
	t_point			*points;
	t_line			*lines;
	t_sline			*slines;
	t_sline			*last_slines;
	t_point			*last_points;
	t_line			*last_lines;
	t_point			*start;
	t_point			*end;
	t_loc			*location;
}					t_data;

typedef struct		s_path
{
	int				num_steps_in_paths;
	int				len;
	t_point			*points;
	struct s_path	*prev;
	struct s_path	*next;
}					t_path;

int					main(void);

/*
** read & check
*/

void				parsing_line(char *str, t_data *map, int mod_command);
int					ft_atoi_check(const char *str);
void				check_st_end(t_data *map, int mod_command);
void				check_line(t_data *map);
void				check_duplicate(t_data *map, char *name);
int					add_point(char **str, t_data *map, int mod_command);
void				copy_points2(t_data *map);
int					ft_find_counts(const char *s, int c);
t_data				*int_map(void);
t_data				*read_map(int fd);
void				free_str(char **str, int num);

/*
** slines
*/

t_point				*get_point(t_data *map, int num, int p);
t_sline				*set_slines(t_data *map);
t_sline				*new_sline(t_point *p1, t_point *p2, int weight);
void				line_swap(t_line *line);
t_sline				*add_sline(t_data *map, t_point *p1,
					t_point *p2, int weight);

/*
** algorithm
*/

t_path				**ft_alg(t_data *map);
int					ft_bellman_ford(t_data *map);
t_path				**ft_init_paths(t_data *map);
void				ft_init_slines(t_sline *slines);
void				ft_init_points(t_data *map);
void				ft_num_of_max_paths(t_data *map);
int					ft_change_edge(t_sline *slines);
t_path				*ft_create_path(t_data *map);
void				ft_copy_in_best_paths(t_path **paths, t_path **best_paths);
void				ft_free_path(t_path **path);
void				ft_free_all_paths(t_path **paths);
void				ft_free_all_in_alg(t_path **paths, t_sline *slines);

/*
** ants
*/

int					ft_let_go_ants(t_path **paths, t_data *map);
void				cut_path(t_path **paths, t_data *map);
void				set_len_paths(t_path **paths, t_data *map);
int					get_num_path(t_path **paths);
void				add_loc(t_data *map, char *name, int num_ant);
void				del_location(t_data *map);
int					iter_count(t_path **paths, t_data *map);
int					add_ant(t_path *path, t_data *map, int ants);
int					*set_ant_in_path(t_path **paths, t_data *map);
void				ft_move_by_path(t_path **paths, t_data *map, int *ants);

/*
** debug
*/

void				print_sline(t_data *map);
void				print_paths(t_path **paths);
void				ft_check_repeat_rooms(t_path **paths);

int					put_err(char *str);
void				free_point(t_point	*point);
void				free_line(t_line	*line);

#endif
