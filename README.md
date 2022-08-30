# A Borderlands 1 Loader


[![Github All Releases](https://img.shields.io/github/downloads/Montrii/Borderlands1.Injector/total.svg)]()
[![Github Forks](https://img.shields.io/github/forks/Montrii/Borderlands1.Injector)]()
[![Github Stars](https://img.shields.io/github/stars/Montrii/Borderlands1.Injector)]()
[![Github Issues](https://img.shields.io/github/issues/Montrii/Borderlands1.Injector)]()

This `loader` allows you to bring any form of **.dll** files into the original Borderlands game.

The goal of this project is to prevent using an usual .dll injector.  
Using this form of a loader allows a more user-friendly implementation of modifications to the game.

As Borderlands 1 is a *x86* Application, **please** remember all modifications, including this one, need to be *x86* compiled.

Contents
========

* [Installation](#installation)
* [Versions](#versions)
* [Compiling yourself](#compiling)
* [Credits](#credits)


### Installation
---


In order to install this `loader`, you will **require** a digital copy of Borderlands 1.   
([Versions](#versions) for more Information).

As we won't use a conventional .dll injector, we'll need to replace files within the original Game.  
After research, i have decided to replace the original `vorbisenc.dll` file with a modified version of it.  


> **Warning**  
> **For Devs**: This method only works if you provide all functions the game needs from that .dll.

Now, follow these steps in order to install this `loader` successfully.   

```bash
1. Get a compiled version of vorbisenc.dll from this repository.
2. Navigate to your Borderlands 1 Directory.
3. Open the "Binaries" folder, where the actual Borderlands.exe lies.
4. Replace the original vorbisenc.dll with your compiled one.
5. Restart your game.
```   

The game now has a `loader` brought in.   
By default, if there **is not** any `\\scripts` directory within `\\Binaries`, it will auto-create one.


### Versions
---

Displaying the supported versions of the game to this day.

| Name                           | Supported? |
|--------------------------------|------------|
| Borderlands 1 Steam (Now GOTY) | Yes        |
| Borderlands 1 Enhanced Steam   | Yes, view [Enhanced Branch](https://github.com/Montrii/Borderlands1.Injector/tree/enhanced)  |


### Compiling yourself
---

#### Requirements/Recommendations

* Visual Studio 2022 with C/C++ Support
* .NET Framework 4.8
   
1. Open the included `asiinjector.sln` with Visual Studio 2022. 
2. Make sure Visual Studio 2022 compiles for `x86` with `Release`.
![Screenshot_6](https://user-images.githubusercontent.com/69902394/187504915-8391f008-643b-40ca-a436-7e89921fe2dc.png)

2. Once the project is fully loaded, rightclick the Project.           
![Screenshot_4](https://user-images.githubusercontent.com/69902394/187504918-b6dd6f0e-ba31-45d6-bad3-138f2395b6ee.png)

3. Click on `Build` and let the project build itself. 
![Screenshot_5](https://user-images.githubusercontent.com/69902394/187504917-2e9d0151-1646-4d05-95d6-e95ae270e2e4.png)

4. Once finished, you can receive your compiled file from `[ProjectFilder]\Release\`.

If you wish to view the compiling process for the Enhanced version, please view [Enhanced Branch](https://github.com/Montrii/Borderlands1.Injector/tree/enhanced).


### Credits
---

Credits go to me, the creator of the project and idea: Montri.   
Credits also go to any future collaborator.

Licensed under MIT License.





