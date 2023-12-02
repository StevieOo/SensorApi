#ifndef WEB_API_H
#define WEB_API_H

#include "crow.h"
#include "WeatherData.h"

class WebApi {
private:
	crow::SimpleApp app;
	const int portNumber;
	WeatherData* weatherData;

	void bindRoot(void);
	void bindTemp(void);
	void bindRH(void);
	void bindAll(void);
	void bindMaxTemp(void);
	void bindMaxHumid(void);
	void bindMinTemp(void);
	void bindMinHumid(void);
	static double convertCtoF(double);
	static double checkAndReturnMeasurement(std::shared_ptr<Measurement>);
	void run(void);

public:
	WebApi(int, WeatherData*);
	~WebApi();
	void start(void);
	void stop(void);
};

#endif