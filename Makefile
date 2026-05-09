NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP -g

INCLUDES	= -Iinclude -Iinclude -Ilibft/include -Iminilibx-linux
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux
LIBFT_A		= $(LIBFT_DIR)/libft.a
MLX_A		= $(MLX_DIR)/libmlx_Linux.a

MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
LIBFT_FLAG	= -L$(LIBFT_DIR) -lft

OBJ_DIR		= objs

# Entry point: separate object + dependency file (not mixed into SRCS).
MAIN_SRC	= src/entry/main.c
MAIN_OBJ	= $(OBJ_DIR)/src/entry/main.o

SRCS		=	src/helpers/utils.c						\
				src/setup/game.c						\
				src/setup/player.c						\
				src/input/input.c						\
				src/files/file_loader.c					\
				src/runtime/game_cleanup.c				\
				src/runtime/signals.c					\
				src/player_motion/player_move.c			\
				src/parser/parser_text_helpers.c 		\
				src/parser/parse_header_tokenize.c		\
				src/parser/parse_header.c 				\
				src/parser/parse_map_grid.c				\
				src/parser/parse_map.c					\
				src/raycast/raycast_frame.c				\
				src/raycast/ray_column_screen.c			\
				src/raycast/ray_dda_walk.c				\
				src/raycast/ray_wall_face_texture.c		\
				src/render/draw_frame_surfaces.c		\
				src/render/draw_wall_texture_column.c	\
				src/map_check/map_validate.c			\
				src/map_check/map_enclosure_bfs.c		

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS		= $(OBJS:.o=.d) $(MAIN_OBJ:.o=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(MAIN_OBJ) $(OBJS) | $(LIBFT_A) $(MLX_A)
	$(CC) $(MAIN_OBJ) $(OBJS) $(INCLUDES) $(LIBFT_FLAG) $(MLX_FLAGS) -o $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	@chmod +x "$(MLX_DIR)/configure"
	@$(MAKE) -C $(MLX_DIR)

$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(MAIN_SRC) -o $(MAIN_OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@chmod +x "$(MLX_DIR)/configure" 2>/dev/null || true
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)
