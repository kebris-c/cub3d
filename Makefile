NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP

INCLUDES	= -Iinclude -Iinclude/core -Ilibft/include -Iminilibx-linux
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux
LIBFT_A		= $(LIBFT_DIR)/libft.a
MLX_A		= $(MLX_DIR)/libmlx_Linux.a

MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
LIBFT_FLAG	= -L$(LIBFT_DIR) -lft

OBJ_DIR		= objs

# Entry point: separate object + dependency file (not mixed into SRCS).
MAIN_SRC	= src/core/main.c
MAIN_OBJ	= $(OBJ_DIR)/src/core/main.o

SRCS		=	src/common/utils.c \
				src/parsers/parse_utils.c \
				src/parsers/parse_header.c \
				src/parsers/parse_map_grid.c \
				src/parsers/parse_map.c \
				src/io/file_loader.c \
				src/validate/map_validate.c \
				src/render/render.c \
				src/render/image_utils.c \
				src/input/input.c \
				src/movement/movement.c \
				src/lifecycle/game_cleanup.c \
				src/init/game.c \
				src/init/player.c

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
