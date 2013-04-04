// Zigbee SDK platform dependent header
#ifndef _ZIGBEE_HAL_HEADER
#define _ZIGBEE_HAL_HEADER

#ifdef __cplusplus
extern "C" {
#endif


#include "libpandora.h"
#include "usb_type.h"

#define PACKET_DATA0    		2
#define INVERSE_PACKET_DATA0 	3
#define PACKET_DATA1    		4
#define INVERSE_PACKET_DATA1 	5
#define PACKET_LENGTH 			6



int zgb_hal_open( int devIndex, int baudrate );
void zgb_hal_close(void);
int zgb_hal_tx( unsigned char *pPacket, int numPacket );
int zgb_hal_rx( unsigned char *pPacket, int numPacket );

#ifdef __cplusplus
}
#endif

#endif
