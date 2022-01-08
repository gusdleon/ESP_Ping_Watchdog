// Seleccione el Sistema de archivos descomentando una de las siguientes 3 lineas

#define USAR_SPIFFS
//#define USAR_LITTLEFS
//#define USAR_SDFS


#if defined USAR_SPIFFS
#include <FS.h>
#include "SPIFFS.h"
//#define FORMAT_SPIFFS_IF_FAILED true
#define fileSystem SPIFFS
//SPIFFSConfig fileSystemConfig = SPIFFSConfig();


#elif defined USAR_LITTLEFS
//#include <LittleFS.h>
#define fileSystem LittleFS
//LittleFSConfig fileSystemConfig = LittleFSConfig();


#elif defined USAR_SDFS
#include <SDFS.h>
#define fileSystem SDFS
SDFSConfig fileSystemConfig = SDFSConfig();


#else
#error Por Favor seleccione un sistema de archivos primero, descomentando uno de las lineas "#define USAR_xxx" al inicio de el archivo File_System.h
#endif
