//input finger id ti module
//insert key to power the finger print module
//insert finger print
//check valid id and
//open feature

// if key lost bypass the key circuit
//open bluetooth module
//send data to initialize relay to power the finger print
//#include <iostream.h>
#include <math.h>
#include<stdio.h>

int input_read = 2;
int output_data = 7;
int output_relay_two = 12;
int output_relay_four = 11;
int data = 0;
String password;
String vipin = "VIPIN";
int count=0;


struct test {
int counter =0;
int d_input;
};

struct test function(){
struct test t;
data = digitalRead(input_read);
t.counter ;
  Serial.println("initial value of counter in struct function is");
  Serial.println(t.counter);

t.d_input =data;
Serial.println("inside test function");
Serial.println(t.d_input);

 if (t.d_input==1){
//  t.counter =t.counter+1;
//  Serial.println(t.counter);

count=count+1;
  
  Serial.println("end in struct");
  Serial.println(count);

 }
 return t;
}


void key_insert() {
  Serial.println("key insert function is called ");
  digitalWrite(output_relay_four, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(output_relay_two, LOW);    // turn the LED off by making the voltage LOW
  data = digitalRead(input_read);
  Serial.println("low");
  Serial.println(data);
  delay(1000);

  if (data == 1) {
    digitalWrite(output_data, HIGH);
    Serial.println("  signal read from ELSE signal to 12 volt main supply");
    delay(1000);
  }

  if (data == 0) {
    digitalWrite(output_data, LOW );
    Serial.println("  signal read from ELSE signal to 12 volt main supply  OFFFF");
    delay(1000);
  }
}

//.........................

void bluetooth_on() {
  Serial.println("bluetooth_on  is called");
  digitalWrite(output_relay_four, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(output_relay_two, HIGH);   // turn the LED on (HIGH is the voltage level)
  data = digitalRead(input_read);
  Serial.println("high");
  Serial.println(data);
  delay(1000);

  if (data == 1) {
    digitalWrite(output_data, HIGH);
    Serial.println("  signal read from ELSE signal to 12 volt main supply");
    delay(1000);
  }
}

void bluetooth_off() {
  Serial.println("bluetooth_off is called");
  digitalWrite(output_relay_four, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(output_relay_two, HIGH);   // turn the LED on (HIGH is the voltage level)
  data = digitalRead(input_read);   
  Serial.println("high");                 
  Serial.println(data);                 
  delay(1000);

  if (data == 0) {
    digitalWrite(output_data, LOW );
    Serial.println("  signal read from ELSE signal to 12 volt main supply  OFFFF");
    delay(1000);
  }
}





void bluetooth() {
  Serial.println("bluetooth is called");
  digitalWrite(output_relay_four, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(output_relay_two, HIGH);   // turn the LED on (HIGH is the voltage level)
  data = digitalRead(input_read);
  Serial.println("high");
  Serial.println(data);
  delay(1000);

struct test test_call=function();
Serial.println("test call");
Serial.println(test_call.counter);
Serial.println(test_call.d_input);

int counter_in_bluetooth=test_call.counter ;

Serial.println("hiiii   counter_in_bluetooth ptint in blurtooth is ");
Serial.println(counter_in_bluetooth);


if (count==1){
if (data == 1) {
    digitalWrite(output_data, HIGH);
    Serial.println("  signal read from ELSE signal to 12 volt main supply");
    delay(1000);
  }

  if (data == 0) {
    digitalWrite(output_data, LOW );
    Serial.println("  signal read from ELSE signal to 12 volt main supply  OFFFF");
    delay(1000);
  }
}

if (count==2){
//if counter is 2 means that user input to moule second time to off his vehicle
if (data == 1) {
    digitalWrite(output_data, LOW);
    Serial.println("  signal read from ELSE signal to 12 volt main supply");
    delay(1000);
  }

  if (data == 0) {
    digitalWrite(output_data, LOW );
    Serial.println("  signal read from ELSE signal to 12 volt main supply  OFFFF");
    delay(1000);
  }

    count =0;
    Serial.println("counter_in_bluetoothcounter_in_bluetooth is zero frcefully ");
}

 
  if (data == 1) {
    digitalWrite(output_data, HIGH);
    Serial.println("  signal read from ELSE signal to 12 volt main supply");
    delay(1000);
  }

  if (data == 0) {
    digitalWrite(output_data, LOW );
    Serial.println("  signal read from ELSE signal to 12 volt main supply  OFFFF");
    delay(1000);
  }
}

//..............................................

void  serial_read() {
  password = Serial.readString();
  Serial.println(password);
}




void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("WELCOME TO WORLD OF SRIAL PRINT");
  Serial.println(data);
  pinMode(output_relay_four, OUTPUT);
  pinMode(output_relay_two, OUTPUT);
  pinMode(input_read, INPUT);
  pinMode(output_data, OUTPUT);
}

//..........................


int check_data = 0;
void loop() {

  while (check_data == 0) {
    //    key_insert();
    //    delay(1000);

    Serial.println("inside check data");
    delay(1000);
    if (Serial.available() > 0) {
      password = Serial.readString();
      Serial.println(password);
      if (password != "VIPIN") {
        Serial.println("your password is incorrect please enter correct passwoed: ....");
        serial_read();
      }

      if (password == "VIPIN") {
        Serial.println("inside Serial available");
        while (1) {
          bluetooth();
          delay(1000);
        }

        //        check_data = check_data + 1;
        //        Serial.println(check_data);
      }
      //      break;
    }
  }

  Serial.println("inside main loop");
  delay(1000);

  //  key_insert();
  //   bluetooth();
}





