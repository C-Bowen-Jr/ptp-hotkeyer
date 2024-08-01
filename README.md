# PNGTuber Plus Hotkeyer
PTPH is a 2 part solution to the hotkey for issue [#7](https://github.com/kaiakairos/PNGTuber-Plus/issues/7) for [PNGTuber Plus](https://kaiakairos.itch.io/pngtuber-plus). 
**Part 1** is to modify the ```main.gd``` script. This allows the number keys to to toggle costume/emotes as expected. This can be used stand alone if you have focus on PNGTuber Plus. So commentary users should be fine. 
**Part 2** is a companion program that asks X11 permission of the (non-numpad) number keys, plus the Home key. This then sends a localhost TCP message to PNGTuber Plus (secondary alteration to ```main.gd```) which is acting as a server to await these messages. This is helpful to users who want to user PNGTuber Plus while playing video games.

## Requirements
 - [Godot](https://godotengine.org) (Parts 1 & 2)
 - [PNGTuber Plus Source](https://github.com/kaiakairos/PNGTuber-Plus) (Parts 1 & 2)
 - g++ (Part 2)
 - keyboard with Home key[^1] (Part 2)

 [^1]: Home key is used to close ptph by default, alter source for another key or you might need to restart X server if you experience being locked out of your number keys

 ## Changes To Do
 Parts 1 & 2 both require making changes to ```main.gd```. You can replace the whole file with the new one, or run a diff checker to find just the changes and implement it by hand.

 For Part 2, either use the released binary and run ```./ptph```, or compile from source using 
 ```bash
 g++ -o ptph ptphotkeyer.cpp -lX11
 ```
 and then run. While ptph is running, both it and PNGTuber Plus can be minimized or otherwise out of focus

 ## Limitations
  - Hogs use of number keys (but not numpad) and Home key. Any game that needs these keys will be without them
  - Does not fix the "Awaiting input..." issue in binding new macros in PNGTuber Plus' settings
  - Doesn't support dynamic bindings, but .cpp file would be the place to make these changes