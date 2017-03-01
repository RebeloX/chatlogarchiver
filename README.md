# Chatlog Archiver [![GitHub release](https://img.shields.io/github/release/RebeloX/chatlogarchiver.svg)](https://github.com/RebeloX/chatlogarchiver)
###### A mod that automatically saves your chatlog, made exclusively for San Andreas Multiplayer.

### Description

The **Chatlog Archiver** is a mod that automatically saves your chatlog while you play **San Andreas Multiplayer**, the way the mod works is simple.
When you start SA-MP and select a server, Grand Theft Auto will be executed, the mod is attached to the game and waits until the game closes. Once your game closes the mod proceeds to copy the chatlog created by SA-MP and archive it.

All archives use the following date format
>YYYY-MM-DD - HH:MM:SS

### How do I install this?

To install this mod you will have to extract the file to scripts' folder or main directory of your GTA, once the extraction is done you should open the `chatlogarchive.ini` and edit the following line:

`PATH=NULL`

You should change `NULL` to the directory where the chatlog is archived, usually is under `GTA San Andreas User Files`. An example would be
`PATH=C:\Users\RebeloX\Documents\GTA San Andreas User Files\SAMP`

Once the file is changed you may save it and enjoy your game, the archive folder will be created automatically, so there is no need to worry about it.

### Contributing
You're welcome to contribute to the better of this mod, just file the issues under GitHub, or submit a pull request if you would like to contribute directly.
