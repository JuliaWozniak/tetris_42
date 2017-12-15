#include "h_fillit.h"

// void clear_array(char **array)
// {
// 	int i;

// 	while (array[i])
// 	{
// 		free(array[i]);
// 		array[i] = NULL;
// 		i++;
// 	}
// 	free(array);
// 	array = NULL;
// }





void fill(t_tetr *list, char *square)
{

	while (list->pr_t)
		list = list->pr_t;

//printf("%s\n", square);

	while (list && (list->s_p != -1))
	{
		add_figure(list->fig, square, list->s_p);
		list = list->n_t;
	}
	//printf("%s\n", square);
}







int check_sp(char *square, t_tetr t, int start, int side)
{
	int i;
	int j;
	int all;


	i = 0;
	j = 0;
	all = 0;
	while (square[i + start] && t.fig[i])
	{
		if ((square[i + start] == '.') && (t.fig[i] != '.'))
			i++;
		else if ((square[i + start] != '.') && (t.fig[i] != '.'))
			return (0);
		else if (t.fig[i] == '.')
			i++;
	}
	if (t.fig[i] == '\0')
	{
		 i = 0;
		 while (((i + start) % side) != 0 || (i == 0))
		 	{
		 		i++;
		 		all++;
		 	}
		 i = 0;
		 while (i < all)
		 {
		 	if (t.fig[i] != '.' && t.fig[i] != '\0')
		 		j++;
		 	i++;
		 }
		 if (j != t.wid)
		 	return (0);
		 if (all < t.wid_k)
		 	return (0);
		return (1);
	}
	return (0);
}

int get_sp(char *square, t_tetr t, int side, int start) 
{

	int i;
	i = start;

	while (square[i])
	{
		if (check_sp(square, t, i, side) == 1)
		{
			//printf("YAASSS %i\n", i);
			return (i);
		}
		i++;
	}
	return (-1);
}




int make_square(int number)
{
	int i;

	i = 2;
	while ((i * i) < number)
		i++;
	return (i);
}

char *create_sqr(int side)
{
	char *str;
	int numb;

	numb = side * side;
	str = (char *)malloc(sizeof(char) * (numb + 1));
	if (str == NULL)
		return (NULL);
	str[numb] = '\0';
	while (numb--)
		str[numb] = '.';
	return (str);
}

void clear(char *sqr)
{
	while (*sqr)
	{
		*sqr = '.';
		sqr++;
	}
}

int try(int side, t_tetr *list, char *sqr)
{
	//int temp;
	int sp;
	//int k;

	while (list)
	{
		if (list->s_p == -1)
		{
			if (( sp = get_sp(sqr, *list, side, list->tries)) == -1)
			{
				list->tries = 0;
				if (list->pr_t == NULL)
					return (0);
				list = list->pr_t;
				list->tries = list->s_p + 1;
				list->s_p = -1;
				clear(sqr);
				fill(list, sqr);
			}
			else
			{
				list->s_p = sp;
				add_figure(list->fig, sqr, sp);
				list = list->n_t;
			}
		}
	}

	int i;
	i = 0;
	while (sqr[i])
	{
		if (i % side == 0 && i != 0)
			printf("\n");
		printf("%c", sqr[i]);
		i++;
	}
	printf("\n");
	return (1);
}

int fit_in_square(int side, t_tetr *list)
{
	char *sqr;
	int res;

	//printf("square with %i side\n", side);
	sqr = create_sqr(side);
	res = try (side, list, sqr);
	if (res == 0)
		return (0);
	return (1);
}


int print_one(char *single)
{
	int len;

	single = ft_strtrim(single);
	len = ft_strlen(single);
	if (len == 13 || len == 4)
		return (4);
	else if (len > 6)
		return (3);
	else if (len == 5)
		return (3);
	else if (len == 6)
		return (2);
	return(1);
}



void algorithm(char **valid, int count)
{
	int side;
	int res;
	t_tetr *list;

	if (count == 1)
		side = print_one(valid[0]);
	else 
		side = make_square(count * 4);
	list = prepare_list(valid, side);
	if (list == NULL)
		printf("SHIT\n");
	res = fit_in_square(side, list);
	while (res == 0)
	{
		side += 1;
		list = change_list(valid, side, list);
		res = fit_in_square(side, list);
	}
}


