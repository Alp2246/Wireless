#include <SPI.h>
#include <DW1000.h>

// Pin tanımlamaları
#define DW1000_RST 9
#define DW1000_IRQ 2

DW1000 dw1000;

void setup() {
  // Seri haberleşme başlat
  Serial.begin(115200);

  // DW1000 çipi başlat
  dw1000.begin(DW1000_RST, DW1000_IRQ);
  dw1000.setDefaults();
  dw1000.setDeviceAddress(0x12345678);  // Kendi cihaz adresinizi ayarlayın
}

void loop() {
  // Mesaj gönderme
  char message[] = "Merhaba, UWB!";
  dw1000.newTransmit();
  dw1000.setDestinationAddress(0x87654321);  // Alıcı cihazın adresini ayarlayın
  dw1000.setNetworkId(0xDECA);
  dw1000.setAntennaDelay(16436);
  dw1000.send(message, strlen(message));
  dw1000.waitForResponse();
  
  if (dw1000.status == DW1000::WAITING_FOR_RESPONSE) {
    Serial.println("Mesaj gönderildi.");
  } else {
    Serial.println("Mesaj gönderme hatası.");
  }

  // Mesaj alma
  dw1000.newReceive();
  dw1000.startReceive();
  if (dw1000.receiveComplete()) {
    char receivedMessage[64];
    int messageLength = dw1000.getData(receivedMessage);
    receivedMessage[messageLength] = '\0';
    Serial.print("Alınan Mesaj: ");
    Serial.println(receivedMessage);
  }
  
  delay(1000);  // Bir saniye bekle
}
