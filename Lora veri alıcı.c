#include <stdio.h>
#include <string.h>
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
    if (rf95.available()) {
        uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
        uint8_t len = sizeof(buf);
        if (rf95.recv(buf, &len)) {
            printf("Alınan Veri: ");
            for (int i = 0; i < len; i++) {
                printf("%c", buf[i]);
            }
            printf("\n");
        }
    }
    delay(1000); // 1 saniye bekle
}

int main() {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
