#!/usr/bin/python

import sys
sys.path.append( "." )

import urjtag

#urjtag.loglevel(0) # ALL

urc = urjtag.chain()
urc.parse_line("cable ft2232 pid=0x6010 vid=0x403 interface=1 driver=ftdi-mpsse")
urc.parse_line("frequency 1000000")
urc.parse_line("detect")