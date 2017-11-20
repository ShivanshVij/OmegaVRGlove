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


extern int buffer = 0;

class RCTIMING {
    public:
        static long readvalue(FINGER& finger);
        static void exitprotocol(HAND& hand);
    private:
        static bool errorcheck(FINGER& finger);
        static int setpin(FINGER& finger, int direction, int value);
        static int writepin(FINGER& finger, int value);
        static int readpin(FINGER& finger);
        
};

// RCTIMING::readvalue(hand.finger[0])

void RCTIMING::exitprotocol(HAND& hand){
    for(int i = 0; i < 5; i++){
        gpio_free(hand.finger[i].GPIOPIN);
    }
}

bool RCTIMING::errorcheck(FINGER& finger){
    //Check if pin is in use
    if((buffer = gpio_is_requested(finger.GPIOPIN)) < 0){
        cerr << "Requested pin " << finger.GPIOPIN << " is currently in use, releasing it now." << endl;
        gpio_free(finger.GPIOPIN);
        if((buffer = gpio_request(finger.GPIOPIN, NULL)) < 0){
            cerr << "Error releasing pin " << finger.GPIOPIN << endl;
            return false;
        }
        else{
            return true;
        }
    }
    else if((buffer = gpio_request(finger.GPIOPIN, NULL)) < 0){
        cerr << "Error releasing pin " << finger.GPIOPIN << endl;
        return false;
    }
    else{
        return true;
    }
}

int RCTIMING::setpin(FINGER& finger, int direction, int value = 0){
    if(direction == 0){
        buffer = gpio_direction_input(finger.GPIOPIN);
        return 0;
    }
    else if(direction == 1){
        if(value == 0 || value == 1){
             buffer = gpio_direction_output(finger.GPIOPIN, value);
            return value;
        }
        else{
            return -1;
        }
    }
    else{
        return -1;
    }
}

int RCTIMING::readpin(FINGER& finger){
    return gpio_get_value(finger.GPIOPIN);
}

int RCTIMING::writepin(FINGER& finger, int value){
    if(value == 0 || value == 1){
        buffer = gpio_set_value(finger.GPIOPIN, value);
        return value;
    }
    else{
        return -1;
    }
    
}

long RCTIMING::readvalue(FINGER& finger){
    long result = 0;
    RCTIMING::setpin(finger, 1);
    RCTIMING::writepin(finger, 1);
    usleep(500);

    RCTIMING::setpin(finger, 1);
    RCTIMING::writepin(finger, 0);
    while(RCTIMING::readpin(finger)){
      result++;
    }
    return result;

}


#endif