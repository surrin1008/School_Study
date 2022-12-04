#include <iostream>
using namespace std;

class FruitSeller {
private:
	int apple_cost;
	int apple_cnt;
	int money;

public:
	FruitSeller(int apple_cost, int apple_cnt, int money)
	{
		this->apple_cost = apple_cost;
		this->apple_cnt = apple_cnt;
		this->money = money;
	}
	int saleApples(int cost)
	{
		int num = cost / apple_cost;
		apple_cnt -= num;
		money += cost;
		return num;
	}
	void ShowSalesResult()
	{
		cout << "남은 사과 : " << apple_cnt << endl;
		cout << "판매 수익 : " << money << endl;
	}
};
class FruitBuyer {
private:
	int money;
	int apple_cnt;

public:
	FruitBuyer(int money, int apple_cnt)
	{
		this->money = money;
		this->apple_cnt = apple_cnt;
	}

	void BuyApples(FruitSeller &seller,int cost)
	{
		apple_cnt += seller.saleApples(cost);
		money -= cost;
	}

	void ShowBuyResult()
	{
		cout << "현재 잔액 : " << money << endl;
		cout << "사과 개수 : " << apple_cnt << endl;
	}
};

int main()
{
	FruitSeller seller(1000, 20, 0);

	FruitBuyer buyer(5000, 0);

	buyer.BuyApples(seller, 2000);

	cout << "과일 판매자의 현황" << endl;
	seller.ShowSalesResult();
	cout << endl;

	cout << "과일 구매자의 현황" << endl;
	buyer.ShowBuyResult();
	return 0;
}