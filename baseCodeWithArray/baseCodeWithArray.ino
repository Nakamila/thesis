/*
VernierAnalogVoltage (v 2015.06)
Reads a Vernier analog (BTA) sensor connected to pin A0 of the Arduino. This
sketch displays the raw voltage reading on the Serial Monitor. As written, the
reading will be displayed every half second. Change the variable TimeBetweenReadings
to change the rate.

See www.vernier.com/arduino for more information.
 */

int rN = 1500; // total number of readings = 10 readings per second for 15 seconds
int TimeBetweenReadings = 10; // using enough readings to find all the peaks of the heart beat



boolean readingSensor;
boolean displayResult;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //  Serial.println("Time (s)    Voltage Readings from A0 (N)");

  readingSensor = true; // create a way to start/ stop reading the sensor
  displayResult = false;// create a way to start/ stop displayng the lights

}


void loop() {

  float volt[rN];
  float timer[rN];
  float Count[rN];


  float t1 = 0;
  float t2 = 0;
  float sum = 0;
  float count = 0;
  float aux = 0;


  for (int readIndex = 0; readIndex <= rN; readIndex++) {

    timer[readIndex] = (readIndex/ 1000 * TimeBetweenReadings);//does the division first to avoid overflows
        Serial.println(timer[readIndex]);
      //  Serial.print("\t");

    Count[readIndex] = analogRead(A0); // reads raw number

    volt[readIndex] = Count[readIndex] / 1023 * 5.0;// convert from count to raw voltage
    //    Serial.println(volt[readIndex]);

    delay(TimeBetweenReadings);// delay in between reads for stability
 

 

    if (volt[readIndex] >= 4.6) { // using only the peaks moment
      t2 = timer[readIndex];
      aux = t2 - t1;  // find the present beat-to-beat interval
      sum = aux + sum; // add the present beat-to-beat interval to the previous one
      count = count++;   // find out how many times the PEAKS occured I have in 15 seconds to be able to calculate a media of beat-to-beat interval for that amount of time
      t2 = t1;

    }

//    if (readingNow >= rN) {
//      Serial.println("I AM DONE!");
//      //      delay(60000); // stop for a minute
//      //      readIndex = 0;
//    }
  }

}
// if we're at the end of the array...
//  if (readIndex >= rN) {
//    // .stop reading:
//    readingSensor = false;
//    displayResult = true;
//    delay (60000) // display result for 1 minute
//
//  }




