/*
 * BM1386GLV test communication example
 * 
 * Created 21 September 2020
 * by Katie Dumont
 */

 #include <BM1386lib.h>
 
 BM1386 bsense;
 
void setup() {
  Serial.begin(9600);

  if (! bsense.begin()) {
    Serial.println("Couldn't find Sensor");
    Serial.flush();
    abort();
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
