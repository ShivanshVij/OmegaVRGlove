#ifndef RCTiming
#define RCTiming

#include <ugpio/ugpio.h>
#include <iostream>
#include <unistd.h>

struct hand{
    int HAND;
    FINGER *finger;
};

struct FINGER {
    int GPIOPIN;
    int IO;
    int VALUE;
};

class RCTIMING {

    public:
        static long readvalue(FINGER& finger);
    private:
        bool errorcheck(FINGER& finger);
        void setpin(FINGER& finger, int value);
        void writepin(FINGER& finger, int value);
        int readpin(FINGER& finger);
        
};

bool errorcheck(FINGER& finger){
    //Check if pin is in use
    if(gpio_is_requested(finger.GPIOPIN) < 0){
        cerr << "Requested pin " << finger.GPIOPIN << " is currently in use, releasing it now." << endl;
        ugpio_free(finger.GPIOPIN);
        return true;
    }
    else{
        return true;
    }
}

int setpin(FINGER& finger, int value){

}

int readpin(FINGER& finger){
    return gpio_get_value(finger.GPIOPIN);
}


#endif