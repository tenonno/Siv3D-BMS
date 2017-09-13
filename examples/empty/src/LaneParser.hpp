#pragma once


#include <iterator>


namespace LaneParser
{


	// 0 ~ LANE_QUALITY �̃L�[�ƈʒu���
	// �� :
	// {
	//     1: Vec3,
	//     50: Vec3
	// }
	using FramePointMap = std::map<int, Vec3>;


	std::array<FramePointMap, LANE_COUNT> Parse2(const JSONArray &lanes)
	{



		std::array<FramePointMap, LANE_COUNT> map;

		int index = 0;

		for (auto &lane : lanes)
		{

			FramePointMap timePointMap;

			auto points = lane[L"points"].getArray();

			std::reverse(points.begin(), points.end());


			auto size = points.size();

			auto length = 0.0;

			// ���[���̒���
			for (auto i : step(size - 1))
			{
				length += (JSONValueToVec3(points[i + 1]) - JSONValueToVec3(points[i])).length();
			}


			auto beforePos = JSONValueToVec3(points[0]);

			auto pos = 0.0;

			for (auto i : step(size))
			{

				// 0.0 ~ 1.0
				double position = 1.0 / size * i;

				pos += (beforePos - JSONValueToVec3(points[i])).length();
				beforePos = JSONValueToVec3(points[i]);

				position = (pos / length);

				int positionInt = Math::Floor(position * LANE_QUALITY);

				timePointMap[positionInt] = JSONArrayToVec3(points[i].getArray());

			}

			map[index++] = timePointMap;
			
		}

		return map;

	}


	Array<Vec3> ToPoints(const FramePointMap &_laneTimeState)
	{
		Array<Vec3> result(LANE_QUALITY);

		auto laneTimeState = _laneTimeState;




		
		// �ŏ��ƍŌ�ɕK����񂪂���悤�ɂ���
		laneTimeState[0] = laneTimeState.begin()->second;
		laneTimeState[LANE_QUALITY - 1] = (--laneTimeState.end())->second;


		auto currentIterator = laneTimeState.begin();
		auto nextIterator = ++laneTimeState.begin();

		for (auto i : step(LANE_QUALITY))
		{

			// �n�_
			auto begin = currentIterator->second;
			// �I�_
			auto end = nextIterator->second;

			// ���̃L�[�t���[���܂ł̗v�f��
			// auto dist = std::distance(currentIterator, nextIterator);
			auto dist = nextIterator->first - currentIterator->first;

			if (dist == 0) MessageBox::Show(L"w");

			auto toVec = end - begin;

			// 0 ~ 1 ( begin -> end �̈ʒu ) 
			auto t = (i - currentIterator->first) / (double)(dist);

				
			// ���W
			auto pos = begin + toVec * t;


			result[i] = pos;


			// ���̃L�[�t���[����
			if (i == nextIterator->first)
			{
				++currentIterator;
				++nextIterator;

				if (nextIterator == laneTimeState.end())
				{
					--nextIterator;
				}

			}


		}




		return result;
	}

}

