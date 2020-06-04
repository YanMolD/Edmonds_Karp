#include "reading.h"
#include "Ed_K_alg.h"

using namespace std;

int main()
{
	ifstream input_file("Text_input.txt");
	List<place>* list_of_p = read_file(input_file);
	fill_everything(list_of_p);
	return 1;
}