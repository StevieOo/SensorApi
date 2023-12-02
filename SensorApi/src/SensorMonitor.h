#ifndef SENSOR_MONITOR
#define SENSOR_MONITOR

#include <string>
#include <thread>

#include "List.h"
#include "Sensor.h"
#include "SensorFactory.h"
#include "WeatherData.h"

class SensorMonitor {
private:
	WeatherData* weatherData;
	const int POLLING_PERIOD;
	List<std::shared_ptr<Measurement>>* currentMeasurements;
	List<Sensor*> sensorList;
	bool runMonitor;
	SensorFactory factory;
	std::thread monitorThread;

	std::string getDataString(std::shared_ptr<Measurement>);
	void printData(void);
	void run(void);

public:
	List<MeasurementType> MEASUREMENTS_TO_COLLECT;

	SensorMonitor(void) = default;
	SensorMonitor(List<std::string>*, int, WeatherData*);
	~SensorMonitor(void);

	void start(void);
	void stop(void);
};

#endif