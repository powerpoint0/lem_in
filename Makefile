NAME = lem-in

LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror

source_dirs = . srcs libft/includes

SRCS = srcs/lem-in.c \
		srcs/alg.c \
			srcs/bellman_ford.c \
			srcs/init.c \
			srcs/moving_ants.c \
			srcs/read.c

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