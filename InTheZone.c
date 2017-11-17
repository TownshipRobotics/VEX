//declare variables below
double calculatedPower = 0;
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;
float leftPercentage = 0.0;
float rightPercentage = 0.0;

void moveWheels(){
	//last year, we used the right joystick to drive the wheels
	//motors used for wheels will most likely be motors 9 and 10 for back wheels
	//to calcuate the power to move the motor at, take the distance between (ch4 value, ch3 value) and (0,0) or the square root of ((x^2)+(y^2))
	calculatedPower = sqrt(pow(vexRt[ChC],2)+pow(vexRt[ChD],2));
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
	if(vexRt[ChD]>0){
		//right motor speed = ((ch4Value/254)+.5)*(calculated power)
		rightMotorSpeed = (vexRT[ChD]/254+.5)*calculatedPower;
		//left motor speed = 1-(right motor speed)
		leftMotorSpeed = 1-rightMotorSpeed;
	}
	//if ch4 < 0
		//left motor speed = ((ch4Value/254)+.5)*(calculated power)
		//right motor speed = 1-(left motor speed)
	//else
		//return
}

//make sure main() is the last "task", weird C mechanic
task main()
{
	//apparently does not compile, but book says "this command should be the first thing in your "task main()" so idk
	//will not set up any motors and sensors, you must manually set the motos and sensors in the 'Motors and Sensors Setup' menu
	//robotType();
	//only two motors will be used for the base so we can use the rest to lift the cones and mobile goal

	moveWheels();





}
