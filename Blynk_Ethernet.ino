//#define BLYNK_PRINT Serial
#include <SPI.h>
#include <Ethernet2.h>
#include <BlynkSimpleEthernet2.h>
#include <Wire.h>
#include <LCD.h>
HardwareSerial Serial( PA10, PA9 ); 
LCD lcd1(16,2);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

// Remark "#include author.h" and write the Blynk token
//  that you got yourself as follows instead.
//#include  "author.h"
//#ifndef  __AUTHORED__
char auth[] = "ZxdV0ZDYBnvJBJ7cMT31wEBmCre2LD4B";  // token
//#endif  /* __AUTHORED__ */

byte mac[] = {0x80, 0x1F, 0x12, 0xF8, 0x41, 0xC8};

#define  ACT_LED    PB4
#define  RED_LED    PB3

#define  TXD6       PC6
#define  RXD6       PC7
#define  RTS6       PC8
#define  TXD1       PA9
#define  RXD1       PA10
#define  USBDM      PA11
#define  USBDP      PA12
#define  USBON      PA15
#define  SCL1       PB6
#define  SDA1       PB7

#define  SPI2_MOSI  PB15
#define  SPI2_MISO  PB14
#define  SPI2_SCK   PB13
#define  W5500_CS   PB12
#define  W5500_RST  PA8
#define  W5500_INT  PC9

#define  DIO0       PB9
#define  DIO1       PC13
#define  DIO2       PC14
#define  DIO3       PC15

#define  IN00       PC0
#define  IN01       PC1
#define  IN02       PC2
#define  IN03       PC3
#define  IN04       PA0
#define  IN05       PA1
#define  IN06       PA2
#define  IN07       PA3

#define  OUT00      PA4
#define  OUT01      PA5
#define  OUT02      PA6
#define  OUT03      PA7
#define  OUT04      PC4
#define  OUT05      PC5
#define  OUT06      PB0
#define  OUT07      PB1

#define  LCD_RES    PB5
bool stat;

void setup()
{
  // Debug console
  Serial.begin( 115200UL );

  pinMode( ACT_LED, OUTPUT );
  digitalWrite( ACT_LED, LOW );
  pinMode( W5500_RST, OUTPUT );
  digitalWrite( W5500_RST, LOW );
  delay( 10UL );
  digitalWrite( W5500_RST, HIGH );
  delay( 500UL );

  // SPI connected with w5500 initialize.
  SPI.setMISO( SPI2_MISO );
  SPI.setMOSI( SPI2_MOSI );
  SPI.setSCLK( SPI2_SCK );
  SPI.setSSEL( W5500_CS );

  //Blynk.begin( auth );  
 Blynk.begin( auth,"blynk-cloud.com",8080,mac );
  // You can also specify server:
  //Blynk.begin(auth, "blynk-cloud.com", 80);
  //Blynk.begin(auth, IPAddress(192,168,1,100), 8080);
  
  Wire.begin();
  lcd1.initLCD();
  lcd1.setcursor(0,0);
  lcd1.printchar("Status : ");
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
  stat=digitalRead(ACT_LED);
  lcd1.setcursor(10,0);
  if(stat==true){lcd1.printchar("ON ");}
  else {lcd1.printchar("OFF");}
}

/*
  blynk virtual pin 0 function.
    connected with act led.
*/
BLYNK_WRITE( V0 ) //
{ 
  int value = param.asInt();
  if( value == 0 ) digitalWrite( ACT_LED, LOW );
  else  digitalWrite( ACT_LED, HIGH );
}
