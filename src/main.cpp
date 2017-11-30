#include <main.h>

/* -------------------------------------------------------------OUR WORK START---------------------------------------------------------------------- */

#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>

#include "statistics.h"
#include "logging.h"

using namespace std;

struct Stats ;

/* -------------------------------------------------------------OUR WORK END---------------------------------------------------------------------- */
//Sets up the gpioSetup object
void initGpioSetup (gpioSetup* obj){
	obj->pinNumber	= -1;
	obj->pinValue	= 0;
	obj->pinDir		= 0;
	
	obj->bPwm		= 0;
	obj->pwmFreq	= 0;
	obj->pwmDuty	= 0;

	obj->verbose 	= FASTGPIO_DEFAULT_VERBOSITY;
	obj->debug 		= FASTGPIO_DEFAULT_DEBUG;

	obj->cmdString 	= new char[255];
}

//Called whenever not enough arguments are entered
void usage(const char* progName) {
	printf("Edited by Shivansh Vij for RCTiming\n");
	printf("Usage:\n");
	printf("RCTiming <gpio to read from> <gpio to read from>\n");
	printf("\n");
}

void print(int verbosity, char* cmd, int pin, char* val){
	if 	(	verbosity != FASTGPIO_VERBOSITY_QUIET &&
			verbosity != FASTGPIO_VERBOSITY_JSON
		) 
	{
		printf(FASTGPIO_STDOUT_STRING, cmd, pin, val);
	}
	else if ( verbosity == FASTGPIO_VERBOSITY_JSON ) {
		printf(FASTGPIO_JSON_STRING, cmd, pin, val);
	}
}

// function to run gpio commands
int gpioRun(gpioSetup* setup){
	int status	= EXIT_SUCCESS;
	FastGpio	* gpioObj;
	// object setup
	gpioObj = new FastGpioOmega2();
	char* 		valString = new char[255];
	// Modify here to point to Omega or Omega2 Object. 
	// object setup
	gpioObj->SetVerbosity(setup->verbose == FASTGPIO_VERBOSITY_ALL ? 1 : 0);
	gpioObj->SetDebugMode(setup->debug);

	// object operations	
	switch (setup->cmd) {
		case GPIO_CMD_SET:
			gpioObj->SetDirection(setup->pinNumber, 1); // set to output
			gpioObj->Set(setup->pinNumber, setup->pinValue);

			strcpy(valString, (setup->pinValue == 1 ? "1" : "0") );
			break;

		case GPIO_CMD_READ:
			gpioObj->Read(setup->pinNumber, setup->pinValue);
			strcpy(valString, (setup->pinValue == 1 ? "1" : "0") );
			//cout << "valString: " << valString << endl;
			break;

		case GPIO_CMD_SET_DIRECTION:
			gpioObj->SetDirection(setup->pinNumber, setup->pinDir); // set pin direction
			strcpy(valString, (setup->pinDir == 1 ? "output" : "input") );
			//cout << "valString: " << valString << endl;
			break;
		default:
			status = EXIT_FAILURE;
			break;
	}

	/*if (status != EXIT_FAILURE) {
		print(setup->verbose, setup->cmdString, setup->pinNumber, valString);
	}*/
	sscanf(valString, "%d", &status);
	// clean-up
	delete valString;
	return status;
}

// function to read any existing pid notes and kill the child processes
int killOldProcess(int pinNum){
	char 	pathname[255];
	char	line[255];
	char	cmd[255];
	int 	pid;
	std::ifstream myfile;

	// determine thef file name and open the file
	snprintf(pathname, sizeof(pathname), PID_FILE, pinNum);
	myfile.open (pathname);

	// read the file
	if ( myfile.is_open() ) {
		// file exists, check for pid
		myfile.getline(line, 255);
		pid = atoi(line);

		// kill the process
		if (pid > 0)
		{
			sprintf(cmd, "kill %d >& /dev/null", pid);
			system(cmd);
			if (FASTGPIO_VERBOSE > 0) printf("Exiting current pwm process (pid: %d)\n", pid);
		}
	}


	return EXIT_SUCCESS;
}

// function to kill any old processes, based on which command is being run
int checkOldProcess(gpioSetup *setup){
	switch (setup->cmd) {
		case GPIO_CMD_SET:
		case GPIO_CMD_SET_DIRECTION:
		case GPIO_CMD_PWM:
			// kill the old process
			killOldProcess(setup->pinNumber);
			break;

		default:
			// do nothing
			break;
	}

	return EXIT_SUCCESS;
}

/* -------------------------------------------------------------OUR WORK START---------------------------------------------------------------------- */
long RCTimer(gpioSetup* setup, int PIN){
		long result = 0;
		int status = 0;
		//Set pin to output
		setup->cmd 		= GPIO_CMD_SET_DIRECTION;
		setup->pinDir 	= 1;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_SET_DIR);
		setup->pinNumber = PIN;
		status = gpioRun(setup);

		usleep(500);

		//Set pin to high output
		setup->cmd 		= GPIO_CMD_SET;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_SET);
		setup->pinValue = 1;
		status = gpioRun(setup);

		usleep(500);

		//Set pin to input
		setup->cmd 		= GPIO_CMD_SET_DIRECTION;
		setup->pinDir 	= 0;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_SET_DIR);
		status = gpioRun(setup);

		usleep(500);

		//Read the RCTime value
		setup->cmd 		= GPIO_CMD_READ;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_READ);
		while(gpioRun(setup)){
			result++;
		}
		return result;
}

int main(int argc, char* argv[]){
	int 		status;
	int 		ch;

	const char 	*progname;
	char*		val 	= new char[255];
	
	gpioSetup* 	setup 	= new gpioSetup;

	// reset gpio setup and set defaults
	initGpioSetup(setup);

	setup->verbose 		= FASTGPIO_DEFAULT_VERBOSITY;
	setup->debug 		= FASTGPIO_DEFAULT_DEBUG;

	// save the program name
	progname = argv[0];	

	// advance past the option arguments
	argc 	-= optind;
	argv	+= optind;

	if(argc < 2){
		printf("Enter a pin number.\n");
		return -1;
	}
	cout << "| FINGER |\t| RESISTANCE VALUE |\t| CALCULATED ANGLE";

	// check for any pwm processes already running on this pin
	status = checkOldProcess(setup);
	while(true){
		long VALUE = RCTimer(setup, atoi(argv[1]));
		cout << "| 1 |\t| " << VALUE << " |\t| " << VALUE/15 << " |" << endl;
		usleep(1000*50);
	}

	// clean-up
	delete 	val;
	delete 	setup;

	return 0;
}
/* -------------------------------------------------------------OUR WORK END---------------------------------------------------------------------- */