 /*
1-enroll
2-match
3-clear db
*/
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>
// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial


/****************************Variables for ESP8266***************************************/
#define ESP8266_rxPin 12
#define ESP8266_txPin 13
#define finger_rxpin 10
#define finger_txpin 11
#define CONFIDENCE_THRESHOLD 60 //Not in use currently

//SSID + KEY
const char SSID_ESP[] = "Moto";
const char SSID_KEY[] = "helloworld";

// URLs
const char URL_enroll[] = "GET /enroll.php?";
const char URL_match[] = "GET /match.php?";//?rgb=ON&balarm=OFF GET /receiver.php?apples=56&oranges=23 HTTP/1.1\r\nHost: esp8266.allaboutee.com\r\n\r\n
const char append[] = " HTTP/1.0\r\nHost: pbat.000webhostapp.com\r\n\r\n";//GET https://espha.000webhostapp.com/sensor.php?
//MODES
const char CWMODE = '1';//CWMODE 1=STATION, 2=APMODE, 3=BOTH
const char CIPMUX = '1';//CWMODE 0=Single Connection, 1=Multiple Connections

SoftwareSerial ESP8266(ESP8266_rxPin, ESP8266_txPin);// rx tx
SoftwareSerial mySerial(finger_rxpin, finger_txpin);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//DEFINE ALL FUNCTIONS HERE
String Sense_Values;
boolean setup_ESP();
boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode);
void timeout_start();
boolean timeout_check(int timeout_ms);
void serial_dump_ESP();
boolean connect_attendo();
//int get_enroll();
//int get_match();

//DEFINE ALL GLOBAL VAARIABLES HERE
unsigned long timeout_start_val;
char scratch_data_from_ESP[20];//first byte is the length of bytes
char payload[150];
byte payload_size=0, counter=0;
char ip_address[16];
char data[10];
char state[3];
char onTime[12];
char current_temp[5];
int cost=0;

//DEFINE KEYWORDS HERE
const char keyword_OK[] = "OK";
const char keyword_Ready[] = "Ready";
const char keyword_no_change[] = "no change";
const char keyword_blank[] = "#&";
const char keyword_ip[] = "192.";
const char keyword_rn[] = "\r\n";
const char keyword_quote[] = "\"";
const char keyword_carrot[] = ">";
const char keyword_sendok[] = "SEND OK";
const char keyword_linkdisc[] = "Unlink";



//keywords for youtube
const char keyword_html_start_b[] = "b>";
const char keyword_html_end_b[] = "</b";
/***************************Variables end for esp8266*******************************/


/******************************Variables for r307**************************************/
#define PASS_KEY 128
#define MAX_SPACE 1000

String sid;
int match_counter;
String class_name;
String teacher_name;
int confirm;
uint8_t id; // store id while enrolling
int teacher_pass;
uint8_t enroller();
uint8_t getFingerprintEnroll();
uint8_t readnumber();
uint8_t getFingerprintID();
int getFingerprintIDez();
int clear_db();
/***********************************************************************/

// initialize the library by providing the nuber of pins to it
//LiquidCrystal lcd(8,9,4,5,6,7);

void setup() 
{
  /*lcd.begin(16,2);
  // set cursor position to start of first line on the LCD
  lcd.setCursor(0,0);
  //text to print
  lcd.print("    16x2 LCD");
  // set cusor position to start of next line
  lcd.setCursor(0,1);
  lcd.print("   DISPLAY");*/

  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial3.begin(57600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("PBAT - Attendence System");
  Serial.println("INITIAL SETUP START");
   // set the data rate for the sensor serial port
  
  /****************Start esp8266 And Fingerprint Sensor*****/
  pinMode(ESP8266_rxPin, INPUT);
  pinMode(ESP8266_txPin, OUTPUT);
  ESP8266.begin(9600);//default baudrate for ESP
  ESP8266.listen();//not needed unless using other software serial instances
  delay(2500);//delay before kicking things off
  setup_ESP();//go setup the ESP
  finger.begin(57600);
  if (finger.verifyPassword()) 
  {
    Serial.println("Found fingerprint sensor!");
  } 
  else 
  {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  /**********************************************************/
  
  while(1)
  {
    confirm=0;
    Serial.println("Please tell your id(teacher id) you entered on Server :");
    teacher_name = readstring();
    Serial.print("Your Teacher_id entered is : ");
    Serial.println(teacher_name);
    Serial.print("Is it correct(1/0)?");
    confirm = (int)readnumber();
    if(confirm==1)break;  
  }
  
  
  serialflush();
  while(1)
  {
    confirm=0;
    Serial.println("Please tell the Class name you entered on Server :");
    class_name = readstring();
    Serial.print("Class entered is : ");
    Serial.println(class_name);
    Serial.print("Is it correct(1/0)?");
    confirm = (int)readnumber();
    if(confirm==1)break;
  }
  serialflush();
}


void loop() 
{
  Serial.println("MAIN LOOP START");
  fast_finger();
  finger.getTemplateCount();
  Serial.print("Sensor contains "); 
  Serial.print(finger.templateCount); 
  Serial.println(" templates");
  Serial.println("Menu :");
  Serial.print("1: Enroll  ");
  Serial.print("2: Match  ");
  Serial.println("3: Clr Database");
  uint8_t user_input = readnumber();
  switch(user_input)
  {
    case 1:
          enroller();
          break;
    case 2: 
          while(1)
          {
             fast_finger();
             Serial.println("ATTENDO ON");
             match_counter=50;
             Sense_Values = "tid=";
             Sense_Values += teacher_name;
             Sense_Values += "&cname=";
             Sense_Values += class_name;
             Sense_Values += "&id=";
             while(match_counter--)
             {
                 Serial.println(match_counter);
                 getFingerprintIDez();
                 delay(50);
             }
             Serial.println("Would you like to stop match and upload data to server?");
             teacher_pass = readnumber();
             if(teacher_pass==PASS_KEY)break;
          }
          //send data to server
          if(match_cloud())Serial.println("SUCCESS : MARKED ATTENDENCE");
          else
          {
            Serial.println("!!INTERNET FAILURE!!");
            setup_ESP();
            while(!match_cloud())Serial.println("Retrying.........");
          }
          Sense_Values.remove(0,Sense_Values.length());
          break;
    case 3:
          clear_db();
          break;
    default:
          Serial.println("Wrong Input");
  }
  serialflush();
}
