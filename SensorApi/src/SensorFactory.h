#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include <string>

#include "Sensor.h"

class SensorFactory {
public:
	SensorFactory(void);
	Sensor* getSensor(std::string);
};

#endif