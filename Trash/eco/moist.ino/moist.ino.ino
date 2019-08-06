int sensor_pin = A1;

int output_value ;

void setup() {

   Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");

   delay(2000);

   }

void loop() {

   output_value= analogRead(sensor_pin);

   output_value = map(output_value,550,0,0,100);

   Serial.print("Mositure : ");
  if(output_value < 0){
    output_value = 0;
  }
   Serial.print(output_value);

   Serial.println("%");

   delay(1000);

   }
