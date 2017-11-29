#ifndef RCTiming
#define RCTiming

#include <ugpio/ugpio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

/*----------------------------------- INPUT = 0 -------------------------------- OUTPUT = 1 -----------------------------------*/

struct FINGER {
    int GPIOPIN;
    int IO;
    int VALUE;
};

struct HAND{
    int hand;
    FINGER* finger;
};


//extern int buffer = 0;

class RCTIMING {
    public:
        static long readvalue(FINGER& finger);
        static void exitprotocol(HAND& hand);    
};

// RCTIMING::readvalue(hand.finger[0])

void RCTIMING::exitprotocol(HAND& hand){
    for(int i = 0; i < 5; i++){
        gpio_free(hand.finger[i].GPIOPIN);
    }
}

long RCTIMING::readvalue(FINGER& finger){
    //Static bool's state will be remembered between function calls
    static bool ranonce = false;
    int Request, Set;

    //if ranonce is false, this is the first time the program has called readvalue, so the pin must be requested
    if(!ranonce){
        if((Request = gpio_is_requested(finger.GPIOPIN)) < 0){
		    cerr << "This GPIO pin is in use" << endl;
		    return -1;
	    }
	    else{
		    cout << "Starting GPIO pin" << endl;
		    if((Set = gpio_request(finger.GPIOPIN, NULL)) < 0){
			    cerr << "There was an error setting the pin value" << endl;
			    return -1;
		    }
        }
        //Set ranonce to true to make sure we don't accidentally request the pin again
        ranonce = true;
    }

    long result = 0;

    if((Request = gpio_direction_output(finger.GPIOPIN, 1)) < 0){
        cerr << "There was an error setting pin to output" << endl;
        return -1;
    }
    else{
        usleep(1000); //1000 microseconds, should be enough time to reset the gpio direction to input
        if((Request = gpio_direction_input(finger.GPIOPIN)) < 0){
            cerr << "There was an error setting pin to input" << endl;
            return -1;
        }
        else{
            while(gpio_get_value(finger.GPIOPIN) != 0){
                if(result > 50000){
                    cerr << "Result took too long" << endl;
                    return -1;
                }
                result++;
            }
            gpio_free(finger.GPIOPIN);
            return result;
        }
    }

}


#endif