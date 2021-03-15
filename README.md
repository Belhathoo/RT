# RT


### Installing

#### Mac OS
```
Nothing :smile:
```

#### Windows

* terminal of ubuntu or other linux distributions (windows store)
#### to run graphical Linux programs on your windows 10 desktop you need a GUI server, such as X11. Such does not exist for Windows, but there are alternatives, one of which is Xming, which can be downloaded free of charge, from [SourceForge](https://sourceforge.net/projects/xming/) (set private when ask) then enable bash to use xming which can be done by executing the following command:
```
echo "export DISPLAY=:0" >> ~/.bashrc
```
#### Linux

* update and upgrade ur system:
```
apt-get update
apt-get upgrade
```
* install gcc and make
* install the following packages:
```
apt-get install libx11-dev
apt-get install libxext-dev
```
* install SDL packages:
```
apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

### Installing
```
- default window size:
  make
```

## Run the program
```
  ./rt scenes/scene.xml
```

### Language: C

### Libraries: SDL, miniLibX, pthread

### Features implemented:
```
Voronoi noise, Perlin noise, UV mapping, Reflection, Refraction, Antialiasing, Motion blur, Multi thread computing, slice different objects following its own axis, Point light, Parallel light
```

### Objects:
```
The Moebius ribbon, perforated cube, torus, paraboloid, cube, cone, cylinder, sphere, plane.
```


## RESOURCES

* [Ray tracing in One Weekend](https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf) - Positionable camera
* [Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) - Phong reflection model
* [Moebius](https://www.mathcurve.com/surfaces/mobiussurface/mobiussurface.shtml) - The Moebius ribbon
* [Voronoi noise](https://www.ronja-tutorials.com/2018/09/29/voronoi-noise.html) - a noise based on cells
* [Perlin noise](http://evasion.imag.fr/Publications/2006/AN06/Flow-noise_temps_reel.pdf) - a repeatable noise
* [Perlin noise code](https://www.realtimerendering.com/raytracing/Ray%20Tracing_%20The%20Next%20Week.pdf)
* [Lighting](https://www.utc.fr/~vberge/lo12/iso_album/cours7_1.pdf) - Lighting
* [Shadow](http://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/shadow.pdf) - Shadow
* [Soft_Shadows](https://www.cs.unc.edu/~dm/UNC/COMP236/LECTURES/SoftShadows.pdf) - Soft_Shadows

## Captures


#### Inside A Holo Cube
![alt text](https://raw.githubusercontent.com/Belhathoo/RT-1.0/main/saved_img/holo_32520.bmp)


#### Reflection / Refraction

![alt_text](https://raw.githubusercontent.com/Belhathoo/RT-1.0/main/saved_img/refs_0.bmp)

