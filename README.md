# Building Pong for the GBA

https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/8e3d83e8-2b41-4725-b507-9a368d5c1c17

This repository provides an example of how to build pong for the Game Boy Advance (GBA). It is built in such a way that it can be ported to other consoles with few changes. It is not meant to win any prizes or be heavily optimized. Rather, it is made to be simple to understand, and an example game that can be used for learning.

When building games and programs for new hardware, or using a new language or framework, building a simple game like pong is one of the best ways to familiarize yourself with the platform. For the same reasons, if you are just getting into game development, or getting into homebrew development for the first time, pong makes an excellent first game to learn the fundamentals. Without much code, building pong teaches you about:

- User Input
- Rendering Graphics
- Collision Detection
- Designing Game Logic
- Scoring Points
- Winning and Losing
- A Computer Player / AI
- Multiple Game States

If the GBA, game dev, homebrew, or any the items above are new to you, hopefully the code in this repo can help you start to familiarize yourself with them. Other uses for this example game include:

- Practicing ROM Hacking with a small game and source code you can check
- Testing core functionality for a GBA emulator you're developing
- Practicing porting a game to other consoles with an easy example

Additionally, if you want to learn about more advanced game dev features you can extend the game with your own code to:

- Use sprites and more complex graphics
- Add a multiplayer mode
- Add more menus and the ability to edit settings
- Build a 3D version

https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/f04ae7a7-4ca6-4a88-aa54-b163cf397883

This game uses mode 3, one of the bitmap modes for the GBA (3, 4, and 5 are bitmap modes). This is one of the simplest modes to work with, but has its limitations. Updating pixels with the CPU is not particularly fast. For more intense graphics for 2d games, using one of the tile modes is *usually* a better choice for the GBA. But bitmap modes do have their place. For simple 2d graphics like in this game, or highly dynamic graphics such as those used in 3d games and semi-3d (raycaster) games, bitmap modes are often needed for software rendering. If you do plan on building a graphically intense game in a bitmap mode, keep in mind you'll have to do a fair amount of optimization to get it to run at a good speed. This certainly can be done, and there are impressive ports of Doom, Wolfenstein, and even <a href="https://www.youtube.com/watch?v=_GVSLcqGP7g">Tomb Raider</a> to the GBA that use bitmap modes. For our purposes mode 3 will be sufficient.

## Getting and building the code

First install devkitPro, see <a href="https://devkitpro.org/wiki/Getting_Started">https://devkitpro.org/wiki/Getting_Started</a>

If you need any help getting a homebrew dev environment setup, see my guides for <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-mac">macOS</a>, <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-windows">Windows</a>, or <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-linux">Linux</a>. 

With devkitPro installed, you're ready to go.

Clone the project:
```
git clone https://github.com/ZeroDayArcade/Pong-Homebrew-GBA
```

cd into the project directory:
```
cd Pong-Homebrew-GBA
```

Build the project:
```
make
```

You should now have a .gba ROM. At this point you can test it with a GBA emulator such as <a href="https://visualboyadvance.org/">Visual Boy Advance</a>, or test on real hardware with a GBA flashcart:

![gba-rom-slot-2-ds](https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/42d1ac2d-b16b-4a32-a57c-e356bfc00b70)
*ROM loaded from GBA Flashcart in slot-2 on a Nintendo DS*

A modern way to play a game you create (and encourage others to play it), is by running it on a retro emulation handheld. Any handheld with a GBA emulator should do. Here's an example on an Anbernic RG353PS:

https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/c2c55b5d-b9f9-40e2-a02d-a4987a0146e7

This way people can play your game without a flash cartridge, or the need to jailbreak their console (if you're building homebrew for consoles that require that). If your emulation console supports connecting to a TV via HDMI or wireless, that is also a great option, and allows you to easily play on the big screen.

# More ZDA Code and Resources:
**Learn Reverse Engineering, Assembly, Code Injection and More:**  
🎓  <a href="https://zerodayarcade.com/tutorials">zerodayarcade.com/tutorials</a> 

**Learn About Hacking:**  
<a href="https://github.com/ZeroDayArcade/capture-pmkid-wpa-wifi-hacking">Capturing PMKID from WiFi Networks</a>  
<a href="https://github.com/ZeroDayArcade/wpa-password-cracking-with-pmkid/">Cracking WiFi Passwords with PMKID</a>  
<a href="https://github.com/ZeroDayArcade/capture-handshake-wpa-wifi-hacking">Capturing 4-Way Handshake from WPA/WPA2 Networks</a>  
<a href="https://github.com/ZeroDayArcade/cracking-wpa-with-handshake">Cracking WPA/WPA2 Passwords with 4-Way Handshake</a>  

**More Retro Gaming Handhelds:**  
<a href="https://www.youtube.com/shorts/auvxesBrZwU">Connecting a Game Boy Advance SP to the Internet</a>  
<a href="https://www.youtube.com/shorts/94pTU2rXiVE">Multiplayer Quake 1 on a Nintendo DS vs PC Player: Crossplay</a>  
<a href="https://zerodayarcade.com/tutorials/anbernic-rg353-quake-multiplayer">Tutorial - Crossplay Quake on Anbernic RG353PS vs PC</a>  
<a href="https://github.com/ZeroDayArcade/RG353-WiFi-Penetration-Tool">Hacking WiFi Networks with the Anbernic Handhelds</a>

# Find Homebrew Bounties in Gaming:
🎮  <a href="https://zerodayarcade.com/bounties">zerodayarcade.com/bounties</a>

<a href="https://zerodayarcade.com/bounties/ps-vita">PS Vita Bounties</a>  
<a href="https://zerodayarcade.com/bounties/ps4">PS4 Bounties</a>  
<a href="https://zerodayarcade.com/bounties/ps5">PS5 Bounties</a>  
<a href="https://zerodayarcade.com/bounties/gamecube">GameCube Bounties</a>  
<a href="https://zerodayarcade.com/bounties/3ds">3DS Bounties</a>  
<a href="https://zerodayarcade.com/bounties/switch">Switch Bounties</a>  
<a href="https://zerodayarcade.com/bounties/xbox-one">XBox One Bounties</a>  
<a href="https://zerodayarcade.com/bounties/xbox-series-x-s">XBox Series X|S Bounties</a>  
<a href="https://zerodayarcade.com/bounties/pc">PC/Mac Bounties</a>  
<a href="https://zerodayarcade.com/bounties/other">RetroArch Bounties</a>  
