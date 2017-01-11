// Limits n to between -limit and limit
int lim(int n, int limit)
{
    if(n > limit) return limit;
    if(n < -limit) return -limit;
    return n;
}

// Makes values closer to 0 more sensitive:
// 0 -> 0; 127 -> 127; 64 -> 64^3/127^2 = 16.25
// As n -> 127, returns an int that increases exponentially
int curve(int n)
{
    return pow(lim(n, 127), 3)/16129;
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
int * getOmniPowers(int x, int y, int z) {
    int d = curve(sqrt(pow(x, 2) + pow(x, 2)));
    float A = (1.27323954474 * atan2(y, x)+8)%8;
    int powers[4];
    switch(floor(A/2)) {
    	case 0:
    		powers[0] = -d;
    		powers[1] = d*(A-1);
    		powers[2] = d;
    		powers[3] = d*(1-A);
    		break;
    	case 1:
    		powers[0] = d*(A-3);
    		powers[1] = d;
    		powers[2] = d*(3-A);
    		powers[3] = -d;
    		break;
    	case 2:
    		powers[0] = d;
    		powers[1] = d*(5-A);
    		powers[2] = -d;
    		powers[3] = d*(A-5);
    		break;
    	case 3:
    		powers[0] = d*(7-A);
    		powers[1] = -d;
    		powers[2] = d*(A-7);
    		powers[3] = d;
    }
    return powers;
}

// Updates the power of the wheels
void updateOmni()
{
    int * powers = getOmniPowers(vexRT[Ch4], vexRT[Ch3], vexRT[Ch1]);
    motor[port2] = powers[0];
    motor[port3] = powers[1];
    motor[port4] = powers[2];
    motor[port5] = powers[3];
}

// When robot starts, this runs
task main()
{
    while(true) {
        updateOmni();
    }
}
