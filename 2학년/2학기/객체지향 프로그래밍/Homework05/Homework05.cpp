#include <iostream>
using namespace std;

class Box {
private:
	int w;
	int h;
	int v_h;

public:
	Box(int w = 1, int h = 1, int v_h = 1)
	{
		this->w = w;
		this->h = h;
		this->v_h = v_h;
	}
	void empty()
	{
	}
	int getVolume()
	{
		return (w * h * v_h);
	}
	void print()
	{
		cout << "밑면적 : " << w * h << "\t상자 높이 : " << v_h << "\t부피 : " << w * h * v_h << endl;
	}
};
int main()
{
	Box b1(2, 3, 4), b2(4, 5, 6);
	Box b3; // 매개변수 없는 경우 w=1, h=1, v_h=1 으로 지정
	cout << "========================================" << endl;
	cout << "박스 1 "; b1.print();
	cout << "박스 2 "; b2.print();
	cout << "박스 3 "; b3.print();
	cout << "========================================" << endl;
	int vb1 = b1.getVolume();
	int vb2 = b2.getVolume();
	int vb3 = b3.getVolume();
	// 3 상자의 부피 비교하여 가장 큰 것 출력하는 내용
	if (vb1>=vb2 && vb1>=vb3)
	{
	cout << "박스1의 부피가 가장큽니다 : " << vb1 << endl;
	}
	else if (vb2 >= vb1 && vb2 >= vb3)
	{
		cout << "박스2의 부피가 가장큽니다 : " << vb2 << endl;
	}
	else 
	{
		cout << "박스3의 부피가 가장큽니다 : " << vb3 << endl;
	}
	return 0;
}