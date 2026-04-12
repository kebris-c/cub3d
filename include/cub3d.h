/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjroydev <kjroydev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 19:11:59 by kjroydev          #+#    #+#             */
/*   Updated: 2026/04/12 19:48:43 by kjroydev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>

# define WIN_WIDTH 1240
# define WIN_HEIGHT 1080
# define MOVE_SPEED 0.08
# define ROT_SPEED 0.05

typedef enum e_tex_id
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3,
	TEX_COUNT = 4
}	t_tex_id;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

/**
 * @struct s_ray
 * @brief Structure that contains the information of an `x` ray.
 * 
 * This structure contains the representation of a 2D vector `(x, y)`, with the
 * adition of it's next step. The direction is determinated by the starting
 * position `(x, y)` of the player in the grid. `direction-x` and `direction-y` 
 * of the current vector, it's determinated by the `direction-x` and
 * `direction-y` the player is facing at  the beginning 
 * of the game/level `(N, S, E, W)`.
 * 
 * Composition:
 * 
 * - Delta distance the vector can advance from a `(x, y)` starting point
 * 		without hiting a wall.
 * 
 * - Side distance the vector has between the player and
 * 			a wall/interactive object.
 * 
 * - Direction `(x, y)` the vector is facing.
 * 
 * - The next step in `(x, y)` it has to advance.
 * 
 * - Starting position in `(x, y)`.
 */
typedef struct s_ray
{
	/** Magnitude the current vector can advance in `x`. */
	double	delta_dist_x;

	/** Magnitude the current vector can advance in `y`. */
	double	delta_dist_y;

	/** Distance between vector and player in `x`. */
	double	side_dist_x;

	/** Distance between vector and player in `y`. */
	double	side_dist_y;

	/** Direction of the vector in `x`. */
	double	dir_x;

	/** Direction of the vector in `y`. */
	double	dir_y;

	/** Next step in `x`. */
	int		step_x;

	/** Next step in `y`. */
	int		step_y;

	/** Max lenght in `x`. */
	int		map_x;

	/** Max lenght in `y`. */
	int		map_y;
	int		side;
}	t_ray;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_config
{
	char	*tex_path[TEX_COUNT];
	int		floor_color;
	int		ceil_color;
	t_map	map;
	double	player_x;
	double	player_y;
	char	player_dir;
}	t_config;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/**
 * @struct s_game
 * @brief Structure that contains all the information of the game.
 * 
 * This structure stores relevant information of the game core,
 * including references to other structures like the
 * initial configuration information; the keyboard input;
 * rays of the 2D engine (raycasting) of the game and the player.
 * 
 * Composition:
 * 
 * - mlx: Pointer to the MiniLibX context (graphics library instance).
 * 
 * - win: Pointer to the window created by MiniLibX.
 * 
 * - frame: Image buffer used as the current render target.
 * 
 * - textures: Array of textures used for wall rendering.
 * 
 * - cfg: Parsed configuration data (map, colors, textures paths, etc.).
 * 
 * - player: Player state (position, direction, camera plane).
 * 
 * - rays: Array of rays casted per screen column (raycasting engine).
 * 
 * - keys: Structure storing the current keyboard input state.
 */
typedef struct s_game
{
	/** Pointer to the MiniLibX */
	void		*mlx;

	/** Pointer to the windows created by MiniLibX. */
	void		*win;

	/** Image buffer. */
	t_image		frame;

	/** Array of textures for wall rendering */
	t_image		textures[TEX_COUNT];

	/** Parsed configuration. */
	t_config	cfg;

	/** Player state. */
	t_player	player;

	/** Array of rays casted per screen column (raycasting engine). */
	t_ray		rays[WIN_WIDTH];

	/** Keyboard keys functions. */
	t_keys		keys;
}	t_game;

// Engine Functions

void	determine_hit(t_game *game, t_map *map, int *x);
void	precal_camera_factors(double cam_factor[WIN_WIDTH]);
void	render_frame(t_game *game);
void	move_player(t_game *game);

int		parse_cub_file(t_config *cfg, const char *path);
int		parse_header_line(t_config *cfg, const char *line);
int		headers_complete(t_config *cfg);
int		validate_map(t_config *cfg);
int		init_game(t_game *game);
int		game_loop(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(t_game *game);
void	cleanup_game(t_game *game);
int		error_msg(const char *msg);
int		rgb_to_int(int r, int g, int b);
int		file_has_extension(const char *file, const char *ext);
int		load_file_lines(const char *path, char ***lines);
void	free_lines(char **lines);
int		is_blank_line(const char *line);
int		is_map_line(const char *line);
size_t	line_len_no_nl(const char *line);
char	*trim_spaces(const char *line);
void	put_pixel(t_image *img, int x, int y, int color);
int		get_texel(t_image *img, int x, int y);
int		is_walkable(t_map *map, double x, double y);
void	free_config(t_config *cfg);

#endif
