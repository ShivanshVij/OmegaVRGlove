#include <main.h>

/* -------------------------------------------------------------OUR WORK START---------------------------------------------------------------------- */

#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>


#include "logging.h"
#include "statistics.h"

using namespace std;

struct FINGER ;

struct HAND ;

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
long RCTimer(HAND& hand, gpioSetup* setup, int PIN){
		long result = 0;
		int status = 0;
		//Set pin to output
		setup->cmd 		= GPIO_CMD_SET_DIRECTION;
		setup->pinDir 	= 1;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_SET_DIR);
		setup->pinNumber = PIN;
		status = gpioRun(setup);

		if(status != 0){
			LOG::HLOG(hand, "RCTIMER", 1, 3, 166);
		}

		usleep(500);

		//Set pin to high output
		setup->cmd 		= GPIO_CMD_SET;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_SET);
		setup->pinValue = 1;
		status = gpioRun(setup);

		if(status == 0){
			LOG::HLOG(hand, "RCTIMER", 1, 3, 180);
		}

		usleep(500);

		//Set pin to input
		setup->cmd 		= GPIO_CMD_SET_DIRECTION;
		setup->pinDir 	= 0;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_SET_DIR);
		status = gpioRun(setup);

		if(status != 0){
			LOG::HLOG(hand, "RCTIMER", 1, 3, 190);
		}

		usleep(500);

		//Read the RCTime value
		setup->cmd 		= GPIO_CMD_READ;
		strcpy(setup->cmdString, FASTGPIO_CMD_STRING_READ);

		while(gpioRun(setup)){
			result++;

			if(result > 10000){
				LOG::HLOG(hand, "RCTIMER", 1, 5, 203);
				break;
			}
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


	HAND hand = {0};
   	hand.hand = 1;
	hand.finger = new FINGER[5];
	Stats FINGER1STATS = {0};
	Stats FINGER2STATS = {0};
	Stats FINGER3STATS = {0};
	Stats FINGER4STATS = {0};
	Stats FINGER5STATS = {0};
	for(int i = 0; i < 1000; i++){
		FINGER1STATS.dataset[i] = 0;
		FINGER2STATS.dataset[i] = 0;
		FINGER3STATS.dataset[i] = 0;
		FINGER4STATS.dataset[i] = 0;
		FINGER5STATS.dataset[i] = 0;
	}
	int statsStructSize = 1;

	//LOG::HLOG(hand);
    /*
        GPIO Pins:
        Thumb:finger[0]: 1
        Index:finger[1]: 2
        Middle:finger[2]: 3
        Ring:finger[3]: 19
        Pinky:finger[4]: 18
    */
    hand.finger[0].GPIOPIN = 1;
    hand.finger[1].GPIOPIN = 2;
    hand.finger[2].GPIOPIN = 11;
    hand.finger[3].GPIOPIN = 19;
	hand.finger[4].GPIOPIN = 18;
	//LOG::HLOG(hand);

    for(int i = 0; i < 5; i++){
		hand.finger[i].VALUE=0;
		//LOG::HLOG(hand);
	}

	/*if(argc < 2){
		printf("Enter a pin number.\n");
		LOG::HLOG(hand,1);
		return -1;
	}*/

	// check for any pwm processes already running on this pin
	status = checkOldProcess(setup);
	//LOG::HLOG(hand);
	int counter = 0;

	while(true){

		if(counter == 1000){
			LOG::HLOG(hand, "main", 0, 1, 279);
			LOG::SLOG(FINGER4STATS, "STATS::STATISTICS from main", 0, 1, 286);
			LOG::SLOG(FINGER5STATS, "STATS::STATISTICS from main", 0, 1, 287);
			// break;
			counter=0; // reset for sliding window stats
		}

		if(counter%50 == 0){
			LOG::HLOG(hand, "main", 0, 1, 285);
			LOG::SLOG(FINGER4STATS, "STATS::STATISTICS from main", 0, 1, 294);
			LOG::SLOG(FINGER5STATS, "STATS::STATISTICS from main", 0, 1, 295);
		}

		

		long VALUE1 = 0;//RCTimer(setup, hand.finger[0].GPIOPIN);
		//usleep(1000*100);
		long VALUE2 = 0;//RCTimer(setup, hand.finger[1].GPIOPIN);
		//usleep(1000*100);
		long VALUE3 = RCTimer(hand, setup, hand.finger[2].GPIOPIN);
		usleep(1000*100);
		long VALUE4 = RCTimer(hand, setup, hand.finger[3].GPIOPIN);
		usleep(1000*100);
		long VALUE5 = RCTimer(hand, setup, hand.finger[4].GPIOPIN);
		usleep(1000*100);

		// FINGER1STATS.dataset[counter] = VALUE1;
		// FINGER2STATS.dataset[counter] = VALUE2;
		// FINGER3STATS.dataset[counter] = VALUE3;
		FINGER4STATS.dataset[counter] = VALUE4;
		FINGER5STATS.dataset[counter] = VALUE5;

		// STATS::STATISTICS(FINGER1STATS, statsStructSize);
		// STATS::STATISTICS(FINGER2STATS, statsStructSize);
		// STATS::STATISTICS(FINGER3STATS, statsStructSize);
		STATS::STATISTICS(FINGER4STATS, statsStructSize);
		STATS::STATISTICS(FINGER5STATS, statsStructSize);

		cout << "| FINGER 1 |\t| FINGER 2 |\t| FINGER 3 |\t| FINGER 4 |\t| FINGER 5 |" << endl;
		cout << "| " << VALUE1 << " |\t\t| " << VALUE2 << " |\t\t| " << VALUE3 << " |\t\t| " << VALUE4 << " |\t\t| " << VALUE5 << " |" << endl;
		
		
		usleep(1000*250);

		counter++;
		if(statsStructSize < 1000){
			statsStructSize++;
		}
		
	}
	//LOG::HLOG(hand);
	
	cout << "PROGRAM ENDED WITH CLEANUP" << endl;
	//LOG::HLOG(hand);
	return 0;
}
/* -------------------------------------------------------------OUR WORK END---------------------------------------------------------------------- */