#ifndef logging
#define logging

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "statistics.h"

using namespace std;

const char* filename = "Logging.stat";

extern int VERBOSITY;

/*

The following is the expected enum declaration for VERBOSITY

(1) Lowest level. Ignore errors and do not log them. (aka QUIET)
(2) Level 2. Output error (default) (aka. NORMAL)
(3) Level 3. Output error and function name
(4) Level 4. Output error, function name and line number
(5) Level 5. Output error, function name, line number and stop the execution of the program by retuning false/-1/equivalent (aka. debug)

Small LED indicators are given as to what is "going on" in the logging function. This acts as a small GUI (or equivalent):

- Constant light no blinking: Logging in process. No errors logged.
- Blinking rapidly: Logging in process. Error logged with VERBOSITY 3-5
- Slow blinking: Logging in process. Error logged with VERBOSITY 1-2
- OFF: logging is not occuring at the moment (acts as a mini debugger since you will know when the logger function should actually work).

*/

struct FINGER {

        int GPIOPIN;
        int VALUE;

};

struct HAND {

        int hand;
        FINGER* finger;

};

struct Stats ;

class LOG {

public:

    static bool HLOG(HAND& object, int status, int VERBOSITY, const char functionName[], int lineNumber=0);
    static bool SLOG(Stats& object, int status, VERBOSITY, const char functionName[], int lineNumber=0);

private:

    static bool HANDLOG(HAND& object, int VERBOSITY, const char functionName[], int lineNumber=0);
    static bool STATSLOG(Stats& object, int VERBOSITY, const char functionName[], int lineNumber=0);
    static bool HERROR(HAND& object, int VERBOSITY, const char functionName[], int lineNumber=0);
    static bool SERROR(Stats& object, int VERBOSITY, const char functionName[], int lineNumber=0);

};

bool LOG::HLOG(HAND& object, int status=0, int VERBOSITY, const char functionName[], int lineNumber=0){

    if (status!=0){

        LOG::HERROR(object, VERBOSITY, functionName, lineNumber);
        return true;

    }
    else{

        LOG::HANDLOG(object, VERBOSITY,functionName, lineNumber);
        return true;

    }
}

bool LOG::SLOG(Stats& object, int status=0, int VERBOSITY, const char functionName[], int lineNumber=0){

    if (status!=0){

        LOG::SERROR(object, VERBOSITY,functionName, lineNumber);
        return true;

    }
    else{

        LOG::STATSLOG(object, VERBOSITY, functionName, lineNumber);
        return true;

    }
}


bool LOG::HANDLOG(HAND& hand, int VERBOSITY, const char functionName[], int lineNumber=0){

    ofstream outfile;
    outfile.open(filename,ios_base::app);

    if(!outfile.is_open())
    return LOG::HERROR(hand,functionName, lineNumber);

	switch (VERBOSITY){
		case 1:
			break;
		case 2:
			break;
		case 3:
			outfile<<"Logged from "<<functionName<<endl;
			break;
		case 4:
			outfile<<"Logged from "<<functionName<<endl;
			outfile<<"Line: "<<lineNumber<<endl;
			break;
		case 5:
			outfile<<"Logged from "<<functionName<<endl;
			outfile<<"Line: "<<lineNumber<<endl;
			break;

	}



    outfile<<"---------------------------------"<<endl;
    outfile<<"Hand and Fingers Settings"<<endl;
    outfile<<"---------------------------------\n"<<endl;
    
    time_t currentTime=time (0);
    char* localTime=ctime(&currentTime);


    outfile<<"Local Time: "<<localTime<<endl;
    outfile<<endl;
    
    outfile<<"Finger 1 Settings: Thumb"<<endl;
    outfile<<"Pin Number: "<<hand.finger[0].GPIOPIN<<endl;


    if (hand.finger[0].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[0].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }


    outfile<<"Finger 2 Settings: Index"<<endl;
    outfile<<"Pin Number: "<<hand.finger[1].GPIOPIN<<endl;
    
    if (hand.finger[1].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[1].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }



    outfile<<"Finger 3 Settings: Middle Finger"<<endl;
    outfile<<"Pin Number: "<<hand.finger[2].GPIOPIN<<endl;
    
    if (hand.finger[2].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[2].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }




    outfile<<"Finger 4 Settings: Ring Finger"<<endl;
    outfile<<"Pin Number: "<<hand.finger[3].GPIOPIN<<endl;
    
    if (hand.finger[3].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[3].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }



    outfile<<"Finger 5 Settings: Pinky (Little Finger)"<<endl;
    outfile<<"Pin Number: "<<hand.finger[4].GPIOPIN<<endl;
    
    if (hand.finger[4].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[4].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }

    outfile<<endl;

    outfile.close();
    
    return true;
}

bool LOG::STATSLOG(Stats& stats, int VERBOSITY, const char functionName[], int lineNumber=0){

    int s=0;
    ofstream outfile;
    outfile.open(filename,ios_base::app);

    if(!outfile.is_open())
    return LOG::SERROR(stats,functionName, lineNumber);   

    if (stats.minimum<0 || stats.maximum<0 || stats.average<0){
        
        return LOG::SERROR(stats,functionName, lineNumber);
    }

	
	switch (VERBOSITY){
		case 1:
			break;
		case 2:
			break;
		case 3:
			outfile<<"Logged from "<<functionName<<endl;
			break;
		case 4:
			outfile<<"Logged from "<<functionName<<endl;
			outfile<<"Line: "<<lineNumber<<endl;
			break;
		case 5:
			outfile<<"Logged from "<<functionName<<endl;
			outfile<<"Line: "<<lineNumber<<endl;
			break;

	}
    outfile<<"---------------------------------"<<endl;
    outfile<<"Statistics Log"<<endl;
    outfile<<"---------------------------------\n"<<endl;
    
    time_t currentTime=time (0);
    char* localTime=ctime(&currentTime);

    outfile<<"Local Time: "<<localTime<<endl;
    outfile<<endl;

    outfile << "Minimum: " << stats.minimum << endl;
    outfile << "Average: " << stats.average << endl;
    outfile << "Maximum: " << stats.maximum << endl;
    outfile << "Population Standard Deviation: " << stats.popStdDev << endl;
    outfile << "Sample Standard Deviation: " << stats.sampleStdDev << endl;
    outfile.close();

    return true;

}

bool LOG::HERROR(HAND& hand, int VERBOSITY, const char functionName[], int lineNumber=0){

    int s=0;
    ofstream outfile;
    outfile.open(filename,ios_base::app);

    if(!outfile.is_open()){

        return false;   
    }

	swtich (VERBOSITY){
		case 1:
			return true;
			break;
		case 2:
			break;
		case 3:
			outfile<<"Error received in "<<functionName<<endl;
			break;
		case 4:
			outfile<<"Error received in "<<functionName<<endl;
			outfile<<"on line "<<lineNumber<<endl;
			break;
		case 5:
			outfile<<"Error received in "<<functionName<<endl;
			outfile<<"on line "<<lineNumber<<endl;
			return false;
			break;
		
	}


    time_t currentTime=time (0);
    char* localTime=ctime(&currentTime);

    outfile<<"---------------------------------"<<endl;
    outfile<<"HAND ERROR LOGGING!"<<endl;
    outfile<<"---------------------------------\n"<<endl;

    outfile<<"Local Time: "<<localTime<<endl;
    outfile<<endl;
    outfile << "Error Finding Hand and Fingers Settings"<< endl;

    outfile.close();
    return true;

}


bool LOG::SERROR(Stats& stats, int VERBOSITY, const char functionName[], int lineNumber=0){

    int s=0;
    ofstream outfile;
    outfile.open(filename,ios_base::app);

    if(!outfile.is_open()){

        return false;   
    }


	swtich (VERBOSITY){
		case 1:
			return true;
			break;
		case 2:
			break;
		case 3:
			outfile<<"Error received in "<<functionName<<endl;
			break;
		case 4:
			outfile<<"Error received in "<<functionName<<endl;
			outfile<<"on line "<<lineNumber<<endl;
			break;
		case 5:
			outfile<<"Error received in "<<functionName<<endl;
			outfile<<"on line "<<lineNumber<<endl;
			return false;
			break;
	}



    outfile<<"---------------------------------"<<endl;
    outfile<<"STATISTICS ERROR LOGGING!"<<endl;
    outfile<<"---------------------------------\n"<<endl;

    time_t currentTime=time (0);
    char* localTime=ctime(&currentTime);
    
    
    outfile<<"Local Time: "<<localTime<<endl;
    outfile<<endl;
    outfile << "Error Calculating Statistics"<< endl;



    outfile.close();
    return true;
}

#endif