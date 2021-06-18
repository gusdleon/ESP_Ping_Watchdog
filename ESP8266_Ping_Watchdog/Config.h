#define ssid "SSID"
#define password "PASSWORD"

char host_remoto[] = "Nombre_De_Host_Remoto_O_IP";

char nombre_mdns[] = "Ping_Watchdog";

byte n_pings = 1; //numero de pings a realizar

#define IFTTT_host "maker.ifttt.com"
#define IFTTT_Maker_Key "TU_KEY" //Añade tus credenciales de IFTTT, Puedes encontrar tu key en https://ifttt.com/maker_webhooks/settings
#define IFTTT_Event "TU_EVENTO" //Añade el nombre de tu evento, para esto tendras que haber creado primero un Applet en IFTTT con el Trigger Webhooks

// Huella digital de *.ifttt.com expira el 29/04/2022 pero es posible que deje de funcionar antes.
const uint8_t huellaDigital[20] = {0xB8, 0x71, 0x16, 0x7C, 0x62, 0x9F, 0x5E, 0xAA, 0x33, 0x46, 0x83, 0x2A, 0x7E, 0x95, 0xAD, 0x4B, 0xE6, 0xB2, 0xB8, 0x07};

unsigned long intervalo = 30000;
