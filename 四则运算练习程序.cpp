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
	stack<double> nums;   // 存放数字的栈
	stack<char> ops;   // 存放运算符的栈
	int n = s.size();
	for (int i = 0; i < n; i++) {
		char c = s[i];
		if (isdigit(c) || c == '.') {   // 如果是数字或小数点则将其压入数字栈中
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
		else if (c == '(') {   // 如果是左括号则将其压入运算符栈中
			ops.push(c);
		}
		else if (c == ')') {   // 如果是右括号则从运算符栈中取出一个运算符和两个数字，进行运算并将结果压入数字栈中
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
			ops.pop();   // 弹出左括号
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (!ops.empty() && (ops.top() == '*' || ops.top() == '/') && i > 0 && s[i - 1] != '(') {
				// 如果当前运算符优先级小于等于栈顶运算符，则取出栈顶运算符和两个数字进行运算并将结果压入数字栈中，直到当前运算符大于栈顶运算符为止
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
	while (!ops.empty()) {   // 依次取出栈中运算符和两个数字进行运算并将结果压入数字栈中
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
	return nums.top();   // 数字栈中唯一的元素即为计算结果
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

// 制作题库
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
		cleardevice();  // 清空屏幕
		char s[10];
		for (int i = 0; i < num; ++i) {
			InputBox(s, 10, expressions[i].c_str(), "四则运算练习程序", "=");
			string result_s(s);
			if (fabs(atof(result_s.c_str()) - atof(results[i].c_str())) < 1e-6) {
				outtextxy(140, 80, "结果正确");
 				_getch(); cleardevice();
			}
			else {
				outtextxy(140, 80, "结果错误");
				_getch(); cleardevice();
			}
		}
		outtextxy(140, 80, "结束");
		_getch();  // 等待用户按下任意键
		closegraph();  // 关闭图形界面
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

	initgraph(360, 200);  // 初始化图形界面

	setbkcolor(WHITE);  // 设置背景颜色为白色
	settextcolor(BLACK);  // 设置文本颜色为黑色
	cleardevice();  // 清空屏幕

	char s[10];
	while (true) {
		InputBox(s, 10, "请输入题目数量", "四则运算练习程序");
		if (num = atoi(s)) {
			break;
		}
		outtextxy(120, 60, "非法输入请重试");
		_getch(); cleardevice();
	}

	while (true) {
		InputBox(s, 10, "请输入最大数", "四则运算练习程序");
		if (max_num = atoi(s)) {
			break;
		}
		outtextxy(120, 60, "非法输入请重试");
		_getch(); cleardevice();
	}
	string legal_ops = "+-*/";
	while (true) {
		InputBox(s, 10, "请输入运算符", "四则运算练习程序");
		operators = s;
		bool is_legal = true;
		for (char op : operators) {
			if (legal_ops.find(op) == string::npos) {
				is_legal = false;
				break;
			}
		}
		if (is_legal) break;
		outtextxy(120, 60, "非法输入请重试");
		_getch(); cleardevice();
	}
	while (true) {
		InputBox(s, 10, "是否允许括号？(Y/N)", "四则运算练习程序");
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
		outtextxy(120, 60, "非法输入请重试");
		_getch(); cleardevice();
	}
	while (true) {
		InputBox(s, 10, "是否允许小数？(Y/N)", "四则运算练习程序");
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
		
		outtextxy(120, 60, "非法输入请重试");
		_getch(); cleardevice();
	}
	while (true) {
		InputBox(s, 10, "请选择输出方式(console|file)", "四则运算练习程序");
		print_type = s;
		if (print_type == "console") {
			break;
		}
		else if (print_type == "file") {
			break;
		}
		outtextxy(120, 60, "非法输入请重试");
		_getch(); cleardevice();

	}
	test(num, max_num, operators, allow_parenthesis, allow_decimal, print_type);
	return 0;
}
