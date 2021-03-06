﻿//////////////////////////////////////////////////////////////////////////
// Mapper048  Taito TC190V                                              //
//////////////////////////////////////////////////////////////////////////
void	Mapper048::Reset()
{
	reg = 0;
	irq_enable = 0;
	irq_counter = 0;

	nes->mmu.SetPROM_32K_Bank( 0, 1, nes->mmu.PROM_8K_SIZE-2, nes->mmu.PROM_8K_SIZE-1 );
	nes->mmu.SetVROM_8K_Bank( 0 );

	DWORD	crc = nes->rom->GetPROM_CRC();
//	if( crc == 0x547e6cc1 ) { // Flintstones - The Rescue of Dino & Hoppy(J)
//		nes->SetRenderMethod( NES::POST_RENDER );
//	}
}

void	Mapper048::Write( WORD addr, BYTE data )
{
	switch( addr ) {
		case	0x8000:
			if( !reg ) {
				if( data & 0x40 ) nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
				else		  nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			}
			nes->mmu.SetPROM_8K_Bank( 4, data );
			break;
		case	0x8001:
			nes->mmu.SetPROM_8K_Bank( 5, data );
			break;

		case	0x8002:
			nes->mmu.SetVROM_2K_Bank( 0, data );
			break;
		case	0x8003:
			nes->mmu.SetVROM_2K_Bank( 2, data );
			break;
		case	0xA000:
			nes->mmu.SetVROM_1K_Bank( 4, data );
			break;
		case	0xA001:
			nes->mmu.SetVROM_1K_Bank( 5, data );
			break;
		case	0xA002:
			nes->mmu.SetVROM_1K_Bank( 6, data );
			break;
		case	0xA003:
			nes->mmu.SetVROM_1K_Bank( 7, data );
			break;

		case	0xC000:
			irq_counter = data;
			irq_enable = 0;
//			nes->cpu->ClrIRQ( IRQ_MAPPER );
			break;

		case	0xC001:
			irq_counter = data;
			irq_enable = 1;
//			irq_enable = data & 0x01;
//			nes->cpu->ClrIRQ( IRQ_MAPPER );
			break;

		case	0xC002:
			break;
		case	0xC003:
			break;

		case	0xE000:
			if( data & 0x40 ) nes->mmu.SetVRAM_Mirror( VRAM_HMIRROR );
			else		  nes->mmu.SetVRAM_Mirror( VRAM_VMIRROR );
			reg = 1;
			break;
	}
}

void	Mapper048::HSync( INT scanline )
{
	if( (scanline >= 0 && scanline <= 239) ) {
		if( nes->ppu->IsDispON() ) {
			if( irq_enable ) {
				if( irq_counter == 0xFF ) {
//					nes->cpu->IRQ_NotPending();
//					nes->cpu->SetIRQ( IRQ_MAPPER );
					nes->cpu->SetIRQ( IRQ_TRIGGER2 );
				}
				irq_counter++;
			}
		}
	}
}

void	Mapper048::SaveState( LPBYTE p )
{
	p[0] = reg;
	p[1] = irq_enable;
	p[2] = irq_counter;
}

void	Mapper048::LoadState( LPBYTE p )
{
	reg = p[0];
	irq_enable  = p[1];
	irq_counter = p[2];
}
