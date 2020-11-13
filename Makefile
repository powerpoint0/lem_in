NAME = lem-in

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror

source_dirs = . srcs libft/includes libft libft/ft_printf

SRCS = srcs/lem_in.c \
			srcs/alg.c \
			srcs/bellman_ford.c \
			srcs/init.c \
			srcs/moving_ants.c \
			srcs/read.c \
			srcs/debug.c \
			srcs/alg_copy_n_free_paths.c \
			srcs/check_and_read.c \
			srcs/read_points.c \
			srcs/read_reline.c \
			srcs/read_lines.c \
			srcs/util_slines.c \
			srcs/util_lines.c \
			srcs/util_ants.c

OBJS = $(notdir $(patsubst %.c,%.o,$(SRCS)))

HEAD = lem-in.h

LDIRS = libft/

LIB_ALL = $(addsuffix .all,$(LDIRS))

all: $(LIB_ALL) $(LIBFT) $(NAME)

%.o:%.c
		gcc $(FLAGS) -c -MD $(addprefix -I,$(source_dirs)) $< -o $@

$(NAME): $(OBJS) $(LIBFT)
		gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT)

VPATH := $(source_dirs)

clean:
	cd libft && make clean
	rm -f $(patsubst %.o,%.d,$(OBJS)) $(OBJS)

fclean: clean
	cd libft && make fclean
	rm -f $(NAME)

re: fclean all

%.all:
	make -C $*

include $(wildcard *.d)