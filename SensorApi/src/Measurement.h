#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <limits>
#include <memory>

enum MeasurementType {
	TEMPERATURE,
	HUMIDITY
};

class Measurement {
private:
	const MeasurementType measurementType;
	const double measurementValue;

public:
	Measurement(MeasurementType, double);
	MeasurementType getMeasurementType(void);
	double getMeasurementValue(void);

	static double checkAndReturnMeasurement(std::shared_ptr<Measurement>);
};

#endif