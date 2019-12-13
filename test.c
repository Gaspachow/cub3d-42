#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mlx.h>

typedef struct		data_s
{
	void			*mlx_ptr;
	void			*mlx_win;
}					data_t;

typedef struct		img_s
{
	int				x;
	int				y;
	int				h;
	int				w;
	void			*ptr;
	void			*win;
	void			*mlx;
}					img_t;

int	rgb_int(int red, int green, int blue)
{
	int	rgb;
	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int	test()
{
	static int i;
	i = 0;
	printf("%i coucou\n", i);
	i++;
	return (1);
}

int	deal_key(int key, img_t *datapepe)
{
	if (key == 13)
		{
			datapepe->h += 500;
			datapepe->w += 500;
			datapepe->x -= 25;
			datapepe->y -= 25;
			mlx_destroy_image(datapepe->mlx, datapepe->ptr);
			datapepe->ptr = mlx_xpm_file_to_image(datapepe->mlx, "pepe.xpm", &(datapepe->h), &(datapepe->w));
			mlx_put_image_to_window(datapepe->mlx, datapepe->win, datapepe->ptr, datapepe->x, datapepe->y);
		}
	if (key == 1)
		mlx_destroy_image(datapepe->mlx, datapepe->ptr);
	return (0);
}

int	main(void)
{
	data_t	data;
	int		i;
	void *pepe;
	int height = 194;
	int width = 259;
	img_t	datapepe;

	datapepe.x = 900;
	datapepe.y = 500;
	datapepe.h = 50;
	datapepe.w = 50;

	i = 0;
	if (!(data.mlx_ptr = mlx_init()))
		return (EXIT_FAILURE);
	if (!(data.mlx_win = mlx_new_window(data.mlx_ptr, 1920, 1080, "coucou")))
		return (EXIT_FAILURE);
	datapepe.mlx = data.mlx_ptr;
	datapepe.win = data.mlx_win;
	while (i++ < 2000)
		mlx_pixel_put(data.mlx_ptr, data.mlx_win, 0 + i / 2, 0 + i, rgb_int(0, 255, 0));
	datapepe.ptr = mlx_xpm_file_to_image(data.mlx_ptr, "pepe.xpm", &height, &width);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, datapepe.ptr, 900, 500);
	mlx_string_put(data.mlx_ptr, data.mlx_win, 1000, 540, rgb_int(255, 255, 0), "PEPE IS SAD... sad pepe is very sad");

	mlx_hook(data.mlx_win, 2, 1, deal_key, (void *)&datapepe);
	mlx_loop(data.mlx_ptr);
	return (EXIT_SUCCESS);
}
