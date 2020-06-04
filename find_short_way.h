#pragma once
#include "Structures.h"

using namespace std;

int find_place_pos(string name, List<place>* list_p)
{
	Node<place>* buf = list_p->Get_Root();
	int counter = 0;
	while (buf != NULL)
	{
		if (buf->value.name == name)
			return counter;
		else
			buf = buf->next;
		counter++;
	}
	throw out_of_range("No places with that name");
}

bool check_name(List<place>* places, string name)
{
	Node<place>* buf = places->Get_Root();
	while (buf != NULL)
	{
		if (buf->value.name == name)
			return false;
		else
			buf = buf->next;
	}
	return true;
}

int** fill_main_matrix(List<place>* list_p)
{
	int** matrix = new int* [list_p->size_t()];//matrix initialization
	for (int i = 0; i < list_p->size_t(); i++)
		matrix[i] = new int[list_p->size_t()];
	for (int i = 0; i < list_p->size_t(); i++)//filling of matrix
		for (int j = 0; j < list_p->size_t(); j++)
			matrix[i][j] = 0;
	int save_pos = 0;
	place::edge buffer_edge;
	for (int i = 1; i < list_p->size_t(); i++)
	{
		for (int j = 0; j < list_p->size_t(); j++)
		{
			if (i == 1) //filling all ways with 1 edge from source
				for (int l = 0; l < list_p->Get_Root()->value.edges_from->size_t(); l++)
				{
					buffer_edge = list_p->Get_Root()->value.edges_from->at(l);//edge from root
					matrix[i][find_place_pos(buffer_edge.to->name, list_p)] = buffer_edge.value;
				}
			else// filling all other ways
			{
				if (matrix[i - 1][j] != 0)
				{
					for (int l = 0; l < list_p->at(j).edges_from->size_t(); l++)
					{
						buffer_edge = list_p->at(j).edges_from->at(l);
						if (list_p->at(j).edges_from->at(l).available != 0)
						{
							save_pos = find_place_pos(buffer_edge.to->name, list_p);//saving number of node (which current edge directed to)
							if (matrix[i][save_pos] == 0)
								matrix[i][save_pos] = matrix[i - 1][j] + buffer_edge.value;
							else
								if (matrix[i][save_pos] > matrix[i - 1][j] + buffer_edge.value)
									matrix[i][save_pos] = matrix[i - 1][j] + buffer_edge.value;
						}
					}
				}
			}
		}
	}

	return matrix;
}

void recreate_way(List<place>* list_p, int** matrix)
{
	int Last_elem_pos = list_p->size_t() - 1;
	int aog_buf = list_p->size_t();
	int amount_of_edges = 0;
	for (int i = 0; i < aog_buf; i++)// finding shortest way in matrix
	{
		if (matrix[i][Last_elem_pos] != 0)
		{
			amount_of_edges = i;
			break;
		}
	}
	List<place>* List_of_p_way = new List<place>();
	List_of_p_way->push_front(&list_p->at(Last_elem_pos));
	place::edge buffer_edge;
	int save_pos;
	while (amount_of_edges != 0)
	{
		for (int i = 0; i < List_of_p_way->Get_Root()->value.edges_to->size_t(); i++)
		{
			if (List_of_p_way->Get_Root()->value.edges_to->at(i).available != 0)
			{
				buffer_edge = List_of_p_way->Get_Root()->value.edges_to->at(i);
				save_pos = find_place_pos(buffer_edge.from->name, list_p);
				if (matrix[amount_of_edges][Last_elem_pos] - buffer_edge.value == matrix[amount_of_edges - 1][save_pos])
				{
					amount_of_edges--;
					Last_elem_pos = save_pos;
					List_of_p_way->push_front(&list_p->at(Last_elem_pos));
					break;
				}
			}
		}
	}
	Node<place>* buf = List_of_p_way->Get_Root();
	Node<place::edge>* buf_edge;
	int min_flow = 100;
	while (buf->next != NULL)//finding minimal edge
	{
		buf_edge = buf->value.edges_from->Get_Root();
		while (buf_edge->value.to->name != buf->next->value.name)
			buf_edge = buf_edge->next;
		if (buf_edge->value.available < min_flow)
			min_flow = buf_edge->value.available;
		buf = buf->next;
	}
	buf = List_of_p_way->Get_Root();
	while (buf->next != NULL) //filling all edges with minimal edge size
	{
		buf_edge = buf->value.edges_from->Get_Root();
		while (buf_edge->value.to->name != buf->next->value.name)
			buf_edge = buf_edge->next;
		buf_edge->value.available -= min_flow;
		buf = buf->next;
	}
}
