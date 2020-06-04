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
			if (list_p->at(i).edges_from->at(l).to->name == "T")
				save += list_p->at(i).edges_from->at(l).value - list_p->at(i).edges_from->at(l).available;
			cout << "Edge from " << list_p->at(i).edges_from->at(l).from->name
				<< " to " << list_p->at(i).edges_from->at(l).to->name
				<< " is loaded " << list_p->at(i).edges_from->at(l).value - list_p->at(i).edges_from->at(l).available
				<< " out of " << list_p->at(i).edges_from->at(l).value << endl;
		}
	}
	cout << "Maximum flow is " << save;
}

void fill_everything(List<place>* list_p)
{
	int buffer = list_p->size_t(), save = -1;
	int** matrix = fill_main_matrix(list_p);
	for (int i = 0; i < buffer; i++)
	{
		if (matrix[i][list_p->size_t() - 1] != 0)
		{
			save = i;
			break;
		}
	}
	if (save == -1)
	{
		cout_everything(list_p);
		return;
	}
	recreate_way(list_p, matrix);
	fill_everything(list_p);
}