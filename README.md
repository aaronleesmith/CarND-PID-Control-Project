# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Reflections
As part of the project, I am including reflections on my experience implementing the PID control here.

### Describe the effect each of the P, I, D components had in your implementation.

#### P
Changing the proprotional tuning parameter (P) resulted in the system overcorrecting and making large, sweeping motions around the center line. This casued the system to quickly become unstable and drive off the road. A large CTE combined with a large value for <i>P</i> can create even higher CTE, causing oscillation and finally system divergence.

#### I
I set the integral tuning parameter to a high value at first to see what would happen. If this error is too high (say one order of magnitude too high) it can throw the whole system off very early. In order for this parameter to be effective, it needs to be correcting for cumulative error which is smoothed by many successive measurements. If the value is too high, it is too reactive to errors early on and overcorrects. 

On the other hand, if I is set to a very low value (0, for example), the car ends up driving straight and then making abrupt corrections around turns. It can drive the track with my implementation, but it is decidedly less smooth. This is because the car does not adjust to minor errors and continues to be biased to straight lines, only correcting after the error in the turn starts to heavily negatively impact the system.

#### D 
Increating the derivative term an order of magintude tends to make the car very jerky and make abrupt corrections. A very small <i>D</i> causes the car to be very wobbly. I suspect this is because the derivative, which represents the slope of the error over time, helps to smooth the corrections. A small D means P is overinfluential to the correction and therefore overcorrects.


### Describe how the final hyperparameters were chosen.
I used a combination of guessing and checking and TWIDDLE. Initially, I attempted to hand-tune my parameters to get the car to drive. This got me in the realm I wanted to be in, with P, I, and D being set to 0.14, 0.001, and 3.0 initially. 

To improve performance, I also use TWIDDLE to tune these parameters at drive time. Twiddle is implemented as part of the PID control, and nudges P, I, and D in very small values until a threshold is reached. Most of the success of the car is a results of the initial parameter settings, however.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
