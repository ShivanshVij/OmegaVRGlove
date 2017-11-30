#ifndef logging
#define logging

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "statistics.h"
#include <vector>
#include <cmath>

using namespace std;

struct FINGER {
    int GPIOPIN;
    int VALUE;
};

struct HAND{
    int hand;
    FINGER* finger;
};

class LOG{

public:
    static bool LOG(HAND& object, int status);
    static bool LOG(STATS& object, int status);

private:
    char filename = "Logging.stat";
    ofstream outfile;
    static bool HAND(HAND& object);
    static bool STATS(STATS& object);
    static bool ERROR(HAND& object);
    static bool ERROR(STATS& object);
};

bool LOG::LOG(HAND& object, int status=0;){
    if (status!=0){
        LOG::ERROR(object);
        return true;
    }
    else{
        LOG::HAND(object);
        return true;
    }
}

bool LOG::LOG(STATS object, int status=0;){
    if (status!=0){
        LOG::ERROR(object);
        return true;
    }
    else{
        LOG::STATS(object);
        return true;
    }
}


bool LOG::HAND(HAND hand){
    ofstream.open(filename,ios_base::app);
    if(!outfile.is_open())
    return LOG::ERROR(hand);

    outfile<<"---------------------------------"<<endl;
    outfile<<"Hand and Fingers Settings"<<endl;
    outfile<<"---------------------------------\n"<<endl;
    
    time_t currentTime=time (0);
    char* localTime=ctime(&currentTime);
    outfile<<"Local Time: "<<localTime<<endl;
    outfile<<endl;
    
    outfile<<"Finger 1 Settings: Thumb"<<endl;
    outfile<<"Pin Number: "<<hand.finger[0].GPIOPIN<<endl;
    if (hand.finger[0].IO==0){
        outfile<<"Pin Mode: Input"<<endl;   
    }
    else if (hand.finger[0].IO==1){
        outfile<<"Pin Mode: Output"<<endl;   
    }
    
    if (hand.finger[0].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[0].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }


    outfile<<"Finger 2 Settings: Index"<<endl;
    outfile<<"Pin Number: "<<hand.finger[1].GPIOPIN<<endl;
    if (hand.finger[1].IO==0){
        outfile<<"Pin Mode: Input"<<endl;   
    }
    else if (hand.finger[1].IO==1){
        outfile<<"Pin Mode: Output"<<endl;   
    }
    
    if (hand.finger[1].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[1].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }



    outfile<<"Finger 3 Settings: Middle Finger"<<endl;
    outfile<<"Pin Number: "<<hand.finger[2].GPIOPIN<<endl;
    if (hand.finger[2].IO==0){
        outfile<<"Pin Mode: Input"<<endl;   
    }
    else if (hand.finger[2].IO==1){
        outfile<<"Pin Mode: Output"<<endl;   
    }
    
    if (hand.finger[2].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[2].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }




    outfile<<"Finger 4 Settings: Ring Finger"<<endl;
    outfile<<"Pin Number: "<<hand.finger[3].GPIOPIN<<endl;
    if (hand.finger[3].IO==0){
        outfile<<"Pin Mode: Input"<<endl;   
    }
    else if (hand.finger[3].IO==1){
        outfile<<"Pin Mode: Output"<<endl;   
    }
    
    if (hand.finger[3].VALUE==0){
        outfile<<"Pin Mode: Low"<<endl;   
    }
    else if (hand.finger[3].VALUE==1){
        outfile<<"Pin Mode: High"<<endl;   
    }



    outfile<<"Finger 5 Settings: Pinky (Little Finger)"<<endl;
    outfile<<"Pin Number: "<<hand.finger[4].GPIOPIN<<endl;
    if (hand.finger[4].IO==0){
        outfile<<"Pin Mode: Input"<<endl;   
    }
    else if (hand.finger[4].IO==1){
        outfile<<"Pin Mode: Output"<<endl;   
    }
    
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

bool LOG::STATS(STATS stats){
    int s=0;
    ofstream.open(filename,ios_base::app);
    if(!outfile.is_open())
    return LOG::ERROR(stats);   
    if (stats.minimum<0 || stats.maximum<0 || stats.average<0 || stats.mode.numModes<0 ){
        
        return LOG::ERROR(stats);
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

    outfile << "Sample Standard Deviation: " << stats.smplStdDev << endl;
    outfile << "Modes: ";
    if (stats.mode.numModes>0){
        
        outfile<<stats.mode.modes[0];
        for (unsigned char x = 1; x < stats.mode.numModes; x++)
        {
            outfile << ", "<<stats.mode.modes[x];
        }
    }
    outfile.close();

    return true;
}

bool LOG::ERROR(HAND hand){
    int s=0;
    ofstream.open(filename,ios_base::app);
    if(!outfile.is_open()){
        return false;   
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
bool LOG::ERROR(STATS stats){
    int s=0;
    ofstream.open(filename,ios_base::app);
    if(!outfile.is_open()){
        return false;   
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