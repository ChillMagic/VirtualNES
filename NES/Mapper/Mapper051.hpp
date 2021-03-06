﻿//////////////////////////////////////////////////////////////////////////
// Mapper051  11-in-1                                                   //
//////////////////////////////////////////////////////////////////////////
void	Mapper051::Reset()
{
	bank = 0;
	mode = 1;

	SetBank_CPU();

	nes->mmu.SetCRAM_8K_Bank( 0 );
}

void	Mapper051::WriteLow( WORD addr, BYTE data )
{
	if( addr>=0x6000 ) {
		mode = ((data & 0x10) >> 3) | ((data & 0x02) >> 1);
		SetBank_CPU();
	}
}

void	Mapper051::Write( WORD addr, BYTE data )
{
	bank = (data & 0x0f) << 2;
	if( 0xC000 <= addr && addr <= 0xDFFF ) {
		mode = (mode & 0x01) | ((data & 0x10) >> 3);
	}
	SetBank_CPU();
}

void	Mapper051::SetBank_CPU()
{
	switch(mode) {
		case 0:
			nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			nes->mmu.SetPROM_8K_Bank( 3, (bank|0x2c|3) );
			nes->mmu.SetPROM_8K_Bank( 4, (bank|0x00|0) );
			nes->mmu.SetPROM_8K_Bank( 5, (bank|0x00|1) );
			nes->mmu.SetPROM_8K_Bank( 6, (bank|0x0c|2) );
			nes->mmu.SetPROM_8K_Bank( 7, (bank|0x0c|3) );
			break;
		case 1:
			nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			nes->mmu.SetPROM_8K_Bank( 3, (bank|0x20|3) );
			nes->mmu.SetPROM_8K_Bank( 4, (bank|0x00|0) );
			nes->mmu.SetPROM_8K_Bank( 5, (bank|0x00|1) );
			nes->mmu.SetPROM_8K_Bank( 6, (bank|0x00|2) );
			nes->mmu.SetPROM_8K_Bank( 7, (bank|0x00|3) );
			break;
		case 2:
			nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			nes->mmu.SetPROM_8K_Bank( 3, (bank|0x2e|3) );
			nes->mmu.SetPROM_8K_Bank( 4, (bank|0x02|0) );
			nes->mmu.SetPROM_8K_Bank( 5, (bank|0x02|1) );
			nes->mmu.SetPROM_8K_Bank( 6, (bank|0x0e|2) );
			nes->mmu.SetPROM_8K_Bank( 7, (bank|0x0e|3) );
			break;
		case 3:
			nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
			nes->mmu.SetPROM_8K_Bank( 3, (bank|0x20|3) );
			nes->mmu.SetPROM_8K_Bank( 4, (bank|0x00|0) );
			nes->mmu.SetPROM_8K_Bank( 5, (bank|0x00|1) );
			nes->mmu.SetPROM_8K_Bank( 6, (bank|0x00|2) );
			nes->mmu.SetPROM_8K_Bank( 7, (bank|0x00|3) );
			break;
	}
}

void	Mapper051::SaveState( LPBYTE p )
{
	p[ 0] = mode;
	p[ 1] = bank;
}

void	Mapper051::LoadState( LPBYTE p )
{
	mode = p[ 0];
	bank = p[ 1];
}
