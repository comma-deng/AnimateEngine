#pragma once

#include <vector>
#include <map>
#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

#include "BoneKeyFrame.h"

using namespace std;

/*
	一个meshNode对应一个KeyFrameTracker。
	一个animation对应一个Mesh。
	管理一系列KeyFrameTracker。
*/
class KeyFrameTracker
{
public:
	KeyFrameTracker(vector<BoneKeyFrame> list)
	{
		this->keyFramesList = list;
	}

	//TOTEST:有待测试
	quat getInterpRotation(double timepos)
	{
		int index1,index2;
		int num = binarySearchKeyFrame(timepos,index1,index2);
		switch (num)
		{

		case 0:
			{
				cerr<<"找不到KeyFrame！";
				break;
			}
		case 1:
			{
				return keyFramesList[index1].rotation;
			}
		case 2:
			{
				float rate =(timepos - keyFramesList[index1].timepos) /
					(keyFramesList[index2].timepos - keyFramesList[index1].timepos);
				
				return mix(keyFramesList[index1].rotation , keyFramesList[index2].rotation , rate); 

				break;
			}
		default:
			break;
		}

	}

	vec3 getInterpShift(TimePos timepos)
	{
		int index1,index2;
		int num = binarySearchKeyFrame(timepos,index1,index2);
		switch (num)
		{

		case 0:
			{
				cerr<<"找不到KeyFrame！";
				break;
			}
		case 1:
			{
				return keyFramesList[index1].shift;
			}
		case 2:
			{
				float rate =(timepos - keyFramesList[index1].timepos) /
					(keyFramesList[index2].timepos - keyFramesList[index1].timepos);
				
				return keyFramesList[index1].shift * (1-rate) + rate * keyFramesList[index2].shift; 

				break;
			}
		default:
			break;
		}
	}


	void test()
	{
		TimePos timepos;
		while(cin>>timepos)
		{
			
		vec3 shift = getInterpShift(timepos);
		cout<<shift.x<<" "<<shift.y<<" "<<shift.z<<endl;
		
		/*
		int index1,index2;
		cout<< binarySearchKeyFrame(timepos,index1,index2)<<endl;
		cout<<index1<<" "<<index2<<endl;*/
		}
	}

private:

	/*
	给定timepos,查找该时刻是夹在哪两个keyframe中间。
	index1和index2代表这两个keyframe在vector中的下标。
	找到返回1（刚好和某个keyframe对应），并把那个keyFrame的index写入index1。
	或者2（在两个KeyFrame中间），把两个index写入index1和index2.
	找不到则返回0。
	暂且采用二分搜索法进行搜索。
	*/
	int binarySearchKeyFrame(TimePos timepos , int &index1 , int& index2)
	{
		int indexA = 0;
		int indexB = keyFramesList.size()-1;

		if(timepos>keyFramesList[indexB].timepos || timepos<keyFramesList[indexA].timepos)
		{
			return 0;
		}

		int middle;

		while(indexA<indexB)
		{
			middle = indexA + (indexB - indexA)/2;

			if(timepos == keyFramesList[middle].timepos)
			{
				index1 = middle;
				return 1;
			}
			if(timepos > keyFramesList[middle].timepos)
			{
				indexA = middle;
			}
			else //timepos < keyFramesList[middle].timepos
			{
				indexB = middle;
			}
			
			if(indexA+1 == indexB) 
			{
				if(keyFramesList[indexA].timepos == timepos)
				{
					index1 = indexA;
					return 1;
				}
				else if(keyFramesList[indexB].timepos == timepos)
				{
					index1 = indexB;
					return 1;
				}
				else 
				{
					index1 = indexA;
					index2 = indexB;
					return 2;
				}
			}
		}

		
	}


	/*存储关键帧的列表 的列表。该列表中的每一个元素，是某一个骨骼对应的不同时间的KeyFrame,按照timepos从小到大顺序排列。*/
	vector<BoneKeyFrame>  keyFramesList;
};