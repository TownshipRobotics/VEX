//Modifies the xyz vectors so that x+y+z <= 127 to make for more accurate controls
int * modify(int x, int y, int z) {
	float hypo = sqrt(pow(x, 2) + pow(y, 2));
	float rotPer = z/127.0;
	int nums[3];
	nums[0] = (1-rotPer)*x*hypo/127;//formula for x
	nums[1] = (1-rotPer)*y*hypo/127;//formula for y
	nums[2] = rotPer*z;
	return nums;
}

//Limits n to between -limit and limit
int lim(int n, int limit)
{
	if(n > limit) return limit;
	if(n < -limit) return -limit;
	return n;
}

//Makes values closer to 0 more sensitive:
//0 -> 0; 127 -> 127; 64 -> 64^3/127^2 = 16.25
//As n -> 127, returns an int that increases exponentially
int curve(int n)
{
	return pow(lim(n, 127), 3)/16129;
}

//Updates the power of the wheels
void updateOmni()
{
	int * coords = modify(vexRT[Ch4], vexRT[Ch3], vexRT[Ch1]);
	int x = coords[0];
	int y = coords[1];
	int z = coords[2];
	motor[port2] = curve(x+y+z);
	motor[port3] = curve(x-y+z);
	motor[port4] = curve(-x-y+z);
	motor[port5] = curve(-x+y+z);
}

//When robot starts, this runs
task main()
{
	while(true) {
		updateOmni();
	}
/*
0/1   -1  1  1 -1		-1  1  1 -1
1/1   -1  0  1  0		-2  0  2  0
1/0   -1 -1  1  1		-1 -1  1  1
1/-1   0 -1  0  1		 0 -2  0  1
0/-1   1 -1 -1  1
-1/-1  1  0 -1  0
-1/0   1  1 -1 -1
-1/1   0  1  0 -1
0/0    0  0  0  0

-x-y  -x+y  x+y  x-y
/(|x|+|y|)*/
}
