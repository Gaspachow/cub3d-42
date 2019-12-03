#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct		data_s
{
	void			*mlx_ptr;
	void			*mlx_win;
}					data_t;

unsigned int	rgb_int(int red, int green, int blue)
{
	int	rgb;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int	main(void)
{
	data_t	data;
	int		i;
	void *pepe;
	int height = 194;
	int width = 259;

	i = 0;
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, 1920, 1080, "coucou")))
		return (EXIT_FAILURE);
	while (i++ < 2000)
		mlx_pixel_put(data.mlx_ptr, data.mlx_win, 0 + i, 0 + i, rgb_int(0, 255, 0));
	pepe = mlx_xpm_file_to_image(data.mlx_ptr, "pepe.xpm", &height, &width);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, pepe, 500, 500);

	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}