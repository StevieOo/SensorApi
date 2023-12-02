#include <iostream>
#include <thread>

#include "SensorMonitor.h"

SensorMonitor::SensorMonitor(List<std::string>* _sensorStringList, int _pollingPeriod, WeatherData* _weatherData) :
	POLLING_PERIOD(_pollingPeriod)
{
	MEASUREMENTS_TO_COLLECT.push_back(MeasurementType::HUMIDITY);
	MEASUREMENTS_TO_COLLECT.push_back(MeasurementType::TEMPERATURE);

	currentMeasurements = new List<std::shared_ptr<Measurement>>;
	weatherData = _weatherData;

	Iterator<std::string>* iterator = _sensorStringList->createIterator();

	while (!iterator->isDone()) {
		if ("" != iterator->currentItem()) sensorList.push_back(factory.getSensor(iterator->currentItem()));
		iterator->next();
	}
}

SensorMonitor::~SensorMonitor(void) {
	delete currentMeasurements;
}

void SensorMonitor::start(void) {
	runMonitor = true;
	std::thread t1(&SensorMonitor::run, this);
	t1.detach();
}

void SensorMonitor::stop(void) {
	runMonitor = false;
}

void SensorMonitor::run(void) {
	while (runMonitor) {

		Iterator<Sensor*>* iterator = sensorList.createIterator();

		while (!iterator->isDone()) {
			if (iterator->currentItem() != nullptr)
				currentMeasurements->push_back(iterator->currentItem()->getMeasurement(&MEASUREMENTS_TO_COLLECT));
			iterator->next();
		}

		weatherData->updateWeatherData(currentMeasurements);
		printData();
		std::this_thread::sleep_for(std::chrono::seconds(POLLING_PERIOD));
	}
}

void SensorMonitor::printData(void) {
	std::cout << "Current Temperature: " << getDataString(weatherData->getCurrentTemperature()) << std::endl;
	std::cout << "Maximum Temperature: " << getDataString(weatherData->getMaximumTemperature()) << std::endl;
	std::cout << "Minimum Temperature: " << getDataString(weatherData->getMinimumTemperature()) << std::endl;
	std::cout << "Current Humidity:    " << getDataString(weatherData->getCurrentHumidity()) << std::endl;
	std::cout << "Maximum Humidity:    " << getDataString(weatherData->getMaximumHumidity()) << std::endl;
	std::cout << "Minimum Humidity:    " << getDataString(weatherData->getMinimumHumidity()) << std::endl;
	std::cout << "\033[6A";  // Move cursor up 6 lines to overwrite on next call.
}

std::string SensorMonitor::getDataString(std::shared_ptr<Measurement> measurement) {
	return ((measurement != nullptr) ? std::to_string(measurement->getMeasurementValue()) : "ERROR");
}