const int CH_1_PIN = 10;
const int CH_2_PIN = 11;
const int STBY_PIN = 9;
const int AIN1_PIN = 2;
const int AIN2_PIN = 4;
const int APWM_PIN = 5;
const int BIN1_PIN = 7;
const int BIN2_PIN = 8;
const int BPWM_PIN = 6;
const int deadzone = -15;
 
 
void setup () {
pinMode (STBY_PIN, OUTPUT);
pinMode (AIN1_PIN, OUTPUT);
pinMode (AIN2_PIN, OUTPUT);
pinMode (APWM_PIN, OUTPUT);
pinMode (BIN1_PIN, OUTPUT);
pinMode (BIN2_PIN, OUTPUT);
pinMode (BPWM_PIN, OUTPUT);
digitalWrite (STBY_PIN, HIGH);
}
 
 
void loop () {
int y = pulseIn (CH_2_PIN, HIGH, 25000);
int x = pulseIn (CH_1_PIN, HIGH, 25000);
Serial.print("Reciever: ");
Serial.println(y);
y = pulseToPWM(y);
Serial.print("Pulse: ");
Serial.println(y);
x = pulseToPWM(x);
int left = y + x;
Serial.print("Left: ");
Serial.println(left);
int right = y - x;
Serial.print("Right: ");
Serial.println(right);
drive (left, right);
delay (2000);
}
 
 
void drive (int speed_a, int speed_b) {
speed_a = constrain (speed_a, -255, 255);
speed_b = constrain (speed_b, -255, 255);
if ( speed_a == 0 ) {
digitalWrite (AIN1_PIN, LOW);
digitalWrite (AIN2_PIN, LOW);
} else if ( speed_a > 0 ) {
digitalWrite (AIN1_PIN, HIGH);
digitalWrite (AIN2_PIN, LOW);
} else {
digitalWrite (AIN1_PIN, LOW);
digitalWrite (AIN2_PIN, HIGH);
}
if ( speed_b == 0 ) {
digitalWrite (BIN1_PIN, LOW);
digitalWrite (BIN2_PIN, LOW);
} else if ( speed_b > 0 ) {
digitalWrite (BIN1_PIN, HIGH);
digitalWrite (BIN2_PIN, LOW);
} else {
digitalWrite (BIN1_PIN, LOW);
digitalWrite (BIN2_PIN, HIGH);
}
//analogWrite (APWM_PIN, abs (speed_a));
//analogWrite (BPWM_PIN, abs (speed_b));
}
 
 
int pulseToPWM(int pulse) {
if ( pulse > 1000 ) {
pulse = map(pulse, 1000, 2000, -500, 500);
pulse = constrain(pulse, -255, 255);
} else {
pulse = 0;
}
if ( abs(pulse) <= deadzone ) {
pulse = 0;
}
 
 
return pulse;
}
