#include "zigbee.h"

int main() {
    // Zigbee cihazını başlat
    zigbee_init();

    // Zigbee ağına katıl
    if (zigbee_join_network() == ZIGBEE_OK) {
        printf("Zigbee ağına katılındı.\n");

        while (1) {
            // Algılama işlemi
            int sensor_data = read_sensor_data();
            
            // Veriyi işleme ve kontrol etme
            if (sensor_data > THRESHOLD) {
                char message[] = "Alarm: Tehlikeli Durum!";
                zigbee_send_message(message);
            }

            // Mesaj alındığında işleme geç
            char received_message[50];
            if (zigbee_receive_message(received_message, sizeof(received_message)) == ZIGBEE_OK) {
                printf("Alınan Mesaj: %s\n", received_message);
                // Mesaja göre işlem yap
                if (strcmp(received_message, "Kapat") == 0) {
                    // Cihazı kapat
                    zigbee_shutdown();
                    return 0;
                }
            }

            // Düzenli olarak algılama yapma
            sleep(5); // 5 saniye bekle
        }
    } else {
        printf("Zigbee ağına katılırken bir hata oluştu.\n");
    }

    return 0;
}

/*
Program sürekli olarak bir sensörden veri okur ve bu veriyi işler.
Eğer sensör verisi belirli bir eşiği aşarsa, bir alarm mesajı gönderir.
Program, aynı zamanda diğer cihazlardan gelen mesajları dinler ve bu mesajlara göre işlem yapar.

*/