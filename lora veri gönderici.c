#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wiringPi.h>
#include <RH_RF95.h>

// LoRa modülü için SPI bağlantıları
#define RFM95_CS_PIN 6
#define RFM95_RST_PIN 0

// LoRa modülü nesnesi
RH_RF95 rf95(RFM95_CS_PIN, RFM95_RST_PIN);

void setup() {
    wiringPiSetup();
    if (!rf95.init()) {
        fprintf(stderr, "LoRa modülü başlatılamadı!\n");
        return;
    }
    rf95.setFrequency(915.0); // Frekansı ayarlayın (915 MHz)
    rf95.setTxPower(23, false); // TX gücünü ayarlayın (23dBm)
}

void loop() {
    char message[] = "Merhaba, LoRa!";
    rf95.send((uint8_t *)message, strlen(message));
    rf95.waitPacketSent();
    printf("Veri gönderildi: %s\n", message);
    delay(5000); // 5 saniye bekle
}

int main() {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
