#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
#include <time.h>

# define START 1
# define END 2
# define CLOSE 1
#define INF 1000000
# define POINTS 2
# define LINES 3

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
	int				num_of_edges;
	int 			max_paths;
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
	int				num_of_steps_in_paths;
	int				len;
	t_point			*points;
	struct s_path	*prev;
	struct s_path	*next;
}					t_path;

int					main(int argc, char **argv);
int					put_err(char *str);

//read&check
//check
int					ft_atoi_check(const char *str);
void				check_st_end(t_data *map, int mod_command);
void				check_line(t_data *map);
void				check_start_end_connected(t_data *map);
void				check_duplicate(t_data *map, char *name);
//read points
int					add_point(char **str, t_data *map, int mod_command);
void				copy_points(t_data *map);
//remake lines
t_point				*get_point(t_data *map, int num, int p);
t_sline				*new_sline(t_point *p1, t_point *p2, int weight);
t_sline				*set_sline(t_data *map);
void				parsing_line(char *str, t_data *map, int mod_command);
//read
t_data				*int_map(void);
t_data				*read_map(int fd);
void				free_str(char **str, int num);

t_path				**ft_alg(t_data *map);
int					ft_bellman_ford(t_data *map);
t_path				**ft_init_paths(t_data *map);
void				ft_init_slines(t_sline *slines);
void				ft_init_points(t_data *map);
int					ft_how_much_edges(t_sline *slines);
void				ft_num_of_max_paths(t_data *map);
void				ft_free_all_paths(t_path **paths);
int					ft_change_edge(t_sline *slines);
t_path*				ft_create_path(t_data *map);
void				ft_free_path(t_path **path);

int					ft_letGoAnts(t_path **paths, t_data *map);
//t_loc				*add_loc(t_data *map, char *name, int num_ant);
void				add_loc(t_data *map, char *name, int num_ant);
int					iter_count(t_path **paths, t_data *map);

void				print_sline(t_data *map);
void				print_paths(t_path **paths);
void				ft_check_repeat_rooms(t_path **paths);


void				free_point(t_point	*point);
void				free_line(t_line	*line);

#endif