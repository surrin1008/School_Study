#include <iostream>
#include <cmath>

using namespace std;

double dist_2d(int x1, int y1, int x2, int y2) //두 점간의 거리 반환
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double quad_eqn(double a, double b, double c)// 근을 출력
{
	if ((pow(b, 2) - (4 * a * c)) > 0)
	{
		cout << "근은 " << ((-1 * b) - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a) << "와 " << ((-1 * b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a) << " 입니다." << endl;
	
	}
	else if ((pow(b, 2) - (4 * a * c)) == 0)
	{
		cout << "근은 " << ((-1 * b) + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a) << "입니다." << endl;
	}
	else if((pow(b, 2) - (4 * a * c)) < 0)
	{
		cout << "근이 없습니다." << endl;
	}
	return 0;
}

void P9() //좌표 및 거리 출력
{
	int x1, y1, x2, y2;
	
	cout << "x1, y1, x2, y2를 차례대로 입력하시오." << endl;
	cin >> x1 >> y1 >> x2 >> y2;
	
	cout << "좌표1 : (" << x1 << "," << y1 << ")" << endl;
	cout << "좌표2 : (" << x2 << "," << y2 << ")" << endl;
	
	cout << "두 점간의 거리 :" << dist_2d(x1, y1, x2, y2) << endl;
}

void P10() // quad_eqn을 호출
{
	int a, b, c;
	cout << "ax^2 + bx + c = 0" << endl;
	cout << "2차 방정식의 계수를 입력하시오." << endl;
	
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	cout << "c: ";
	cin >> c;

	quad_eqn(a, b, c);
}

int main()
{
	P9();
	P10();
	return 0;
}