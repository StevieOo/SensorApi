#include <limits>
#include <memory>

#include "Measurement.h"
#include "WebApi.h"

WebApi::WebApi(int _portNumber, WeatherData* _weatherData) :
	portNumber(_portNumber)
{
	weatherData = _weatherData;
	app.port(portNumber).multithreaded();
}

void WebApi::start(void) {
	bindRoot();
	bindTemp();
	bindRH();
	bindAll();
	bindMaxTemp();
	bindMaxHumid();
	bindMinHumid();
	bindMinTemp();

	std::thread t1(&WebApi::run, this);
	t1.detach();
}

void WebApi::stop(void) {
	app.stop();
}

void WebApi::bindRoot(void) {
	CROW_ROUTE(app, "/")([]() {
		return "SENSOR API\n\n"
			"This API sends sensor measurements that capture things like temperature and relative humidity.\n"
			"All data is returned in JSON format.  Minimum and maximum values are since device reset.\n\n"
			"Supported Functions:\n"
			"/Temp      Displays current temperature in deg. Celsius.  Use F parameter for Fahrenheit.\n"
			"/MinTemp   Displays minimum temperature in deg. Celsius.  Use F parameter for Fahrenheit.\n"
			"/MaxTemp   Displays maximum temperature in deg. Celsius.  Use F parameter for Fahrenheit.\n"
			"/RH        Displays current relative humidity as a percentage.\n"
			"/MinRH     Dislpays minimum relative humidity as a percentage.\n"
			"/MaxRH     Displays maximum relative humidity as a percentage.\n"
			"/AllData   Displays all data available.\n";
		});
}

void WebApi::bindTemp(void) {
	CROW_ROUTE(app, "/Temp")([&](const crow::request& req) {
		crow::json::wvalue json;

		if (req.url_params.get("F") != nullptr) {
			json["CurrentTemp"] = convertCtoF(checkAndReturnMeasurement(weatherData->getCurrentTemperature()));
		}
		else {
			json["CurrentTemp"] = checkAndReturnMeasurement(weatherData->getCurrentTemperature());
		}
		return json;
		});
}

void WebApi::bindRH(void) {

	CROW_ROUTE(app, "/RH")([&]() {
		crow::json::wvalue json;
		json["CurrentRH"] = checkAndReturnMeasurement(weatherData->getCurrentHumidity());
		return json;
		});
}

void WebApi::bindAll(void) {
	CROW_ROUTE(app, "/AllData")([&](const crow::request& req) {
		crow::json::wvalue json;

		if (req.url_params.get("F") != nullptr) {
			json["CurrentTemp"] = convertCtoF(checkAndReturnMeasurement(weatherData->getCurrentTemperature()));
			json["MinTemp"] = convertCtoF(checkAndReturnMeasurement(weatherData->getMinimumTemperature()));
			json["MaxTemp"] = convertCtoF(checkAndReturnMeasurement(weatherData->getMaximumTemperature()));
		}
		else {
			json["CurrentTemp"] = checkAndReturnMeasurement(weatherData->getCurrentTemperature());
			json["MinTemp"] = checkAndReturnMeasurement(weatherData->getMinimumTemperature());
			json["MaxTemp"] = checkAndReturnMeasurement(weatherData->getMaximumTemperature());
		}
		json["CurrentRH"] = checkAndReturnMeasurement(weatherData->getCurrentHumidity());
		json["MinRH"] = checkAndReturnMeasurement(weatherData->getMinimumHumidity());
		json["MaxRH"] = checkAndReturnMeasurement(weatherData->getMaximumHumidity());
		return json;
		});
}

void WebApi::bindMinHumid(void) {
	CROW_ROUTE(app, "/MinRH")([&]() {
		crow::json::wvalue json;
		json["MinRH"] = checkAndReturnMeasurement(weatherData->getMinimumHumidity());
		return json;
		});
}

void WebApi::bindMaxHumid(void) {
	CROW_ROUTE(app, "/MaxRH")([&]() {
		crow::json::wvalue json;
		json["MaxRH"] = checkAndReturnMeasurement(weatherData->getMaximumHumidity());
		return json;
		});
}

void WebApi::bindMinTemp(void) {
	CROW_ROUTE(app, "/MinTemp")([&](const crow::request& req) {
		crow::json::wvalue json;

		if (req.url_params.get("F") != nullptr) {
			json["MinTemp"] = convertCtoF(checkAndReturnMeasurement(weatherData->getMinimumTemperature()));
		}
		else {
			json["MinTemp"] = checkAndReturnMeasurement(weatherData->getMinimumTemperature());
		}
		return json;
		});
}

void WebApi::bindMaxTemp(void) {
	CROW_ROUTE(app, "/MaxTemp")([&](const crow::request& req) {
		crow::json::wvalue json;

		if (req.url_params.get("F") != nullptr) {
			json["MaxTemp"] = convertCtoF(checkAndReturnMeasurement(weatherData->getMaximumTemperature()));
		}
		else {
			json["MaxTemp"] = checkAndReturnMeasurement(weatherData->getMaximumTemperature());
		}
		return json;
		});
}

double WebApi::convertCtoF(double input) {
	return (input * 9.0 / 5.0) + 32.0;
}

double WebApi::checkAndReturnMeasurement(std::shared_ptr<Measurement> measurement) {
	double returnValue = std::numeric_limits<double>::quiet_NaN();
	if (measurement != nullptr) {
		returnValue = measurement->getMeasurementValue();
	}
	return returnValue;
}

WebApi::~WebApi(void) {

}

void WebApi::run(void) {
	auto thread = app.run_async();
}