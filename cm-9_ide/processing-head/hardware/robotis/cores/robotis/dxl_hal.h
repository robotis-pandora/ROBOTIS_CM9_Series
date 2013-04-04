// Dynamixel SDK platform dependent header
#ifndef _DYNAMIXEL_HAL_HEADER
#define _DYNAMIXEL_HAL_HEADER


#ifdef __cplusplus
extern "C" {
#endif


#include "libpandora.h"
//[ROBOTIS]For use u8,u16,...
#include "usb_type.h"
#include "gpio.h"

int dxl_hal_open( int devIndex, int baudrate );
void dxl_hal_close(void);
void dxl_hal_clear(void);
int dxl_hal_tx( unsigned char *pPacket, int numPacket );
int dxl_hal_rx( unsigned char *pPacket, int numPacket );
void dxl_hal_set_timeout( int NumRcvByte );
int dxl_hal_timeout(void);

byte RxByte(void);


void ClearBuffer256(void);
byte CheckNewArrive(void);
u8 CheckTimeOut(void);

vu32      gu32TimingCounter1ms, gw1msCounter;

volatile byte  gbDXLWritePointer;
volatile byte  gbDXLReadPointer;
volatile byte  gbpDXLDataBuffer[256];

void TIM2_IRQHandler(void);
void StartDiscount(s32 StartTime);
void Interrupt1ms(void);


#ifdef BOARD_CM900
#define PORT_ENABLE_TXD			GPIOB
#define PORT_ENABLE_RXD			GPIOB

#define PIN_ENABLE_TXD			4
#define PIN_ENABLE_RXD			5


#define PORT_DXL_TXD			GPIOB
#define PORT_DXL_RXD			GPIOB

#define PIN_DXL_TXD				6
#define PIN_DXL_RXD				7

#elif BOARD_CM900_REV10

#define PORT_TXRX_DIRECTION		GPIOB
#define PIN_TXRX_DIRECTION		5

#define PORT_DXL_TXD			GPIOB
#define PORT_DXL_RXD			GPIOB

#define PIN_DXL_TXD				6
#define PIN_DXL_RXD				7
#endif


#ifdef __cplusplus
}
#endif

#endif
