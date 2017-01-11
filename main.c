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

// Updates the power of the wheels
void updateOmni()
{
    int x = vexRT[Ch4];
    int y = vexRT[Ch3];
    int z = vexRT[Ch1];
    motor[port2] = curve(x+y+z);
    motor[port3] = curve(x-y+z);
    motor[port4] = curve(-x-y+z);
    motor[port5] = curve(-x+y+z);
}

// When robot starts, this runs
task main()
{
    while(true) {
        updateOmni();
    }
}
