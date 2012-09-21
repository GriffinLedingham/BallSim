BallSim
=======

Created by: Griffin Ledingham
Student #: V00712188
E-Mail: gcledingham@gmail.com

If an issue occurs running the program, please email me arrange for me to bring in my laptop to demo.

BallSim is a physics based bouncing ball simulator.

Hit detection is present between the ball class and the surface class, and is implemented by calling ->collide(). The collide function is only working between surfaces, and the specific myBall object, as an array was not necessary for this implementation.

Multiple balls could easily be added, and hit detected by declaring a ball array, and checking each array index in the collide function. Likewise, a surface array could be created, saving the specific surface collision calls, and replacing them with an iteration loops calling collide from each index of the surface array.

The surface and ball classes are modular making placement of the objects simple and efficient.

I have added a "Pong" option to the simulation. By clicking on the pong mode check box, the camera shifts to a birds eye angle, and pong-style walls are spawned. 

One bug which has persisted in the program occurs when the simulation is newly compiled and run for the first time. Spontaneously, the ball will not initially spawn correctly. This can be worked around by spawning a new ball using the push button or the spacebar. I have not yet found the cause of this issue.
