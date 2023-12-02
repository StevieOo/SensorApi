#include "WeatherData.h"

WeatherData::WeatherData() {
	currentTemperature = nullptr;
	maximumTemperature = nullptr;
	minimumTemperature = nullptr;

	currentHumidity = nullptr;
	maximumHumidity = nullptr;
	minimumHumidity = nullptr;
}

WeatherData::~WeatherData() {
	currentTemperature.reset();
	maximumTemperature.reset();
	minimumTemperature.reset();

	currentHumidity.reset();
	maximumHumidity.reset();
	minimumHumidity.reset();
}

std::shared_ptr<Measurement> WeatherData::getCurrentTemperature(void) {
	return currentTemperature;
}

std::shared_ptr<Measurement> WeatherData::getMaximumTemperature(void) {
	return maximumTemperature;
}

std::shared_ptr<Measurement> WeatherData::getMinimumTemperature(void) {
	return minimumTemperature;
}


std::shared_ptr<Measurement>  WeatherData::getCurrentHumidity(void) {
	return currentHumidity;
}

std::shared_ptr<Measurement>  WeatherData::getMaximumHumidity(void) {
	return maximumHumidity;
}

std::shared_ptr<Measurement>  WeatherData::getMinimumHumidity(void) {
	return minimumHumidity;
}

void WeatherData::updateWeatherData(List<std::shared_ptr<Measurement>>* measurements) {
	Iterator<std::shared_ptr<Measurement>>* iterator = measurements->createIterator();

	while (!iterator->isDone()) {
		if (iterator->currentItem() != nullptr) {
			if (MeasurementType::TEMPERATURE == iterator->currentItem()->getMeasurementType()) {
				std::shared_ptr<Measurement> measurment = iterator->currentItem();
				updateMeasurements(&measurment, &currentTemperature, &maximumTemperature, &minimumTemperature);
			}
			else if (MeasurementType::HUMIDITY == iterator->currentItem()->getMeasurementType()) {
				std::shared_ptr<Measurement> measurment = iterator->currentItem();
				updateMeasurements(&measurment, &currentHumidity, &maximumHumidity, &minimumHumidity);
			}
			else {

			}
		}
		iterator->next();
	}

	measurements->clear();
}

void WeatherData::updateMeasurements(std::shared_ptr<Measurement>* newMeasurement, std::shared_ptr<Measurement>* currentMeasurement,
	std::shared_ptr<Measurement>* maximumMeasurement, std::shared_ptr<Measurement>* minimumMeasurement) {

	if (*currentMeasurement == nullptr) *currentMeasurement = *newMeasurement;
	if (*maximumMeasurement == nullptr) *maximumMeasurement = *newMeasurement;
	if (*minimumMeasurement == nullptr) *minimumMeasurement = *newMeasurement;

	if ((*maximumMeasurement)->getMeasurementValue() < (*newMeasurement)->getMeasurementValue()) {
		std::shared_ptr<Measurement> temporaryPtr = *maximumMeasurement;
		*maximumMeasurement = *newMeasurement;

		if (*minimumMeasurement != temporaryPtr && *currentMeasurement != temporaryPtr) {
			temporaryPtr.reset();
		}
	}

	if ((*minimumMeasurement)->getMeasurementValue() > (*newMeasurement)->getMeasurementValue()) {
		std::shared_ptr<Measurement>  temporaryPtr = *minimumMeasurement;
		*minimumMeasurement = *newMeasurement;

		if (*maximumMeasurement != temporaryPtr && *currentMeasurement != temporaryPtr) {
			temporaryPtr.reset();
		}
	}

	if (*maximumMeasurement != *currentMeasurement && *minimumMeasurement != *currentMeasurement) {
		currentMeasurement->reset();
	}

	*currentMeasurement = *newMeasurement;
}