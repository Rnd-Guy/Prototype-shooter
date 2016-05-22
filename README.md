# Prototype-shooter
A one-stage boss shooter where you upgrade your weapons by shooting at different parts of the boss.  
Currently in development.  
Created using visual studio 2015 and SFML 2.3.2. (http://www.sfml-dev.org/)  

#####Compiling:  
If you have visual studio 2015, it should be sufficient to download the repository and load up the solution file (.sln)

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
Escape to pause/unpause

#####Features:
A red/yellow/blue power bar system where you get stronger depending on which part of the boss you shoot!  
Higher red power lets you shoot more bullets,  
Higher yellow power lets you shoot more laser beams,  
(Blue power does not do anything right now).  

#####Feature progress:
Feature | Description | Progress
:---:|---|---
Gamestates|Seperate the game state with the main menu and be able to switch between them freely|100%
Pause|Be able to pause the game|100%
Retry|Be able to start over|100%
Player|Player sprites, lives, shooting, collisions and movement|90% 
Boss|Boss sprites, life, shooting, collisions and possibly movement|80% 
Powers|Red, yellow and blue powers for boss and player|66% 
Bullets|Bullet mechanics and collisions|100%
Beams|Laser beam mechanics and collisions|100%
Blue power|Haven't come up with one yet|0%

#####To-do list:  
Add blue power  
Add a game-over screen when the player runs out of lives  
Fix bug where player lasers spawn off-center (most notable when firing whilst moving left or right)
[Release .exe only] Find out why the pause menu doesn't display correctly (functions as normal however) despite no source code changes between debug and release  

#####Changelog:
Version | Description
---|---
v0.3.0 | Rebalanced power levels and finished boss attacks.
v0.2.1 | Added more lasers for yellow power level 3-5 and added some more boss attacks
v0.2.0 | Reshuffled folders and project files to a more standard format.
v0.1.2 | Fixed player beams not colliding with the boss or dealing damage.
v0.1.1 | Fixed visual bug where the power level displayed on screen did not reset back to level 1 when retrying the game. <br>Added autofire toggle using the "a" button.
v0.1.0 | First upload to github, most of the engine is working fine and the game is playable, but is unbalanced. <br>Missing blue power.


#####Preview:

![Sample play](/res/Preview Pictures/Sample Play.PNG)  
Screenshot of sample play
