# BDSP_Randomisers
A collection of tools to randomize BDSP assets

# Archived
The code you see is old, and shouldnt be used. It is simply public for the sake of preservation. I suggest using this tool, which I am working on with 3 other  
people: https://gamebanana.com/tools/7848. 
github link: https://github.com/Aldo796/BDSP-Randomizers

# Setup (Windows 10 only)

- Install Ubuntu 18.04 via WSL1 (plenty of tutorials on that)
- In Ubuntu, install gcc, make, git and build-essentials
- Clone this repo
- Follow compiling steps

# Compiling

Make sure that you have the gcc compiler installed on your computer.  
Then, clone this repo and type make. A new folder will be created, containing each program properly labelled.
You can also type make [randomiser you want to compile] to compile invidual randomizers.

# Usage

Use UABEA to extract the necessary sheets from your game's assets.

The usage for all programs is the same: 
  ./program_name sheet_to_randomise.txt
 
 Output txt will have a trailing _randomised. Remove it, import back the txt in the game and do the proper steps to patching the game with atmo/yuzu.  
 
 # Other info
 
 - This is not intended to the public. I'm not responsible for anything. Code is also a fucking mess.
 - I will not add new randomisers unless I want to. Whatever Kaphotics will release in the future will simply be better for everybody.
 - If you indeed use any code in here for your own project, please credit.
 - I don't intend to really support this for a long time, but if you want to contribute go ahead I guess. Contributions are always nice.
 
 # Credits
 
 - XLuma(me), for coding all this obv
 - PlatinumMaster and BluRose for helping me figure out why fread in a single buffer isnt the best solution
 - Kurt(a.k.a Kaphotics) and SciresM for datamining the game, and providing useful info about game behavior
 - My bed, for giving me some rest
