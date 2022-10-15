# Dodgee
Game where the goal is to avoid projectile with your mouse

# How to compile (Linux)
Make sure CMake and the development libraries for SDL, SDL-Image, SDL-ttf, SDL-mixer are installed.  
Then simply issue:

```
mkdir build && cd build
cmake ..
make
```

# How to play
Once compiled and everything went well, issue:

```
./Dodgee
```

# TODO
Change difficulty ramp, should be easier at the begining and ramp up  
Make it playable with gamepad?  

Add sound effect on the buttons  
Add persinten highscore (including ability to input name)  
Add top 5? names on the gameover screen  
Add circular collision for more accurate representation  
Add texture 'cache', avoid creating same texture mutiple times  
