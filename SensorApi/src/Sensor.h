#ifndef SENSOR_H
#define SENSOR_H

#include <memory>

#include "List.h"
#include "Measurement.h"

class Sensor {
public:
	virtual std::shared_ptr<Measurement> getMeasurement(List<MeasurementType>*) = 0;
};

#endif