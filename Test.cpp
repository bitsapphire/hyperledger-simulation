#include <iostream>
#include <iomanip>
#include "pool.h"

#define test1

int main()
{
#ifdef test1
	hyperledger::server::pool* my_pool = new hyperledger::server::pool();
	my_pool->initialize_nodes(31, true);
	my_pool->start_pool(10, 1, 5);

#endif


#ifdef test2
	std::random_device rd;
	std::mt19937 gen(rd());

	std::normal_distribution<> d(150, 10);

	std::map<int, int> hist;

	for (int n = 0; n<1000000; ++n)
	{
		++hist[static_cast<__int32>(std::round(d(gen)))];
		//for (auto i = hist.begin(); i != hist.end(); i++)
		//{
		//	std::cout << i->first << " " << i->second << std::endl;
		//}
		//system("PAUSE");
	}


	for (auto p : hist)
	{
		std::cout << std::fixed << std::setprecision(1) << std::setw(2)
			<< p.first << ' ' << std::string(p.second / 1000, '*') << '\n';
	}
#endif

	system("PAUSE");
	return 0;
}