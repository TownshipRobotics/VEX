//declare variables below


void moveWheels(){
	//last year, we used the right joystick to drive the wheels
	//look up variables for joysticks to use for values
	//motors used for wheels will most likely be motors 9 and 10 for treads
	//to calcuate the power to move the motor at, take the distance between (ch4 value, ch3 value) and (0,0) or the square root of ((x^2)+(y^2))
	//if you were to face the same direction the robot is, left wheel moves -1*(calculated power) and right wheel moves the calculated power
	//to turn, make the power go to the motors at a percentage
	//ch 4 value (x value)		ch 3 (y) value		what i want it to do
	//  0												50								move forward in a straight line
	//	50											0									turn right at full power; only right wheel moves and left wheel stays still
	//  0												-50							  move backward in a straight line
	//  -50											0									turn left at full power; only left wheel moves and right wheel stays still
	//percentage calculation is probably (ch4Value/254)+.5
		//254 is the denominator because it is the max motor speed, 127, times 2
	//if ch4 > 0
		//right motor speed = ((ch4Value/254)+.5)*(calculated power)
		//left motor speed = 1-(right motor speed)
	//if ch4 < 0
		//left motor speed = ((ch4Value/254)+.5)*(calculated power)
		//right motor speed = 1-(left motor speed)
	//else
		//return
}

//make sure main() is the last "task", weird C mechanic
task main()
{
	//speed for the motors attached to the wheels
	//only two motors will be used so we can us them to lift the cones and mobile goal

	//any other motors we need
	moveWheels();





}
