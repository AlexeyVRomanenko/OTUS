#include <iostream>
#include <ffinder/ffinder.h>

int main(int argc, char** cmd_line)
{
	if (argc == 2)
	{
		auto finder = ffinder::FilesDuplicateFinder::Instance(cmd_line[1]);
		if (!finder)
			return 1;

		std::cout << finder->GetOutput();
	}	

	return 0;
}