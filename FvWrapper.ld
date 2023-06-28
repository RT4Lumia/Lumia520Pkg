ENTRY(_start);

SECTIONS
{
    _start = 0xB0200000;
    . = 0xB0200000;
    .data : {
        *(.data)
    }
}
