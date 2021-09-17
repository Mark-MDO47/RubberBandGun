# Sounds for the Rubber Band Gun

## Sounds from SPACE!!! Colliding Celestial Bodies!

Some of my favorite sounds for Rubber Band Gun firing are a sequence similar to the soundified neutron star collisions or black hole collisions.

I particularly like GW170817-template.wav; it has the ramp-up and then the kick at the end, which can be found at https://www.gw-openscience.org/audiogwtc1/. Of course, I would make it just like itself but even more so!!!

Another one I like: Gravitational Waves from a Neutron Star Merger Produced a Signal Detected by LIGO
- https://www.youtube.com/watch?v=CH9JSqUfnSw


Here is a "soundified" rendition of two neutron stars colliding in 2017

- https://qz.com/1103444/ligo-listen-to-a-kilonova-the-sound-of-two-stars-colliding-in-space/

... or maybe from the two black holes colliding in 2015

- https://journals.aps.org/prl/abstract/10.1103/PhysRevLett.116.061102

or a simulation of this. I shamelessly Hollywoodify these sounds!

Thank you LIGO folks for making the fun sounds available to non-researchers!

A very readable one-page comparison of gravity waves to light and sound wave perception is here:
- http://gmunu.mit.edu/sounds/sounds.html

Here are some good articles and overview of LIGO and gravity waves:
- https://www.ligo.org/index.php
- https://www.ligo.org/detections/O1O2catalog.php
- https://www.gw-openscience.org/audiogwtc1/

## Sounds from SPACE!!! Saturn is SO COOL!

Some great science-fictiony sounds came from the Cassini space mission. Here is where you can get audio from the Cassini mission representing radio emissions from Saturn:
- http://www-pw.physics.uiowa.edu/space-audio/cassini/SKR1/
- http://www-pw.physics.uiowa.edu/space-audio/cassini/SKR1/SKR-03-324.wav

You can find more about the Cassini mission here
- https://solarsystem.nasa.gov/missions/cassini/overview/

## A few of the Sounds are Recordings of my Family  Members

## Text-to-Speech Robotic Sounds

The Rubber Band Gun speaks to you when you want to configure the sounds or LED patterns. 
I used the "original" eSpeak text-to-speak program version 1.48.04. This produces sounds with a robotic flavor, which I wanted.

The original eSpeak text to speech code and compiled versions can be found at http://espeak.sourceforge.net/
- Kudos to (email) jonsd at users dot sourceforge dot net for creating eSpeak

Note that eSpeak project is inactive since disappearance of Jonathan Duddington.

Active development and support now happens in eSpeak NG project https://github.com/espeak-ng/espeak-ng, maintained by Reece H. Dunn.
- Kudos to Reece H. Dunn for continuing the good work

A web implementation of eSpeak can be found as below; it is great fun, and just one of many text-to-text and text-to-speech engines on the site. https://lingojam.com/RobotVoiceGenerator

## Processing Text-to-Speech Robotic Sounds

I used the program RobotSounds.py to read StateTable_minimal.xlsx (which contains the text to generate) and make a Linux "bash" script that makes the sounds.
- The bash script generates all the individual *.wav sound files and also a combined totString.wav.
- - totString.wav separates the sounds by having "Ah. Ah. Ah." between each one so I could find the boundaries.
- - You can do the Audacity processing either one at a time or using the totString.wav file, but you need to have individual numbered files when done.
- - See https://github.com/Mark-MDO47/AudioPlayer-YX5200 for more information about the file numbering scheme
- - The bash file invokes the "original" eSpeak program version 1.48.04.
- I think the bash file could easily be converted to a Windows *.bat file.

After creating the text-to-speech audio file(s), this is how I processed them to make them even more robotic:
- import file in Audacity, set to mono if not already set (File->Import->Audio)
- duplicate the track (select track, then Edit->Duplicate)
- reverse one of the tracks (select track, then Effect->Reverse)
- select reversed track and change pitch (Effect->ChangePitch, choose -2 semitones)
- for both tracks one at a time, echo effect (Effect->Echo, choose DelayTime about 0.01 sec and DecayFactor about 0.5)
- select reversed track and reverse it back to normal order (select track, then Effect->Reverse)
- select both tracks (ctrl-A) then render (Tracks->Mix->MixAndRender)
- export as 22050Hz mono, "WAV (microsoft) signed 16-bit PCM" (File->Export->ExportAsWav or for more options File->Export->ExportAudio)

Audacity can be found at https://www.audacityteam.org/

Once you have the individual numbered *.wav files collected (both text to speech and all the others), they need to be stored on an SD card very precisely. For details, see the description of copyem.py in https://github.com/Mark-MDO47/AudioPlayer-YX5200

## Attributions and Licensing

Here are the Creative Commons licenses in the non-speech sound files I used:

| Tag | Name | URL |
| --- | --- | --- |
| zero/1.0/	| Creative Commons 0 License | https://creativecommons.org/publicdomain/zero/1.0/ |
| by/3.0/	| Creative Commons Attribution License | https://creativecommons.org/licenses/by/3.0/ |
| by-nc/3.0/ | Creative Commons Attribution Noncommercial License | https://creativecommons.org/licenses/by-nc/3.0/ |

Here are the sound files I used, modified, and combined for the prototype sounds:

| Tag | File Name | URL | Who |
| --- | --- | --- | --- |
| N/A | GW170817-template.wav | https://www.gw-openscience.org/audiogwtc1/ | LIGO detectors |
| N/A |	SKR-03-324.wav |	http://www-pw.physics.uiowa.edu/space-audio/cassini/SKR1/ |	NASA Cassini mission Radio and Plasma Wave Science |
| zero/1.0/ | 407052__sojan__power-charge.flac | https://freesound.org/s/193610/ | crashoverride61088 |
| zero/1.0/ |	397254__screamstudio__loading.wav |	https://freesound.org/s/397254/ | ScreamStudio |
| zero/1.0/	| 145209__lensflare8642__shotgun-sounds.mp3	| https://freesound.org/s/145209/ | lensflare8642 |
| by/3.0/ | 216096__richerlandtv__u-f-o.mp3 | https://freesound.org/s/216096/ | RICHERlandTV |
| by/3.0/ | 88635__uair01__bicycle-picture-in-spectrum.wav | https://freesound.org/s/88635/ | uair01 |
| by/3.0/ | 7967__cfork__boing-raw.aiff | https://freesound.org/s/7967/ | cfork |
| by/3.0/	| 383205__spiceprogram__loading-sound.wav	| https://freesound.org/s/383205/ | SpiceProgram  |
| by-nc/3.0/ | 179281__timbre__boingy-sweep.flac | https://freesound.org/s/179281/ | Timbre |
| zero/1.0/ | 380886__morganpurkis__doom-shotgun-2017.wav | https://freesound.org/s/380886/ | morganpurkis |
| zero/1.0/ | 500418__dj-somar__intro-reverso-craver-microbrute.wav | https://freesound.org/s/500418/ | DJ_SoMaR |
| by/3.0/ | 272068__ichbinjager__shotgun-action.wav | https://freesound.org/s/272068/ | IchBinJager |
| by/3.0/ | 431117__inspectorj__door-front-opening-a.wav | https://freesound.org/s/431117/ | inspectorj |
| zero/1.0/ | 404068__swordofkings128__backyard-gate-open.wav | https://freesound.org/s/404068/ | swordofkings128 |
| by/3.0/ | 96964__gabisaraceni__porta-abrindo-5.wav | https://freesound.org/s/96964/ | gabisaraceni |
| by/3.0/ | 275537__wjoojoo__contact-mic-on-satellite-dish04.wav | https://freesound.org/s/275537/ | wjoojoo |
| zero/1.0/ | 352852__josepharaoh99__game-style-laser-beam.wav | https://freesound.org/s/352852/ | josepharaoh99 |
| by/3.0/ | 417363__xcreenplay__boing-massive-kick.wav | https://freesound.org/s/417363/ | xcreenplay |
| by/3.0/ | 221875__hero-of-the-winds__spring-boing.wav | https://freesound.org/s/221875/ | hero-of-the-winds |
| by/3.0/ | 240297__jalastram__abstract-guitar-sfx-003.wav | https://freesound.org/s/240297/ | jalastram |
| zero/1.0/ | 383760__deleted-user-7146007__laboratory-mad-scientist-science-fiction-sci-fi.wav | https://freesound.org/s/383760/ | deleted-user-7146007 |
| by/3.0/ | 417131__cuddlenucks__science-fiction-noise-3.wav | https://freesound.org/s/417131/ | cuddlenucks |
| zero/1.0/ | 170136__lazr2012__machinery-bo.flac | https://freesound.org/s/170136/ | lazr2012 |
| by/3.0/ | 169292__lazr2012__haywirefusionator.ogg | https://freesound.org/s/169292/ | lazr2012 |
| by-nc/3.0/ | 165483__timbre__glitch-voice-ep-mp3.mp3 | https://freesound.org/s/165483/ | timbre |
| zero/1.0/ | 162814__timgormly__spaceship-4.aiff | https://freesound.org/s/162814/ | timgormly |
| by-nc/3.0/ | 91296__timbre__bwaang-2-reverb.mp3 | https://freesound.org/s/91296/ | timbre |
| zero/1.0/ |	388276__csnmedia__la-cucaracha-car-horn.wav |	https://freesound.org/s/388276/ |	csnmedia |
| zero/1.0/ |	118807__lmbubec__17-1985-ford-mustang-horn.wav |	https://freesound.org/s/118807/ |	lmbubec |
