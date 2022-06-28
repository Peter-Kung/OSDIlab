SECTIONS
{
    /* text section start from 0x80000 */
  . = 0x80000;
  .text : { *(.text) }
}
