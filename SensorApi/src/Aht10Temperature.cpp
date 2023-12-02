#include <algorithm>

#include "Aht10Temperature.h"

Aht10Temperature Aht10Temperature::instance;
bool Aht10Temperature::instantiated = false;

Aht10Temperature::Aht10Temperature(void) {
	driver = Aht10Driver();
}

std::shared_ptr<Measurement> Aht10Temperature::getMeasurement(List<MeasurementType>* _list) {
	std::shared_ptr<Measurement> returnValue = nullptr;
	bool result;
	double temperature;

	Iterator<MeasurementType>* iterator = _list->createIterator();

	while (!iterator->isDone()) {
		if (iterator->currentItem() == MeasurementType::TEMPERATURE) {
			result = driver.getTemperature(temperature);
			if (result)
				returnValue = std::shared_ptr<Measurement>(new Measurement(MeasurementType::TEMPERATURE, temperature));
			break;
		}
		iterator->next();
	}

	return returnValue;
}

Aht10Temperature* Aht10Temperature::getInstance(void) {
	if (!instantiated) {
		instantiated = true;
		instance = Aht10Temperature();
	}
	return &instance;
}