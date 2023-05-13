#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <numeric>
#include <stack>
#include <graphics.h>
#include<conio.h>
#include <iomanip>
using namespace std;
double evaluate(string s) {
	stack<double> nums;   // ������ֵ�ջ
	stack<char> ops;   // ����������ջ
	int n = s.size();
	for (int i = 0; i < n; i++) {
		char c = s[i];
		if (isdigit(c) || c == '.') {   // ��������ֻ�С��������ѹ������ջ��
			double num = 0, div = 1;
			while (i < n && (isdigit(s[i]) || s[i] == '.')) {
				if (s[i] == '.') {
					div = 10;
				}
				else {
					num = num * 10 + (s[i] - '0');
					if (div > 1) {
						div *= 10;
					}
				}
				i++;
			}
			i--;
			nums.push(num / div);
		}
		else if (c == '(') {   // ���������������ѹ�������ջ��
			ops.push(c);
		}
		else if (c == ')') {   // �������������������ջ��ȡ��һ����������������֣��������㲢�����ѹ������ջ��
			while (ops.top() != '(') {
				double b = nums.top(); nums.pop();
				double a = nums.top(); nums.pop();
				char op = ops.top(); ops.pop();
				switch (op) {
				case '+': nums.push(a + b); break;
				case '-': nums.push(a - b); break;
				case '*': nums.push(a * b); break;
				case '/': nums.push(a / b); break;
				}
			}
			ops.pop();   // ����������
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (!ops.empty() && (ops.top() == '*' || ops.top() == '/') && i > 0 && s[i - 1] != '(') {
				// �����ǰ��������ȼ�С�ڵ���ջ�����������ȡ��ջ����������������ֽ������㲢�����ѹ������ջ�У�ֱ����ǰ���������ջ�������Ϊֹ
				double b = nums.top(); nums.pop();
				double a = nums.top(); nums.pop();
				char op = ops.top(); ops.pop();
				switch (op) {
				case '+': nums.push(a + b); break;
				case '-': nums.push(a - b); break;
				case '*': nums.push(a * b); break;
				case '/': nums.push(a / b); break;
				}
			}
			ops.push(c);
		}
	}
	while (!ops.empty()) {   // ����ȡ��ջ����������������ֽ������㲢�����ѹ������ջ��
		double b = nums.top(); nums.pop();
		double a = nums.top(); nums.pop();
		char op = ops.top(); ops.pop();
		switch (op) {
		case '+': nums.push(a + b); break;
		case '-': nums.push(a - b); break;
		case '*': nums.push(a * b); break;
		case '/': nums.push(a / b); break;
		}
	}
	return nums.top();   // ����ջ��Ψһ��Ԫ�ؼ�Ϊ������
}
string szys(int max_num, string operators, bool allow_parenthesis, bool allow_decimal) {
	vector<string> ops;
	for (int i = 0; i < operators.size(); ++i) {
		ops.push_back(string(1, operators[i]));
	}
	float n1 = allow_decimal ? (float)rand() / RAND_MAX * max_num : rand() % max_num + 1;
	float n2 = allow_decimal ? (float)rand() / RAND_MAX * max_num : rand() % max_num + 1;
	string op = ops[rand() % ops.size()];
	if (allow_parenthesis && rand() % 2 == 0) {
		if (allow_decimal)
			return "(" + to_string(n1) + " " + op + " " + to_string(n2) + ")";
		else return "(" + to_string(int(n1)) + " " + op + " " + to_string(int(n2)) + ")";
	}
	else {
		float res = 0;
		if (op == "+") {
			res = n1 + n2;
		}
		else if (op == "-") {
			res = n1 - n2;
		}
		else if (op == "*") {
			res = n1 * n2;
		}
		else if (op == "/") {
			res = n1 / n2;
		}
		return allow_decimal ? to_string(res) : to_string((int)res);
	}
}

// �������
void test(int num, int max_num, string operators, bool allow_parenthesis, bool allow_decimal, string print_type) {
	vector<string> expressions;
	vector<string> results;
	for (int i = 0; i < num; ++i) {
		string infix = "";
		int n_ops = rand() % 2 + 1;
		for (int j = 0; j < n_ops + 1; ++j) {
			infix += szys(max_num, operators, allow_parenthesis, allow_decimal);
			if (j < n_ops) {
				infix += " " + string(1, operators[rand() % operators.size()]) + " ";
			}
		}
		expressions.push_back(infix);
		results.push_back(to_string(evaluate(infix)));
	}
	if (print_type == "console") {
		cleardevice();  // �����Ļ
		char s[10];
		for (int i = 0; i < num; ++i) {
			InputBox(s, 10, expressions[i].c_str(), "����������ϰ����", "=");
			string result_s(s);
			if (fabs(atof(result_s.c_str()) - atof(results[i].c_str())) < 1e-6) {
				outtextxy(140, 80, "�����ȷ");
 				_getch(); cleardevice();
			}
			else {
				outtextxy(140, 80, "�������");
				_getch(); cleardevice();
			}
		}
		outtextxy(140, 80, "����");
		_getch();  // �ȴ��û����������
		closegraph();  // �ر�ͼ�ν���
	}
	else if (print_type == "file") {
		string filename = "test.txt";
		ofstream f(filename);
		for (int i = 0; i < num; ++i) {
			f << i + 1 << ". " << expressions[i] << " = " << endl;
		}
	}
}

int main() {
	srand((unsigned int)time(NULL));
	cout << fixed << setprecision(2);
	int num, max_num;
	string operators, print_type;
	bool allow_parenthesis, allow_decimal;

	initgraph(360, 200);  // ��ʼ��ͼ�ν���

	setbkcolor(WHITE);  // ���ñ�����ɫΪ��ɫ
	settextcolor(BLACK);  // �����ı���ɫΪ��ɫ
	cleardevice();  // �����Ļ

	char s[10];
	while (true) {
		InputBox(s, 10, "��������Ŀ����", "����������ϰ����");
		if (num = atoi(s)) {
			break;
		}
		outtextxy(120, 60, "�Ƿ�����������");
		_getch(); cleardevice();
	}

	while (true) {
		InputBox(s, 10, "�����������", "����������ϰ����");
		if (max_num = atoi(s)) {
			break;
		}
		outtextxy(120, 60, "�Ƿ�����������");
		_getch(); cleardevice();
	}
	string legal_ops = "+-*/";
	while (true) {
		InputBox(s, 10, "�����������", "����������ϰ����");
		operators = s;
		bool is_legal = true;
		for (char op : operators) {
			if (legal_ops.find(op) == string::npos) {
				is_legal = false;
				break;
			}
		}
		if (is_legal) break;
		outtextxy(120, 60, "�Ƿ�����������");
		_getch(); cleardevice();
	}
	while (true) {
		InputBox(s, 10, "�Ƿ��������ţ�(Y/N)", "����������ϰ����");
		if (s[1]) {
			continue;
		}
		char key = s[0];
		if (key == 'y' || key == 'Y') {
			allow_parenthesis = true;
			break;
		}
		else if (key == 'n' || key == 'N') {
			allow_parenthesis = false;
			break;
		}
		outtextxy(120, 60, "�Ƿ�����������");
		_getch(); cleardevice();
	}
	while (true) {
		InputBox(s, 10, "�Ƿ�����С����(Y/N)", "����������ϰ����");
		if (s[1]) {
			continue;
		}
		char key = s[0];
		if (key == 'y' || key == 'Y') {
			allow_decimal = true;
			break;
		}
		else if (key == 'n' || key == 'N') {
			allow_decimal = false;
			break;
		}
		
		outtextxy(120, 60, "�Ƿ�����������");
		_getch(); cleardevice();
	}
	while (true) {
		InputBox(s, 10, "��ѡ�������ʽ(console|file)", "����������ϰ����");
		print_type = s;
		if (print_type == "console") {
			break;
		}
		else if (print_type == "file") {
			break;
		}
		outtextxy(120, 60, "�Ƿ�����������");
		_getch(); cleardevice();

	}
	test(num, max_num, operators, allow_parenthesis, allow_decimal, print_type);
	return 0;
}
