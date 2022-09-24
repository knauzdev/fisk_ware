# fisk_ware

A WoW 1.12.2 Packet Manipulation / Multihack tool written some time mid-2017.

**This tool was made for educational and research purposes. Does not work on Classic or other iterations of modern WoW titles. In addition, most up to date 1.12.2 emulator servers will have some form of anti-cheat in place to detect or combat some or all features of this tool. I do not take responsibility for suspended accounts nor do I condone hacking/botting in online games.** 

A large portion of the tool is dedicated to sniffing and sending packets through the WoW Client. Some reverse engineering was done by myself and some knowledge was derived from public sources. It's written in C++ and uses Detours to hook game functions. You will need to use a seperate injector to attach the program to the client.

**Other features include:**
* Movement Speed
* Wallclimb
* Teleport
* Dumping entity list
* Wrapped network functionality for casting spells on specific targets (specified by GUID)
* Hooked ClickToMove function.

The last two mentioned features was the beginning of a bot but the idea never came to fruition as I lost interest in the project.

Demo video:
https://www.youtube.com/watch?v=SyDQ76M93b8

The video was recorded about 2 years after the program was put together, that's why you see me going through the code trying to remember my dumb command conventions.
