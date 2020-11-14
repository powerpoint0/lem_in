# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dfigg <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/12 18:01:32 by dfigg             #+#    #+#              #
#    Updated: 2020/02/12 18:30:04 by dfigg            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LEM_VIS = visu-hex

FLAGS = -Wall -Wextra -Werror
CC = gcc

SRC_DIR = src/
LIBFT_DIR = libft/
OBJ_DIR = obj/


LIB_MLX = -Imlx -lmlx -framework OpenGL -framework AppKit

VIS_SRC = vis.c read_vs.c drawing.c controls.c ants_path.c read_utils.c init.c \
			drawing_utils.c drawing_utils2.c ft_find_err.c


LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
VIS_OBJ = $(VIS_SRC:c=o)

all: $(LIBFT) $(LEM_VIS)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I libft/includes/ -I ./includes -c -o $@ $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(LEM_VIS): $(addprefix $(OBJ_DIR), $(VIS_OBJ))
	@$(CC) $(addprefix $(OBJ_DIR), $(VIS_OBJ)) $(LIBFT_DIR)libft.a -I libft/ -I ./includes -I$(LIB_MLX) -o $(LEM_VIS)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(LEM_VIS)

re: fclean all