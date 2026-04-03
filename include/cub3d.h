#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_image		frame;
	t_image		textures[TEX_COUNT];
	t_config	cfg;
	t_player	player;
	t_keys		keys;
}	t_game;

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
void	render_frame(t_game *game);
void	move_player(t_game *game);
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
