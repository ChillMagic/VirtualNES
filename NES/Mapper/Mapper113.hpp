﻿//////////////////////////////////////////////////////////////////////////
// Mapper113  PC-Sachen/Hacker                                          //
//////////////////////////////////////////////////////////////////////////
void	Mapper113::Reset()
{
//	MMU.SetPROM_32K_Bank( 0, 1, MMU.PROM_8K_SIZE-2, MMU.PROM_8K_SIZE-1 );
	MMU.SetPROM_32K_Bank( 0 );
	MMU.SetVROM_8K_Bank( 0 );
}

void	Mapper113::WriteLow( WORD addr, BYTE data )
{
//DEBUGOUT( "$%04X:$%02X L=%3d\n", addr, data, nes->GetScanline() );
	switch( addr ) {
		case	0x4100:
		case	0x4111:
		case	0x4120:
		case	0x4194:
		case	0x4195:
		case	0x4900:
			if( nes->rom->GetPROM_CRC() == 0xA75AEDE5 ) { // HES 6-in-1
				if( data & 0x80 ) {
					MMU.SetVRAM_Mirror( VRAM_VMIRROR );
				} else {
					MMU.SetVRAM_Mirror( VRAM_HMIRROR );
				}
			}
			MMU.SetPROM_32K_Bank( data >> 3 );
			MMU.SetVROM_8K_Bank( ((data>>3)&0x08)+(data&0x07) );
			break;
	}
}

void	Mapper113::Write( WORD addr, BYTE data )
{
//DEBUGOUT( "$%04X:$%02X L=%3d\n", addr, data, nes->GetScanline() );
	switch( addr ) {
		case	0x8008:
		case	0x8009:
			MMU.SetPROM_32K_Bank( data >> 3 );
			MMU.SetVROM_8K_Bank( ((data>>3)&0x08)+(data&0x07) );
			break;
		case	0x8E66:
		case	0x8E67:
			MMU.SetVROM_8K_Bank( (data&0x07)?0:1 );
			break;
		case	0xE00A:
			MMU.SetVRAM_Mirror( VRAM_MIRROR4L );
			break;
	}
}
