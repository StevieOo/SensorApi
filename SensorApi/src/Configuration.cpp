#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Configuration.h"
#include "List.h"

void Configuration::parseError(std::string errorString) {
	std::cout << "[ERROR] " << errorString << std::endl;
	exit(2);
}

Configuration::Configuration(const char* filename) {
	portNumber = -1;
	refreshPeriod = -1;
	
	std::ifstream fileIn(filename);
	List<std::string> lineComponents;

	if (fileIn.is_open()) {
		std::string line;

		while (std::getline(fileIn, line)) {
			// Transform to lower case. Replace whitepace with comma.
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			std::replace(line.begin(), line.end(), ' ', ',');
			std::replace(line.begin(), line.end(), '\t', ',');
			std::replace(line.begin(), line.end(), '\r', ',');

			std::stringstream lineStream(line);

			//Place string fragments into deque.
			std::string fragment;
			while (lineStream.good()) {
				getline(lineStream, fragment, ',');
				if ("" != fragment)
					lineComponents.push_back(fragment);
			}

			if (lineComponents.empty()) continue;

			std::string parameter = lineComponents.front()->data;
			lineComponents.pop_front();

			// Load variable values.
			if ("port_number" == parameter) {
				try {
					portNumber = std::stoi(lineComponents.front()->data);
				}
				catch (...) {
					parseError("Unable to read port number.");
				}
			}
			else if ("refresh_rate" == parameter) {
				try {
					refreshPeriod = std::stoi(lineComponents.front()->data);
				}
				catch (...) {
					parseError("Unable to read refresh rate.");
				}
			}
			else if ("temperature_sensor" == parameter) {
				try {
					sensorStrings.push_back(lineComponents.front()->data);
				}
				catch (...) {
					parseError("Unable to read temperature sensor parameters.");
				}
			}
			else if ("humidity_sensor" == parameter) {
				try {;
					sensorStrings.push_back(lineComponents.front()->data);
				}
				catch (...) {
					parseError("Unable to read humidity sensor parameters.");
				}
			}
			if (!lineComponents.empty())
				lineComponents.clear();
		}
	}
	else {
		parseError("Unable to open configuration file. Check the path and file name.");
	}
	checkConfiguration();
}

void Configuration::checkConfiguration(void) {
	if (portNumber == -1) {
		std::cout << "[WARNING] Port number was not found in configuration file.  Using default (100).\n";
		portNumber = 100;
	}
	if (refreshPeriod == -1) {
		std::cout << "[WARNING] Refresh rate was not found in configuration file.  Using default (10 sec).\n";
		refreshPeriod = 10;
	}
	if (sensorStrings.empty()) {
		parseError("No valid temperature or humidity sensor configuration was found.");
	}
}

int Configuration::getPortNumber(void) {
	return portNumber;
}

int Configuration::getRefreshPeriod(void) {
	return refreshPeriod;
}

List<std::string>* Configuration::getEntries() {
	return &sensorStrings;
}