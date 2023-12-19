DESCRIPTION
This repo contains the source code for an application that reads data from ambient sensor and publishes to the internet using a web API.  This application was developed for the Raspberry Pi, and currently supports AHT10 Temperature/Humidity sensor.


PREREQUISITES
	· Device running Linux (Tested using Debian GNU/Linux 12 [bookworm] and
	  Ubuntu 20.04.6 LTS.)
	· Boost V1.4 or higher (Hint: run "sudo apt-get install libboost-all-dev"
	  to install.)
	· GCC compiler
	· CMAKE V3.15 or higher 
	· Git
	· Make


INSTALLATION INSTRUCTIONS
	1. Clone the repository by typing 
	   "git clone https://github.com/StevieOo/SensorApi.git" in the command
	   line. This will create a folder named "SensorApi".
	2. Navigate to "SensorApi/SensorApi" folder.
	3. Create a build folder here by typing "mkdir build".
	4. Navigate to newly created "build" directory.
	5. Build the makefile with CMake using the command "cmake ..".
	6. Build the project by typing "make". This will create an executable
	   named "SensorApi" in the "SensorApi/SensorApi" folder.


RUN INSTRUCTIONS
	1. Navigate to "SensorApi/SensorApi"folder.
	2. Enter "./SensorApi config" into the terminal to start program
	   (alternatively, enter "./SensorApi" to view error message). The 
	   SensorApi status should now be visible in the terminal. Note, this 
	   application  must continue to run in order to use the web API.
	3. To view the API information, on the same machine running the SensorApi 
	   application, open a web browser and enter "localhost:15000" into the 
	   address bar.
	4. Assets can be viewed by entering "localhost:15000/[ASSET]" into the web
	   browser's address bar (e.g. to view all data enter
	   "localhost:15000/AllData").

	NOTE:  To view temperature and humidity data, this application must be 
	       installed and run on a Raspberry Pi with an AHT10 sensor connected
	       to the external I2C pins.  If this setup is not available, the
	       SensorApi application will run, however, temperature and humidity 
	       data will not be displayed.


REPOSITORY FILE STRUCTURE

	SensorApi/					Root folder.
		|
		|--crow/				Contains CrowCpp (web API) library.
		|
		|--SensorApi/				Contains All SensorApi files.
			|
			|--src/				Contains All SensorApi source code
			|
			|--CMakeLists.txt		CMake list file for build.
			|
			|--config			Application configuration file.
