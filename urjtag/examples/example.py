#!/usr/bin/python

#
# A general test and demonstration of several urjtag operations from python.
#

# works in both python 2 and 3
def printf(format, *args):
     """Format args with the first argument as format string, and print.
     If the format is not a string, it is converted to one with str.
     You must use printf('%s', x) instead of printf(x) if x might
     contain % or backslash characters."""
     sys.stdout.write(str(format) % args)

import sys
sys.path.append( "." )

import urjtag

#urjtag.loglevel(0) # ALL

urc = urjtag.chain()
printf("%s\n", urc);

urc.cable("ft2232", "pid=0x6010", "vid=0x403", "interface=1", "driver=ftdi-mpsse")
printf("urc.cable done %s\n", urc)

urc.tap_detect()
printf("urc.detect done\n")
printf("chainlength=%d\n", urc.len())

printf("id[0]=%08x\n", urc.partid(0) );

urc.set_instruction("IDCODE")
urc.shift_ir()
urc.shift_dr()
drval = urc.get_dr_out()
printf("IDREG dr result: %x\n", drval)

urc.set_instruction("SAMPLE/PRELOAD")
urc.shift_ir()
drval = urc.get_dr_in()
printf("BSR dr_in result: %x\n", drval)
urc.shift_dr()
drval = urc.get_dr_out()
printf("BSR dr_out result: %x\n", drval)


urc.set_instruction("EXTEST")
urc.shift_ir()
# part 0, signal IO44, using instruction EXTEST
#     bit 6 I ? IO44
#     bit 7 C 1 *
#     bit 8 O ? IO44 7 1 Z
regf = urc.get_register(0, 'BSR', 'EXTEST');
print(regf)
urc.set_dr_out(0, 6); #in-cell
urc.set_dr_in(0, 10); #control-cell
urc.set_dr_in(0, 11); #out-cell
urc.shift_dr()
r = urc.get_dr_out(6);
printf("IO44 = %x\n", r)

# part 0, signal IO42
#    bit 12 I ? IO42
#    bit 13 C 1 *
#    bit 14 O ? IO42 13 1 Z
r = urc.get_dr_in_string(12, 0)
printf("IO42 = %x\n", r)
