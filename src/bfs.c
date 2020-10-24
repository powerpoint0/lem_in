//#include "lem_in.h"
//
//#define FREE 0
//#define VISITED 1
//#define PART_OF_PATH 2
//#define PART_OF_PATH_FIRST_STEP 4
//#define PART_OF_PATH_SECOND_STEP 8
//#define IN_QUEUE 3
//#define PART_OF_PATH_IN_AND_OUT 16
//
//void ft_clean_close(t_data *map)
//{
//	t_point *header;
//
//	header = map->points;
//	while(map->points->next)
//	{
//		if(map->points->close == VISITED || map->points->close == IN_QUEUE)
//			map->points->close = FREE;
//		else if(map->points->close == PART_OF_PATH_FIRST_STEP || map->points->close == PART_OF_PATH_SECOND_STEP )
//			map->points->close = PART_OF_PATH;
//		map->points->prev_room_path = NULL;
//		map->points = map->points->next;
//	}
//	map->points->close = 0;
//	map->points = header;
//}
//
///*
// * сначала заполняем 1 указатель
// * после второй
// * восстанавливаем путь в обратном порядке и затираем указатели
// */
//

//
//}
//
//t_point *ft_get_next_empty_room(t_point *current, t_point *next, int i, t_point *end)
//{
//	if (!current->check[i + 1])
//		return (NULL);
//	if (current->close != IN_QUEUE)
//		return (NULL);
//	if (next->close != FREE)
//		return (NULL);
////	printf1("%s_%s\n", current->name, next->name);
//	printf1("%s_%s %d_%d\n", current->name, next->name,current->close, next->close );
//	next->bfs_level = current->bfs_level + 1;
//	next->prev_room_path = current;
//	next->close = IN_QUEUE;
//	if (next == end)
//		next->close = VISITED;
//	return (next);
//}
//
//t_point *ft_get_next_path_room(t_point *current, t_point *next, int i, t_point *end)
//{
//	//связь отключена
//	if (!current->check[i + 1])
//		return (NULL);
//	if (current->close != IN_QUEUE)
//		return (NULL);
//	if (next->close != PART_OF_PATH)
//		return (NULL);
//	printf1("%s_%s %d_%d\n", current->name, next->name,current->close, next->close );
//	next->bfs_level = current->bfs_level + 1;
//	next->prev_room_path = current;
//	next->close = PART_OF_PATH_FIRST_STEP;
//	return (next);
//}
//
//t_point *ft_get_next_path_in_room(t_point *current, t_point *next, int i, t_point *end)
//{
//	//связь отключена
//	if (!current->check[i + 1])
//		return (NULL);
//	if (current->close != PART_OF_PATH_FIRST_STEP)
//		return (NULL);
//	if (next->close != PART_OF_PATH && next->close != PART_OF_PATH_FIRST_STEP)
//		return (NULL);
//	printf1("%s_%s %d_%d\n", current->name, next->name,current->close, next->close );
////	printf1("%s_%s\n", current->name, next->name);
//	next->bfs_level = current->bfs_level - 1;
//	if (!next->prev_room_path)
//		next->prev_room_path = current;
//	else
//		next->prev_room_path2 = current;
//	next->close = PART_OF_PATH_SECOND_STEP;
//	return (next);
//}
//
//t_point *ft_get_next_path_out_room(t_point *current, t_point *next, int i, t_point *end)
//{
//	//связь отключена
//	if (!current->check[i + 1])
//		return (NULL);
//	if (current->close != PART_OF_PATH_SECOND_STEP)
//		return (NULL);
//	if (next->close != FREE && next->close != PART_OF_PATH)
//		return (NULL);
////	printf1("%s_%s\n", current->name, next->name);
//	printf1("%s_%s %d_%d\n", current->name, next->name,current->close, next->close );
//	next->bfs_level = current->bfs_level + 1;
//	if (!next->prev_room_path)
//		next->prev_room_path = current;
//	else
//		next->prev_room_path2 = current;
//	if (next->close == PART_OF_PATH)
//		next->close = PART_OF_PATH_SECOND_STEP;
//	else
//		next->close = IN_QUEUE;
//	return (next);
//}
//
//int		ft_bfs(t_data *map)
//{
//	g_num++;
//
//	t_point **queue;
//	t_point *current;
//	int queue_p;
//	int i;
//	int qp2;
//	qp2 = 1;
//
//	t_point *next;
//
//	if (!(queue = (t_point **) ft_memalloc(sizeof(t_point *) * (map->last_points->num * 2 + 1))))
//		put_err("Init.there is no memory for queue");
//	ft_clean_close(map);
//	queue[0] = map->start;
//	map->start->bfs_level = 0;
//	map->end->bfs_level = 0;
//	map->start->close = IN_QUEUE;
//	queue_p = 0;
//	while (queue_p < qp2)
//	{
//		i = 0;
//		current = queue[queue_p];
//		//надо это обдумать
//		while (current->arr_lines[i])
//		{
//			next = current->arr_lines[i];
////			if (!ft_strcmp(current->name, "1") && !ft_strcmp(next->name, "2") && g_num == 2)
////				ft_atoi("2");
//			if ((next = ft_get_next_empty_room(current, current->arr_lines[i], i, map->end)))
//				queue[qp2++] = next;
//			else if ((next = ft_get_next_path_room(current, current->arr_lines[i], i, map->end)))
//				queue[qp2++] = next;
//			else if ((next = ft_get_next_path_in_room(current, current->arr_lines[i], i, map->end)))
//				queue[qp2++] = next;
//			else if ((next = ft_get_next_path_out_room(current, current->arr_lines[i], i, map->end)))
//				queue[qp2++] = next;
//			i++;
//		}
//		if (current->close == FREE || current->close == IN_QUEUE)
//			current->close = VISITED;
//		queue_p++;
//	}
//	if (!map->end->bfs_level)
//		return (-1);
//	return (0);
//}

#include <stdio.h>
#include "lem_in.h"



//void ft_clean_close(t_data *map)
//{
//	t_point *header;
//
//	header = map->points;
//	while(map->points->next)
//	{
//		if(map->points->close == 1)
//			map->points->close = 0;
//		map->points->prev_room_path = NULL;
//		map->points = map->points->next;
//	}
//	map->points->close = 0;
//	map->points = header;
//}
//void ft_clean_close(t_data *map)
//{
//	t_point *header;
//
//	header = map->points;
//	while(map->points->next)
//	{
//		if(map->points->close == 1)
//			map->points->close = 0;
//		map->points->prev_room_path = NULL;
//		map->points = map->points->next;
//	}
//	map->points->close = 0;
//	map->points = header;
//}

int g_num = 0;
void printf1(char *str, char *name,int close1, char *name2,  int close2)
{
	if (g_num != 1)
		return;
	printf(str, name,close1, name2,  close2);
}

//
//int		ft_bfs(t_data *map)
//{
//	g_num++;
//
//	t_point **queue;
//	t_point *current;
//	t_point *next;
//	int queue_p;
//	int i;
//	int qp2;
//	qp2 = 1;
//
//	if (!(queue = (t_point **) ft_memalloc(sizeof(t_point *) * (map->last_points->num + 1))))
//		put_err("Init.there is no memory for queue");
//	ft_clean_close(map);
//	queue[0] = map->start;
//	map->start->bfs_level = 0;
//	map->end->bfs_level = 0;
//	map->start->close = 1;
//	queue_p = 0;
//	while (queue_p < qp2)
//	{
//		i = 0;
//		current = queue[queue_p];
//		if(current && current->arr_lines)
//		{
//			while (current->arr_lines[i]) {
//				next = current->arr_lines[i];
//				//printf1("%s%d_%s%d\n", current->name, current->p, next->name, next->p);
//				if (current->check[i + 1] && !current->arr_lines[i]->close) {
//					current->arr_lines[i]->bfs_level = current->bfs_level + 1;
//					current->arr_lines[i]->prev_room_path = current;
//				}
//				if (current->close != 2)
//					current->close = 1;
//				if (current->arr_lines[i] == map->end)
//					current->arr_lines[i]->close = 1;
//				if (!current->arr_lines[i]->close && current->check[i + 1])
//					queue[qp2++] = current->arr_lines[i];
//				i++;
//			}
//		}
//		queue_p++;
//	}
//	if (!map->end->bfs_level)
//		return (-1);
//	printf("\n");
//	return (0);
//}

#define INF 1000000
void	ft_init_points(t_data *map)
{
	while (map->points)
	{
		if(map->points == map->start)
			map->points->cost = 0;
		else
			map->points->cost = INF;
		map->points = map->points->next;
	}
	map->points = map->start;
}

int		ft_how_much_edges(t_sline *slines)
{
	int i;

	i = 0;
	t_sline *header;
	header = slines;
	while(slines)
	{
		i++;
		slines = slines->next;
	}
	slines = header;
	return(i);
}
int		ft_bell_ford_deep(t_sline *slines)
{
	t_sline *header;
	header = slines;
	while(slines)
	{
		if((slines->out->cost == INF || slines->out->cost > slines->in->cost + slines->weight))
		{
			slines->out->cost = slines->in->cost + slines->weight;
			slines->out->prev_room_path = slines->in;
			slines = header;
			return(0);
		}
		slines = slines->next;
	}
	// - cycle
	slines = header;
	return(0);
}

int		ft_bellman_ford(t_data *map)
{
	int num_of_edges;
	int iter = 0;

	num_of_edges = 0;
	ft_init_points(map);
	num_of_edges = ft_how_much_edges(map->slines);
	while (iter < num_of_edges)
	{
		ft_bell_ford_deep(map->slines);
		iter++;
	}
	if(!map->end->prev_room_path)
		return(-1);
	//print_sline(map);
	return(0);
}
