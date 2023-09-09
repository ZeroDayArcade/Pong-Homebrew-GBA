# Building Pong for the GBA

When building games and programs for new hardware, or using a new language or framework, building pong is one of the best ways to familiarize yourself with the platform. For the same reasons, if your just getting into game development in general, or getting into homebrew development for the first time, pong makes an excellent first game to learn the fundamentals. Without much code, building pong teaches you about:

- User Input
- Rendering Graphics
- Collision Detection
- Designing Game Logic
- Scoring Points
- Winning and Losing
- A Computer Player / AI
- Multiple Game States

This repository is an example of building pong for gaming hardware, in this case the Game Boy Advance (GBA). It is built in such a way that it can be ported to other consoles with few changes. It is not meant to win any prizes or be heavily optimized. Rather, it is made to be simple to understand, and an example that can be used for learning. You can of course build it out further to build a more feature-rich and entertaining game which would be a good exercise in and of itself.  

Because of its simplicity and available code, other uses for this game include:

- Practicing ROM Hacking
- Testing an emulator you're developing
- Porting to other consoles

Additionally, if you want to learn about more advanced features you can extend the game with your own code to:

- Try using a different GBA mode that takes advantage of hardware scaling and rotation
- Add a multiplayer mode
- Use sprites and richer graphics
- Add more menus and the ability to edit settings
- Build a 3D version 

This game uses mode 3, one of the bitmap modes for the GBA (3, 4, and 5 are bitmap modes). This is one of the simplest modes to work with, but has its limitations. Updating pixels with the CPU is not particularly fast. For more intense graphics for 2d games, using one of the tile modes is *usually* a better choice for the GBA. But bitmap modes do have their place. For simple 2d graphics like in this game, or highly dynamic graphics such as those used in 3d games and semi-3d (raycaster) games, bitmap modes are often needed for software rendering. If you do plan on building a graphically intense game in a bitmap mode, keep in mind you'll have to do a fair amount of optimization to get it to run at a good speed. This certainly can be done, and there are impressive ports to the GBA of Doom, Wolfenstein, and even <a href="https://www.youtube.com/watch?v=_GVSLcqGP7g">Tomb Raider</a> that use bitmap modes. For our purposes mode 3 will be more than sufficient.

## Getting and building the code

First install devkitPro, see <a href="https://devkitpro.org/wiki/Getting_Started">https://devkitpro.org/wiki/Getting_Started</a>

Additionally you can learn about getting started in homebrew for <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-mac">macOS</a>, <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-windows">Windows</a>, or <a href="https://zerodayarcade.com/tutorials/setup-nintendo-homebrew-dev-environment-on-linux">Linux</a>. 

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

Another modern way to play your game is by playing it is with a Retro Gaming Handheld. Any handheld with a GBA emulator should do. Here's an example on an Anbernic RG353PS:

This way people can play your game without a flash cartridge, or the need to jailbreak their main console (if you're building for other consoles that don't use flash carts). 

If your emulation console supports connecting to a TV via HDMI or wireless, that is also a great option:
