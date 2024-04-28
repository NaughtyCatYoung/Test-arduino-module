//! I don't know the link to the product. I found it at my school
#define IN1 2
#define IN2 3
//pin IN1 connect to digital 2 and IN2 connect to digital 3
bool signal1=false,signal2=false;
void setup()
{
    Serial.begin(9600);
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
}

void loop()
{
    if(Serial.available())
    {
        int command=Serial.read();
        if(command=='1')
        {
            signal1^=1;
        }
        else if(command=='2')
        {
            signal2^=1;
        }

    }
    if(signal1)
        digitalWrite(IN1,HIGH);
    else 
        digitalWrite(IN1,LOW);
    if(signal2)
        digitalWrite(IN2,HIGH);
    else
        digitalWrite(IN2,LOW);
    Serial.print("IN1 = ");
    Serial.print(signal1? "HIGH  ":"LOW  ");
    Serial.print("IN2 = ");
    Serial.print(signal2? "HIGH":"LOW");
    Serial.println(" ");
}