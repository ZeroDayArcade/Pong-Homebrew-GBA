# Building Pong for the GBA

https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/cf09e58a-b542-4851-8088-dfbfd495f2c8

This repository provides an example of how to build pong for the Game Boy Advance (GBA). It is built in such a way that it can be ported to other consoles with few changes. It is not meant to win any prizes or be heavily optimized. Rather, it is made to be simple to understand, and an example game that can be used for learning.

When building games and programs for new hardware, or using a new language or framework, building a simple game like pong is one of the best ways to familiarize yourself with the platform. For the same reasons, if you are just getting into game development, or getting into homebrew development for the first time, pong makes an excellent first game to learn the fundamentals. Without much code, building pong teaches you about:

- User Input
- Rendering Graphics
- Collision Detection
- Designing Game Logic
- Creating a Points System
- Computer Players / AI
- Managing Game States

If the GBA, game dev, homebrew, or any the items above are new to you, hopefully the code in this repo can help you start to familiarize yourself with them. Other uses for this example game include:

- Practicing ROM Hacking with a small game and source code you can check
- Testing core functionality for a GBA emulator you're developing
- Practicing porting a game to other consoles with an easy example
  
<br/>  

https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/9e19deda-527a-4842-b2d4-d27a90e1a384


This game has a *very* simple menu that is primarily included to demonstrate switching between game states in a game loop, and to allow the player to choose when they start a new game. It is not meant to show you how to create a proper menu, but I suppose you could modify the code to handle more menu options and sub menus if you wanted.

Additionally, if you want to learn about more advanced game dev features you can extend the game with your own code to:

- Use sprites and more complex graphics
- Add a multiplayer mode
- Add more menus and the ability to edit settings
- Build a 3D version

This game uses mode 3, one of the bitmap modes for the GBA (3, 4, and 5 are bitmap modes). This is one of the simplest modes to work with, but has its limitations. Updating pixels with the CPU is not particularly fast. For more intense graphics for 2d games, using one of the tile modes is *usually* a better choice for the GBA. But bitmap modes do have their place. For simple 2d graphics like in this game, or highly dynamic graphics such as those used in 3d games and semi-3d (raycaster) games, bitmap modes are often needed for software rendering. If you do plan on building a graphically intense game in a bitmap mode, keep in mind you'll have to do a fair amount of optimization to get it to run at a good speed. This certainly can be done, and there are impressive ports of Doom, Wolfenstein, and even <a href="https://www.youtube.com/watch?v=_GVSLcqGP7g">Tomb Raider</a> to the GBA that use bitmap modes. For our purposes mode 3 will be sufficient.

You can also watch my ▶️ <a href="https://www.youtube.com/watch?v=nh0B5qBXPmA">video on getting started building pong for the GBA</a> that links to this repo.

## Getting and building the code

First install devkitPro, see <a href="https://devkitpro.org/wiki/Getting_Started">https://devkitpro.org/wiki/Getting_Started</a>

Make sure to install the GBA tools for devkitPro. If you are on Windows this is usually done with the devkitPro Installer, whereas if you are using macOS or Linux you'd typically use <a href="https://devkitpro.org/wiki/devkitPro_pacman#Predefined_Groups">devkitPro Pacman on the command line</a>. See the link above for details.

If you need any help getting a homebrew dev environment setup, see my guides for <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-mac">macOS</a>, <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-windows">Windows</a>, and <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-linux">Linux</a>. 

With devkitPro and the GBA tools installed, you're ready to go.

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

You should now have a .gba ROM. At this point you can test it with a GBA emulator such as <a href="https://visualboyadvance.org/">Visual Boy Advance</a>, or test on real hardware with a GBA flashcart on an actual GBA as shown at the top, or using a GBA flashcart with the DS or DS Lite:

![IMG_4633](https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/1002b9d9-e9a1-4a60-8934-fe23cde5ea4e)
*ROM loaded from GBA Flashcart in slot-2 on a Nintendo DS*

One modern way to play a homebrew game you create (or encourage others to play it), is by running it on a retro emulation handheld. Any handheld with a GBA emulator should do. Here's an example on an Anbernic RG353PS:

https://github.com/ZeroDayArcade/Pong-Homebrew-GBA/assets/141867962/ea1e033d-eb47-45a3-9e8b-ab319b6da470

This way people can play your game without a flash cartridge, or the need to jailbreak their console (if you're building homebrew for consoles that require that). If your emulation console supports connecting to a TV via HDMI or wireless, that is also a great option, and allows you to easily play on the big screen.

# More ZDA Code and Resources:
### *Interested in gaming, hacking, and homebrew?*

**Learn Reverse Engineering, Assembly, Code Injection and More:**  
🎓  <a href="https://zerodayarcade.com/tutorials">zerodayarcade.com/tutorials</a>  

**More Retro Gaming Handhelds:**  
<a href="https://www.youtube.com/shorts/auvxesBrZwU">Connecting a Game Boy Advance SP to the Internet</a>  
<a href="https://www.youtube.com/shorts/94pTU2rXiVE">Multiplayer Quake 1 on a Nintendo DS vs PC Player: Crossplay</a>  
<a href="https://zerodayarcade.com/tutorials/anbernic-rg353-quake-multiplayer">Tutorial - Crossplay Quake on Anbernic RG353PS vs PC</a>  
<a href="https://github.com/ZeroDayArcade/RG353-WiFi-Penetration-Tool">WiFi Penetration Testing with Anbernic Handhelds</a>

**Penetration Testing:**  
<a href="https://github.com/ZeroDayArcade/capture-pmkid-wpa-wifi-hacking">Capturing PMKID from a Wireless Router</a>  
<a href="https://github.com/ZeroDayArcade/wpa-password-cracking-with-pmkid/">Cracking Passwords with PMKID</a>  
<a href="https://github.com/ZeroDayArcade/capture-handshake-wpa-wifi-hacking">Capturing 4-Way Handshake from WPA/WPA2 Networks</a>  
<a href="https://github.com/ZeroDayArcade/cracking-wpa-with-handshake">Cracking WPA/WPA2 Passwords with 4-Way Handshake</a> 

# Find Homebrew & Hacking Bounties:
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
