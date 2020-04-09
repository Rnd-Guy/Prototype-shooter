# Prototype-shooter
A one-stage boss shooter where you upgrade your weapons by shooting at different parts of the boss.  
Created mostly for coding practice, will not be developed further.

Created using visual studio 2015 and SFML 2.3.2. (http://www.sfml-dev.org/)  

#####Compiling:  
If you have visual studio 2015, it should be sufficient to download the repository and load up the solution file (.sln)  
(As of v0.4.0 use of "__declspec(noinline)" means code will only compile with visual studio)  

#####Folders:
-build-debug: Where the debug .exe can be found  
-build-release: Where the release .exe can be found  
-src: Source code  
-doc: Documents  
-res: Resources such as images and font files  
-lib: External libraries stored here (currently includes SFML 2.3.2 32bit for visual studio 2015)  

#####Controls:
Arrow keys to move  
Z key to shoot and select menu options  
A key to toggle autofire  
Shift key to show player's hitbox and slows down the player to perform precise movement  
Escape to pause/unpause

#####Features:
A red/yellow/blue power bar system where you get stronger depending on which part of the boss you shoot!  
Higher red power lets you shoot more bullets!  
Higher yellow power lets you shoot more laser beams!  
Levelling up blue power grants extra lives to survive longer!  

#####To-do list:  
Add better blue power (sometime later)  
Add better victory/defeat screens  
Maybe refactor certain classes and optimise others. Most notably the "beam" class, as this class can cause a lot of lag  
Fix bug where player lasers spawn off-center (most notable when firing whilst moving left or right)  
[Debug build only] Find out why the program doesn't close properly after returning from main  
[Release build only] [May be fixed as of v0.4.0] Find out why the pause menu doesn't display correctly (functions as normal however) despite no source code changes between debug and release   

#####Changelog:
Version | Description
---|---
v0.4.0 | Added very temporary victory/defeat screens. Possible bug fix for release build pause menu.
v0.3.1 | Added blue power which just gives extra lives. <br>Added shift button to slow down movement and reveal player hitbox.
v0.3.0 | Rebalanced power levels and finished boss attacks.
v0.2.1 | Added more lasers for yellow power level 3-5 and added some more boss attacks
v0.2.0 | Reshuffled folders and project files to a more standard format.
v0.1.2 | Fixed player beams not colliding with the boss or dealing damage.
v0.1.1 | Fixed visual bug where the power level displayed on screen did not reset back to level 1 when retrying the game. <br>Added autofire toggle using the "a" button.
v0.1.0 | First upload to github, most of the engine is working fine and the game is playable, but is unbalanced. <br>Missing blue power.


#####Preview:

![Sample play](/res/Preview Pictures/Sample Play.PNG)  
Screenshot of sample play
