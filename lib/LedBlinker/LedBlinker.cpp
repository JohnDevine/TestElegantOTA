#include "LedBlinker.h"



LedBlinker::LedBlinker(int Pin, int DelayBetweenFlashes, 
int DelayBetweenMessages, int RepeatCount) :
_pin(Pin), _delayBetweenFlashes(DelayBetweenFlashes),
_delayBetweenMessages(DelayBetweenMessages), _repeatCount(RepeatCount) {
  
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);   // initialise led to off

}

// Getter methods
int LedBlinker::GetDelayBetweenFlashes() const {
    return _delayBetweenFlashes;
}

int LedBlinker::GetDelayBetweenMessages() const {
    return _delayBetweenMessages;
}

int LedBlinker::GetRepeatCount() const {
    return _repeatCount;
}

// Setter methods
void LedBlinker::SetDelayBetweenFlashes(int delay) {
    _delayBetweenFlashes = delay;
}

void LedBlinker::SetDelayBetweenMessages(int delay) {
    _delayBetweenMessages = delay;
}

void LedBlinker::SetRepeatCount(int count) {
    _repeatCount = count;
}

bool LedBlinker::BlinkIt(int NumberofBlinks) {

    if (NumberofBlinks < 1) // if NumberofBlinks is less than 1 turn off led then return false
    {
        digitalWrite(_pin, LOW);   // initialise led to off
        return false;
    }
    for (int i = 0; i < _repeatCount; i++) {
        for (int j = 0; j < NumberofBlinks; j++) {
            digitalWrite(_pin, HIGH);
            delay(_delayBetweenFlashes);
            digitalWrite(_pin, LOW);
            delay(_delayBetweenFlashes);
        }
        delay(_delayBetweenMessages);
    }
    digitalWrite(_pin, LOW);   // force LED off.
    return true;
}
