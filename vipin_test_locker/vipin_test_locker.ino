//input finger id ti module
//insert key to power the finger print module
//insert finger print
//check valid id and
//open feature

// if key lost bypass the key circuit
//open bluetooth module
//send data to initialize relay to power the finger print


#include <math.h>
#include<stdio.h>

int input_read = 2;
int output_data = 7;
int output_relay_two = 12;
int output_relay_four = 11;
int data = 0;
String password;
String vipin = "VIPIN";
int count = 0;
int count_again = 0;


//........................................................................................................struct
struct test {
  int counter = 0;
  int d_input;
};

struct test function() {
  struct test t;
  Serial.println("welcome in struct function ");
  delay(1000);
  data = digitalRead(input_read);
  //t.counter ;
  //  Serial.println("initial value of counter in struct function is");
  //  Serial.println(t.counter);

  t.d_input = data;
  Serial.println("print the value of t.d_input in struct  function");
  Serial.println(t.d_input);

  if (t.d_input == 1) {
    count = count + 1;
    Serial.print("value of count in struct function is :  "); Serial.println(count);
    Serial.println("end of struct function ");
  }
  return t;
}


//............................................................................................................stop_while_bluetooth

void stop_while_bluetooth() {
  Serial.println("stop while bluetooth is called");
  loop();
}

// .............................................................................................................. key insert
void key_insert() {
  Serial.println("key_insert function is called ");
  digitalWrite(output_relay_four, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(output_relay_two, LOW);    // turn the LED off by making the voltage LOW
  data = digitalRead(input_read);
  Serial.print("print digital read inside key_insert data is : ");   Serial.println(data);
  delay(1000);

  if (data == 1) {
    digitalWrite(output_data, HIGH);
    Serial.println("key is on and power supply is ON for other function ");
    delay(1000);
  }

  if (data == 0) {
    digitalWrite(output_data, LOW );
    Serial.println("  key is off and power supply is OFF  for other function");
    delay(1000);
  }
}

//...........................................................................................................bike on function
int bike_on_function() {

  while (1) {
    digitalWrite(output_data, LOW);
    Serial.println("count is 2 and data is 1");
    Serial.println("  bike ONN...");
    int data = digitalRead(input_read);
    if (data == 1) {
      Serial.println("inside bike  ON  while loop function  in if statment : .. ");
      count_again = count_again + 1;
      Serial.println(count_again);
      return count_again;
    }
  }
  delay(1000);
}

//...........................................................................................................bike function off

int bike_function_off () {
  while (1) {
    digitalWrite(output_data, LOW );
    Serial.println("count is 2 and data is 0");
    Serial.println("bike off");

    int data = digitalRead(input_read);
    if (data == 1) {
      Serial.println("inside bike OFF  function IN while  in if statment : .. ");
      count_again = 0;
      delay(1000);
      return count_again;
    }
  }
}

//............................................................................................................bluetooth

void bluetooth() {
  Serial.println("bluetooth  function is called :  ");
  digitalWrite(output_relay_four, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(output_relay_two, HIGH);    // turn the LED on (HIGH is the voltage level)
  data = digitalRead(input_read);
  Serial.print("print digital read inside bluetooth  data is : "); Serial.println(data);
  delay(1000);

  //  Serial.println("now flow goes to structure function  : ");
  //  delay(1000);
  //  struct test test_call = function();
  //  Serial.println("test call");
  //  Serial.println(test_call.counter);
  //  Serial.println(test_call.d_input);

  Serial.println("press the push button ");
  delay(1000);

  if (data == 1) {
    count_again = count_again + 1;
    if (count_again == 1) {
      int x = bike_on_function();
    }

    if (count_again == 2) {
      int y = bike_function_off ();
    }
  }

}

//.............................................. ............................................srial read  function

void  serial_read() {
  Serial.println("your password is incorrect please enter correct passwoed: ....");
  password = Serial.readString();
  Serial.println(password);
}


//..............................................................................................srting read
String  string_read() {
  password = Serial.readString();
  Serial.println(password);
  return password;
}

//.................................................................................................correct_code

int correct_code(){
  while (1) {
          bluetooth();
        String   read_string = string_read();
          if (read_string == "STOP") {
            stop_while_bluetooth();
            return 1;
          }
          delay(1000);
        }


  
}

//.................................................................................................. setup 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("wELCOME IN SECCURITY SYSTEM SOLUTIONS :");
  Serial.println(data);
  pinMode(output_relay_four, OUTPUT);
  pinMode(output_relay_two, OUTPUT);
  pinMode(input_read, INPUT);
  pinMode(output_data, OUTPUT);
}

//..................................................................................................void loop



void loop() {
//  Serial.println("LOOP.....LOOP.....LOOP.....");
  int check_data = 0;
  while (check_data == 0) {
    if (!Serial.available()) {
      key_insert();
//      delay(1000);
    }

    Serial.println("inside check data while loop ");
//    delay(1000);
    if ( Serial.available() ) {
      String  read_string = string_read();
      if (read_string != "VIPIN" && read_string != "STOP") {
        serial_read();
      }

      if (read_string == "VIPIN") {
        Serial.println("your password is correct YOU HAVE LOGIN :...");
      int correct_code_variable = correct_code();
      
      }
      //      break;
    }
    check_data = check_data + 1;
//    Serial.print("value of check data value is:   "); Serial.println(check_data);
  }

}





