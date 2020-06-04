#pragma once
#include "find_short_way.h"

using namespace std;

List<place>* read_file(ifstream& input_file)
{
	ifstream check("Text_input.txt", ios::binary | ios::ate);
	if (check.tellg() == 0)
		throw out_of_range("No symbols in file");
	check.close();
	List<place>* list_s = new List<place>();
	string name;
	char buf = 1;
	int counter = 0;
	int saving = 0;
	input_file.seekg(0);
	Node<place>* save1 = NULL, * save2 = NULL;
	Node<place>* list_iterator = NULL;
	while (!input_file.eof())
	{
		for (int i = 0; i < 2; i++)
		{
			buf = 1;
			while (buf != ';')
			{
				input_file.get(buf);
				if ((buf != ';') && (buf != '\n'))
					name.push_back(buf);
				else
				{
					if (check_name(list_s, name))
					{
						place new_place(name);// Source pushing in front of List and becoming root
						if (name == "S")
						{
							list_s->push_front(&new_place);
							i == 0 ? save1 = list_s->Get_Root() : save2 = list_s->Get_Root();
						}
						else
						{
							if (list_s->Get_Last())
							{
								if (list_s->Get_Last()->value.name == "T")//if element T (sink) already exist, new element pushing before last element, and sink will be still on last position
								{
									list_s->push_pre_back(&new_place);
									i == 0 ? save1 = list_s->Get_Last()->prev : save2 = list_s->Get_Last()->prev;
								}
								else
								{
									list_s->push_back(&new_place);
									i == 0 ? save1 = list_s->Get_Last() : save2 = list_s->Get_Last();
								}
							}
							else
							{
								list_s->push_back(&new_place);
								i == 0 ? save1 = list_s->Get_Last() : save2 = list_s->Get_Last();
							}
						}
					}
					list_iterator = list_s->Get_Root();
					while (list_iterator != NULL)
					{
						if (list_iterator->value.name == name)
						{
							i == 0 ? save1 = list_iterator : save2 = list_iterator;
							break;
						}
						else
							list_iterator = list_iterator->next;
					}
					name.clear();
				}
			}
		}
		input_file >> saving;
		if (saving >= 0)
			throw invalid_argument("Incorrect data in file");
		save1->value.push_back_edge(&save1->value, &save2->value, saving);//pushing edge to lists of edges
		input_file.get(buf);
		name.clear();
	}
	try
	{
		find_place_pos("S", list_s);//checking existence of source
	}
	catch (out_of_range exception)
	{
		throw invalid_argument("In this net doesn't exist source");
	}
	try
	{
		find_place_pos("T", list_s);//checking existence of sink
	}
	catch (out_of_range exception)
	{
		throw invalid_argument("In this net doesn't exist sink");
	}
	int** matrix = fill_main_matrix(list_s);
	bool check_ways = 0;
	for (int i = 0; i < list_s->size_t() - 1; i++)
	{
		if (matrix[list_s->size_t() - 1][i] != 0)
			throw invalid_argument("In this net exist a loop");
		if (matrix[i][list_s->size_t() - 1] != 0)
			check_ways = 1;
	}
	if (check_ways)
		throw invalid_argument("In this net doesn't exist way from source to sink");
	return list_s;
}
