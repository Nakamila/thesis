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
  Serial.println("Time (s)    Voltage Readings from A0 (N)");

  readingSensor = true; // create a way to start/ stop reading the sensor 
  displayResult = false;// create a way to start/ stop displayng the lights

}


void loop() {


  int readIndex;             // the index of the current reading


  float volt[rN];
  float Time[rN];
  float Count[rN];




  // Time = rN / 1000 * TimeBetweenReadings; // on the readings transform the time of 15 secons into 1500 values
  // Serial.print(Time);

  // read from the sensor:
//  Count[readIndex] = analogRead(A0);
//  // add the reading to the total:
//  delay(TimeBetweenReadings);// delay in between reads for stability
  // advance to the next position in the array:
  readIndex = readIndex ++;

//  Serial.println(Count[readIndex]);



  // Count = analogRead(A0);

  float t1 = 0;
  float t2 = 0;
  float sum = 0;
  float count = 0;
  float aux = 0;

  for (int readIndex = 0; readIndex <= rN; readIndex++) {
    
    Count[readIndex] = analogRead(A0);
    delay(TimeBetweenReadings);// delay in between reads for stability
    volt[readIndex] = Count[readIndex] / 1023 * 5.0;// convert from count to raw voltage
    Serial.println(volt[readIndex]);
    
    
    if (volt[readIndex] >= 4.5) { // using only the peaks moment
      Time[readIndex] = rN / 1000 * TimeBetweenReadings;//does the division first to avoid overflows
      t2 = Time[readIndex];
      aux = t2 - t1;  // find the present beat-to-beat interval
      sum = aux + sum; // add the present beat-to-beat interval to the previous one
      count = count++;   // find out how many times the PEAKS occured I have in 15 seconds to be able to calculate a media of beat-to-beat interval for that amount of time
      t2 = t1;
      
          
//      Serial.print("aux:");
//      Serial.println(aux);
//       
//      Serial.print("sum:");
//      Serial.println(sum);
// 
//      Serial.print("count:");
//      Serial.println(count);
// 
      

    }
    
      // if we're at the end of the array...
  if (readIndex >= rN) {
    // .stop reading:
    readingSensor = false;
    displayResult = true;
    delay (60000) // display result for 1 minute
    
  }

  }




}

//to analize 15 seconds of heart beats utilize an if (Voltage != 0) to start the time and start analyzing the voltage



//
//for (int rN = 0; rN <= 1500; i++) { // 1500 is the number of values we are going to have in 15 seconds
//  if (volt[i] >= 4.0) { // using only the peaks moment
//    t2 = time[i];
//    aux = t2 - t1;  // find the present beat-to-beat interval
//    sum = aux + sum; // add the present beat-to-beat interval to the previous one
//    count = count++;   // find out how many times the PEAKS occured I have in 15 seconds to be able to calculate a media of beat-to-beat interval for that amount of time
//    t2 = t1;
//
//  }
//
//  float media = sum / count; // media of beat to beat intervals during the 15 seconds
//  float sum_var = 0;
//
//  for (int i = 0, i < 1500; i++) { // for the same data analized before - needs to be in an array - analyze:
//    if (voltage[i] >= 4.0) { // for the peaks
//      t2 = time[i];
//      aux = t2 - t1; // find the present beat-to-beat interval
//      var = (media - aux) * (media - aux); // power of 2, so you can analyze only the positive numbers
//      sum_var = var + sum_var; // using the var value of all the intervals of beats is possible to find the total variance of the time period of 15 seconds.
//
//    }
//  }
//  float variance = sum_var / count; // variance (the media of all the var values per times occured- will be evaluated to return light color results - the lower the variance, more coherent is the HRV
//
//
//}
//}
//

