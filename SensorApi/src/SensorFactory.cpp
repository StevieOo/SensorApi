#include "SensorFactory.h"
#include "Aht10Humidity.h"
#include "Aht10Temperature.h"

SensorFactory::SensorFactory(void) {}

Sensor* SensorFactory::getSensor(std::string sensorString) {
	Sensor* returnSensor = nullptr;
	
	if ("aht10_temperature" == sensorString) {
		return Aht10Temperature::getInstance();
	}
	else if ("aht10_humidity" == sensorString) {
		return Aht10Humidity::getInstance();
	}
	
	return returnSensor;
}