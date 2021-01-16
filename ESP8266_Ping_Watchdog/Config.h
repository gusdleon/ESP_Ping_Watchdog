#define ssid "SSID"
#define password "PASSWORD"

char host_remoto[] = "Nombre_De_Host_Remoto_O_IP";

char nombre_mdns[] = "Ping_Watchdog";

byte n_pings = 1; //numero de pings a realizar

#define IFTTT_host "maker.ifttt.com"
#define IFTTT_Maker_Key "TU_KEY" //Añade tus credenciales de IFTTT, Puedes encontrar tu key en https://ifttt.com/maker_webhooks/settings
#define IFTTT_Event "TU_EVENTO" //Añade el nombre de tu evento, para esto tendras que haber creado primero un Applet en IFTTT con el Trigger Webhooks

// Huella digital de *.ifttt.com expira el 29/05/2021 pero es posible que deje de funcionar antes.
const uint8_t huellaDigital[20] = {0x24, 0x8E, 0x25, 0x32, 0x85, 0xE5, 0xE8, 0x64, 0x2C, 0xC9, 0x94, 0x41, 0x1A, 0xB2, 0xFB, 0x84, 0x36, 0x2B, 0xDD, 0x09};

unsigned long intervalo = 30000;
