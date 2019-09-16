# Proposal: Flappy Canada Goose

## Synopsis

#  Elements

This game will have 2 main elements in its game play:

 - A bird (represented by a Canada Goose image sprite) that is user controlled and
 moves vertically

 - A series of pairs of pipes (represented by green rectangle sprites) that will
 continuously move horizontally towards the left edge of the screen.

#  Goal

The player's goal is to get the bird through as many pipe obstacles as possible without
making contact with one of the pipes or having the bird hit the ground (which will be the
bottom of the screen).

#  Game play

The player starts the game by pressing the space bar, after which, gravity will immediately
start working on the bird and the the bird will then move towards the pipes. The user can
press the space bar to create a temporary upwards acceleration or 'flap' that will allow
them to dodge the pipes and stay above the ground. If the bird touches a pipe or hits
the bottom of the screen, the game is over.

## Functional requirements

1. In the dead state of the game, the bird will be fixed in place on the left side of
the screen, at the center of the vertical axis. The very first pipe pair is initialized off
the right side of the screen.

2. The pipes come in pairs - in each pair, one pipe will hang upside down from the ceiling
and one pipe will stand right side up on the ground. The distance between the upper and lower
pipes is constant, as well as the width of each pipe and the distance between pipe pairs. The
height of the bottom pipe is randomized for each pair (the height of the top pipe is based on
the height of the bottom pipe).

3. The player switches from the dead state to the live state once they press the space bar
for the first time.

4. As soon as the game's live state is initiated, the force of gravity will constantly act
on the bird until the game is over.

5.  During the game's live state, the user can control the y-coordinate of the bird using
the space bar. Every time the space bar is pressed, the bird has a small upward
acceleration that will be stronger than the force of gravity, allowing the bird to 'flap'
upwards.

6. The user will only be able to activate the flaps while the bird is falling, instead of
continuously being able to build their upward trajectory (in the context of C++, this
means the bird's velocity has to be positive for the user input (i.e pressing the space
bar to have any effect)). This gives the flapping action a jerky, discontinuous motion
that prevents the game from being too easy for the user.

7. The bird's x-coordinate will be fixed throughout the game. Instead of the bird moving
in the horizontal direction, as time elapses, the game will increment the x-coordinate of
all the pipes in the negative x-direction. This will give the illusion that the bird is
moving horizontally, when really, it is stationary on the x-plane.

8. The screen will be split into 4 sections, where each section contains a pipe pair. As
soon as the right edge of the section is equal to the x-coordinate of the edge of the
screen (aka the pipe passes through the left edge of the screen), a new pipe pair is created at
the back of the the pipe vector off the screen (to the right of the right edge of the screen) with
a new randomized height for the pipes and will immediately increment in the left hand directions along
with the other pipe sections. This will make the game seem like an infinite course.

9. At the beginning of the game, the player's score is 0. Every time the bird passes
through a gap in the pair of pipes, the player's score updates by 1.

10. If the bird hits the ground or makes contact with any of the pipes, the game will
transition to the game over state.

11. In the game over state, the player's final score will display, as well as their medal.
If the player gets 10 points or over, they get a bronze medal. If the player gets 20 points
or over, they get a silver medal. If the player gets 30 points or over, they get a gold
medal. If the player is below 10 points, they get a condescending message.

12. The game will be in the game over state until the program is closed and CLion is run again.

## Open questions

- What arguments should the constructors take, if any?
- What values for gravity and upward acceleration for the flaps would make the game work best?
- How many pipes should be on the screen at one time?
- What velocity should the pipes be moving at for the game to have the appropriate amount of
difficulty.


