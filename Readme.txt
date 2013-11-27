Nikolas Aleliunas
aleliuna@uvic.ca / nik.aleliunas@gmail.com
Boids - Zombie Firefly Edition

Controls:
Mouse Controls :
 - Clicking Changes between normal PREDATOR rules and Follow the Leader Rules (the leader firefly will turn blue)
	- Use the slider to change the amount of fireflies.
Code Usage:
   Implementations from http://www.red3d.com/cwr/boids/
   
Features:
  Zombie Predator Movement:
	-Reds are slower but turn faster, seek out other fireflies.
	-Normals Try to run away from the center of mass of all nearby zombies.
	-when one is tagged, it turns red as well.
  Follow the Leader:
	-Turns zombie infection into random motion.
	-When a firefly gets near to the leader, it tries to follow it.

Notes:
   Wandering Settings for Lead Firefly unimplemented, so it uses literal brownian motion.
   Firefly flashing code based off the fact that fireflies continuously like to sync together ( see: http://www.youtube.com/watch?v=a-Vy7NZTGos ).
   Fireflies "flashes" are a series of Differential equations based on cos.. when they reach 0/2PI, they flash. Every other firefly knows when the others will flash, so they try to sync up with their resetting strength.
   Included is the code I created for this (much) earlier project, which is undocumented, but shows the firefly flash patterns much clearer.
	Some elementary controls for this earlier project:
	Q: Quit
	E: Add 50 Random Fireflies
	F: Change how fireflies interpret flashes. (0 changes it to a normal ODE)
	R: add randomness to fireflies
	[ & ]: increase/decrease resetting strength.
	; & ': increase/decrease the frequency of flashes.
	, & .: increase/decrease the number of fireflies.