
#include "MyBubbles.h"

MyBubbles::MyBubbles(float x, float y, float sp)
{
    position.x = x;
    position.y = y;
    speed = sp;
}


void MyBubbles::advance(int count)
{
    speed *= count;
}
