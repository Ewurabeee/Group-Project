#include <M5Core2.h>

void setup() {
  M5.begin();
  Serial.begin(9600);
  int x = M5.IMU.Init(); //
  Serial.println(x); 
}

void loop() {
  menu();
}

//Presents a menu to the user
void menu() {
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextWrap(true, true);    //Turn on automatic line wrapping for x and y axis
  M5.Lcd.setTextSize(3);
  M5.Lcd.drawString("Welcome to StressX", 0, 100);
  delay(3000);
  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("StressX", 30, 40); //Provides options to user
  M5.Lcd.drawString("A.Stress Detector", 10, 80);
  M5.Lcd.drawString("B.Panacea", 10, 120);
  while (1){
    M5.update(); //Reads user input
    //Checks for option selected
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(100000, 200000)) {
      M5.Lcd.clear();
      M5.Lcd.setCursor(0, 0);
      int h = movement(); //Returns quantified value for stress tremor 
      M5.Lcd.clear();
      M5.Lcd.setCursor(0,0);
      if(h>20) {  //Action if stress level is significant
        M5.Lcd.clear();
        M5.Lcd.setCursor(0, 0);
        questions();
        break;
      }
      else {  //Action if stress level
        M5.Lcd.setTextSize(2);
        M5.Lcd.println("No significant stress was detected");
        delay(5000);
        M5.Lcd.clear();
        M5.Lcd.setCursor(0,0);
        break;
      }
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(100000, 200000)) { //Provides temporary solution
      M5.Lcd.clear();
      M5.Lcd.setCursor(0,0);
      M5.Lcd.drawString("A.Meditation", 10, 40); //Provides user with options
      M5.Lcd.drawString("B.Calming music", 10, 80);
      while (1) {
        M5.update(); //Reads user input
        if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(100000, 200000)) {
          M5.Lcd.clear();
          M5.Lcd.setCursor(0, 0);
          M5.Lcd.qrcode("https://www.youtube.com/watch?v=nMfPqeZjc2c", 40, 10, 220, 6); //Provides a link for to external resource in the form of a qr code
          delay(15000);
          meditation();
          break; 
        }
        else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(100000, 200000)) {
          M5.Lcd.clear();
          M5.Lcd.setCursor(0, 0);
          M5.Lcd.println("Scan the code");
          delay(5000);
          M5.Lcd.clear();
          M5.Lcd.setCursor(0, 0);
          M5.Lcd.qrcode("https://youtu.be/rOor-3U45tI", 40, 10, 220, 6); //Provides a link for to external resource in the form of a qr code
          delay(15000);
          break; 
        }
      }
      break;
    }
  }
}

//Questionnaire following the tremor analysis
int questions() {
  M5.Lcd.setTextWrap(true, true);
  int totstresslev = 0;
  int s = 0;
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("You'll be asked to\nrespond to a series of\nstatements to help assess your level of stress");
  delay(10000);

  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Your feedback will be\nrecorded by pressing\nbutton A, B, or C");
  delay(10000);

  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("The answers to the\nquestions will be with\nregards to the frequency\nof occurrence");
  delay(10000);

  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Button A corresponds to\nhaving the experience\nrarely");
  M5.Lcd.println(" ");
  M5.Lcd.println("Button B corresponds to\nhaving the experience\nsometimes");
  M5.Lcd.println(" ");
  M5.Lcd.println("Button C corresponds to\nhaving the experience\noften");
  delay(5000);

  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Press B to continue");
  while (1){
  M5.update();
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(100000, 200000)) {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    break;
  }
  }

  M5.Lcd.setTextSize(2);
  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 1", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I generally feel sleepy\nduring the day");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 2", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I have a lot of financial responsibilities to\nfulfill");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 3", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I tend to have mood swings");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 4", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I suffer from chronic\nbouts of an ailment\n(asthma, rheumatism, etc)");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 5", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I have no personal time\nfor myself because of my\nwork schedule");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 6", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I do not attend well-being\nand counseling sessions\norganized by my school");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 7", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I feel angry when things\nget out of control");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 8", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I approach problems with\npessimism");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 9", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I experience dizziness,\nfever, and/or diarrhea");
  s=stresslevel();
  totstresslev += s;
  
  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 10", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I suffer from low morale\nor self-confidence");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 11", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("My work leaves no time\nto contribute to the\ndemands at home");
  s=stresslevel();
  totstresslev += s;

  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.drawString("Question 12", 0, 0);
  M5.Lcd.setCursor(0, 30);
  M5.Lcd.println("I am expected to do more\nthan I am trained for");
  s=stresslevel();
  totstresslev += s;
 
  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.printf("Your stress level was\nquantified to be %d out\nof 36", totstresslev);
  M5.Lcd.println(" ");
  delay(7000);
  
  //Evaluation of responses
  if (totstresslev >= 24) { 
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.println("Your stress level is high");
    M5.Lcd.println(" ");
    M5.Lcd.println("You should consider\nvisiting a psychologist\nimmediately for expert\nadvice");
    delay(7000);
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.println("For tips,scan the\nfollowing QR code");
    delay(7000);
    M5.Lcd.clear();
    M5.Lcd.qrcode("https://www.healthline.com/nutrition/16-ways-relieve-stress-anxiety", 40, 10, 220, 6); //Provides a link for to external resource in the form of a qr code
    delay(15000);
    M5.Axp.DeepSleep(SLEEP_SEC(1));
  }
  else if (totstresslev >= 12 && totstresslev < 24) {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.println("Your stress level is\nmedium");
    M5.Lcd.println(" ");
    M5.Lcd.println("Meditation is recommended");
    delay(5000);
    M5.Axp.DeepSleep(SLEEP_SEC(1));
  }
  else if (totstresslev < 12) {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.println("Your stress level is\nlow");
    M5.Lcd.println(" ");
    M5.Lcd.println("You should consider\ngetting enough rest");
    delay(5000);
    M5.Axp.DeepSleep(SLEEP_SEC(1));
  }
  delay(5000);

  //Returns to the menu
  M5.Lcd.clear();
  M5.Lcd.setCursor(0,0);
  M5.Lcd.println("Press B to continue");
  while (1){
  M5.update();
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(100000, 200000)) {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    break;
    }
  }
 
}

//Calculates the stress points associated with answers to questions
int stresslevel() {
  int s=0;
  while (true) {
    M5.update();
    if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(10000, 2000)) {
      s += 1;
      M5.Lcd.clear();
      M5.Lcd.setCursor(0,0);
      return s;
      break;
    }
    else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(10000, 2000)) {
      s += 2;
      M5.Lcd.clear();
      M5.Lcd.setCursor(0,0);
      return s;
      break;
    }
    else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(10000, 2000)) {
      s += 3;
      M5.Lcd.clear();
      M5.Lcd.setCursor(0,0);
      return s;
      break;
    }
   
  }
}


//Breathing exercise
void meditation() {
  int i=0;
  while ( i < 4) {
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);
    M5.Lcd.setTextSize(3);
    M5.Lcd.drawString("Breathe in", 0, 110);
    delay(3000);
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);
    M5.Lcd.drawString("Hold your breath", 0, 110);
    delay(3000);
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);
    M5.Lcd.drawString("Breathe out", 0, 110);
    delay(3000);
    i++;
  }

}


int movement()
{
    // define variables for storing inertial sensor data
    float gyroX = 0.0F;
    float gyroY = 0.0F;
    float gyroZ = 0.0F;
   
   
    //define variables to calculate the different directions
    float x_c;
    float y_c;
    float z_c;
   
    //define a variable to calculate the sum
    float sumx = 0;
    float sumy = 0;
    float sumz = 0;
   
    // define a variable to calculate the average
    float averagex;
    float averagey;
    float averagez;
   
    float ctr = 0;
    float total_average;//define a variable to calculate the average of the three directions
    float prev_total_average = 0; //define and initialize a variable to store the previous average value of each iteration.
   
    unsigned long startTime; //define a variable to store the duration of each iteration
    unsigned long endTime;
    int pt = 0;

    int start;
    int endt;
    
    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);

    M5.Lcd.clear();
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("Place device in your palm");
    delay(7000);

    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);
   
    startTime = millis(); //initialize the start time to milliseconds  
    endTime = startTime;

    while ((endTime - startTime) <= 10000)
    {
      
      M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ); //Stores the triaxial gyroscope data of the inertial sensor to the relevant variable
      
      M5.Lcd.clear(); 
      M5.Lcd.setCursor(0,0); //Move the cursor position to (x,y).
      M5.Lcd.drawString("Running...", 30, 60);
      x_c = abs(gyroX); //store the absolute value of the change in direction
      y_c = abs(gyroY);
      z_c = abs(gyroZ);
      start = millis(); //initialize the start time to milliseconds  
      endt = start;

      while ((endt - start) <= 500) //loops every half of a second
      {
          sumx += x_c; //find the sum of the change in direction to find the average
          sumy += y_c;
          sumz += z_c;
          ctr++;
          M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
          x_c = abs(gyroX);
          y_c = abs(gyroY);
          z_c = abs(gyroZ);
          endt = millis();
          delay(5);
      }

      averagex = (sumx / ctr); //calculate the average change in direction for one second
      averagey = (sumy / ctr);
      averagez = (sumz / ctr);

      total_average = ((averagex + averagey + averagez) / 3);

      //Plots total average
      Serial.print("total average: ");
      Serial.println(total_average);
      //minimizes the number of intentional (non stress related) movements
      if (abs(total_average - prev_total_average) < 60) {
          //for low range of movement
          if (total_average > 60 && total_average < 120) {
              pt = pt + 2;
          }
          // for medium level of movement
          if (total_average >= 120 && total_average < 240) {
              pt = pt + 5;
          }
          //for high level of movement
          if (total_average >= 240) {
              pt = pt + 10;
          }
          //Plots point
          Serial.print("Points: ");
          Serial.println(pt);
      }
      if (pt > 20) {
          M5.Axp.SetLDOEnable(3, true);
          delay(1000);
          M5.Axp.SetLDOEnable(3, false);
          break;
      }
      prev_total_average = total_average;
      sumx = 0;
      sumy = 0;
      sumz = 0;
      ctr = 0;
      endTime = millis();
      delay(5);
  }
  M5.Axp.SetLDOEnable(3, true);
  delay(1000);
  M5.Axp.SetLDOEnable(3, false);
  return pt;
}