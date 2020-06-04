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

int count_edges(List<place>* list_p)
{
	Node<place>* buf = list_p->Get_Root();
	int counter = 0;
	while (buf != NULL)
	{
		counter += buf->value.edges_from->size_t();
		buf = buf->next;
	}
	return counter;
}

int** fill_main_matrix(List<place>* list_p)
{
	int buffer = list_p->size_t();
	int** matrix = new int* [buffer];
	for (int i = 0; i < buffer; i++)
		matrix[i] = new int[list_p->size_t()];
	for (int i = 0; i < buffer; i++)
		for (int j = 0; j < list_p->size_t(); j++)
			matrix[i][j] = 0;
	int save_pos = 0;
	for (int i = 1; i < buffer; i++)
	{
		for (int j = 0; j < list_p->size_t(); j++)
		{
			if (i == 1)
				for (int l = 0; l < list_p->Get_Root()->value.edges_from->size_t(); l++)
					matrix[i][find_place_pos(list_p->Get_Root()->value.edges_from->at(l).to->name, list_p)] = list_p->Get_Root()->value.edges_from->at(l).value;
			else
			{
				if (matrix[i - 1][j] != 0)
				{
					for (int l = 0; l < list_p->at(j).edges_from->size_t(); l++)
					{
						if (list_p->at(j).edges_from->at(l).available != 0)
						{
							save_pos = find_place_pos(list_p->at(j).edges_from->at(l).to->name, list_p);
							matrix[i][save_pos] =
								(matrix[i][save_pos] == 0 ?
									matrix[i - 1][j] + list_p->at(j).edges_from->at(l).value :
									(matrix[i][save_pos] > matrix[i - 1][j] + list_p->at(j).edges_from->at(l).value ?
										matrix[i - 1][j] + list_p->at(j).edges_from->at(l).value :
										matrix[i][save_pos]));
						}
					}
				}
			}
		}
		/*for (int j = 0; j < list_p->size_t(); j++)
			cout << matrix[i][j] << "    ";
		cout << endl;*/
	}

	return matrix;
}

void recreate_way(List<place>* list_p, int** matrix)
{
	int f = list_p->size_t() - 1;
	int aog_buf = list_p->size_t();
	int min_way_value = matrix[aog_buf - 1][f];
	int amount_of_edges = 0;
	for (int i = 0; i < aog_buf; i++)
	{
		if (matrix[i][f] != 0)
		{
			amount_of_edges = i;
			break;
		}
	}
	List<place>* List_of_p_way = new List<place>();
	List_of_p_way->push_front(&list_p->at(f));
	while (amount_of_edges != 0)
	{
		for (int i = 0; i < List_of_p_way->Get_Root()->value.edges_to->size_t(); i++)
		{
			if (List_of_p_way->Get_Root()->value.edges_to->at(i).available != 0)
			{
				if (matrix[amount_of_edges][f] - List_of_p_way->Get_Root()->value.edges_to->at(i).value ==
					matrix[amount_of_edges - 1][find_place_pos(List_of_p_way->Get_Root()->value.edges_to->at(i).from->name, list_p)])
				{
					amount_of_edges--;
					f = find_place_pos(List_of_p_way->Get_Root()->value.edges_to->at(i).from->name, list_p);
					List_of_p_way->push_front(&list_p->at(f));
					break;
				}
			}
		}
	}
	Node<place>* buf = List_of_p_way->Get_Root();
	Node<place::edge>* buf_edge;
	int min_flow = 100;
	while (buf->next != NULL)
	{
		buf_edge = buf->value.edges_from->Get_Root();
		while (buf_edge->value.to->name != buf->next->value.name)
			buf_edge = buf_edge->next;
		if (buf_edge->value.available < min_flow)
			min_flow = buf_edge->value.available;
		buf = buf->next;
	}
	buf = List_of_p_way->Get_Root();
	while (buf->next != NULL)
	{
		buf_edge = buf->value.edges_from->Get_Root();
		while (buf_edge->value.to->name != buf->next->value.name)
			buf_edge = buf_edge->next;
		buf_edge->value.available -= min_flow;
		buf = buf->next;
	}
}
