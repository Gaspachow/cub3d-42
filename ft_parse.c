#include "ft_cub3d.h"

int		parse_cub(char *fname, t_param *p)
{
	int		fd;
	int		i;
	int		j;
	int		ret;
	char	*s;
	char	**tmp;
	char	**lines;

	fd = open(fname, O_RDONLY);
	i = 1;
	lines = 0;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &s);
		tmp = lines;
		j = 0;
		lines = malloc((i + 1) * sizeof(char *));
		if (tmp)
			while(tmp[j])
			{
				lines[j] = tmp[j];
				j++;
			}
		free(tmp);
		lines[j++] = s;
		lines[j] = 0;
		i++;
	}
	p->map->worldmap = malloc(j * sizeof (int *));
	p->map->worldmap[j] = 0;
	i = 0;
	while (lines[i])
	{
		p->map->worldmap[i] = malloc((ft_strlen(lines[i]) + 1) * sizeof(int *));
		j = 0;
		while(lines[i][j])
		{
			if (lines[i][j] > '2' || lines[i][j] < '0')
				player_init(i, j, lines[i][j], p);
			p->map->worldmap[i][j] = lines[i][j] - '0';
			j++;
		}
		p->map->worldmap[i][j] = -1;
		free(lines[i]);
		i++;
	}
	close(fd);
	return (1);
}