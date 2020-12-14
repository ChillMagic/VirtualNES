﻿//////////////////////////////////////////////////////////////////////////
// Mapper244                                                            //
//////////////////////////////////////////////////////////////////////////
void	Mapper244::Reset()
{
	MMU.SetPROM_32K_Bank( 0 );
}

void	Mapper244::Write( WORD addr, BYTE data )
{
	if( addr>=0x8065 && addr<=0x80A4 ) {
		MMU.SetPROM_32K_Bank( (addr-0x8065)&0x3 );
	}

	if( addr>=0x80A5 && addr<=0x80E4 ) {
		MMU.SetVROM_8K_Bank( (addr-0x80A5)&0x7 );
	}
}
