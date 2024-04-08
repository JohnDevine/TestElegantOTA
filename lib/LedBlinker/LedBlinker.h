#ifndef LEDBLINKER_H
#define LEDBLINKER_H

#include <JDGlobal.h>

/*
This class controls a led. The constructor sets up LedBlinker 
and takes four parameters: 
Pin, 
DelayBetweenFlashes, 
DelayBetweenMessages, and 
RepeatCount.

A method called BlinkIt takes 
an integer parameter NumberofBlinks and returns a boolean value. 
This method blinks the LED attached to the pin specified in the 
constructor. It blinks the LED for NumberofBlinks times with 
a delay of _DelayBetweenFlashes between each blink. 
After blinking NumberofBlinks times, it waits for a 
delay of _DelayBetweenMessages before repeating the blink sequence again.
This is done for _Repeat_count number of times.

NOTE: If the NumberofBlinks is less than 1, the LED is turned off and the method returns false.
*/

class LedBlinker {
public:
    LedBlinker(int Pin, int DelayBetweenFlashes, int DelayBetweenMessages, int RepeatCount);

    // Getter methods
    int GetDelayBetweenFlashes() const;
    int GetDelayBetweenMessages() const;
    int GetRepeatCount() const;

    // Setter methods
    void SetDelayBetweenFlashes(int delay);
    void SetDelayBetweenMessages(int delay);
    void SetRepeatCount(int count);

    bool BlinkIt(int NumberofBlinks);

private:
    int _pin;
    int _delayBetweenFlashes;
    int _delayBetweenMessages;
    int _repeatCount;
};

#endif /* LEDBLINKER_H */
