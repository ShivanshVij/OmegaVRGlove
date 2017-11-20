#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <climits>

#include <ugpio/ugpio.h>

#include "RCTiming.h"

using namespace std;

struct Stats{
    long minimum;
    float average;
    long maximum;
    float popStdDev;
    float sampleStdDev;
    long mode;
}

// change signature
long minimum(const long dataset[], const int size) {
    
    float mnm = dataset[0];
    int argument_index = 1;
    while(argument_index < size){
        
        float value = dataset[argument_index];
             
        if(value < mnm){
            mnm = value;
        }
        
        argument_index++;
    }
    return mnm;
}

float average(const long dataset[], const int size) {
    
    float total = 0;
    int argument_index2 = 0;
    
    while(argument_index2 < size){
        float value2 = dataset[argument_index2];
        total += value2;
        argument_index2++;
    }
    
    float avrg = total/(float)size;
    return avrg;   
}

long maximum(const long dataset[], const int size) {
    
    float maxm = dataset[0];
    int argument_index3 = 1;
    
    while(argument_index3 < size){
        float value3 = dataset[argument_index3];
        if(value3 > maxm){
            maxm = value3;
        }        
        argument_index3++;
    }
    return maxm;
}

float popStdDev(const long dataset[], const int size) {
    
    if(size == 0){
        return std::numeric_limits<float>::quiet_NaN();
    }
    
	float sum = 0;
    float tmp = 0;
    int k = 0;
    
	while(k < size){
		float value4 = dataset[k];
		tmp = value4 - average(dataset, size);
        sum += pow(tmp,2);
		k++;
	}
    
    float poptemp = sum*(1/(float)size);
	float popStdDev = sqrt(poptemp);
    return popStdDev;
}

float smplStdDev(const long dataset[], const int size) {

    if(size == 1){
        return std::numeric_limits<float>::quiet_NaN();
    }
	
    float add = 0;
	float tmpry = 0;
    float t = 0;
    int j = 0;
    
	while(j < size){
		float value5 = dataset[j];
		tmpry = value5 - average(dataset, size);
		add += pow(tmpry,2);
		j++;
	}
  
    float sampletemp = add*((float)1/(float)(size-1));
    float sampleStdDev = sqrt(sampletemp);
    return sampleStdDev;
 
}

bool sort(long dataset[], const int size){
    bool tmp = selection(dataset, size);
    return true;
}

bool selection(long dataset[], const int size){
    long max = LLONG_MIN;
    int maxIndex = 0;
    
    if(size == 1){
        return true;
    }
    
    for(int i = 0; i < size; i++)
    {
        if(dataset[i] > max)
        {
            max = dataset[i];
            maxIndex = i; 
        }
    }
    
    long temp = dataset[size-1];
    dataset[size-1] = max;
    dataset[maxIndex] = temp;
    return selection(dataset, size-1);
}

int main()
{
    HAND hand = {0};
    hand.hand = 1;
    hand.finger = new FINGER[5];
    /*
        GPIO Pins:
        Thumb:PinFinger1: 0
        Index:PinFinger2: 1
        Middle:PinFinger3: 6
        Ring:PinFinger4: 7
        Pinky:PinFinger5: 8
    */
    hand.finger[0].GPIOPIN = 0;
    hand.finger[1].GPIOPIN = 1;
    hand.finger[2].GPIOPIN = 6;
    hand.finger[3].GPIOPIN = 7;
    hand.finger[4].GPIOPIN = 8;
    for(int i = 0; i < 5; i++)
    {
        hand.finger[i].IO=0;
        hand.finger[i].VALUE=0;
    }

    long val = 0;

    vector<long> dataset;

    Stats st = new Stats;

    while()
    {
        val = RCTiming::readValue(hand.finger[2]);
        dataset.push_back(val);
        st.minimum = minimum(dataset,dataset.size());
        st.average = average(dataset,dataset.size());
        st.maximum = maximum(dataset,dataset.size());
        st.popStdDev = popStdDev(dataset,dataset.size());
        st.sampleStdDev = smplStdDev(dataset,dataset.size());

        LOGGER(st);
    }


    RCTiming::exitprotocol(hand);
    return 0;
}