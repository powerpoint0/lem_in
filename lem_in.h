#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# define START 1
# define END 2

typedef struct		s_line
{
	char			*p_first;
	char			*p_next;
	struct s_line	*next;
}				t_line;

typedef struct		s_point
{
	char			*name;
	int				x;
	int 			y;
	int				st_end;
	int 			in_path;
	struct s_point	*next;
}					t_point;

typedef struct		s_data
{
	int				num_ants;
	t_point			*points;
	t_line			*lines;
}					t_data;

typedef struct		s_path
{
	t_point			*point;
}					t_path;

int					put_err(char *str);
t_data				*int_map(void);
t_data				*read_map(int fd);

int					alg(t_data *map);

#endif