# Tools

## Upload Utility (From RebeccaRGB's LisaKeys Project)
This directory contains a utility called lkupload.py that works with this mode. Enter Service Mode on the Lisa, then run lkupload.py to generate the keystrokes that will load a binary file into the Lisa's memory. For example:

```
python lkupload.py -u /dev/tty.usbmodemfd121 -a 0x9c0 -l 0x9380 -i BLU090.dc42
```

The above command will load 0x9380 bytes of the file BLU090.dc42 at address 0x9C0 by typing lines like the following on the Lisa:

29c0 162d 6e6f 7420 6120 4d61 6369 6e74 6f73
29d0 6820 6469 736b 2d20 424c 5556 302e 3930
29e0 2020 2020 2020 2020 2020 2020 2020 2020
29f0 2020 2020 2020 2020 2020 2020 2020 2020

The first 2 on each line selects the SET MEMORY option in Service Mode.