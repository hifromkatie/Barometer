/* Code for Arduino Barometer, Pressure 6 click board (BM1386GLV) Sensor, 
 * DS1307 RTC and 72 Neopixels.
 * V0.2 temperature display from left to right
 */
#include <RTClib.h>
#include <BM1386lib.h>
#include <Adafruit_NeoPixel.h>


RTC_DS1307 rtc;
BM1386 bsense;
//Pixels object, Arg1 number of pixels, Arg2 pin number, GRB colour 880kHz speed
Adafruit_NeoPixel pixels(72, 5, NEO_GRB + NEO_KHZ800);

int data[2][24];
int next_loc;
int print_loc;
int pLED;
int tLED;
int fade;
int startup;



#define INTERVAL 60000 //1 minute for testing

void setup() {
  Serial.begin(9600);

  if (!bsense.begin()) {
    Serial.println ("Couldn't find Sensor");
    Serial.flush();
    abort();
  }

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("Setting the date and time to PC date and time");
  DateTime now = rtc.now();
  Serial.print(now.year(),DEC);
  Serial.print('/');
  Serial.print(now.month(),DEC);
  Serial.print('/');
  Serial.print(now.day(),DEC);
  Serial.print(" ");  
  Serial.print(now.hour(),DEC);
  Serial.print(':');
  Serial.print(now.minute(),DEC);
  Serial.print(':');
  Serial.println(now.second(),DEC);
  
  
  pixels.begin();
  pixels.clear();

  //Startup sequence
  for (int i=0; i<72; i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();
    delay(100);
  }
  delay (1000);
  pixels.clear();
  pixels.show();
  
  for (int i=0; i<24; i++){
    data[0][i]= 0;
    data[1][i]= 0;
  }
  next_loc = 0;
  startup=1;


}

void loop() {

  DateTime now = rtc.now();

  //Take a reading immediatly on startup and then every hour on the hour.
  if ((now.minute()==0) or (startup==1)){ 
    Serial.print(now.hour(),DEC);
    Serial.print(':');
    Serial.println(now.minute(),DEC);
    
    pixels.clear();
    pLED= round(((bsense.getPressure()/2048)-960)/2.2);
    tLED= round(((bsense.getTemp()/32)+10)/2);
  
    data[0][next_loc]=pLED;
    data[1][next_loc]=tLED;
    
    print_loc=next_loc;
    fade =30;
    for (int x=0; x<23; x++){
        if (print_loc==0){
          print_loc=23;
        }else{
          print_loc=print_loc-1;
        }
      if ((data[0][print_loc]!=0)&&(data[1][print_loc]!=0)){      
          
        pixels.setPixelColor((data[0][print_loc]),pixels.Color(0,0,(255-fade)));
        pixels.setPixelColor((71-(data[1][print_loc])),pixels.Color((255-fade),0,0)); //display temperature on neopixels from the end of the strip, so it is left to right when mounted in a circle

        //output for testing and debugging
        Serial.print(print_loc);
        Serial.print(" ");
        Serial.print(data[0][print_loc]);
        Serial.print(" ");
        Serial.println(data[1][print_loc]);
        
  
      }
      fade= fade+10; //reduce colour as each reading gets older
    }
    //do latest reading last, and in a white with touch of red for temperature and blue for pressure.
    pixels.setPixelColor((data[0][next_loc]),pixels.Color(50,50,75));
    pixels.setPixelColor((71-data[1][next_loc]),pixels.Color(75,50,50)); //display temperature on neopixels from the end of the strip, so it is left to right when mounted in a circle

//output for testing and debugging
    Serial.print(next_loc);
    Serial.print(" ");
    Serial.print(data[0][next_loc]);
    Serial.print(" ");
    Serial.println(data[1][next_loc]);
  
    if (next_loc<23){
      next_loc++;
    }else{
      next_loc=0;
    }
    pixels.show();
    startup=0;
    delay(60000); //wait 60seconds after the reading
  }else{
    delay(60000); //wait additonal 60seconds if not on the hour to take a reading
  }




}
