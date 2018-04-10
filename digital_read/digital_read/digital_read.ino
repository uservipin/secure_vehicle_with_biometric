



//take digital output from pin 

//read digital output  as digital input and do some function with digital read

int output_pin =13 ;
int input_pin =10;
int data =0;

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
pinMode(output_pin,OUTPUT);
pinMode(input_pin,INPUT);

}

void loop() {

digitalWrite(output_pin,HIGH);

data=digitalRead(input_pin);

Serial.println(data);

if(data==1){

 Serial.println("digital pin is high");
 Serial.println("  ");
}
else
{
   Serial.print("digital pin is low");
   Serial.println("  ");

}
  
 delay(2000);
  // put your main code here, to run repeatedly:

}
