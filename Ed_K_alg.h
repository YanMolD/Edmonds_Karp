#pragma once
#include "find_short_way.h"

using namespace std;

void cout_everything(List<place>* list_p)
{
	int save = 0;
	for (int i = 0; i < list_p->size_t(); i++)
	{
		for (int l = 0; l < list_p->at(i).edges_from->size_t(); l++)
		{
			place::edge buffer = list_p->at(i).edges_from->at(l);//edge from node number i
			if (list_p->at(i).edges_from->at(l).to->name == "T")
				save += buffer.value - buffer.available;
			cout << "Edge from " << buffer.from->name
				<< " to " << buffer.to->name
				<< " is loaded " << buffer.value - buffer.available
				<< " out of " << buffer.value << endl;
		}
	}
	cout << "Maximum flow is " << save;
}

void fill_everything(List<place>* list_p)
{
	int buffer = list_p->size_t(), save = -1;
	int** matrix = fill_main_matrix(list_p);//fill matrix B-F
	for (int i = 0; i < buffer; i++)//Check path availability from source to sink
	{
		if (matrix[i][list_p->size_t() - 1] != 0)
		{
			save = i;
			break;
		}
	}
	if (save == -1)// if it doesn't exist
	{
		cout_everything(list_p);
		return;
	}
	recreate_way(list_p, matrix);//fill shortest way by minimum flow
	fill_everything(list_p);
}