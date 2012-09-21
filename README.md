BallSim
=======

Created by: Griffin Ledingham
Student #: V00712188
E-Mail: gcledingham@gmail.com

If an issue occurs running the program, please email me arrange for me to bring in my laptop to demo.

BallSim is a physics based bouncing ball simulator.

Hit detection is present between the ball class and the surface class, and is implemented by calling ->collide(). The collide function is working between surfaces, and any balls in the sceneBalls array.

Multiple balls in the scene has been implemented, but only 1 ball is spawned in my deliverable. The number of balls can be modified by changing the num_balls variable, and adding new ball objects to the initialization "ball *sceneBalls[#]". Extra balls in the scene have full hit detection, as well as full randomized attributes when spawning new balls. Likewise, a surface array could be created, removing the specific surface collision calls, and replacing them with an iteration loop calling collide from each index of the surface array.

Due to my pong implementation, I have decided to not have the walls scalable in an array like I did balls. It would be very simple to make this change, mirroring how I have the ball array set up.

The surface and ball classes are modular making placement of the objects simple and efficient.

I have added a "Pong" option to the simulation. By clicking on the pong mode check box, the camera shifts to a birds eye angle, and pong-style walls are spawned. The speed of the spawned ball may be upped by enabling the "Nightmare Mode" checkbox. 

One bug which has persisted in the program occurs when the simulation is newly compiled and run for the first time. Spontaneously, the ball will not initially spawn correctly. This can be worked around by spawning a new ball using the push button or the spacebar. I have not yet found the cause of this issue.
