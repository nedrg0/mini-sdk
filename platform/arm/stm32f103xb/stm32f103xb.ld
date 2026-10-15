ENTRY(Reset_Handler)

MEMORY {
	FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
	SRAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}
/* Place end of stack at end of ram */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS {
	    .isr_vector : {
		KEEP(*(.isr_vector))
	    } > FLASH

	    .text : {
		*(.text*)
		*(.rodata*)
		. = ALIGN(4);
	    } > FLASH

	    _sidata = LOADADDR(.data);

	    .data : {
		. = ALIGN(4);
		_sdata = .;
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	    } > SRAM AT > FLASH

	    .bss : {
		. = ALIGN(4);
		_sbss = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	    } > SRAM

	    /* nosys/sbrk looks up 'end' */
	    PROVIDE(end = _ebss);
	    PROVIDE(_end = _ebss);
}
