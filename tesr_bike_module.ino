
//stop command stop all processes and back to loop to take next command.
//what is effect of baurd rate

#include <Adafruit_Fingerprint.h>
#include<TimerOne.h>
#include <SoftwareSerial.h>
#include<stdio.h>
uint8_t id;
uint8_t getFingerprintEnroll();
//#if ARDUINO >= 100
int getFingerprintIDez();
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// RELAY NO. 3 IS CONNECTED TO POWER SUPPLY
int array[5];
int sent_data = 7;
int recive_data = A0;

int input_read = 2;            // is input to finget print module
int pass_circuit = 11;         // connected to relay no. 5
int output_data = 13;          // relay no. 1 and 6 connected
int output_relay_two = 10;     // relay no. 2                                                                                                                                                                                                      relay no. 2
int output_relay_four = 12;    // relay no. 4
int data = 0;
String password;
//String vipin = "VIPIN";
int count = 0;
//int count_again = 0;

int variable_for_out_while_loop = 1;






//........................................................array

int array_average() {
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    //    Serial.println("values in array");
    //here analog data is read and add to array
    int data = analogRead(A0);
    //    Serial.println(data);
    array[i] = data;
    sum = sum + array[i];

    //    Serial.println(array[i]);
  }
  Serial.print("sum of number      ");    Serial.println(sum);
  int average = sum / 5;
  Serial.print("average is ");               Serial.println(average);
  for (int i = 0; i < 5; i++)
  {
    array[i] = 0;
  }

  //  Serial.println("new array is ");
  for (int i = 0; i < 5; i++)
  {

    //    Serial.println(array[i]);
  }
  return average;
}

// ........................................................ key insert
void key_insert() {
  while (true) {
    //  Serial.println("key_insert function is called ");
    //  relay 2 and relay 4 are off because we are using simple bike key to power the finger
    //  print module so
    digitalWrite(output_relay_four, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(output_relay_two, LOW);     // turn the LED off by making the voltage LOW
    //  .............................................................
    //    here data should be come from digital read and pass with relay no. 7
    //    READ DATA OF HIGH DIGITAL PIN

    //here function array average is called
    int return_average = array_average();

    if (return_average > 1000) {
      digitalWrite(output_data, HIGH);
      Serial.println("key is ON and power supply is ON");
      //      delay(150);
    }

    if (return_average < 1000) {
      digitalWrite(output_data, LOW );
      //      check the below digital write code  with execution
      digitalWrite(sent_data, LOW);
      variable_for_out_while_loop = 1;
      Serial.print(" variable_for_out_while_loop is "); Serial.println( variable_for_out_while_loop);
      //OFF EVERY REVELENT DIGITAL SWITCH AND RETURN
      //variable_for_out_while_loop=1  ACCORDING TO CONDITION IF POSSIBLE
      controll_finger_print();
      Serial.println("  key is OFF and power supply is OFF  ");
      delay(150);
    }

    //    data = digitalRead(recive_data);
    //    Serial.print("print digital read inside key_insert data is : ");   Serial.println(data);
    //    delay(150);
    //    if (data == 1) {
    //      digitalWrite(output_data, HIGH);
    //      Serial.println("key is ON and power supply is ON");
    //      delay(150);
    //    }
    //    if (data == 0) {
    //      digitalWrite(output_data, LOW );
    //      //      check the below digital write code  with execution
    //      digitalWrite(sent_data, LOW);
    //      variable_for_out_while_loop = 1;
    //      Serial.print(" variable_for_out_while_loop is "); Serial.println( variable_for_out_while_loop);
    //      //OFF EVERY REVELENT DIGITAL SWITCH AND RETURN
    //      //variable_for_out_while_loop=1  ACCORDING TO CONDITION IF POSSIBLE
    //      controll_finger_print();
    //      Serial.println("  key is OFF and power supply is OFF  ");
    //      delay(150);
    //    }
  }
}


//.................................  get finger print id  with verification
int getFingerprintIDez() {
  while (true) {
    Serial.println("inside get finger print  while loop");
    //    Serial.println("enter any integer and press enter");
    //    while (! Serial.available());
    uint8_t p = finger.getImage();
    if (p != FINGERPRINT_OK)  return -1;
    p = finger.image2Tz();
    if (p != FINGERPRINT_OK)  return -1;
    p = finger.fingerFastSearch();
    if (p != FINGERPRINT_OK)  return -1;
    Serial.print("Found ID #"); Serial.print(finger.fingerID);
    Serial.print(" with confidence of "); Serial.println(finger.confidence);
    if (finger.confidence >= 70) {

      //      high digital pin to read for  calling  contoll finger print ;
      digitalWrite(sent_data, HIGH);
      return  finger.confidence;
    }
  }
}


//.................................control finger print
int controll_finger_print() {
  if (variable_for_out_while_loop == 1) {
    while (true) {
      Serial.println("enter any integer and press enter");
      while (! Serial.available());
      Serial.println("inside control finger print  while loop");
      int confidence_data =  getFingerprintIDez();
      Serial.println(confidence_data);
      if (confidence_data >= 70) {
        Serial.println("inside IF of control finger print ()");
        variable_for_out_while_loop = 2;
        return confidence_data;
      }
    }
  }
}




//..................................................bluetooth
void bluetooth() {
  ///fingerprint call...
  //fingerprint verify
  while (1) {
    controll_finger_print();

    Serial.println("bluetooth  function is called :  ");
    digitalWrite(pass_circuit, LOW);
    digitalWrite(output_relay_four, LOW                                                                                                                                                                                             );   // turn the LED on (HIGH is the voltage level)
    digitalWrite(output_relay_two, LOW);    // turn the LED on (HIGH is the voltage level)
    //    data = analogRead(recive_data);
    //      Serial.print("print analog  read inside bluetooth  data is : "); Serial.println(data);
    //    delay(150);


    //here function array average is called
    int return_average = array_average();

    if (return_average > 1000) {
      Serial.println("bike ONN... with bluetooth ");
      digitalWrite(output_data, HIGH);
      //    delay(1000);
    }

    if (return_average < 1000) {
      Serial.println("bike off with bluetooth");
      digitalWrite(output_data, LOW);
      variable_for_out_while_loop = 1;
      controll_finger_print();
      //    delay(1000);
    }

    String  read_string = string_read();
    if (read_string == "STOP") {
      stop_while_bluetooth();
    }
  }
}

//.............................................bike on function
int bike_on_function() {

  //    Serial.println("count is 2 and data is 1");
  Serial.println("bike ONN... with bluetooth ");
  digitalWrite(output_data, HIGH);
  delay(100);
  //here input_read is replaced by recived data
  String  read_string = string_read();
  if (read_string == "STOP") {
    stop_while_bluetooth();
  }

  //  delay(150);
}


//....................................................bike function off
int bike_function_off () {

  digitalWrite(output_data, LOW );
  // Serial.println("count is 2 and data is 0");
  Serial.println("bike off");
  //read from pin no. 6  data of digitalpin no. 7
  String  read_string = string_read();
  if (read_string == "STOP") {
    stop_while_bluetooth();
  }
}

// .........................bypass bluetooth

void bypass_bluetooth() {

  //  AFTER VERIFY BY OWNER RETURN INTO THE MAIN LOOP
  //  inside bypass bluetooth function bypass only on fingrtprint module not key .
  //  NOW MODIFY THIS FUNCTION ACCORDING TO THEM
  //  hrer to bypass only finger print not key so,
  //  low relay no. 2
  //  high relay no. 3   realy of 12 volt.
  //  low relay no. 4
  while (true) {
    Serial.println("inside pass function");
    digitalWrite(output_relay_two, LOW);  //correct
    digitalWrite(output_relay_four, LOW); //correc
    delay(500);

    //here function array average is called
    int return_average = array_average();

    if (return_average > 1000) {
      digitalWrite(output_data, HIGH);
      Serial.println("key is ON and power supply is ON");
      //      delay(100);
      String  read_string = string_read();
      if (read_string == "STOP") {
        //        return can be used insted of   stop_while_bluetooth();
//        return ;
                stop_while_bluetooth();
      }
    }

    if (return_average < 1000) {
      digitalWrite(output_data, LOW);
      Serial.println("key is OFF and power supply is OFF");
      //      delay(100);
      String  read_string = string_read();
      if (read_string == "STOP") {
        //        return can be used insted of   stop_while_bluetooth();
        //        stop_while_bluetooth();
        return ;
      }
    }

    //    data = digitalRead(recive_data);
    //    Serial.print("print digital read inside key_insert data is : ");   Serial.println(data);
    //    if bike off on.
    //    low exceleqtor and signal wothouut off the key
    //    if (data == 1) {
    //      digitalWrite(output_data, HIGH);
    //      Serial.println("key is ON and power supply is ON");
    //      //      delay(100);
    //      String  read_string = string_read();
    //      if (read_string == "STOP") {
    //        //        return can be used insted of   stop_while_bluetooth();
    //        return ;
    //        //        stop_while_bluetooth();
    //      }
    //    }
    //    if (data == 0) {
    //      digitalWrite(output_data, LOW);
    //      Serial.println("key is OFF and power supply is OFF");
    //      //      delay(100);
    //      String  read_string = string_read();
    //      if (read_string == "STOP") {
    //        //        return can be used insted of   stop_while_bluetooth();
    //        //        stop_while_bluetooth();
    //        return ;
    //      }
    //    }

  }

  //  delay(1000);
  //  why pass circuit is low
  //  digitalWrite(pass_circui  , LOW);
}

//.....................................................srial read  function

void  serial_read() {
  Serial.println("your password is incorrect please enter correct passwoed: ....");
  password = Serial.readString();
  Serial.println(password);
}


//.........................................................srting read
String  string_read() {
  password = Serial.readString();
  Serial.println(password);
  return password;
}

//.............................stop_while_bluetooth
void stop_while_bluetooth() {
  //  Serial.println("stop while bluetooth is called");
  digitalWrite(output_data, LOW);
  digitalWrite(output_relay_four, LOW);
  digitalWrite(output_relay_two, LOW);
  digitalWrite(sent_data, LOW);
  loop();
}

int correct_code() {
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


//..................................................... setup

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("WELCOME IN SECCURITY SYSTEM SOLUTIONS... :");
  //  Serial.println(data);
  pinMode(recive_data, INPUT);
  pinMode(sent_data, OUTPUT);
  pinMode(output_relay_four, OUTPUT);
  pinMode(pass_circuit, OUTPUT);
  pinMode(output_relay_two, OUTPUT);
  pinMode(input_read, INPUT);
  pinMode(output_data, OUTPUT);
  //  Timer1.initialize(5000000);
  //  Timer1.attachInterrupt(getFingerprintIDez);
  finger.begin(57600);
  //pinMode(buzzer, OUTPUT); // Set buzzer - pin 10 as an output
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1)
      Serial.println("Waiting for valid finger...");
  }
}

//........................................................................void loop

void loop() {

  //      int confidence_data_of_finger_print = controll_finger_print();
  //      if (confidence_data_of_finger_print >= 70) {
  //call key insert function
  //      }


  //  Serial.print("finger  id CONFIDENCE is ");  Serial.println(finger_id);
  //  if (finger_id) {
  //    Serial.println("welcome you are securely login ");
  //  }


  int check_data = 0;
  while (check_data == 0) {
    //    if (!Serial.available()) {
    //      Serial.println("inside not serial");
    //          key_insert();
    //      delay(100);
    //    }
    //    Serial.println("WELCOME IN SECURITY LOOP ........ ");
    //    delay(1000);
Serial.println("inside looop");

    if ( Serial.available() ) {
      String  read_string = string_read();
      //      password is incorrect please enter correct password

Serial.println("inside serial available");

      if (read_string != "VIPIN" && read_string != "STOP" && read_string != "PASS"  && read_string != "ENROLL"  && read_string != "DELETE") {
        serial_read();
      }

      // key and fingerprint is bypass here password is pass
      if (read_string == "PASS") {
        digitalWrite(sent_data, HIGH);
        bypass_bluetooth() ;
      }
      if (read_string == "VIPIN") {
        Serial.println("your password is correct YOU HAVE LOGIN :...");
        int correct_code_variable = correct_code();
      }

          if (read_string == "ENROLL") {
        Serial.println("your password is correct YOU HAVE LOGIN :...");
         enroll();
      }
          if (read_string == "DELETE") {
        Serial.println("your password is correct YOU HAVE LOGIN :...");
       deletet();
      }
      break;
    }
    //    check_data = check_data + 1;
    //    Serial.print("value of check data value is:   "); Serial.println(check_data);
  }
}


void Blink() {
  Serial.println("inside blink..................................");
}

//............................................................... for enroll enter id

uint8_t readnumber(void) {
  uint8_t num = 0;
  boolean validnum = false;
  while (1) {
    while (! Serial.available());
    Serial.println("hoiiiiiii");
    char c = Serial.read();
    if (isdigit(c)) {
      num *= 10;
      num += c - '0';
      validnum = true;
      //  } else if (validnum) {
      return num;
    }
  }
}


//........................................................enroll
void enroll() {
  Serial.println("Ready to enroll a fingerprint! Please Type in the ID # you want to save this finger as...");

  id = readnumber();

  Serial.print("Enrolling ID #");
  Serial.println(id);

  while (!  getFingerprintEnroll() );

}


uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.println(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }


  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
}

//........................................................... delete

void deletet() {
  Serial.println("Type in the ID # you want delete...");
  uint8_t id = 0;
  while (true) {
    while (! Serial.available());
    char c = Serial.read();
    if (! isdigit(c)) break;
    id *= 10;
    id += c - '0';
  }
  Serial.print("deleting ID #");
  Serial.println(id);
  deleteFingerprint(id);

}



uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  p = finger.deleteModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }
}


