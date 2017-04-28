#pragma once

#include <vector>
#include <map>
#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>

#include "BoneKeyFrame.h"

using namespace std;

/*
	һ��meshNode��Ӧһ��KeyFrameTracker��
	һ��animation��Ӧһ��Mesh��
	����һϵ��KeyFrameTracker��
*/
class KeyFrameTracker
{
public:
	KeyFrameTracker(vector<BoneKeyFrame> list)
	{
		this->keyFramesList = list;
	}

	//TOTEST:�д�����
	quat getInterpRotation(double timepos)
	{
		int index1,index2;
		int num = binarySearchKeyFrame(timepos,index1,index2);
		switch (num)
		{

		case 0:
			{
				cerr<<"�Ҳ���KeyFrame��";
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
				cerr<<"�Ҳ���KeyFrame��";
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
	����timepos,���Ҹ�ʱ���Ǽ���������keyframe�м䡣
	index1��index2����������keyframe��vector�е��±ꡣ
	�ҵ�����1���պú�ĳ��keyframe��Ӧ���������Ǹ�keyFrame��indexд��index1��
	����2��������KeyFrame�м䣩��������indexд��index1��index2.
	�Ҳ����򷵻�0��
	���Ҳ��ö�������������������
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


	/*�洢�ؼ�֡���б� ���б����б��е�ÿһ��Ԫ�أ���ĳһ��������Ӧ�Ĳ�ͬʱ���KeyFrame,����timepos��С����˳�����С�*/
	vector<BoneKeyFrame>  keyFramesList;
};