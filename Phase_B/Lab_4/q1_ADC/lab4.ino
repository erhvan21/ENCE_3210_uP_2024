#define bitsize 14
#define debug false
float quantized = 0;

// struct for returning data to, initialize to 0
struct BinaryQuantized{
  int binary[bitsize] = {0};
  float quantized = 0.0;
};

// setup, serial monitor
void setup(){
  Serial.begin(9600);
}

// main loop, test values and print to serial
void loop(){
  // test variables
  float Vref = 3.0;
  float Vins[] = {0.42, 0.83, 1.65, 2.752};

  // for each test variable
  for(int i = 0; i<sizeof(Vins)/sizeof(float); i++){
    // print the test value
    Serial.print(Vins[i]);
    Serial.println(":\n------------------------");
    //set the result to the ADC function with test variable
    BinaryQuantized result = SAR14(Vins[i],Vref);
    // print binary result
    Serial.print("Binary: ");
    printArray(result.binary);
    // print quantized result
    Serial.print("Quantized: ");
    Serial.println(result.quantized);
    Serial.println();
  }
  //stop after doing once
  while(1);
}

// function for printing binary array
void printArray(int array[bitsize]){
  for(int j = 0; j<bitsize;j++){
    Serial.print(array[j]);
  }
  Serial.println();
} 

// SAR 14 converter function
BinaryQuantized SAR14(float Vin, float Vref){
  // function variables
  float thresh;             // fluctuating threshold 
  int bitval;               // changing bit value
  BinaryQuantized result;   // data to hold result
  float quantVal;           // changing quantized value

    // initial halfing, setting thresh to Vref
    Vref /= 2;
    thresh = Vref;

    // starting with MSB, for each bit in the output
    for(int count=0; count<bitsize; count++){
      // set the quantized value
      quantVal = Vref;
      // 1/2 the reference voltage
      Vref /= 2;
      if(debug){//Serial.print("Vref: ");Serial.println(Vref);
                Serial.print("Thresh: ");Serial.println(thresh);}
        // if thresh is greater than vin, lower threshold by vref, set bitval to 0
        if (thresh > Vin){
            bitval = 0;             // set bitVal to 0
            thresh -= Vref;         // subtract thresh from Vref
        }
        // if thresh is less than vin, raise threshold by vref, set bitval to 1
        else{
            bitval = 1;             // set bitVal to 1
            thresh += Vref;         // add Vref to thresh
        }
        result.binary[count] = bitval;       // set the bitVal in bits[count]
        if(debug){Serial.print("Binary: "); printArray(result.binary);}

        if(bitval==1){
          result.quantized += quantVal;   // approximate what the quantized value would be
        }
        if(debug){Serial.print("Quantized: ");Serial.println(result.quantized, 3); Serial.println();}
    }
    return result;
}