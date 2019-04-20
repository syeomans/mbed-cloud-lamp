#include "mbed.h"

//{"coord":{"lon":-0.13,"lat":51.51},"weather":[{"id":300,"main":"Drizzle","description":"light intensity drizzle","icon":"09d"}],"base":"stations","main":{"temp":280.32,"pressure":1012,"humidity":81,"temp_min":279.15,"temp_max":281.15},"visibility":10000,"wind":{"speed":4.1,"deg":80},"clouds":{"all":90},"dt":1485789600,"sys":{"type":1,"id":5091,"message":0.0103,"country":"GB","sunrise":1485762037,"sunset":1485794875},"id":2643743,"name":"London","cod":200}

PwmOut red(p23);
PwmOut green(p22);
PwmOut blue(p21);


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


int main() {
    red.period(0.01f);//setting the period of one PWMOut sets all of them

    red = 1.0;
    green = 1.0;
    blue = 1.0;
    
    fade(1.0, 0.1, 0.0, 0.01, 0.03); // fade to red
    fade(0.8, 0.3, 0.0, 0.001, 0.03); // fade to orange
    fade(0.4, 0.2, 0.1, 0.001, 0.03); //fade to yellow
    fade(0.1, 0.1, 0.3, 0.01, 0.03); //fade to indigo
}
