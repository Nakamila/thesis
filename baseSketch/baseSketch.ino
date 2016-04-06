/*
VernierAnalogVoltage (v 2015.06)
Reads a Vernier analog (BTA) sensor connected to pin A0 of the Arduino. This
sketch displays the raw voltage reading on the Serial Monitor. As written, the
reading will be displayed every half second. Change the variable TimeBetweenReadings
to change the rate.

See www.vernier.com/arduino for more information.
 */

int ReadingNumber = 0; //
int TimeBetweenReadings = 10; // using enough readings to find all the peaks of the heart beat

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Time (s)    Voltage Readings from A0 (N)");
}


void loop() {


  float Count;
  float Voltage;
  float SensorReading;
  float Time;//the print below does the division first to avoid overflows

  Time = ReadingNumber/1000 * TimeBetweenReadings; // on the readings transform the time of 15 secons into 1500 values 
  Serial.print(Time);
  Count = analogRead(A0);
  Voltage = Count / 1023 * 5.0;// convert from count to raw voltage
  Serial.print("            ");
  Serial.println(Voltage);
  delay(TimeBetweenReadings);// delay in between reads for stability
  ReadingNumber++;

}
/*
//to analize 15 seconds of heart beats utilize an if (Voltage != 0) to start the time and start analyzing the voltage


    float t1 = 0;
    float t2 = 0;
    float sum = 0;
    float count= 0;
    float aux = 0;

   for (int i = 0; i<=1500; i++){ // 1500 is the number of values we are going to have in 15 seconds
    if (voltage[i]>= 4.0){ // using only the peaks moment 
      t2=time[i];
      aux = t2 - t1;  // find the present beat-to-beat interval
      sum = aux + sum; // add the present beat-to-beat interval to the previous one
      count= count++;    // find out how many times the PEAKS occured I have in 15 seconds to be able to calculate a media of beat-to-beat interval for that amount of time
      t2 = t1;
     
  }

  float media = sum/count;  // media of beat to beat intervals during the 15 seconds
  float sum_var = 0;

  for (int i = 0, i<1500; i++){ // for the same data analized before - needs to be in an array - analyze: 
   if (voltage[i]>=4.0) { // for the peaks
    t2 = time[i];
    aux = t2 -t1; // find the present beat-to-beat interval
    var = (media - aux)*(media -aux); // power of 2, so you can analyze only the positive numbers
    sum_var = var + sum_var; // using the var value of all the intervals of beats is possible to find the total variance of the time period of 15 seconds. 

   }
  }
  float variance = sum_var/count; // variance (the media of all the var values per times occured- will be evaluated to return light color results - the lower the variance, more coherent is the HRV


   }
}
*/



