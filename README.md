# DISCLAIMER

This is a fork of [MapleEzorsia](https://github.com/izarooni/MapleEzorsia). The original work belongs to its author(s) — I just made a few tweaks so it works with a specific client and all my changes are in the `hendi_client_4gb` branch.

This repo is here for learning and tinkering purposes only. Please do NOT use it to break game rules, mess with servers, or do anything shady.

I am not responsible for how anyone else decides to use this code. If you are a copyright holder and have concerns, just reach out and I will take care of it.

## Credits
- Original project by [izarooni](https://github.com/izarooni) (thank yooooooou)

# MapleEzorsia

This DLL modifies the memory of v83 MapleStory clients to change the experience of the game.

[Screen Shots](/readme-screenshots/README.md)

### Libraries
- [Detours](https://github.com/microsoft/Detours) - Intercepts windows api and in-game function calls

### Features
- Modify game window and canvas resolution
- Center the game window on start-up
- Position of some in-game components are modified to scale with any resolution
- Enable the minimize button
- Skip the start-up animations
- Hide login screen book border automatically on higher resolutions
- Increase chat log history from 64 to 127
- Fix fear effect (LimitedView fieldType) for any resolution

### How To Use
In your v83 MapleStory directory,  
1. Rename file `nmconew.dll` to `nmconew2.dll`
2. Build Solution in the project and a `nmconew.dll` file is compiled
3. Insert the compiled `nmconew.dll` in that directory
4. Run your client!

### Configure
The default `config.ini` file isn't included because it's optional.  
The default resolution is 1024x768 if no config is present.  

Make a file called `config.ini` in your game folder and the program will try to use it.  
All settings are optional and can be ommitted (in case you don't want players knowing/using it).  
```
[general]
width=1280
height=720
discord=false
debug=false
```

- `discord`=`true/false` Enables to disables discord presence
- `debug`=`true/false` Enables or disables the output console

## Developing

**This code can only be compiled on \[Release\] \[x86\] configuration**

- I was able to compile using Visual Studio 2022 with `.NET desktop development` and `Desktop development with C++` installed from the Workloads tab when installing Visual Studio 2022

### TODOs
- Clean code by remove discord rich presence interation (because I am not sure how I would like to use it, but it is definitely helpful to learn from it)
- Maybe put some of the stuffs into compiling `dinput8.dll` like [Ro](https://github.com/444Ro666) in [Ezorsia-v2](https://github.com/444Ro666/MapleEzorsia-v2) to enable tubi?

## To Work with Hendi 4GB Client

**My journey of making this to work with Hendi 4GB client (apparently the Hendi client doesn't have CRC bypass built in which causes Ezorsia failing to work with it. Also need to force windowed mode on it)**

- Special thanks to Frost in Discord advising to use Ezorsia v1 if really wanting to do img loading along with Ezorsia (and make improvements later on), which inspired me to do this.

- You can grab the [clean v83 Hendi 4GB client on RaGEZONE](https://forum.ragezone.com/threads/localhost-workshop.1202021/) (thanks to Hendi48)

0. Pull the project and switch to branch `hendi_client_4gb`, please refer to [Developing](#developing) for possible hints on Visual Studio for setting up this project to compile
1. Follow [Cosmic](https://github.com/P0nk/Cosmic?tab=readme-ov-file) to setup the Database and the Server (thanks to P0nk)
2. Go to [Cosmic-client](https://github.com/P0nk/Cosmic-client) to grab the `MapleGlobal-v83-setup.exe` and the `cosmic-wz folder` (thanks to P0nk again)
3. Follow Cosmic-client Installation guide up until Step 4, also copying client to the installation directory but it's the Hendi client here
4. DO NOT start the client yet, need to make sure the following tweaks are done first (**MAKE SURE to be at the `hendi_client_4gb` branch of the project!!!!**)
    - CRC bypass (this is too much for me right now to understand and implement). A simpler workaround is just adding VirtualProtect to memory editing calls which is done in the `Memory.cpp` in this repo already (thanks to [Ro mentioning this on RaGEZONE](https://forum.ragezone.com/threads/release-v83-major-update-to-ezorsia-v2-the-hd-client-patch-is-now-a-standalone-hd-dll-client-localhost.1220746/post-9213834), Stelmo discussing this and linking the code in Discord, and ColaMint actually providing the VirtualProtect code in Discord)
    - Force windowed mode. It is done in the `Memory.h`, `Memory.cpp` and `Client.cpp` in this repo already (thanks to Ro discussing this in Discord, and Stelmo helping out in Discord. Special thanks to [Eric on RaGEZONE](https://forum.ragezone.com/threads/windows-8-10-client-support-fix.1126357/#post-8758145) explaining this)
    - Remove admin elevation request. I am not sure if this is a must or not, but I just did it by hex editing the client (AGAIN thanks to Ro discussing this in Discord, and Stelmo sharing the approach)
        - Go to [here](https://github.com/444Ro666/MapleEzorsia-v2/wiki/v83%E2%80%90Client%E2%80%90Setup%E2%80%90and%E2%80%90Development%E2%80%90Guide) and clicked the FIRST `shown here` for the picture of the steps. Do ALL of the things said in the picture
5. Follow the [How To Use](#how-to-use) above
6. Yay!

## Next, To Also Work with Client Image Loader (CIL)
- You may refer to my [forked CIL](https://github.com/Kiz486/ClientImageLoader) for the changes I made as well as the process to make the setup (Cosmic + Hendi + Ezorsia + CIL) work.
- For more information about the project, check out:
    - The [original ClientImageLoader repo](https://github.com/MapleMyth/ClientImageLoader) and the [RaGEZONE release](https://forum.ragezone.com/threads/release-client-load-img-instead-of-wz-v62-v92.1165258/) (thanks to the MapleMyth, bhnet, MapleSuxBalls, iloveroblox2011, buttbeam, Darter, Eric)