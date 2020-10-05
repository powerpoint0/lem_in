#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>
# define START 1
# define END 2

typedef struct		s_line
{
	char			*p_first;
	char			*p_next;
	int				num_first;
	int				num_next;
	struct s_line	*next;
}				t_line;

typedef struct		s_point
{
	int				num;
	char			*name;
	int				x;
	int 			y;
	int				st_end;
	int 			in_path;
	int 			bfs_level;
	struct s_point **arr_lines;
	int				close;
	struct s_point	*prev_room_path;
	struct s_point	*next;
}					t_point;

typedef struct		s_data
{
	int				num_ants;
	t_point			*points;
	t_line			*lines;
	t_point			*last_points;
	t_line			*last_lines;
	t_point			*start;
	t_point			*end;
}					t_data;

typedef struct		s_path
{
	int len;
	t_point			*points;
	t_point			*last_points;
	t_point			*next;
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

int					alg(t_data *map);
int				ft_bfs(t_data *map);
#endif