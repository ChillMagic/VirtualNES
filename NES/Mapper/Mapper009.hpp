﻿//////////////////////////////////////////////////////////////////////////
// Mapper009  Nintendo MMC2                                             //
//////////////////////////////////////////////////////////////////////////
void	Mapper009::Reset()
{
	nes->mmu.SetPROM_32K_Bank( 0, nes->mmu.PROM_8K_SIZE-3, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );

	reg[0] = 0; reg[1] = 4;
	reg[2] = 0; reg[3] = 0;

	latch_a = 0xFE;
	latch_b = 0xFE;
	nes->mmu.SetVROM_4K_Bank( 0, 4 );
	nes->mmu.SetVROM_4K_Bank( 4, 0 );

	nes->ppu->SetChrLatchMode( TRUE );
}

void	Mapper009::Write( WORD addr, BYTE data )
{
	switch( addr & 0xF000 ) {
		case	0xA000:
			nes->mmu.SetPROM_8K_Bank( 4, data );
			break;
		case	0xB000:
			reg[0] = data;
			if( latch_a == 0xFD ) {
				nes->mmu.SetVROM_4K_Bank( 0, reg[0] );
			}
			break;
		case	0xC000:
			reg[1] = data;
			if( latch_a == 0xFE ) {
				nes->mmu.SetVROM_4K_Bank( 0, reg[1] );
			}
			break;
		case	0xD000:
			reg[2] = data;
			if( latch_b == 0xFD ) {
				nes->mmu.SetVROM_4K_Bank( 4, reg[2] );
			}
			break;
		case	0xE000:
			reg[3] = data;
			if( latch_b == 0xFE ) {
				nes->mmu.SetVROM_4K_Bank( 4, reg[3] );
			}
			break;
		case	0xF000:
			if( data & 0x01 ) nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
			else		  nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			break;
	}
}

void	Mapper009::PPU_ChrLatch( WORD addr )
{
	if( (addr&0x1FF0) == 0x0FD0 && latch_a != 0xFD ) {
		latch_a = 0xFD;
		nes->mmu.SetVROM_4K_Bank( 0, reg[0] );
	} else if( (addr&0x1FF0) == 0x0FE0 && latch_a != 0xFE ) {
		latch_a = 0xFE;
		nes->mmu.SetVROM_4K_Bank( 0, reg[1] );
	} else if( (addr&0x1FF0) == 0x1FD0 && latch_b != 0xFD ) {
		latch_b = 0xFD;
		nes->mmu.SetVROM_4K_Bank( 4, reg[2] );
	} else if( (addr&0x1FF0) == 0x1FE0 && latch_b != 0xFE ) {
		latch_b = 0xFE;
		nes->mmu.SetVROM_4K_Bank( 4, reg[3] );
	}
}

void	Mapper009::SaveState( LPBYTE p )
{
	p[0] = reg[0];
	p[1] = reg[1];
	p[2] = reg[2];
	p[3] = reg[3];
	p[4] = latch_a;
	p[5] = latch_b;
}

void	Mapper009::LoadState( LPBYTE p )
{
	reg[0] = p[0];
	reg[1] = p[1];
	reg[2] = p[2];
	reg[3] = p[3];
	latch_a = p[4];
	latch_b = p[5];
}
