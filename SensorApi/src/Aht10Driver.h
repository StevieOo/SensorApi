#ifndef AHT10DRIVER_H
#define AHT10DRIVER_H

#include <cstdint>

class Aht10Driver {
private:
	static constexpr char DEVICE_ADDRESS				= 0x38;		// Device I2C address.
	static constexpr uint8_t INITIALIZE_COMMAND			= 0xE1;		// Intialize sensor command.
	static constexpr uint8_t TRIGGER_MEASUREMENT_COMMAND	= 0xAC;		// Trigger sensor measurement command.
	static constexpr uint8_t SOFT_RESET_COMMAND			= 0xBA;		// Reset sensor command.
	static constexpr int RESPONSE_WAIT					= 500'000;	// Time to wait after command is sent (micro s).
	static constexpr int BUFFER_SIZE					= 6;		// This is the size (in bytes) of the I2C buffer.  

	bool getRawData(uint8_t*);
	bool initializeSensor(void);
	bool resetSensor(void);
	bool receiveMessage(const int, uint8_t*, const int);
	bool sendMessage(const int, uint8_t*, const int);

public:
	Aht10Driver(void);
	
	bool getTemperature(double&);
	bool getHumidity(double&);
};


#endif