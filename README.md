# ZiiRobots-Joystick-Control

This project sets up a joystick controller that will communicate with a given ZiiRobots robot through I2C communication. The joystick sends instructions to the robot every 
50 milliseconds. The instructions include the direction and magnitude of power that the robot should turn. These values were calculated using the given specifications of
the joystick; depending on user input, the program calculates the angle and magnitude of the joystick motion. This information is then transferred to the robot to control
its movement. More specifically, the power sent to the left and right wheels of the robot are adjusted to be consistent with the indicated movement of the joystick.
