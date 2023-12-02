#ifndef WEATHER_DATA_H
#define WEATHER_DATA_H

#include <memory>

#include "List.h"
#include "Measurement.h"

class WeatherData {
private:
	std::shared_ptr<Measurement> currentTemperature;
	std::shared_ptr<Measurement> maximumTemperature;
	std::shared_ptr<Measurement> minimumTemperature;
	std::shared_ptr<Measurement> currentHumidity;
	std::shared_ptr<Measurement> maximumHumidity;
	std::shared_ptr<Measurement> minimumHumidity;
	void updateMeasurements(std::shared_ptr<Measurement>*, std::shared_ptr<Measurement>*, 
		std::shared_ptr<Measurement>*, std::shared_ptr<Measurement>*);

public:
	WeatherData(void);
	~WeatherData(void);
	std::shared_ptr<Measurement>  getCurrentTemperature(void);
	std::shared_ptr<Measurement>  getMaximumTemperature(void);
	std::shared_ptr<Measurement>  getMinimumTemperature(void);
	std::shared_ptr<Measurement>  getCurrentHumidity(void);
	std::shared_ptr<Measurement>  getMaximumHumidity(void);
	std::shared_ptr<Measurement>  getMinimumHumidity(void);
	void updateWeatherData(List<std::shared_ptr<Measurement>>*);
};
#endif