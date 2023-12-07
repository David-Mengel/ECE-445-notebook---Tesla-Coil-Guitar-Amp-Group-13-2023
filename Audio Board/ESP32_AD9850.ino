#define W_CLK 2 // pin 2 - Signal, the timer bus (W_CLK) 
 #define FQ_UD 3 // Pin 3 - change the frequency (FQ) 
 #define DATA 4 // Pin 4 - data Line of the serial interface (DATE) 
 #define RESET 5 // Pin 5 - Reset module (RESET) 
 
 #define pulseHigh(pin) {digitalWrite(pin, HIGH); digitalWrite(pin, LOW); } // a function of the heartbeat is set at the time the high status 
 
 // transfer byte bit after beating the AD9850 module via the DATA line 
void tfr_byte(byte data) 
{ 
 for (int i=0; i<8; i++, data>>=1) { 
 digitalWrite(DATA, data & 0x01); 
 pulseHigh(W_CLK); // after each beating signal CLK is set to high 
 } 
} 
 
 // frequency is calculated according to the formula on page 8 documentation = */2^32 
void sendFrequency(double frequency) { 
 int32_t freq = frequency * 4294967295/5000000; // frequency 125 MHz AD9850 
 for (int b=0; b<4; b++, freq>>=8) { 
 tfr_byte(freq & 0xFF); 
 } 
 tfr_byte(0x000); // control byte of zero "0" for module AD9850 
 pulseHigh(FQ_UD); // update frequency 
} 
 
void setup() { 
 // pin configuration Arduino 
 pinMode(FQ_UD, OUTPUT); 
 pinMode(W_CLK, OUTPUT); 
 pinMode(DATA, OUTPUT); 
 pinMode(RESET, OUTPUT); 
 
 pulseHigh(RESET); 
 pulseHigh(W_CLK); 
 pulseHigh(FQ_UD); // toggles serial interface 
} 
 
void loop() { 
 sendFrequency(100000); // enter the frequency for generator 
 while(1); 
}
