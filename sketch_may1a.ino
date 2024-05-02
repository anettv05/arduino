#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(5,4,3,2,1,0); 
#define SS_PIN 10
#define RST_PIN 9
#define RELAY 7 //relay pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  lcd.begin(16,2);
    lcd.print("Put you card in reader");
   lcd.setCursor(1,1);
  lcd.print("reader");
  lcd.cursor();
  lcd.blink();
  delay(2000);
  lcd.noBlink();
  lcd.noCursor();
  lcd.clear();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RELAY, OUTPUT);

  digitalWrite(RELAY, HIGH);
  Serial.println("Put your card to the reader...");
  Serial.println();
  

}
void loop() 
{ 
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "EA 51 64 02") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    lcd.print("Access granded");
    digitalWrite(RELAY, LOW);
    Serial.println();
    delay(5000);
    lcd.clear();
    digitalWrite(RELAY, HIGH);
    

  }
 
 else   {
    Serial.println(" Access denied");
    lcd.print("Access denied");
    delay(1000);
    lcd.clear();

  }
}
