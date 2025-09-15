#include <iostream>
#include <algorithm> 

int main(int argc, char** argv){
	if (argc < 4) {
        	std::cerr << "Usage: " << argv[0] << " num1 num2 num3\n";
       		return 1;
	}
	int a = std::atoi(argv[1]);
	int b = std::atoi(argv[2]);
	int c = std::atoi(argv[3]);

	int max = std::max({a, b, c});
	int min = std::min({a, b, c});


	std::cout << "min: " <<  min << std::endl;
	std::cout << "max: " <<  max << std::endl; 

	return 0;
}
