#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main() {
	short people;
	cout << "请输入用餐人数（2-3）" << endl;
	cin >> people;
	float *v = new float[pow(2,people) + 1];
	cout << "请依次输入各人所购买金额" << endl;
	for (int i = 1; i <= people; i++) {
		cin >> v[i];
	}
	cout << "请输入总配送费" << endl;
	float fee;
	cin >> fee;
	cout << "请输入达到的满减数量，如果没有请输入0" << endl;
	short number;
	cin >> number;
	if (number != 0) {
		cout << "请输入各满减（从小到大）的门槛" << endl;
		int *edge = new int[number + 1];
		for (int i = 1; i <= number; i++) {
			cin >> edge[i];
		}
		cout << "请输入各满减（从小到大）的满减金额" << endl;
		int *discount = new int[number + 1];
		for (int i = 1; i <= number; i++) {
			cin >> discount[i];
		}
		
		float sum = 0;
		for (int i = 1; i <= people; i++) {
			sum += v[i];
		}

		if (people == 2) {
			int i = 1;//人的指标
			for (i = 1; i <= people; i++) {
				int j = number;//满减的指标，从大到小判断
				while (j >= 1) {
					if (v[i] >= edge[j]) {//有满减
						v[i] = v[i] - discount[j];
						break;
					}
					else {
						j--;
					}
				}
			}
			int j = number;
			while (j >= 1) {
				if (sum >= edge[j]) {//有满减
					sum = sum - discount[j];
					break;
				}
				j--;
			}
			cout << "各人依次应出:" << endl;
			cout.setf(ios::fixed);
			
			cout << setprecision(2) << (v[1] - v[2] + sum) / 2.0 + fee / (float)people << endl;
			cout << setprecision(2) << (v[2] - v[1] + sum) / 2.0 + fee / (float)people << endl;
		}

		if (people == 3) {
			v[4] = v[1] + v[2];
			v[5] = v[1] + v[3];
			v[6] = v[2] + v[3];//合作的值

			for (int i = 1; i <= 6; i++) {
				int j = number;//满减的指标，从大到小判断
				while (j >= 1) {
					if (v[i] >= edge[j]) {//有满减
						v[i] = v[i] - discount[j];
						break;
					}
					else {
						j--;
					}
				}
			}
			for (int i = 1; i <= 6; i++) {
				v[i] = -v[i];
			}
			int j = number;
			while (j >= 1) {
				if (sum >= edge[j]) {//有满减
					sum = sum - discount[j];
					break;
				}
				j--;
			}
			sum = -sum;
			//接下来求shapley value
			float x1, x2, x3;
			x1 = (2 * v[1] + v[4] - v[2] + v[5] - v[3] + sum - v[6] + sum - v[6]) / 6.0;
			x2 = (2 * v[2] + v[4] - v[1] + v[6] - v[3] + sum - v[5] + sum - v[5]) / 6.0;
			x3 = (2 * v[3] + v[5] - v[1] + v[6] - v[2] + sum - v[4] + sum - v[4]) / 6.0;
			cout << "各人依次应出:" << endl;
			cout.setf(ios::fixed);

			cout << setprecision(2) << -x1 + fee / (float)people << endl;
			cout << setprecision(2) << -x2 + fee / (float)people << endl; 
			cout << setprecision(2) << -x3 + fee / (float)people << endl;
		}
	}
	else if (number == 0) {
		cout << "各人依次应出:" << endl;
		cout.setf(ios::fixed);
		for (int i = 1; i <= people; i++) {
			cout << setprecision(2) << v[i] + fee / (float)people <<endl;
		}
	}
	system("pause");
}