//https://th.cytron.io/c-motor-driver/p-20amp-6v-30v-dc-motor-driver

//*press 1 to decrease speed and 2 to increase speed.

class Cytron_20a_motor_driver
{
private:
    int PWM, DIR;
public:
    Cytron_20a_motor_driver(int pwm, int dir) : PWM(pwm), DIR(dir)
    {
        pinMode(PWM, OUTPUT);
        pinMode(DIR, OUTPUT);
    }

    void set_speed(int speed)
    {
        if (speed > 255 || speed < -255)  // Fixed the condition for out-of-range speed
        {
            Serial.println("Speed is out of range");
            return;
        }
        
        if (speed == 0)
        {
            analogWrite(PWM, 0);
            digitalWrite(DIR, LOW);
        }
        else if (speed > 0)
        {
            analogWrite(PWM, speed);
            digitalWrite(DIR, LOW);
        }
        else
        {
            analogWrite(PWM, -speed);
            digitalWrite(DIR, HIGH);
        }
    }
};

int speeda = 0;
int increasement = 51;

Cytron_20a_motor_driver motor1(2, 22);

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