#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include <windows.h>
#include<mmsystem.h>
#include <graphics.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

int Data[10][10] = { 0 };
int Size, side = -1;
int T = 0;
IMAGE img, img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048, imgl, imgw;

//���ϲ���
void Up() {
	int tmp = 0;
	for (int i = 1; i <= Size; i++) {
		//���������������ƶ����ǿ�����
		for (int j = 2; j <= Size; j++) {
			if (Data[i][j] != 0) {
				tmp = j;
				while (Data[i][--tmp] == 0);
				tmp++;
				if (tmp == 1 || tmp != j) {
					Data[i][tmp] = Data[i][j];
					Data[i][j] = 0;
					T = 1;
				}
			}
		}
		//�ϲ�
		for (int j = 1; j <= Size; j++) {
			if (Data[i][j] == Data[i][j + 1] && Data[i][j] != 0) {
				Data[i][j] *= 2;
				Data[i][j + 1] = 0;
				j++;
				T = 1;
			}
		}
		//�ٴθ��ǿ�����
		for (int j = 2; j <= Size; j++) {
			if (Data[i][j] != 0) {
				tmp = j;
				while (Data[i][--tmp] == 0);
				tmp++;
				if (tmp == 1 || tmp != j) {
					Data[i][tmp] = Data[i][j];
					Data[i][j] = 0;
				}
			}
		}
	}
}

//���²���
void Down() {
	int tmp = 0;
	for (int i = Size; i > 0; i--) {
		//���������������ƶ����ǿ�����
		for (int j = Size - 1; j > 0; j--) {
			if (Data[i][j] != 0) {
				tmp = j;
				while (Data[i][++tmp] == 0);
				tmp--;
				if (tmp == Size || tmp != j) {
					Data[i][tmp] = Data[i][j];
					Data[i][j] = 0;
					T = 1;
				}
			}
		}
		//�ϲ�
		for (int j = Size; j > 0; j--) {
			if (Data[i][j] == Data[i][j - 1] && Data[i][j] != 0) {
				Data[i][j] *= 2;
				Data[i][j - 1] = 0;
				j--;
				T = 1;
			}
		}
		//�ٴθ��ǿ�����
		for (int j = Size - 1; j > 0; j--) {
			if (Data[i][j] != 0) {
				tmp = j;
				while (Data[i][++tmp] == 0);
				tmp--;
				if (tmp == Size || tmp != j) {
					Data[i][tmp] = Data[i][j];
					Data[i][j] = 0;
				}
			}
		}
	}
}

//�������
void Left() {
	int tmp = 0;
	for (int j = 1; j <= Size; j++) {
		//���������������ƶ����ǿ�����
		for (int i = 2; i <= Size; i++) {
			if (Data[i][j] != 0) {
				tmp = i;
				while (Data[--tmp][j] == 0);
				tmp++;
				if (tmp == 1 || tmp != i) {
					Data[tmp][j] = Data[i][j];
					Data[i][j] = 0;
					T = 1;
				}
			}
		}
		//�ϲ�
		for (int i = 1; i <= Size; i++) {
			if (Data[i][j] == Data[i + 1][j] && Data[i][j] != 0) {
				Data[i][j] *= 2;
				Data[i + 1][j] = 0;
				i++;
				T = 1;
			}
		}
		//�ٴθ��ǿ�����
		for (int i = 2; i <= Size; i++) {
			if (Data[i][j] != 0) {
				tmp = i;
				while (Data[--tmp][j] == 0);
				tmp++;
				if (tmp == 1 || tmp != i) {
					Data[tmp][j] = Data[i][j];
					Data[i][j] = 0;
				}
			}
		}
	}
}

//���Ҳ���
void Right() {
	int tmp = 0;
	for (int j = 1; j <= Size; j++) {
		//���������������ƶ����ǿ�����
		for (int i = Size - 1; i > 0; i--) {
			if (Data[i][j] != 0) {
				tmp = i;
				while (Data[++tmp][j] == 0);
				tmp--;
				if (tmp == Size || tmp != i) {
					Data[tmp][j] = Data[i][j];
					Data[i][j] = 0;
					T = 1;
				}
			}
		}
		//�ϲ�
		for (int i = Size; i > 0; i--) {
			if (Data[i][j] == Data[i - 1][j] && Data[i][j] != 0) {
				Data[i][j] *= 2;
				Data[i - 1][j] = 0;
				i--;
				T = 1;
			}
		}
		//�ٴθ��ǿ�����
		for (int i = Size - 1; i > 0; i--) {
			if (Data[i][j] != 0) {
				tmp = i;
				while (Data[++tmp][j] == 0);
				tmp--;
				if (tmp == Size || tmp != i) {
					Data[tmp][j] = Data[i][j];
					Data[i][j] = 0;
				}
			}
		}
	}
}

//�����Ϸ״̬
void Print() {
	setlinecolor(WHITE);

	for (int i = 1; i <= Size; i++) {
		for (int j = 1; j <= Size; j++) {
			switch (Data[i][j])
			{
			case 0: img = img0; break;
			case 2: img = img2; break;
			case 4: img = img4; break;
			case 8: img = img8; break;
			case 16: img = img16; break;
			case 32: img = img32; break;
			case 64: img = img64; break;
			case 128: img = img128; break;
			case 256: img = img256; break;
			case 512: img = img512; break;
			case 1024: img = img1024; break;
			case 2048: img = img2048; break;
			}
			putimage((400 - Size * 30) + (i - 1) * 60, (300 - Size * 30) + (j - 1) * 60, &img);
			line((400 - Size * 30) + (i - 1) * 60, (300 - Size * 30) + (j - 1) * 60, (400 - Size * 30) + i * 60, (300 - Size * 30) + (j - 1) * 60);
			line((400 - Size * 30) + (i - 1) * 60, (300 - Size * 30) + (j - 1) * 60, (400 - Size * 30) + (i - 1) * 60, (300 - Size * 30) + j * 60);
		}
	}
	line((400 + Size * 30), (300 - Size * 30), (400 + Size * 30), (300 + Size * 30));
	line((400 - Size * 30), (300 + Size * 30), (400 + Size * 30), (300 + Size * 30));
}

//��¼�����ݵĸ����Ա�����������2��4
int EmptyData() {
	int sum = 0;
	for (int i = 1; i <= Size; i++) {
		for (int j = 1; j <= Size; j++) {
			if (Data[i][j] == 0) {
				sum++;
			}
		}
	}
	return sum;
}

//����2��4���������еĿ�����
void SetNUM() {
	int s = 1, randnum1 = 0, randnum2 = 0;
	srand((int)time(0));
	//���ѡȡһ������2��4�Ŀ�����
	if (EmptyData() != 0)
		randnum1 = rand() % EmptyData() + 1;
	//����2�ĸ�����90%������4�ĸ�����10%
	randnum2 = rand() % 10 + 1;
	for (int i = 1; i <= Size; i++) {
		for (int j = 1; j <= Size; j++) {
			if (Data[i][j] == 0) {
				if (s++ == randnum1) {
					if (randnum2 < 2)Data[i][j] = 4;
					else Data[i][j] = 2;
				}
			}
		}
	}
}

//�ж���Ϸ��Ӯ
int isGameWin()
{
	for (int i = 1; i <= Size; ++i)
	{
		for (int j = 1; j <= Size; ++j)
		{
			//����һ��Ϊ2048����Ϸʤ��
			if (Data[i][j] == 2048)return 1;
		}
	}
	return 0;
}
int isGameLose() {
	if (EmptyData() == 0) {
		for (int i = 1; i <= Size; ++i)
		{
			for (int j = 1; j <= Size; ++j)
			{
				//��������������ȣ���Ϸ����
				if (Data[i][j] == Data[i + 1][j])return 0;
				if (Data[i][j] == Data[i][j + 1])return 0;
			}
		}
		return 1;
	}
	return 0;
}

//����ͼƬ
void LoadImg()
{
	loadimage(&img0, L"./picture/0.jpg", 60, 60);
	loadimage(&img2, L"./picture/2.jpg", 60, 60);
	loadimage(&img4, L"./picture/4.jpg", 60, 60);
	loadimage(&img8, L"./picture/8.jpg", 60, 60);
	loadimage(&img16, L"./picture/16.jpg", 60, 60);
	loadimage(&img32, L"./picture/32.jpg", 60, 60);
	loadimage(&img64, L"./picture/64.jpg", 60, 60);
	loadimage(&img128, L"./picture/128.jpg", 60, 60);
	loadimage(&img256, L"./picture/256.jpg", 60, 60);
	loadimage(&img512, L"./picture/512.jpg", 60, 60);
	loadimage(&img1024, L"./picture/1024.jpg", 60, 60);
	loadimage(&img2048, L"./picture/2048.jpg", 60, 60);
	loadimage(&imgl, L"./picture/lose.jpg", 400, 600);
	loadimage(&imgw, L"./picture/win.jpg", 400, 600);
}

void Begin()
{
	COLORREF BKC = RGB(146, 223, 237);
	LoadImg();
	initgraph(800, 600);
	setbkcolor(BKC);//�趨������ɫ
	cleardevice();
	settextcolor(BLACK);
	mciSendString(L"open ./music/One-Last-Kiss(Instrumental).mp3 alias BGM", NULL, 0, NULL);//aliasȡ����
	mciSendString(L"play BGM repeat", NULL, 0, NULL);
	settextstyle(50, 0, L"����");
	outtextxy(0, 0, L"��Ϸ����");
	outtextxy(230, 300, L"�����������");
	settextstyle(30, 0, L"����");
	outtextxy(0, 100, L"ʹ���������һ���WASD(wasd)���в�������ͬ���ֿ��Ժϲ�,");
	outtextxy(0, 140, L"���Ϻϲ�ֱ������2048��Ϊʤ������Ч��������Ӱ����Ϸ");
	_getch();
	cleardevice();
	outtextxy(140, 120, L"��������Ϸ�����С(����2������9):");
	char Sz = _getch();
	outtextxy(370, 160, Sz);
	while (Sz - '0' < 2 || Sz - '0' > 8) {
		outtextxy(120, 120, L"��ֵ���Ϸ�o(*�����*)o��������һ�ΰ�:");
		Sz = _getch();
		outtextxy(370, 160, Sz);
	}
	Sleep(500);
	cleardevice();
	Size = Sz - '0';
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if ((i<1 || i>Size) || (j<1 || j>Size)) {
				Data[i][j] = side;
			}
		}
	}
}

int input() {//������������ָ�������Ϸ 
	//�Լ�����������ʶ�� 
	int tmp;
	tmp = _getch();
	if (tmp == 0xE0) {
		switch (_getch()) {
		case 72: return 87; break;//�� 
		case 80: return 83; break;//�� 
		case 75: return 65; break;//�� 
		case 77: return 68; break;//��
		default: {
			outtextxy(120, 530, L"Υ������(����(OO)��)����������һ�ΰ�:");
			return input();
		}
		}
	}
	else if (tmp == 87 || tmp == 83 || tmp == 65 || tmp == 68) {
		return tmp;
	}
	else if (tmp == 119 || tmp == 115 || tmp == 97 || tmp == 100) {
		return tmp - 32;
	}
	else {
		outtextxy(120, 530, L"Υ������(����(OO)��)����������һ�ΰ�:");
		return input();
	}
}

int main()
{
	int ans = 0;
	Begin();
	SetNUM();
	SetNUM();
	Print();
	while (1) {
		switch (input())
		{
		case 87: Up(); break;
		case 83: Down(); break;
		case 65: Left(); break;
		case 68: Right(); break;
		};
		if (T != 1) {
			outtextxy(220, 530, L"��Ч����(�������)������");
			continue;
		}
		cleardevice();
		Print();
		if (isGameWin()) {
			Sleep(2000);
			cleardevice();
			closegraph();//�رջ�ͼ����
			initgraph(400, 600);
			putimage(0, 0, &imgw);
			_getch();
			return 0;
		}
		Sleep(200);
		SetNUM();
		cleardevice();
		Print();
		T = 0;
		if (isGameLose()) {
			Sleep(2000);
			cleardevice();
			closegraph();//�رջ�ͼ����
			initgraph(400, 600);
			putimage(0, 0, &imgl);
			_getch();
			return 0;
		}
	}
}