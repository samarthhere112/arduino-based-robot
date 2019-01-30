#include <SoftwareSerial.h>
#include <Servo.h>

Servo head, left, right;
int degl = 180;
int degr = 0;

boolean obstacle();
char c;


void setup() {
Serial.begin(9600);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT); //Ultrasonic sensor trigPin
pinMode(8, INPUT);  //Ultrasonic Sensor echoPin
head.attach(10);
left.attach(11);
right.attach(9);
head.write(90);
left.write(degl);
right.write(degr);

}
//-----------------------------------------------------------------------//
void loop() {
if (Serial.available() > 0) //Check if there is an available byte to read
{
delay(10); //Delay added to make thing stable
c = Serial.read(); //Conduct a serial read
}


Serial.println(c);

if (!obstacle())
{
if(c == 'u') //forward
{
digitalWrite(3, HIGH);
digitalWrite (4, HIGH);
digitalWrite(5,LOW);
digitalWrite(6,LOW);
delay(100);
}

}



if(c == 'd') //reverse
{
digitalWrite(3, LOW);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
digitalWrite(6,HIGH);
delay(100);
}

else if (c == 'r')  //right
{
digitalWrite (3,HIGH);
digitalWrite (4,LOW);
digitalWrite (5,LOW);
digitalWrite (6,LOW);
delay (100);

}

else if ( c == 'l') //left
{
digitalWrite (3, LOW);
digitalWrite (4, HIGH);
digitalWrite (5, LOW);
digitalWrite (6, LOW);
delay (100);
}

else if ( c == '1') //head left
{
head.write(180);
}

else if ( c == '7' )  //head centre
{
head.write(90);
}

else if ( c == '2') //head right
{
head.write(0);
}

else if ( c == '3'&& degl > 0 )  //left arm up
{
degl -= 45;
left.write(degl);
}

else if ( c == '4'&& degr < 180 ) //right arm up
{
degr += 45;
right.write(degr);
}

else if ( c == '5'&& degr > 0 ) //right arm down
{
degr -= 45;
right.write(degr);
}

else if ( c == '6'&& degl < 180 )  //left arm down
{
degl += 45;
left.write(degl);
}

else if ( c == 'a' )  //AUTORUN
{
while(c=='0')
{
if(!obstacle())        //forward run
{
digitalWrite(3, HIGH);
digitalWrite (4, HIGH);
digitalWrite(5,LOW);
digitalWrite(6,LOW);
delay(100);
}
else               //turn left
{
digitalWrite (3, LOW);
digitalWrite (4, HIGH);
digitalWrite (5, LOW);
digitalWrite (6, LOW);
delay (100);
}
;
if (Serial.available()>0)
{
c=Serial.read();
}
}
}

else if ( c == '0' )   //stop
{
digitalWrite (3, LOW);
digitalWrite (4, LOW);
digitalWrite (5, LOW);
digitalWrite (6, LOW);
delay (100);
}


//reset the variable
}


boolean obstacle()
{
long duration;
int distance;

digitalWrite(7, LOW);
delayMicroseconds(2);

digitalWrite(7, HIGH);
delayMicroseconds(10);
digitalWrite(7, LOW);

duration=pulseIn(8, HIGH);
distance= duration*0.034/2;

if (distance <= 20)
{
return true;
}

return false;

}
