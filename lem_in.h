#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>
# define START 1
# define END 2

typedef struct		s_line
{
	int				weight;
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
	int 			y;
	int				st_end;
	int 			in_path;
	int 			bfs_level;
	struct s_point **arr_lines;
	int				*check;
	int				close;
	int 			cost;
	struct s_point	*prev_room_path;
	struct s_point	*prev_room_path2;
	struct s_point	*next;
}					t_point;

typedef struct		s_sline
{
	int				weight;
	int 			close;
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
	int				ants_end;
	int				ants_count;
	t_point			*points;
	t_line			*lines;
	t_sline			*slines;
	t_point			*last_points;
	t_line			*last_lines;
	t_point			*start;
	t_point			*end;
	t_loc			*location;
}					t_data;

typedef struct		s_path
{
	int len;
	t_point			*points;
	t_point			*last_points;
	struct s_path	*prev;
	struct s_path	*next;
}					t_path;

//typedef struct		s_arr
//{
//	int size;
//	int used;
//	void			**arr;
//}					t_arr;
//
//typedef struct		s_list2
//{
//	t_node			*start;
//	t_node			*end;
//}					t_list2;


int					put_err(char *str);
t_data				*int_map(void);
t_data				*read_map(int fd);
int					*set_check(int size);

int					alg(t_data *map);
int				ft_bfs(t_data *map);
int				ft_bellman_ford(t_data *map);

int		ft_letGoAnts(t_path **paths, t_data *map);
t_loc	*add_loc(t_data *map, char *name, int num_ant);
void	print_sline(t_data *map);
void print_paths(t_path **paths);
#endif