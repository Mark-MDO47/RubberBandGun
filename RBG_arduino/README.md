YX5200 module looks like it will work fine; does not require a separate programmer and  can play MP3 files

You definitely want to use the 1K resistor on the TX line or you can distinctly hear clicks during serial communication.

Files to help with using YX5200 can be found here:

https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299

https://github.com/DFRobot/DFRobotDFPlayerMini

My experience:
- Using .playMp3Folder() worked on the first few calls but I had trouble making it work when interrupting a playing sound. I tried a bunch of things (but not every combination) and finally gave it up and now use the most basic of functions .play().
- While doing the above experiments I had the impression that turning ACK on (default at this time) made it more likely to have the trouble above. I turned ACK off in the .begin(mySoftwareSerial, false, true) call.
- Sometimes there was a delay in the BUSY pin registering after starting a sound. So far all the delays I have documented were <= 40 milliseconds. Since my code wants to do things (LED-related) faster than that, I put in code to force a fake BUSY for the first 250 milliseconds after starting a sound. Probably overkill.
- Some of my readings indicate that there are knock-off clones of the YX5200 module that may not implement all the functions properly. My guess would be that they have an out-of-date set of firmware. At least some of these clones used a red LED to indicate sound playing instead of the blue LED used on the genuine YX5200. My modules did have a blue LED, but this is not necessarily a guarantee that they were genuine, so it is possible the problems I had were due to using a knock-off clone.

Check out https://https://github.com/PowerBroker2/DFPlayerMini_Fast for a re-write (much simplified) of the DFRobot routines. That area also includes the PDF file I put into the YX5200_info; that is the best information on the chip that forms the basis of the YX5200 module that I have seen.
