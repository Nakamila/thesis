/*
VernierAnalogVoltage (v 2015.06)
Reads a Vernier analog (BTA) sensor connected to pin A0 of the Arduino. This
sketch displays the raw voltage reading on the Serial Monitor. As written, the
reading will be displayed every half second. Change the variable TimeBetweenReadings
to change the rate.

See www.vernier.com/arduino for more information.
 */

int rN = 1500; // total number of readings = 10 readings per second for 15 seconds
int TimeBetweenReadings = 20; // using enough readings to find all the peaks of the heart beat



//boolean readingSensor;
//boolean displayResult;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Time (s)    Voltage Readings from A0 (N)");

  //  readingSensor = true; // create a way to start/ stop reading the sensor
  //  displayResult = false;// create a way to start/ stop displayng the lights

}


void loop() {

  float volt[rN];
  float Time[rN];
  float Count[rN];

  
    float t1 = 0;
    float t2 = 0;
    float sum = 0;
    float count = 0;
    float aux = 0;



  for (int readIndex = 0; readIndex < 380 ; readIndex++) {

    Time[readIndex] = (readIndex / 1000.0 * TimeBetweenReadings); //does the division first to avoid overflows
    Serial.print(Time[readIndex]);
    Serial.print("\t");

    Count[readIndex] = analogRead(A0); // reads raw number
    delay(TimeBetweenReadings);// delay in between reads for stability

    volt[readIndex] = Count[readIndex] / 1023 * 5.0;// convert from count to raw voltage
    Serial.println(volt[readIndex]);
    
   
    if (volt[readIndex] >= 4.30) { // using only the peaks moment
         t2 = Time[readIndex];
          aux = t2 - t1;  // find the present beat-to-beat interval
          sum = aux + sum; // add the present beat-to-beat interval to the previous one
          count = count++;   // find out how many times the PEAKS occured I have in 15 seconds to be able to calculate a media of beat-to-beat interval for that amount of time
          t2 = t1;
    
        }
        
      
//  float media = sum/count;  // media of beat to beat intervals during the 15 seconds
//  float sum_var = 0;
//  float var = 0; 
//
// 
//  for (int readIndex = 0; readIndex < 380 ; readIndex++) { // for the same data analyzed before - needs to be in an array - analyze: 
//   if (volt[readIndex] >=4.30) { // for the peaks
//    t2 = Time[readIndex];
//    aux = t2 -t1; // find the present beat-to-beat interval
//    var = (media - aux)*(media -aux); // power of 2, so you can analyze only the positive numbers
//    sum_var = var + sum_var; // using the var value of all the intervals of beats is possible to find the total variance of the time period of 15 seconds. 
//
//   }
//  }
//  float variance = sum_var/count; // variance (the media of all the var values per times occured- will be evaluated to return light color results - the lower the variance, more coherent is the HRV
//  
//  Serial.println(variance);
    }
  
  }


