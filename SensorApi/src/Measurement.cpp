#include "Measurement.h"

Measurement::Measurement(MeasurementType _measurementType, double _measurement) :
	measurementType(_measurementType),
	measurementValue(_measurement)
{}

MeasurementType Measurement::getMeasurementType(void) {
	return measurementType;
}

double Measurement::getMeasurementValue(void) {
	return measurementValue;
}

double Measurement::checkAndReturnMeasurement(std::shared_ptr<Measurement> measurement) {
	double returnValue = std::numeric_limits<double>::quiet_NaN();
	if (measurement != nullptr) {
		returnValue = measurement->getMeasurementValue();
	}
	return returnValue;
}