#include "ft_cub3d.h"

int		fill_map(char **lines, int fd, t_param *p)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (lines[i])
	{
		p->map->worldmap[i] = malloc((ft_strlen(lines[i]) + 1) * sizeof(int *));
		j = 0;
		while(lines[i][j])
		{
			if (lines[i][j] > '2' || lines[i][j] < '0')
			{
				player_init(i, j, lines[i][j], p);
				p->map->worldmap[i][j] = 0;
			}
			else
				p->map->worldmap[i][j] = lines[i][j] - '0';
			j++;
		}
		p->map->worldmap[i][j] = -1;
		free(lines[i]);
		i++;
	}
	close(fd);
	return(1);
}

int		get_lines(char ***lines, char ***tmp, int fd)
{
	char	*s;
	int		i;
	int		j;
	int		ret;

	ret = 1;
	i = 1;
	while (ret)
	{
		ret = get_next_line(fd, &s);
		(*tmp) = (*lines);
		j = 0;
		(*lines) = malloc((i + 1) * sizeof(char *));
		if ((*tmp))
			while((*tmp)[j])
			{
				(*lines)[j] = (*tmp)[j];
				j++;
			}
		free((*tmp));
		(*lines)[j++] = s;
		(*lines)[j] = 0;
		i++;
	}
	return (j);
}

int		parse_cub(char *fname, t_param *p)
{
	int		fd;
	int		j;
	char	**tmp;
	char	**lines;

	fd = open(fname, O_RDONLY);
	lines = 0;
	j = get_lines(&lines, &tmp, fd);
	p->map->worldmap = malloc(j * sizeof (int *));
	p->map->worldmap[j] = 0;
	fill_map(lines, fd, p);
	return (1);
}