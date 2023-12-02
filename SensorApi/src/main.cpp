#include <iostream>

#include "Configuration.h"
#include "List.h"
#include "SensorMonitor.h"
#include "WeatherData.h"
#include "WebApi.h"

int main(int argc, char* argv[]) {
	Configuration* configuration;
	SensorMonitor* sensorMonitor;
	WeatherData* weatherData;
	WebApi* webApi;

	if (argc != 2) {
		std::cout << "Invalid command line arguements.\n\nCorrect useage is:\n\n\t" <<
			"SensorApi [FILENAME]\n\nwhere [FILENAME] is the path of the configuration file.\n\n";
		return 1;
	}

	system("clear");

	//Load configuration
	configuration = new Configuration(argv[1]);
	std::cout << "Configuration file \"" << argv[1] << "\" was loaded." << std::endl;
	
	// Create Objects
	weatherData = new WeatherData();
	sensorMonitor = new SensorMonitor(configuration->getEntries(), configuration->getRefreshPeriod(), weatherData);
	webApi = new WebApi(configuration->getPortNumber(), weatherData);
	
	// Start Sensor Monitor Thread
	sensorMonitor->start();
	std::cout << "Measurement monitor started.  Refresh period set to " << configuration->getRefreshPeriod()
		<< " seconds.\n";

	// Start API
	webApi->start();
	std::cout << "\n\nPRESS [ENTER] TO EXIT.\n\n";

	// Wait until console input
	std::cin.get();

	// Stop Data Monitor and API
	sensorMonitor->stop();
	webApi->stop();

	// Clean up.
	delete configuration;
	delete weatherData;
	delete sensorMonitor;
	delete webApi;

	system("clear");

	return 0;
}