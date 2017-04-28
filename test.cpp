#include <iostream>



#include "KeyFrameTracker.h"

using namespace std;


int main()
{
	vector<BoneKeyFrame> KeyFrameList;
	BoneKeyFrame k1;
	k1.timepos = 0;
	k1.shift = vec3(0,0,0);
	BoneKeyFrame k2;
	k2.timepos = 5;
	k2.shift = vec3(10,10,10);
	BoneKeyFrame k3;
	k3.timepos = 9;
	k3.shift = vec3(6,6,6);

	KeyFrameList.push_back(k1);
	KeyFrameList.push_back(k2);
	KeyFrameList.push_back(k3);

	KeyFrameTracker tracker(KeyFrameList);
	tracker.test();
}