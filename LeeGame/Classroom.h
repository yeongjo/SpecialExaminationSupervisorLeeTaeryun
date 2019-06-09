#pragma once

#include "Student.h"
using namespace std;

constexpr int classroomX = 464*2;
constexpr int classroomY = 426*2;

class TestPaper;

// ����

// GameM���� ����������

// �л��� 9���� �⺻

//�����¹���ǥ���������ְ�
//���Ǿȿ� �ִ� �л����� �����Ѵ�.
// �ʿ��ϸ� �� ���ǿ��� �����л� �߻���ٰ� �˷��ִ°ŵ� �����ҵ�

// �۷ι� ���� �Ҷ��� ���⼭ ��
// �۷ι� ����� �� ģ���� Ư�� �Լ��� �ҷ� ������ ������
// �ٸ� ��� �л��鿡�� ���ظ� ��
class Classroom : public Obj{
	// �л��� ��ӹ޴� �����ڰ� �����Ŷ� �����ͷ� ��
	vector<Student*> students;
	vector<Desk *> desks;
	static CImage *img;

	bool isInit = false;
public:
	TestPaper *paper = nullptr;
	
	Classroom();
	~Classroom();

	/* TODO �̹��� �ҷ�����
	 �л� �� 9������ �ʱ�ȭ
	 ������ ������ ����
	 i�� ���� ��ġ�� x�������� ���� �����ŭ �з������ϱ�
	 */
	// �л��� å���� ��� �ʱ�ȭ��
	void init(int i);

	// �ٸ�������� ȭ�����ϰ������ ȣ��
	// stu���� �� ����� ������ ����� ȭ���� �Ѵ�. ������ ��������
	void makeAngryStudentInClass(Student *stu, float amount, float range);
	//void makeAngryThisStuent(Student *stu, float amount);

	void removeStudent(int i);
	void removeStudent(Student *stu);

	void changeOffX(float _x);

	void tick();

	// TODO �̹��� �׸���
	virtual void render(HDC h);

	size_t getStudentSize();
	//�ڵ����� assert �Ǵϱ� ����
	Student *getStudent(int i) { return students [i]; }
};

class TestPaper : public Guy{
public:
	Pos<float> lastDragDropPos;
	static CImage *img;

	static void loadImg() {
		if (img) return;
		img = new CImage();
		img->Load(L"img/testpaper.jpg");
	}

	TestPaper(Pos<float>& _p){
		p = _p+Pos<float>(221*2,328*2);
		loadImg();
		size.x = img->GetWidth()<<1;
		size.y = img->GetHeight()<<1;
	}
	void render(HDC h) {
		if (!isAble) return;
		auto t = p + off;
		img->StretchBlt(h, t.x, t.y, size.x, size.y, SRCCOPY);
	}

	void onceUp() {
		if (isDraging) {
			lastDragDropPos = p;
		}
		Guy::onceUp();
	}
	void onceDown() {
		Guy::onceDown();
		SoundM::paperDrop();
	}
	void onceUpWithOutMouseCheck() {
		if (isDraging) {
		SoundM::paperDrop();
	}
	Guy::onceUpWithOutMouseCheck();
	}

	bool isDestroyZone() { return false; }
};