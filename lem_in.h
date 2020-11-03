#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>
# define START 1
# define END 2
# define CLOSE 1
#define INF 1000000

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
	int 			y;
	int 			in_path;
	struct s_point **arr_lines;  //////
	int 			*check;   //////poschitat kolvo svyazey tolko u starta
	int 			cost;
	struct s_point	*prev_room_path;
	struct s_point	*next;
}					t_point;

typedef struct		s_sline
{
	int				weight;
	int 			close;
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
	int				num_of_steps_in_paths;
	int				len;
	t_point			*points;
	t_point			*last_points;
	struct s_path	*prev;
	struct s_path	*next;
}					t_path;

int					put_err(char *str);
t_data				*int_map(void);
t_data				*read_map(int fd);
int					*set_check(int size);

t_path				**ft_alg(t_data *map);
int					ft_bellman_ford(t_data *map, int num_of_edges);
void				ft_init_slines(t_sline *slines);
void				ft_init_points(t_data *map);
int					ft_how_much_edges(t_sline *slines);

int					ft_letGoAnts(t_path **paths, t_data *map);
t_loc				*add_loc(t_data *map, char *name, int num_ant);
int					iter_count(t_path **paths, t_data *map);

void				print_sline(t_data *map);
void				print_paths(t_path **paths);

#endif