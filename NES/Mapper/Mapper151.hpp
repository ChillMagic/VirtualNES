﻿//////////////////////////////////////////////////////////////////////////
// Mapper151 VS-Unisystem                                               //
//////////////////////////////////////////////////////////////////////////
void	Mapper151::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

#if	0
	DWORD	crc = nes->rom->GetPROM_CRC();
	if( crc == 0x1E438D52 ) {
		DirectDraw.SetVsPalette( 7 );	//VS_Goonies
	}
	if( crc == 0xD99A2087 ) {
		DirectDraw.SetVsPalette( 6 );	//VS_Gradius
	}
#endif
}

void	Mapper151::Write( WORD addr, BYTE data )
{
	switch( addr ) {
		case 0x8000:
			nes->mmu.SetPROM_8K_Bank( 4,data );
			break;
		case 0xA000:
			nes->mmu.SetPROM_8K_Bank( 5,data );
			break;
		case 0xC000:
			nes->mmu.SetPROM_8K_Bank( 6,data );
			break;
		case 0xE000:
			nes->mmu.SetVROM_4K_Bank( 0, data );
			break;
		case	0xF000:
			nes->mmu.SetVROM_4K_Bank( 4, data );
			break;
	}
}
