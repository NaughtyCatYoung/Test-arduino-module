//http://www.micontechlab.com/product/2183/2x-%E0%B8%9A%E0%B8%AD%E0%B8%A3%E0%B9%8C%E0%B8%94%E0%B8%82%E0%B8%B1%E0%B8%9A%E0%B8%94%E0%B8%B5%E0%B8%8B%E0%B8%B5%E0%B8%A1%E0%B8%AD%E0%B9%80%E0%B8%95%E0%B8%AD%E0%B8%A3%E0%B9%8C-mct-hb-40a-h-bridge-10-30vdc-40a
class MCT_HB_40A_H_Bridge
{
private:
    int PWM,IN1,IN2;
    bool break_enable=false;
public:
    int speed_now=0;
    MCT_HB_40A_H_Bridge(int pwm,int in1,int in2):PWM(pwm),IN1(in1),IN2(in2){
        pinMode(PWM,OUTPUT);
        pinMode(IN1,OUTPUT);
        pinMode(IN2,OUTPUT);
    };
    void set_speed(int speed)
    {
        if (speed > 255 || speed < -255)  // Fixed the condition for out-of-range speed
        {
            Serial.println("Speed is out of range");
            return;
        }
        speed_now=speed;
        if(speed==0)
        {
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,LOW);

            if(break_enable)analogWrite(PWM,255);
            else analogWrite(PWM,0);
        }
        else if(speed>0)
        {
            digitalWrite(IN1,HIGH);
            digitalWrite(IN2,LOW);
            analogWrite(PWM,speed);
        }
        else 
        {
            digitalWrite(IN1,LOW);
            digitalWrite(IN2,HIGH);
            analogWrite(PWM,-speed);
        }

        return;
    }
    
};


int speeda = 0;
int increasement = 51;

MCT_HB_40A_H_Bridge motor1(2,22,23);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)  // Added a check for available serial data
    {
        int commanda = Serial.read();

        switch (commanda - '0')
        {
            case 1:
                Serial.println("Decrease");
                speeda = max(speeda - increasement, -255);
                break;
            case 2:
                Serial.println("Increase");
                speeda = min(speeda + increasement, 255);
                break;
            default:
                break;
        }
        Serial.println(speeda);
        motor1.set_speed(speeda);
    }

    delay(10);
}