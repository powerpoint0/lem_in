# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjoaquin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 18:57:41 by cjoaquin          #+#    #+#              #
#    Updated: 2019/09/22 03:15:53 by cjoaquin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

source_dirs = . includes ft_printf

HEAD = includes/get_next_line.h includes/libft.h includes/ft_printf.h

# OBJ_DIR = obj

SRCS = ft_atoi.c \
ft_bzero.c \
ft_count_words.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memalloc.c \
ft_memccpy.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memdel.c \
ft_memmove.c \
ft_memset.c \
ft_print_params.c \
ft_putchar.c \
ft_putchar_fd.c \
ft_putendl.c \
ft_putendl_fd.c \
ft_putnbr.c \
ft_putnbr_fd.c \
ft_putstr.c \
ft_putstr_fd.c \
ft_sqrt.c \
ft_strcat.c \
ft_strchr.c \
ft_strclr.c \
ft_strcmp.c \
ft_strcpy.c \
ft_strdel.c \
ft_strdup.c \
ft_strequ.c \
ft_striter.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlen.c \
ft_strmap.c \
ft_strmapi.c \
ft_strncat.c \
ft_strncmp.c \
ft_strncpy.c \
ft_strnequ.c \
ft_strnew.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strsplit.c \
ft_strstr.c \
ft_strsub.c \
ft_strtrim.c \
ft_tolower.c \
ft_toupper.c \
ft_lstnew.c \
ft_lstdelone.c \
ft_lstdel.c \
ft_lstadd.c \
ft_lstiter.c \
ft_lstmap.c \
ft_sort_params.c \
ft_binar_chr.c \
get_next_line.c \
ft_printf/ft_printf.c \
ft_printf/print_cs.c	\
ft_printf/print_d.c	\
ft_printf/print_efg.c \
ft_printf/print_f_func.c	\
ft_printf/print_oux_p.c	\
ft_printf/set_flags_n_mods.c	\
ft_printf/utils.c \
ft_printf/additional_func.c

# OBJS = $(addprefix $(OBJ_DIR)/, $(patsubst %.c,%.o,$(SRCS)))
OBJS = $(notdir $(patsubst %.c,%.o,$(SRCS)))

# all: $(OBJ_DIR) $(NAME)

all: $(NAME)

# $(OBJ_DIR)/%.o: %.c $(HEAD)
# 		gcc $(FLAGS) -c -MD $(addprefix -I,$(source_dirs)) $< -o $@

%.o: %.c $(HEAD)
		gcc $(FLAGS) -c -MD $(addprefix -I,$(source_dirs)) $< -o $@

$(NAME): $(OBJS)
		ar rc $(NAME) $?
		ranlib $(NAME)

# $(OBJ_DIR):
# 	mkdir -p $(OBJ_DIR)

VPATH := $(source_dirs)

clean:
	rm -rf $(patsubst %.o,%.d,$(OBJS)) $(OBJS)
# 	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
