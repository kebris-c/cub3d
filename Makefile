NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -MMD -MP

INCLUDES	= -Iinclude -Ilibft/include -Iminilibx-linux
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
LIBFT_FLAG	= -L$(LIBFT_DIR) -lft
LIBFT_CFLAGS	= -Wall -Wextra

SRC_DIR		= src
OBJ_DIR		= objs

SRCS		=	main.c \
				parse_utils.c \
				file_loader.c \
				parse_header.c \
				parse_map.c \
				map_validate.c \
				render.c \
				input.c \
				movement.c \
				image_utils.c \
				game_cleanup.c \
				utils.c

OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
DEPS		= $(OBJS:.o=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) FLAGS="$(LIBFT_CFLAGS)"
	@chmod +x "$(MLX_DIR)/configure"
	@$(MAKE) -C $(MLX_DIR)
	$(CC) $(OBJS) $(INCLUDES) $(LIBFT_FLAG) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)
