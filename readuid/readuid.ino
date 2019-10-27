
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          
#define SS_PIN          10         

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

int a = true;

void setup() {
	Serial.begin(9600);		
	while (!Serial);		
	SPI.begin();			
	mfrc522.PCD_Init();		
	delay(4);				
	mfrc522.PCD_DumpVersionToSerial();	
	Serial.println(F("Scan kartu..."));

  pinMode(7,OUTPUT);
}

void loop() {
	
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}

	// Mendebug semua output
	//mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  //mengambil hanya uid saja
  String rfidUid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfidUid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    rfidUid += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  Serial.print(rfidUid);
  Serial.println("");
  

  if(rfidUid=="046b4cda082a80" || rfidUid=="46b4cda82a80")
  {
    
      
      Serial.print("Cocok.");
      //disini kita hidupkan led;    
      digitalWrite(7,a);

      a = !a;
  }

  delay(1000);

 
}
