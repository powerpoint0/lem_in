/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfigg <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 15:18:03 by dfigg             #+#    #+#             */
/*   Updated: 2020/11/14 15:18:08 by dfigg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_VIS_H
# define LEM_VIS_H
# include "libft.h"
# include "get_next_line.h"
# include <mlx.h>

# define START 1
# define END 2
# define POINTS 2
# define LINES 3
# define STEPS 4
# define RANGE 100

# define W_WEIDTH 1400
# define W_HEIGTH 1400

# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_UP 126
# define KEY_DOWN 125

# define WHITE 0xffffff
# define SILVER 0xC0C0C0
# define BLACK 0x000000
# define RED 0xff0000
# define GREEN 0x00ff00
# define BLUE 0x0000ff
# define YELLOW 0xffff00
# define MAGENTA 0xff00ff

typedef struct		s_vpoint
{
	char			*name;
	int				x;
	int				y;
	int				z;
	int				color;
	char			*ant;
	struct s_vpoint	*next;
}					t_vpoint;

typedef struct		s_vpath
{
	t_vpoint		*points;
	struct s_path	*prev;
	struct s_path	*next;
}					t_vpath;

typedef struct		s_vline
{
	t_vpoint		*p1;
	t_vpoint		*p2;
	struct s_vline	*next;
}					t_vline;

typedef struct		s_vstep
{
	t_vpoint		*vpoint;
	t_vpoint		*last_vpoint;
	struct s_vstep	*next;
}					t_vstep;

typedef struct		s_vmap
{
	int				count_ants;
	t_vpoint		*points;
	t_vpoint		*last_points;
	t_vline			*line;
	t_vline			*last_line;
	t_vstep			*step;
	t_vstep			*last_step;
	t_vpath			*vpath;
	t_vpoint		*start;
	t_vpoint		*end;
}					t_vmap;

typedef struct		s_ants
{
	int				num;
	char			*name;
	int				color;
	t_vpoint		prev;
	t_vpoint		next;
	t_vpoint		cur;
}					t_ants;

typedef struct		s_visual
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bit_per_pixel;
	int				size_line;
	int				endian;
	int				pause;
	int				speed;
	int				finish;
	int				max_x;
	int				max_y;
	t_ants			*ants;
	int				way;
	t_vmap			*v_map;
	char			*buf;
}					t_visual;

int					put_err(char *str);
void				free_str(char **str);
int					ft_atoi_check(const char *str);
int					ft_find_count(const char *s, int c);
t_vmap				*init_vmap();
t_visual			*init_v();
void				set_buf(t_visual *v);
int					ft_check_num_ants(char *str);
t_vpoint			*get_point_by_name(t_vmap *map, char *name);
t_vpoint			get_point(t_vpoint	*p, t_visual *v);
int					add_vpoint(char **str, t_vmap *map, int mod_command);
t_vpoint			*copy_vpoint(t_vpoint *point);
t_vstep				*new_step(char **str, t_vmap *map);
t_vmap				*read_map();
void				ft_drawing(t_vmap *map);
int					run_ants(t_visual *v);
void				control(t_visual *v);
void				on_off_ant(t_visual *v, t_vpoint p, int color, int size);
t_ants				*init_ants(t_vmap *map, t_visual *v);
void				ant_step(t_visual *v);
int					ant_new_step(t_visual *v);
void				print_ants(t_visual *v);
void				print_ants_names(t_visual *v);
void				set_line(t_vpoint p0, t_vpoint p1, t_visual *v);
void				put_pixel(t_visual *v, int x, int y, int color);
void				clear_image(t_visual *v);
void				print_all(t_visual *v);

#endif
