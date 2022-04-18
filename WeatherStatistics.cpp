#include <iostream>
#include <ctime>
#include "WeatherStat.h"

int main()
{
	try {
		WStat::WeatherStatistics ws;
		ws.loadData();
	}
	catch (std::exception e) {
		std::cout << e.what();
	}

	return 0;
}