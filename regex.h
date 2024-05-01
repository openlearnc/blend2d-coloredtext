
#include"blend2d.h"
#include<vector>
using namespace std;

typedef  struct colortext{
	int position;
	int range;
	BLRgba32 color;
}colortext;

vector<colortext> stdd(char*str);