#include "stock.h"

int main (int argc, char *argv[])
{
	if (argc != 2) // we want a second argument
		cout << "USage : "<< argv[0] << " <file_name>";
	else
	{
		stock s (argv[1]);
	}
}
