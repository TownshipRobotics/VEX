#pragma config(Motor,  port1,           armLeft,       tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           frontLeft,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           backRight,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           claw,          tmotorNone, openLoop)
#pragma config(Motor,  port10,          armRight,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// DO NOT TOUCH CONFIGURATION OPTIONS! >:U

//**********************************
//		OMNIWHEEL CONTROL
//**********************************

// Limits n to between -limit and limit
int lim(int n, int limit)
{
    if(n > limit) return limit;
    if(n < -limit) return -limit;
    return n;
}

// Makes values closer to 0 more sensitive:
// 0 -> 0; 127 -> 127; 64 -> 40
// As n -> 127, returns an int that increases exponentially
// (It graphs like y = x/2+x^3)
int curve(int n)
{
    float l = lim(n, 127);
    return (int) (l*(0.5+pow(l, 2)/32258.619)+0.5);
}

// Takes xyz vectors and creates the correct omni powers for it
/*
Calculate vector as (A, d) where 0<=A<8, 0<=d<127
if(floor(A/2)):
	0= -1, A-1, 1, 1-A
	1= A-3, 1, 3-A, -1
	2= 1, 5-A, -1, A-5
	3= 7-A, -1, A-7, 1

multiply all by d
*/
int * getOmniPowers(int x, int y, int z)
{
    z = curve(z);
		// The percent the bot is rotating
    float rotPer = 1.0-abs(z)/127.0;

    // The "distance" of joystick from center 0 <= d < 127
    int d = curve(sqrt(pow(x, 2) + pow(y, 2)));

    // The angle 0 <= A < 8 of the joystick in relation to origin
    // A = 0 is to the right
    float A = (1.27323954474 * atan2(y, x)+8)%8;

    // Too long to explain in a comment >.>
    // (Ask me if you want an explanation)
    int powers[4];
    switch(floor(A/2)) {
        case 0:
            powers[0] = z+rotPer*-d;
            powers[1] = z+rotPer*d*(A-1);
            powers[2] = z+rotPer*d;
            powers[3] = z+rotPer*d*(1-A);
            break;
        case 1:
            powers[0] = z+rotPer*d*(A-3);
            powers[1] = z+rotPer*d;
            powers[2] = z+rotPer*d*(3-A);
            powers[3] = z+rotPer*-d;
            break;
        case 2:
            powers[0] = z+rotPer*d;
            powers[1] = z+rotPer*d*(5-A);
            powers[2] = z+rotPer*-d;
            powers[3] = z+rotPer*d*(A-5);
            break;
        case 3:
            powers[0] = z+rotPer*d*(7-A);
            powers[1] = z+rotPer*-d;
            powers[2] = z+rotPer*d*(A-7);
            powers[3] = z+rotPer*d;
    }

    return powers;
}

// Updates the power of the wheels
void updateOmni()
{
    // Array with the powers for each motor
    int * powers = getOmniPowers(-vexRT[Ch4], vexRT[Ch3], vexRT[Ch1]);
    // Set each motor's power correspondingly
    motor[frontLeft] = powers[0];
    motor[frontRight] = powers[1];
    motor[backRight] = powers[2];
    motor[backLeft] = powers[3];
}

//**********************************
//		ARM CONTROL
//**********************************

void updateArm()
{
    // Gets the power from joystick & curves it
    int power = curve(vexRT[Ch2]);

    // Negative powers already move quickly
    // due to gravity so half speed going down
    if(power < 0) power = power/2;

    // Power to hold arm up when stopped
    if(abs(power) < 5) power = 10;

    // Set motors to proper powers
    motor[armLeft] = -power;
    motor[armRight] = power;
}

//**********************************
//		CLAW CONTROL
//**********************************

// Keeps track of state of the claw
// (Make sure to start the bot with
//       the claw closed!)
bool open = false;

// Opens the claw
void openClaw()
{
    // Check if claw is already open
    if(!open) {
        motor[claw] = 35;
        //wait 1/2 of a second (value will probably turn into a constant)
        sleep(500);
        //stop motor
        motor[claw] = 0;
        open = true;
    }
}

// Closes the claw
void closeClaw()
{
    // Check if claw is already closed
    if(open) {
        motor[claw] = -35;
        //wait 1/2 second then stop
        sleep(600);
        //Leave motor running slightly so as to maintain pressure on claw
        motor[claw] = -10;
        open = false;
    }
}

// Updates claw's position
void updateClaw()
{
    if(vexRT[Btn5U] == 1) // If upper Z button down
        openClaw();
    else if(vexRT[Btn5D] == 1) // If lower Z button down
        closeClaw();
}

//**********************************
//		MAIN LOOP
//**********************************
task main()
{
    while(true) {
        updateOmni();
        updateArm();
        updateClaw();
    }
}
