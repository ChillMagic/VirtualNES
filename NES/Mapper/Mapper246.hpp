﻿//////////////////////////////////////////////////////////////////////////
// Mapper246  Phone Serm Berm                                           //
//////////////////////////////////////////////////////////////////////////

void    Mapper246::Reset()
{
	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
}

void	Mapper246::WriteLow( WORD addr, BYTE data )
{
	if( addr>=0x6000 && addr<0x8000 ) {
		switch( addr ) {
			case 0x6000:
				MMU.SetPROM_8K_Bank( 4, data );
				break;
			case 0x6001:
				MMU.SetPROM_8K_Bank( 5, data );
				break;
			case 0x6002:
				MMU.SetPROM_8K_Bank( 6, data );
				break;
			case 0x6003: 
				MMU.SetPROM_8K_Bank( 7, data );
				break;
			case 0x6004:
				MMU.SetVROM_2K_Bank(0,data);
				break;
			case 0x6005:
				MMU.SetVROM_2K_Bank(2,data);
				break;
			case 0x6006:
				MMU.SetVROM_2K_Bank(4,data);
				break;
			case 0x6007:
				MMU.SetVROM_2K_Bank(6,data);
				break;
			default:
				MMU.CPU_MEM_BANK[addr>>13][addr&0x1FFF] = data;
				break;
		}
	}
}
