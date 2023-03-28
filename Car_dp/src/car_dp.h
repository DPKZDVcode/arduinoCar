
#include "backup.h"

class car{

  public:  
  
    int in1;
    int in2;
    int in3;
    int in4;
    int ena;
    int enb;
    int debugMode = false;

  void init(){

    pinMode(enb, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(in3, OUTPUT);
    
    pinMode(in2, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(ena, OUTPUT);

    digitalWrite(enb, HIGH);
    digitalWrite(ena, HIGH);


  }

  void left(int delayInMs = 0){

    if(debugMode){

      Serial.println("car.left");      
      
    }

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
      
  
    delay(delayInMs);
    
  }

  void right(int delayInMs = 0){

    if(debugMode){
      Serial.println("car.right"); 
    }
    
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    delay(delayInMs);
    
  }

  void forward(int delayInMs = 0){

    if(debugMode){
      Serial.println("car.forward");
    }

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    delay(delayInMs);
    
  }

  void backward(int delayInMs = 0){
    
    if(debugMode){
      Serial.println("car.backward");
    }

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    delay(delayInMs);    
    
  }

  void rotate(int delayInMs = 0){
    
    if(debugMode){      
      Serial.println("car.rotate");  
    }  

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    delay(delayInMs);

  }


  void stop(int delayInMs = 0){

    if(debugMode){  

      Serial.println("car.stop");
      
    } 
     
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
    delay(delayInMs);

  }

  void motorsTest(int delayInMs = 1000){

    forward(delayInMs);

    backward(delayInMs);

    left(delayInMs);

    right(delayInMs);

    rotate(delayInMs);

    stop(delayInMs);

  }

  void execute(String espCMDs){

    String listCMDS[5] = {"forward", "backward", "left", "right", "stop"};
    int listCmdSize = 5;

    String cmdsInOrder = sliceStreamIntoOrder(espCMDs, listCMDS, listCmdSize);

    String lenKey = "lenCMDS-";  

    String lengthCMDs = beforeORafter(cmdsInOrder, lenKey, 0);
    
    String CMDs = beforeORafter(cmdsInOrder, lenKey, 1);
  
    bool fisrtTime = true;
    
    String restCMD = "";

    for(int numCMD = 0; numCMD < lengthCMDs.toInt(); numCMD++){

      String CMD = "";

      if(fisrtTime){

        CMD = beforeORafter(CMDs, String(numCMD), 0);
        
        restCMD = beforeORafter(CMDs, String(numCMD), 1);

        fisrtTime = false;

      }else{

        CMD = beforeORafter(restCMD, String(numCMD), 0);
        
        restCMD = beforeORafter(restCMD, String(numCMD), 1);
        
      }


      if(debugMode){

        Serial.print("CMD: ");
        Serial.println(CMD);
        
      }

      if(wordExistance(CMD, "forward")){

        forward();
        // myCar.stop();
        
      }else if(wordExistance(CMD,"backward")) {
  
        backward();
        // myCar.stop();

      }else if(wordExistance(CMD, "left")) {
        

        left();
        // myCar.stop();

      }else if(wordExistance(CMD, "right")) {


        right();
        // myCar.stop();
        
      }else if (wordExistance(CMD, "stop")){        

        stop();
        
      } 

      
    }
 

  }


};
