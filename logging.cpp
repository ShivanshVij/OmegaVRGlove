#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <ctime>
#include <ugpio/ugpio.h>

#include "RCtiming.h"

using namespace std;



class LOG{
public:
    static LOG (HAND object, int status=0);
    static LOG (STATS object, int status=0);
private:
    char filename[]="Logging.stat";
    ofstream outfile;
    static bool HAND(HAND object);
    static bool STATS(STATS object);
    static bool ERROR(HAND object);
    static bool ERROR(STATS object);
};



static LOG::LOG(HAND object, int status=0){
    if (status!=0){
        LOG::ERROR(object);
    }
    else{
        LOG::HAND(object);
    }
}

static LOG::LOG(STATS object, int status=0){
    
    if (status!=0){
        LOG::ERROR(object);
    }
    else{
        LOG::STATS(object);
    }
}




static bool LOG::HAND(HAND hand){
    
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

static bool LOG::STATS(STATS stats){
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

static bool LOG::ERROR(HAND hand){
    int s=0;
    ofstream.open(filename,ios_base::app);
    if(!outfile.is_open())
    return false;   

    time_t currentTime=time (0);
    char* localTime=ctime(&currentTime);
    outfile<<"---------------------------------"<<endl;
    outfile<<"HAND ERROR LOGGING!"<<endl;
    outfile<<"---------------------------------\n"<<endl;
    outfile<<"Local Time: "<<localTime<<endl;
    outfile<<endl;
    outfile << "Error Finding Hand and Fingers Settings"<< endl;

    outfile.close();
}
static bool LOG::ERROR(STATS stats){
    int s=0;
    ofstream.open(filename,ios_base::app);
    if(!outfile.is_open())
    return false;   
    outfile<<"---------------------------------"<<endl;
    outfile<<"STATISTICS ERROR LOGGING!"<<endl;
    outfile<<"---------------------------------\n"<<endl;
    time_t currentTime=time (0);
    char* localTime=ctime(&currentTime);
    
    
    outfile<<"Local Time: "<<localTime<<endl;
    outfile<<endl;
    outfile << "Error Calculating Statistics"<< endl;

    outfile.close();
}










//bool Logging(Statistics stats, HAND hand);

//bool Logging(Statistics stats, HAND hand){
   // int s=0;
    
  // char filename[]="Logging.stat";
    
    





    
   // if (stats.minimum<0 || stats.maximum<0 || stats.average<0 || stats.mode.numModes<0 ){
   //     return -1;
   // }

    /*ofstream outfile;
    outfile.open(filename);
    if(!outfile.is_open())
        return -1;
*/


    /*    outfile<<"---------------------------------"<<endl;
        outfile<<"Section 1: System Information"<<endl;
        outfile<<"---------------------------------\n"<<endl;
        
        time_t currentTime=time (0);
        char* localTime=ctime(&currentTime);
        outfile<<"Local Time: "<<localTime<<endl;
        outfile<<endl;

        outfile<<"---------------------------------"<<endl;
        outfile<<"Section 2: Hand and Fingers Settings"<<endl;
        outfile<<"---------------------------------\n"<<endl;
        
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

       /* outfile<<"---------------------------------"<<endl;
        outfile<<"Section 3: Motion Statistics"<<endl;
        outfile<<"---------------------------------\n"<<endl;
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
    return 0;
}


*/


int main(){
    // RCTIMING::readvalue(FINGER& finger) returns long

    /*
    struct HAND{
        int hand;
        FINGER *finger;
    };

    struct FINGER {
        int GPIOPIN;
        int IO; //IO = 0 (INPUT), IO = 1 (OUTPUT)
        int VALUE; //VALUE = 0 (LOW), VALUE = 1 (HIGH)
    };
    */


    /*
    hand.finger[0]
    to
    hand.finger[4]
    */


    


}