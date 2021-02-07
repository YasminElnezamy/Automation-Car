int speeed=100; // inital speed

//declaration ultrasonic
#define trigger 7
#define echo 10
unsigned long int duration;
unsigned long int distance;
unsigned long int back_ultra=0;
void setup()
{
    //serial_intil
    Serial.begin(9600);
    //motors  
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    //ultrasonic
    pinMode(trigger,OUTPUT);
    pinMode(echo,INPUT);
    //buzzer
    pinMode(8,OUTPUT);
    //welcome
    Serial.println("Welcome to our smart controlling system");  
    delay(100);
}
void loop()
     {
     char flag=0,flag_pw=0;
     String arr[3]={"yasmin", "zyad", "yehia"}; //user names
     String password[3]={"1234","5678","9876"}; //passwords
     //enter the name 
     Serial.println("Please enter your name");   
     while (Serial.available() == 0) {}    
     String name=Serial.readString();
     name.trim();
     //check the name
    for(unsigned char i =0 ; i<sizeof(arr) ; i++)
    {
        if(name== arr[i])
        { 
          Serial.println("Welcome " + arr[i]); 
        
          for(unsigned char j =0; j<4; j++)
          { 
            //enter the password
            Serial.println("Please enter the password = "); 
             while (Serial.available() == 0) {}  
            String pw = Serial.readString();
            pw.trim();
             //check passowrd
            if(password[i] == pw)
            {
              Serial.println("Correct entry");
              //choose (start - close - inital speed)
              Serial.println("Choose (1) to starting , ");
              Serial.println("Choose (2) to close , ");
              Serial.println("Choose (3) to choose your inital speed ");
              Serial.println("   =   ");
              while (Serial.available() == 0) {}
              String lab=Serial.readString();
              lab.trim();
              if(lab>= "1" && lab<="3")
              {
                 Serial.println("correct number");
                 if(lab =="1")
                 {
                     start();
                     break;
                 }
                else if(lab =="2")
                 {   
                     Serial.println("Close the system");
                     closee();
                     break;
                 }
                else if(lab=="3")
                 { 
                   Serial.println("what's the inital speed ? ");
                   while(Serial.available()==0){}
                   speeed = Serial.parseInt();
                   Serial.print("the speed  = ");
                   Serial.println(speeed);
                   start();
                   break;
                 }
              }
                else
                {
                  Serial.println("Incorrect entry");
                 }
                    
            break;
            }          
         else
            {
                Serial.println("Incorrect pw");
                flag_pw+=1;
                if(flag_pw==3)
                 {
                     blocked();
                     break;
                 } 
            }
            }
           break;
          } 
            else
          {
            flag+=1;
            if(flag==3)
            {
              Serial.println("Wrong user name");
              Serial.println("try again");
              break;
            }
          }
     }
 }

 void start(void)
 { 
    Serial.println("Control the car");
    while(1)
    {
    while(Serial.available()==0){}
    String var=Serial.readString(); 
    var.trim(); 
    back_ultra= ultrasonic();
    Serial.println(back_ultra);
    if(var=="w" || var == "W")
      {
          forward();
      }
    else if(var=="s" || var == "S")
       {
          back();
       }
    else if(var=="d" || var == "D")
       {
          right();
       }
    else if(var=="a" || var == "A")
       {
          left();
       }
    else if (var=="z" || var == "Z")
       {
          stopp();
       }  
}
 }
 void forward()
  {  
     //message inital speed 
      if(speeed== 100)
        {
          Serial.print("The speed = ");
          Serial.println(speeed);
        }
     //forward
     Serial.println("Forward");
    do
      {
      //motor1 
      analogWrite(3,speeed);
      analogWrite(5,0);
      //motor2
      analogWrite(6,0);
      analogWrite(9,speeed);
      
      back_ultra= ultrasonic();
      Serial.println(back_ultra);
      delay(1000);
}
while(Serial.available()==0);
   }

void back()
{   
  //message inital speed 
    if(speeed== 100)
      {
        Serial.print("The speed = ");
        Serial.println(speeed);
      }
  //back
  Serial.println("Back");
do
  {  
    //motor1
   analogWrite(3,0);
   analogWrite(5,speeed);
   //motor2
   analogWrite(6,speeed);
   analogWrite(9,0);

    
   back_ultra= ultrasonic();
   Serial.println(back_ultra);
   delay(1000);
}
while(Serial.available()==0);
 }

void right()
{
    //message inital speed 
    if(speeed== 100)
      {
        Serial.print("The speed = ");
        Serial.println(speeed);
      }
   //right
   Serial.println("Right");
   do
   { 
   //motor1 
   analogWrite(3,0);
   analogWrite(5,0);
   //motor2
   analogWrite(6,0);
   analogWrite(9,speeed);
   
   back_ultra= ultrasonic();
   Serial.println(back_ultra);
   delay(1000);
   }
   while(Serial.available()==0);
} 
void left(void)
{   
    //message inital speed 
    if(speeed== 100)
      {
        Serial.print("The speed = ");
        Serial.println(speeed);
      }
  //left
   Serial.println("Left");
   do
   {
    //motor1 
   analogWrite(3,speeed);
   analogWrite(5,0);
   //motor2
   analogWrite(6,0);
   analogWrite(9,0); 

    
   back_ultra= ultrasonic();
   Serial.println(back_ultra);
   delay(1000);
  }
  while(Serial.available()==0);
} 
 void stopp(void)
{ 
   Serial.println("close the system ,press (1) ");
   Serial.println("Repeat the system ,press (2) ");
   while(Serial.available()==0){}
   String pres=Serial.readString();
   pres.trim();
   if(pres == "1")
   {
     Serial.println("Close the system");
      //stop motor1 
     analogWrite(3,0);
     analogWrite(5,0);
     //stop motor2
     analogWrite(6,0);
     analogWrite(9,0);
     closee();
   }
   else if ( pres == "2")
   {  
     Serial.println("Repeat the system");
      //stop motor1 
     analogWrite(3,0);
     analogWrite(5,0);
     //stop motor2
     analogWrite(6,0);
     analogWrite(9,0);
     loop();   
   }
}
void  blocked(void)
 {
  String pres;
  digitalWrite(8,HIGH);
  Serial.println("Blocked for 2 sec");
  delay(1000);
  Serial.println("1 sec");
  delay(1000);
  Serial.println("2 sec");
  Serial.println("Unblocked");
  Serial.println("To stop buzzer press 1 =");
  Serial.println("To stop buzzer and start again press 2 =");
  while(Serial.available()==0){}
  pres= Serial.readString();
  pres.trim();
  if(pres=="1")
  {
  digitalWrite(8,LOW);
   while(Serial.available()==0){}
  }
  else if(pres=="2")
  {
  digitalWrite(8,LOW);
  
  }
 }

 void closee(void)
{
 while(1);
}

int ultrasonic(void)
{
     Serial.print("ultrasonic reading = ");
     digitalWrite(trigger,LOW);
     delay(1);
     digitalWrite(trigger,HIGH);
     delayMicroseconds(10);
     digitalWrite(trigger,LOW);
     duration = pulseIn(echo,HIGH);
     distance = duration*.034 /2; //calculate distance
     return distance;  
}
