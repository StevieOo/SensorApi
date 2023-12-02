#ifndef AHT10TEMPERATURE_H
#define AHT10TEMPERATURE_H

#include "Aht10Driver.h"
#include "List.h"
#include "Measurement.h"
#include "Sensor.h"


class Aht10Temperature : public Sensor {
private:
	static Aht10Temperature instance;
	static bool instantiated;
	Aht10Driver driver;

	Aht10Temperature(void);

public:
	std::shared_ptr<Measurement> getMeasurement(List<MeasurementType>*);
	static Aht10Temperature* getInstance(void);
};

#endif