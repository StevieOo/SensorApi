#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
//#include <list>

#include "List.h"

class Configuration {
private:
	int portNumber;
	int refreshPeriod;
	List<std::string> sensorStrings;

	void parseError(std::string errorString);
	void checkConfiguration(void);

public:
	Configuration(const char* filename);
	List<std::string>* getEntries(void);
	int getPortNumber(void);
	int getRefreshPeriod(void);

};

#endif