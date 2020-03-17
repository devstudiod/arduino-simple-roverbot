/* This motor shield use Pin 4,5,6,7 to control the motor
 * Simply connect your motors to M1+,M1-,M2+,M2-
 */

const int 
 dir2 = 4
,speed2 = 5
,speed1 = 6
,dir1 = 7
,LED = 13
;
const char
 LEDfON = 0xf1 //(byte)'t'
,LEDOFF = 0xf2 //(byte)'y'
,MTRRUN[] = {6,5,4,0,1,2,3}
,MTRFST = 255
,MTRMED = 128
,MTRSLW = 64
,MTRMAX = 255
,MTRSPD[] = {0,MTRSLW,MTRMED,MTRFST,MTRSLW,MTRMED,MTRFST}
;
const boolean
 MTRREV[] = {false,true,true,true,false,false,false}
;

byte now=0;

void setup(){
	for (int i = 4; i <= 7; i++){ //For Arduino Motor Shield    
		pinMode(i, OUTPUT); //set pin 4,5,6,7 to output mode
	}  
	pinMode(LED, OUTPUT);
	Serial.begin(115200);
}

void loop(){
	int x, delay_en;
	char val;
	
	if(Serial.available()){
		val = Serial.read();

//RUNCODE 
                if(val==now){
                  return;
		}else if(val ==  LEDON){ //led on 
			digitalWrite(LED, HIGH);
		}else if(val ==  LEDOFF){//led off
			digitalWrite(LED, LOW);
		}else if(inrangeof(val/16) && inrangeof(val%16)){
			char ml=val/16, mr=val%16;
			//char ml=val>>4, mr=val & 0x0f;
			//motorRun
			Motor1(MTRSPD[ml],MTRREV[mr]);
                        Motor2(MTRSPD[mr],MTRREV[mr]);
		}
                now = val;
	}
}


boolean inrangeof(char i){
	return (0<= i && i<=6);
}

void Motor1(int pwm, boolean rev){
	analogWrite(speed1, pwm); //set pwm control, 0 for stop, and 255 for maximum speed 
	digitalWrite(dir1, (rev ? HIGH : LOW));
}
void Motor2(int pwm, boolean rev){
	analogWrite(speed2, pwm);
	digitalWrite(dir2, (rev ? HIGH : LOW));
}
