#include "mbed.h"

//{"coord":{"lon":-0.13,"lat":51.51},"weather":[{"id":300,"main":"Drizzle","description":"light intensity drizzle","icon":"09d"}],"base":"stations","main":{"temp":280.32,"pressure":1012,"humidity":81,"temp_min":279.15,"temp_max":281.15},"visibility":10000,"wind":{"speed":4.1,"deg":80},"clouds":{"all":90},"dt":1485789600,"sys":{"type":1,"id":5091,"message":0.0103,"country":"GB","sunrise":1485762037,"sunset":1485794875},"id":2643743,"name":"London","cod":200}

PwmOut red(p23);
PwmOut green(p21);
PwmOut blue(p22);
RawSerial  pi(USBTX, USBRX);
char temp = 'f';
bool flag;

void fade(float r, float g, float b, float stepSize, float delay){
    int rDir;
    int gDir;
    int bDir;
    bool running = true;
    while(running){
        // Get the direction red needs to go (up or down)
        if(r-red>0){rDir = 1;} // 1 if red is going up
        else if (r-red<0){rDir = -1;} // -1 if red is going down
        else {rDir = 0;} // 0 if red is where it needs to be
        
        // Get the direction green needs to go (up or down)
        if(g-green>0){gDir = 1;}
        else if (g-green<0){gDir = -1;}
        else {gDir = 0;}
        
        // Get the direction blue needs to go (up or down)
        if(b-blue>0){bDir = 1;}
        else if (b-blue<0){bDir = -1;}
        else {bDir = 0;}
        
        // Stop direction from flickering back and forth between +1 and -1
        if (abs(r-red) < 2*stepSize){red = r; rDir = 0;}
        if (abs(g-green) < 2*stepSize){green = g; gDir = 0;}
        if (abs(b-blue) < 2*stepSize){blue = b; bDir = 0;}
        
        // Stop when red, green, and blue are in the right spot
        if (rDir == 0 && gDir == 0 && bDir == 0){running = false;}
        
        // Move red, green, and blue in the correct direction
        red = red + rDir*stepSize;
        green = green + gDir*stepSize;
        blue = blue + bDir*stepSize;
        
        // Wait for a little time before looping again
        wait(delay);
    }
}   

void rain(float r, float g, float b, float stepSize, float duration) {
    float step = 0.0;
    while (step < duration) {
        if (red == r && green == g && blue == b) {
            red = r;
            green = g;
            blue = b - 0.2;
            wait(0.1);
        } else {
            red = r;
            green = g;
            blue = b;
            wait(0.5);
        }
        step += stepSize;
    } 
} 

void thunderstorm(float r, float g, float b, float stepSize, float duration) {
    float step = 0.0;
    int lightning = 0;
    while (step < duration) {
        if (red == r && green == g && blue == b) {
            red = r;
            green = g;
            blue = b - 0.2;
            wait(0.05);
        } else {
            red = r;
            green = g;
            blue = b;
            wait(0.2);
        }
        lightning = rand()%8 + 1;
        if (lightning == 1) {
            red = 1.0;
            green = 1.0;
            blue = 0.3;
            wait(0.2);
        }  
        step += stepSize;
    } 
} 

void sunset(){
    fade(1.0, 0.2, 0.0, 0.001, 0.005); //fade to sunset
    while(!pi.readable()){
    }
}

void night(){
    fade(0.1, 0.0, 0.25, 0.001, 0.005); //fade to night
    while(!pi.readable()){
    }
}

void sunny(){
    fade(1.0, 0.45, 0.0, 0.001, 0.005); //fade to sunny
    while(!pi.readable()){
    }
}

void winter(){
    fade(1.0, 1.0, 0.3, 0.001, 0.005); //fade to winter
    while(!pi.readable()){
    }
}

void rain() {
    fade(0.1, 0.0, 0.35, 0.001, 0.005);
    while(!pi.readable()) {
        rain(0.1, 0.0, 0.35, 0.1, 1.0); //blink blue for rain
    }
    
}

void thunderstorm() {
    fade(0.1, 0.0, 0.35, 0.001, 0.005);
    while(!pi.readable()) {
        thunderstorm(0.1, 0.0, 0.35, 0.1, 1.0); //blink blue and flash white for thunder
    }
}
 void cloudy() {
    while(!pi.readable()) {
        fade(0.5, 0.5, 0.15, 0.001, 0.01); //fade to cloudy (half values of winter)
        fade(0.35, 0.35, 0.1, 0.001, 0.01); //fade to slightly cloudy
        fade(0.25, 0.25, 0.075, 0.001, 0.01); //fade to slightly cloudy
    }    
}

void off() {
    fade(0.0, 0.0, 0.0, 0.001, 0.005);
    while(!pi.readable()) {
    }
}

float charConvert(char ch) {
    if (ch == '0') return 0.0;
    if (ch == '1') return 0.1;
    if (ch == '2') return 0.2;
    if (ch == '3') return 0.3;
    if (ch == '4') return 0.4;
    if (ch == '5') return 0.5;
    if (ch == '6') return 0.6;
    if (ch == '7') return 0.7;
    if (ch == '8') return 0.8;
    if (ch == '9') return 0.9;
    if (ch == 'm') return 1.0;
}

void custom() {
    char redChar = pi.getc();
    char greenChar = pi.getc();
    char blueChar = pi.getc();
    fade(charConvert(redChar), charConvert(blueChar), charConvert(greenChar), 0.001, 0.005);
    while(!pi.readable()) {
    }
}
    

void dev_recv()
{
    while(pi.readable()) {
        temp = pi.getc();
        if (temp=='L') sunny();
        if (temp=='c') cloudy();
        if (temp=='r') rain();
        if (temp=='t') thunderstorm();
        if (temp=='s') winter();
        if (temp=='n') night();
        if (temp=='b') sunset(); //sunrise
        if (temp=='e') sunset();
        if (temp =='f') off();
        if (temp == 'u') custom();
    }
}

int main() {
    red.period(0.01f);//setting the period of one PWMOut sets all of them
    off();
    pi.baud(9600);
    pi.attach(&dev_recv, Serial::RxIrq);
    while(1) {
        sleep();
    }
}
