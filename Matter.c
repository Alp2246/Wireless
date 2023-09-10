#include <stdio.h>

// Matter cihazı için temel yapı
typedef struct {
    int device_id;
    char device_name[50];
} MatterDevice;

// Matter cihazının başlatılması
void matter_init(MatterDevice* device, int id, const char* name) {
    device->device_id = id;
    snprintf(device->device_name, sizeof(device->device_name), "%s", name);
}

// Matter cihazının bir diğer cihaza mesaj göndermesi
void matter_send_message(MatterDevice* sender, MatterDevice* receiver, const char* message) {
    printf("%s cihazı, %s cihazına mesaj gönderiyor: %s\n", sender->device_name, receiver->device_name, message);
}

int main() {
    // Matter cihazlarını başlat
    MatterDevice device1, device2;
    matter_init(&device1, 1, "Cihaz 1");
    matter_init(&device2, 2, "Cihaz 2");

    // Mesaj gönderme
    matter_send_message(&device1, &device2, "Merhaba, Matter!");

    return 0;
}
