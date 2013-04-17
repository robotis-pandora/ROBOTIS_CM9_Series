
#include "HaViMo2.h"

//##############################################################################
void havCap(uint8_t id)
{
	Dxl.writeByte(id, 0, 0);
}

//##############################################################################
uint8_t havGet(uint8_t id, HaViMo2_Region_Buffer_t* hvm2rb)
{
    if (hvm2rb==0)
        return 0xFF;

    while (giBusUsing);
	hvm2rb->valid = 0;
    uint8_t i;
    for (i=0; i<15; i++)
    {
        Dxl.setTxPacketId(id);
        Dxl.setTxPacketInstruction(INST_READ);
        Dxl.setTxPacketParameter(0, ((i+1)*16));
        Dxl.setTxPacketParameter(1, 16);
        Dxl.setTxPacketLength(4);

        Dxl.txrxPacket();

        if (Dxl.getRxPacketLength()==(16+2))
        {
        	hvm2rb->valid++;
        }
        else
        {
            return hvm2rb->valid;
        }

        hvm2rb->rb[i].Index=Dxl.getRxPacketParameter(0);
        hvm2rb->rb[i].Color=Dxl.getRxPacketParameter(1);
        hvm2rb->rb[i].NumPix=(
                (uint16_t)Dxl.getRxPacketParameter(2)+
                ((uint16_t)Dxl.getRxPacketParameter(3)<<8));
        hvm2rb->rb[i].SumX=
                (
                    ((uint32_t)Dxl.getRxPacketParameter(4)+
                    ((uint32_t)Dxl.getRxPacketParameter(5)<<8)+
                    ((uint32_t)Dxl.getRxPacketParameter(6)<<16))
                );
        hvm2rb->rb[i].SumY=
                (
                    ((uint32_t)Dxl.getRxPacketParameter(8)+
                    ((uint32_t)Dxl.getRxPacketParameter(9)<<8)+
                    ((uint32_t)Dxl.getRxPacketParameter(10)<<16))
                );
        hvm2rb->rb[i].MaxX=Dxl.getRxPacketParameter(12);
        hvm2rb->rb[i].MinX=Dxl.getRxPacketParameter(13);
        hvm2rb->rb[i].MaxY=Dxl.getRxPacketParameter(14);
        hvm2rb->rb[i].MinY=Dxl.getRxPacketParameter(15);
    }
    return hvm2rb->valid;
}
