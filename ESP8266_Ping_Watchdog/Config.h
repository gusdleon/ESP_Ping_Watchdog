#define ssid "SSID"
#define password "PASSWORD"

char host_remoto[] = "Nombre_De_Host_Remoto_O_IP";

char nombre_mdns[] = "Ping_Watchdog";

byte n_pings = 1; //numero de pings a realizar

#define IFTTT_host "maker.ifttt.com"
#define IFTTT_Maker_Key "TU_KEY" //Añade tus credenciales de IFTTT, Puedes encontrar tu key en https://ifttt.com/maker_webhooks/settings
#define IFTTT_Event "TU_EVENTO" //Añade el nombre de tu evento, para esto tendras que haber creado primero un Applet en IFTTT con el Trigger Webhooks

// Huella digital de *.ifttt.com expira el 28/09/2020 pero es posible que deje de funcionar antes.
const uint8_t huellaDigital[20] = {0xaa, 0x75, 0xcb, 0x41, 0x2e, 0xd5, 0xf9, 0x97, 0xff, 0x5d, 0xa0, 0x8b, 0x7d, 0xac, 0x12, 0x21, 0x08, 0x4b, 0x00, 0x8c};

unsigned long intervalo = 30000;
