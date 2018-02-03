#include "SimpleBLE.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

SimpleBLE ble;

union macaddr {
    char def[18];
    char bt[18];
};
union macaddr addr;
char localName[128];

void setAddr(){
    const char fmt[30] = "%02X:%02X:%02X:%02X:%02X:%02X";
    uint8_t buf[6];

    esp_efuse_mac_get_default(buf);
    sprintf(addr.def, fmt, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);

    esp_read_mac(buf, ESP_MAC_BT);
    sprintf(addr.bt, fmt, buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
}

void advertise(){
    sprintf(localName, "ESP32: %s", addr.bt);
    Serial.println(localName);
    ble.begin(String(localName));
}

void setup() {
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    delay(1000);

    setAddr();
}

void loop() {
    advertise();
    delay(1000);
}