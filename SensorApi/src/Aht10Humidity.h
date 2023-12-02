#ifndef AHT10HUMIDITY_H
#define AHT10HUMIDITY_H


#include <memory>

#include "Aht10Driver.h"
#include "List.h"
#include "Measurement.h"
#include "Sensor.h"

class Aht10Humidity : public Sensor {
private:
	static Aht10Humidity instance;
	static bool instantiated;
	Aht10Driver driver;

	Aht10Humidity(void);

public:
	std::shared_ptr<Measurement> getMeasurement(List<MeasurementType>*) override;
	static Aht10Humidity* getInstance(void);
};

#endif