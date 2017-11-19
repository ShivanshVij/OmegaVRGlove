#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

#include <ugpio/ugpio.h>

#include "RCtiming.h"

using namespace std;

int main()
{
    HAND hand = new HAND;
    hand.finger[] = new FINGER[5];
    /*
        GPIO Pins:
        PinFinger1: 0
        PinFinger2: 1
        PinFinger3: 6
        PinFinger4: 7
        PinFinger5: 8
    */
    hand.finger[0].GPIO = 0;
    hand.finger[1].GPIO = 1;
    hand.finger[2].GPIO = 6;
    hand.finger[3].GPIO = 7;
    hand.finger[4].GPIO = 8;
    for(int i = 0; i < 5; i++)
    {
        hand.finger[i].IO=0;
        hand.finger[i].VALUE=0;
    }
    exitprotocol(hand);
    return 0;
}