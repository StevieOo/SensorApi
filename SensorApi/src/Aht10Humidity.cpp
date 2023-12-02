#include <algorithm>

#include "Aht10Humidity.h"

Aht10Humidity Aht10Humidity::instance;
bool Aht10Humidity::instantiated = false;

Aht10Humidity::Aht10Humidity(void) {
	driver = Aht10Driver();
}

std::shared_ptr<Measurement> Aht10Humidity::getMeasurement(List<MeasurementType>* _list) {
	std::shared_ptr<Measurement> returnValue = nullptr;
	bool result;
	double humidity;

	Iterator<MeasurementType>* iterator = _list->createIterator();

	while (!iterator->isDone()) {
		if (iterator->currentItem() == MeasurementType::HUMIDITY) {
			result = driver.getHumidity(humidity);
			if (result)
				returnValue = std::shared_ptr<Measurement>(new Measurement(MeasurementType::HUMIDITY, humidity));
			break;
		}
		iterator->next();
	}

	return returnValue;
}

Aht10Humidity* Aht10Humidity::getInstance(void) {
	if (!instantiated) {
		instantiated = true;
		instance = Aht10Humidity();
	}

	return &instance;
}