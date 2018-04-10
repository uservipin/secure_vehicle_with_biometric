//input finger id ti module
//insert key to power the finger print module
//insert finger print
//check valid id and
//open feature

// if key lost bypass the key circuit
//open bluetooth module
//send data to initialize relay to power the finger print
int data = 0;
String password;
String vipin = "VIPIN";



void setup() {
  Serial.begin(9600);
  Serial.println("WELCOME TO WORLD OF SRIAL PRINT");
  Serial.println(data);
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);

}

void loop() {
  password = Serial.readString();
  Serial.println(password);


//  if (password == vipin) {
//
//    Serial.println("WELCOME IN WORLD OF VIPIN");
//
//    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
//    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
//    //    data = digitalRead(2);
//    Serial.println(data);
//
//    if (data == 1) {
//      digitalWrite(7, HIGH);
//      Serial.println("  in IFFFFF  signal to 12 volt main supply");
//    }
//
//    delay(1000);
//  }

 
  //  data = digitalRead(2);
  //  Serial.println(data);

//  else {
//    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
//    digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
//
//    //    data = digitalRead(2);
//    ////    Serial.println(" print data of seerial read");
//    Serial.println(data);
////
////    if (data == 1) {
////      digitalWrite(7, HIGH);
////
////      Serial.println("  signal read from ELSE signal to 12 volt main supply");
//
//      delay(1000);
//
////    }
//  }
  //


   // put your main code here, to run repeatedly:




   
    digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)

    
  data = digitalRead(2);
  Serial.println("high");
  Serial.println(data);
    delay(1000);


if(Serial.available() == 0){
  Serial.println("inside Serial available");
  
  }


    
  // wait for a second
    digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);
  data = digitalRead(2);
  Serial.println("low");
  Serial.println(data);

  //  if (data == 1) {
  //    digitalWrite(7, HIGH);
  //    Serial.write("signal to 12 volt main supply");
  //  }
  //  else
  //  {
  //    digitalWrite(7, LOW);
  //    Serial.println("no signal to 2 volt to main supply");
  //  }


}





