#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

#include "Aht10Driver.h"

Aht10Driver::Aht10Driver(void) {
	initializeSensor();
	usleep(RESPONSE_WAIT);
	resetSensor();
}

bool Aht10Driver::initializeSensor(void) {
	bool result = false;
	uint8_t command[1]{ INITIALIZE_COMMAND };

	result = sendMessage(DEVICE_ADDRESS, command, 1);
	return result;
}

bool Aht10Driver::resetSensor(void) {
	bool result = false;
	uint8_t command[1]{ SOFT_RESET_COMMAND };

	result = sendMessage(DEVICE_ADDRESS, command, 1);
	return result;
}

bool Aht10Driver::getRawData(uint8_t* data) {
	uint8_t command{ TRIGGER_MEASUREMENT_COMMAND };
	bool receiveResult;
	bool sendResult;

	sendResult = sendMessage(DEVICE_ADDRESS, &command, 1);
	usleep(RESPONSE_WAIT);
	receiveResult = receiveMessage(DEVICE_ADDRESS, data, BUFFER_SIZE);
	return (sendResult && receiveResult);
}

bool Aht10Driver::getTemperature(double& measurement) {
	uint8_t rawData[BUFFER_SIZE];
	unsigned int temperatureData{ 0 };
	bool returnValue = getRawData(rawData);

	if (returnValue) {
		temperatureData = ((rawData[3] & 0x0F) << 16) | (rawData[4] << 8) | rawData[5];
		measurement = ((double)temperatureData * 200.0 / 1'048'576.0) - 50.0;
	}

	return returnValue;
}

bool Aht10Driver::getHumidity(double& measurement) {
	uint8_t rawData[BUFFER_SIZE];
	unsigned int humidityData{ 0 };
	bool returnValue = getRawData(rawData);

	if (returnValue) {
		humidityData = ((rawData[1] << 16) | (rawData[2] << 8) | rawData[3]) >> 4;
		measurement = (double)humidityData * 100.0 / 1'048'576.0;
	}

	return returnValue;
}

bool Aht10Driver::receiveMessage(const int address, uint8_t* buffer, const int length) {
	ssize_t result;

	int fd = open("/dev/i2c-1", O_RDWR);

	if (ioctl(fd, I2C_SLAVE, address) < 0) {
		return false;
	}

	result = read(fd, buffer, length);
	close(fd);
	return result == length;
}

bool Aht10Driver::sendMessage(const int address, uint8_t* buffer, const int length) {
	ssize_t result;

	int fd = open("/dev/i2c-1", O_RDWR);

	if (ioctl(fd, I2C_SLAVE, address) < 0) {
		return false;
	}

	result = write(fd, buffer, length);
	close(fd);
	return result == length;
}