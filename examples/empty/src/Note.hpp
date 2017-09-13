#pragma once


class Note
{

	uint8 m_index = 0;

public:

	BMS::Note m_bmsNote;


	Note(const BMS::Note &note)
		: m_bmsNote(note)
	{




	}

	uint8 index() const
	{
		return m_bmsNote.pos;
	}

	// ���[���ɉf���Ă��画�胉�C���ɏ��܂ŉ��b�����邩
	double aTime = 0.2;// 1.0;


	double position(const double currentTime)
	{
		return (m_bmsNote.time - currentTime) / aTime;
	}

	double position(const double currentTime, const double noteTime)
	{
		return (m_bmsNote.time - currentTime) / noteTime;
	}


	void update(const double currentTime)
	{

	}


	void draw3D(const Lane &lane, const double currentTime, const LaneTemplate &_template)
	{


		// �Đ��ʒu
		const double pos = position(currentTime, _template.noteTime);


		if (pos > 1) return;
		if (pos < 0) return;


		auto v = pos * LANE_QUALITY;

		auto vv = Math::Floor(v);


		auto vvv = v - vv;

		




		auto begin = lane.point(vv);

		auto next = vv + 1 >= LANE_QUALITY ? vv : vv + 1;

		auto end = lane.point(next);

		auto pos3D = begin + (end - begin) * vvv;

		// Plane(pos3D, 1, 1, q).draw(Palette::Green);


		// ��
		auto color = lane.noteColor;

	

		color.a -= (pos * lane.fadeOpacity);


		// �m�[�c�̌���
		Vec3 forward;



		// �n�_�ƏI�_���قړ����ʒu�ɂȂ�m�[�c�̌����� Vec3::Forward �ɂ���
		// if (begin == end)
		if ((end - begin).lengthSq() < 0.001)
		{
			forward = Vec3::Forward;
		}
		else
		{
			forward = (end - begin).normalized();
		}

		CreatePlane(pos3D, forward, lane.w, lane.noteSize).drawForward(color);


		
		// Sphere(pos3D, 0.1).draw();


	}


};