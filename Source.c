 

#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100
struct Date{
	int ngay;
	int thang;
	int nam;
};
struct MatHang {
	char MaMH[10];
	char Loai[16];
	char TenMH[22];
	int GiaMua, GiaBan, SL;
};
struct NhapHang {
	char MaNH[10];
	char MaMH[10];
	char NguoiNhap[25];
	char NguonNhap[16];
	struct Date NgayNhap;
	int SLN;
	int ThanhTien;
};
struct XuatHang {
	char MaXH[10];
	char MaMH[10];
	char NguoiBan[21];
	char KhachHang[21];
	struct Date NgayXuat;
	int SLX;
	int ThanhTien;
};

typedef struct MatHang MATHANG;
typedef struct NhapHang NHAPHANG;
typedef struct XuatHang XUATHANG;


int a = -1, b = -1, c = -1;

MATHANG MH[MAX];
NHAPHANG NH[MAX];
XUATHANG XH[MAX];

/*-----------------------Khoi Tao Ham------------------------*/
int TimTenMH(MATHANG MH[], int n, char s[]);
int TimMaMH(MATHANG MH[], int n, char s[]);	//TIM MA SO MAT HANG
int TimMaNH(NHAPHANG NH[], int n, char s[]);	//TIM MA SO NHAP HANG
int TimMaXH(XUATHANG XH[], int n, char s[]);
void addMatHang(MATHANG MH[], int *a);
void editMatHang(MATHANG MH[], int a, int vitri);
void delMatHang(MATHANG MH[], int *a, int vitri);
void addNhapHang(MATHANG MH[], NHAPHANG NH[], int a, int *b);
void editNhapHang(MATHANG MH[], NHAPHANG NH[], int a, int b, int vitri);
void delNhapHang(NHAPHANG NH[], int *n, int vitri);
void addXuatHang(MATHANG MH[], XUATHANG XH[], int a, int *c);
void editXuatHang(MATHANG MH[], XUATHANG XH[], int a, int c, int vitri);
void delXuatHang(XUATHANG XH[], int *n, int vitri);
void gotoxy(int x, int y);
void drawFooter();
void drawMenu();
void R_DATA(MATHANG MH[], NHAPHANG NH[], XUATHANG XH[], int *a, int *b, int *c);
void W_DATA(MATHANG MH[], NHAPHANG NH[], XUATHANG XH[], int a, int b, int c);
void setBGColor(WORD color);
void drawTable(int height, int cot, int dong, int array[], int pos);
/*---------------------------End Khoi Tao Ham-----------------------------*/

// Ham xoa man hinh
void xoamanhinh(){
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0, 0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);

}
// Ham an hien con tro
void ShowCur(int CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
// Ham set mau mac dinh cho nen
void setBGDefault(){
	int x, y;
	setBGColor(0);
	for (y = 0; y < 30; y++)
	for (x = 0; x < 120; x++){
		gotoxy(x, y); printf(" ");
	}
}
// Ham xoa man hinh chung
void clrscr()
{
	ShowCur(0);
	xoamanhinh();

	drawFooter();
	gotoxy(0, 0);
}
// Hamxoa chuoi
void delString(int x, int y, int dodai){
	int i = 0;
	gotoxy(x, y);
	for (i = 0; i < dodai; i++){
		printf(" ");
	}
}
// Ham bat toa do
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
		);
}
//Ham set mau van ban
void setColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}
//Ham set mau nen
void setBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//Ham delay
void delay(int x){
	int i = 0, j = 0;
	for (i = 0; i < x; i++){
		for (j = 0; j < 200000; j++){
		}
	}
}
//Bat khi thoat
void Thoat(){
	drawMenu();
}
// Dem do dai chuoi nguyen
int Length(int array[]){
	int i = 0;
	while (array[i] != 0){
		i++;
	}
	return i;
}
// Can giua khung
void setCenter(int *n, int array[]){
	int i;
	*n = 0;
	for (i = 0; i < Length(array); i++){
		*n += array[i];
	}
	*n = (120 - *n) / 2;
}
// Xoa Khoang trang dau cuoi
char* CH_Trim(char s[]) {
	int i = 0;
	while (s[i]) i++;
	while (s[i - 1] == 32) i--;
	s[i] = 0;
	while (*s == 32) s++;
	return s;
}
/*
* Chuan hoa chuoi xoa khoang trang
* Viet in hoa ki tu dau
*/
void setString(char *s) {
	s = _strlwr(s);
	int i, j, n = strlen(s);
	strcpy(s, CH_Trim(s));
	for (i = 0; i <= n; i++) {
		// Neu la ki tu dau thi chuyen thanh chu In Hoa
		if (i == 0) {
			s[0] = toupper(s[0]);
		}
		//printf("%d: %s\n", i, s);
		if (s[i] == ' ') {
			// Neu co khoang trang thi xoa
			if (s[i + 1] == ' ') {
				for (j = i + 1; j < n; j++) {
					s[j] = s[j + 1];
				}
				s[n] = 0;
				n--;
				i--;
				// Khong phai khoang trang thi chuyen thanh in hoa
			}
			else {
				s[i + 1] = toupper(s[i + 1]);
			}
		}
	}

	//return *s;
}
// Kiem tra dinh dang ngay
int isDate(int ngay, int thang, int nam) {
	int max;
	if (thang <= 0 || thang > 12){
		return 0;
	}
	switch (thang){
	case 2:
		if (nam % 400 == 0 || nam % 4 == 0 && nam % 100 != 0){
			max = 29;
		}
		else{
			max = 28;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		max = 30;
		break;
	default:
		max = 31;
		break;
	}
	if (ngay > max){
		return 0;
	}
	if (1950 > nam || nam > 2050){
		return 0;
	}
	return 1;
}
//Ham set van ban
void setVB(int x, int y, int dodai, char chuoi[]){
	int i = 0;
	int key;
	gotoxy(x, y);
	for (i = 0; i < dodai; i++){
		printf(" ");
	}
	gotoxy(x, y);
	i = 0;
	setColor(25);
	do{
		key = _getch();
		if (key == 13){
			chuoi[i] = '\0';
			gotoxy(x, y); setColor(15);
			for (i = 0; i < dodai; i++){
				printf(" ");
			}
			gotoxy(x, y); printf("%s", chuoi);
			break;
		}
		else if (key == 8){
			if (i == 0){
				gotoxy(x, y);
			}
			else{
				chuoi[i - 1] = '\0';
				gotoxy(x + i - 1, y); printf(" ");
				gotoxy(x + i - 1, y);
				i--;
			}
		}
		else if (key == 27){
			Thoat();
		}
		else if (i == dodai){
			continue;
		}
		else {
			chuoi[i] = key;
			printf("%c", key);
			chuoi[++i] = '\0';
		}
	} while (1);
}
// Thiet lap nhap ki tu chuoi
void setText(int x, int y, int dodai, char chuoi[]){
	int i = 0;
	int key;
	delString(x, y, dodai);
	gotoxy(x, y);
	i = 0;
	setColor(25);
	do{
		key = _getch();
		if (key == 13){
			chuoi[i] = '\0';
			setString(chuoi);
			delString(x, y, dodai);
			gotoxy(x, y); setColor(15); printf("%s", chuoi);
			delString(10, 27, 50);
			break;
		}
		else if (key == 8){
			if (i == 0){
				gotoxy(x, y);
			}
			else{
				chuoi[i - 1] = '\0';
				gotoxy(x + i - 1, y); printf(" ");
				gotoxy(x + i - 1, y);
				i--;
			}
		}
		else if (key == 27){
			Thoat();
		}
		else if (i == dodai){
			continue;
		}
		else {
			chuoi[i] = key;
			printf("%c", key);
			chuoi[++i] = '\0';
		}
	} while (1);
}
// Thiet lap chi cho nhap so
void setNumber(int x, int y, int dodai, int *number){
	int i = 0;
	int key;
	char chuoi[30];
	delString(x, y, dodai);
	gotoxy(x, y);
	i = 0;
	setColor(25);
	do{
		key = _getch();
		if (key == 13){
			if (i == 0){
				*number = 0; setColor(15);
				printf("%c", '0');

			}
			else{
				chuoi[i] = '\0';
				*number = atoi(chuoi);
				delString(x, y, dodai);
				delString(10, 27, 50);
				gotoxy(x, y); setColor(15); printf("%d", *number);
			}
			break;
		}
		else if (key == 8){
			if (i == 0){
				gotoxy(x, y);
			}
			else{
				chuoi[i - 1] = '\0';
				gotoxy(x + i - 1, y); printf(" ");
				gotoxy(x + i - 1, y);
				i--;
			}
		}
		else if (key == 27){
			Thoat();
		}
		else if (i == dodai){
			continue;
		}
		else if (48 <= key&&key <= 57){
			chuoi[i] = key;
			printf("%c", key);
			chuoi[++i] = '\0';
		}
		else {
			continue;
		}
	} while (1);
}
// Thiet lap nhap ma 2 chu 3 so
void setCode(int x, int y, char *chuoi){
	int i = 0;
	int key;
	int dodai = 5;
	delString(x, y, dodai);
	gotoxy(x, y);
	i = 0;
	setColor(25);
	do{
		key = _getch();
		if (key == 13){
			chuoi[i] = '\0';
			delString(x, y, dodai);
			delString(10, 27, 50);
			gotoxy(x, y); setColor(15); printf("%s", chuoi);
			break;
		}
		else if (key == 8){
			if (i == 0){
				gotoxy(x, y);
			}
			else{
				chuoi[i - 1] = '\0';
				gotoxy(x + i - 1, y); printf(" ");
				gotoxy(x + i - 1, y);
				i--;
			}
		}
		else if (key == 27){
			Thoat();
		}
		else if (i == dodai){
			continue;
		}
		else if (i < 2 && ((65 <= key&&key <= 90) || (97 <= key&&key <= 122))){
			chuoi[i] = toupper(key);
			printf("%c", chuoi[i]);
			chuoi[++i] = '\0';
		}
		else if ((2 <= i&&i < 5) && 48 <= key&&key <= 57){
			chuoi[i] = key;
			printf("%c", chuoi[i]);
			chuoi[++i] = '\0';
		}
		else {
			continue;
		}
	} while (1);
}

/* NHAP MAT HANG
* Hien thi so mat hang trang cuoi
* Chuan hoa nhap - Bat loi
* Nhap day tu chuyen trang
* Ghi du lieu vao file text
*/
void addMatHang(MATHANG MH[], int *a) {
	int y = 5, i = 0, dem = 0;
	int array[] = { 10, 23, 18, 12, 12, 0 }, x = 0;
	setCenter(&x, array);
	MATHANG Temp;
	int limit = 6;
	int page = (*a + 1) / limit + 1;
	int length = page*limit;
	clrscr();
	// Hien thi du lieu trang cuoi 
	for (i = (page - 1)*limit; i < length; i++){
		if (i < *a + 1){
			gotoxy(x + 2, y + 3 + i%limit * 2); printf(MH[i].MaMH);
			gotoxy(x + 2 + 10, y + 3 + i%limit * 2); printf(MH[i].TenMH);
			gotoxy(x + 2 + 33, y + 3 + i%limit * 2); printf(MH[i].Loai);
			gotoxy(x + 2 + 51, y + 3 + i%limit * 2);
			printf("%d", MH[i].GiaMua);
			gotoxy(x + 2 + 63, y + 3 + i%limit * 2);
			printf("%d", MH[i].GiaBan);
			dem++;
		}

	}
	while (1){
		// Day trang thi xoa di
		if (dem == 6){
			dem = 0;
			page++;
			clrscr();
		}

		ShowCur(1);
		// Khung nhap va xu ly nhap
		drawTable(7, x, y, array, 1); setColor(28);
		gotoxy(x + 1, y + 3 + 6 * 2); printf("                                               ");
		gotoxy(x + 1, y + 4 + 6 * 2); printf("                                               ");
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("TEN MAT HANG");
		gotoxy(x + 2 + 33, y + 1); printf("LOAI");
		gotoxy(x + 2 + 51, y + 1); printf("GIA MUA");
		gotoxy(x + 2 + 63, y + 1); printf("GIA BAN"); setColor(15);

		gotoxy(x + 1, 20);
		printf("%c %d %c   Tong Trang: %d", 174, page, 175, page);


		do{
			setCode(x + 2, y + 3 + dem%limit * 2, Temp.MaMH);
			if (strlen(Temp.MaMH) != 5 || TimMaMH(MH, *a, Temp.MaMH) != -1 || TimMaNH(NH, b, Temp.MaMH) != -1 || TimMaXH(XH, c, Temp.MaMH) != -1){
				gotoxy(10, 27); printf("Ma MH da ton tai");
			}

		} while (strlen(Temp.MaMH) != 5 || TimMaMH(MH, *a, Temp.MaMH) != -1 || TimMaNH(NH, b, Temp.MaMH) != -1 || TimMaXH(XH, c, Temp.MaMH) != -1);

		do{
			setText(x + 2 + 10, y + 3 + dem%limit * 2, 20, Temp.TenMH);
			if (strlen(Temp.TenMH) == 0){
				gotoxy(10, 27); printf("Khong duoc de trong.");
			}
		} while (strlen(Temp.TenMH) == 0);

		do{
			setText(x + 2 + 33, y + 3 + dem%limit * 2, 15, Temp.Loai);
			if (strlen(Temp.Loai) == 0){
				gotoxy(10, 27); printf("Khong duoc de trong");
			}
		} while (strlen(Temp.Loai) == 0);

		setNumber(x + 2 + 51, y + 3 + dem%limit * 2, 9, &Temp.GiaMua);
		do{
			setNumber(x + 2 + 63, y + 3 + dem%limit * 2, 9, &Temp.GiaBan);
			if (Temp.GiaMua > Temp.GiaBan){
				gotoxy(10, 27); printf("Gia ban phai lon hon gia mua");
			}
		} while (Temp.GiaMua > Temp.GiaBan);

		Temp.SL = 0;
		MH[++(*a)] = Temp;
		W_DATA(MH, NH, XH, *a, b, c);
		dem++;
	};
}
// NHAP MAT HANG
void addNhapHang(MATHANG MH[], NHAPHANG NH[], int a, int *b) {
	int  y = 5, i = 0, dem = 0;
	int array[] = { 10, 10, 23, 18, 13, 15, 12, 0 }, x = 0;
	setCenter(&x, array);
	NHAPHANG Temp;
	int limit = 6;
	int page = (*b + 1) / limit + 1;
	int length = page*limit;
	clrscr();
	//Hien thi du lieu trang cuoi
	for (i = (page - 1)*limit; i < length; i++){
		if (i < *b + 1){
			gotoxy(x + 2, y + 3 + i%limit * 2); printf(NH[i].MaMH);
			gotoxy(x + 2 + 10, y + 3 + i%limit * 2); printf(NH[i].MaNH);
			gotoxy(x + 2 + 20, y + 3 + i%limit * 2); printf(NH[i].NguoiNhap);
			gotoxy(x + 2 + 43, y + 3 + i%limit * 2); printf(NH[i].NguonNhap);
			gotoxy(x + 2 + 61, y + 3 + i%limit * 2);
			printf("%d", NH[i].NgayNhap.ngay);
			gotoxy(x + 2 + 63, y + 3 + i%limit * 2); printf("/");
			gotoxy(x + 2 + 64, y + 3 + i%limit * 2);
			printf("%d", NH[i].NgayNhap.thang);
			gotoxy(x + 2 + 66, y + 3 + i%limit * 2); printf("/");
			gotoxy(x + 2 + 67, y + 3 + i%limit * 2);
			printf("%d", NH[i].NgayNhap.nam);
			gotoxy(x + 2 + 74, y + 3 + i%limit * 2);
			printf("%d", NH[i].SLN);
			gotoxy(x + 2 + 89, y + 3 + i%limit * 2);
			printf("%d", NH[i].ThanhTien);
			dem++;
		}
	}
	while (1){
		if (dem == 6){
			dem = 0;
			page++;
			clrscr();
		}
		ShowCur(1);
		//Khung nhap va xu ly du lieu nhap
		drawTable(7, x, y, array, 1); setColor(28);
		gotoxy(x + 1, y + 3 + 6 * 2); printf("                                               ");
		gotoxy(x + 1, y + 4 + 6 * 2); printf("                                               ");
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("MA NH");
		gotoxy(x + 2 + 20, y + 1); printf("NGUOI NHAP");
		gotoxy(x + 2 + 43, y + 1); printf("NGUON NHAP");
		gotoxy(x + 2 + 61, y + 1); printf("NGAY NHAP");
		gotoxy(x + 2 + 74, y + 1); printf("SL NHAP");
		gotoxy(x + 2 + 89, y + 1); printf("THANH TIEN"); setColor(15);


		gotoxy(x + 1, 20);
		printf("%c %d %c   Tong Trang: %d", 174, page, 175, page);


		do{
			setCode(x + 2, y + 3 + dem%limit * 2, Temp.MaMH);

			if (TimMaMH(MH, a, Temp.MaMH) == -1){
				gotoxy(10, 27); printf("Ma khong ton tai");
			}
			if (strlen(Temp.MaMH) != 5){
				gotoxy(10, 27); printf("Phai nhap 5 ki tu");
			}
		} while (strlen(Temp.MaMH) != 5 || TimMaMH(MH, a, Temp.MaMH) == -1);
		do{
			setCode(x + 2 + 10, y + 3 + dem%limit * 2, Temp.MaNH);
			if (TimMaMH(MH, a, Temp.MaNH) != -1 || TimMaNH(NH, *b, Temp.MaNH) != -1 || TimMaXH(XH, c, Temp.MaNH) != -1){
				gotoxy(10, 27); printf("Ma da ton tai");
			}
			if (strlen(Temp.MaNH) != 5){
				gotoxy(10, 27); printf("Phai nhap 5 ki tu");
			}
		} while (strlen(Temp.MaNH) != 5 || TimMaMH(MH, a, Temp.MaNH) != -1 || TimMaNH(NH, *b, Temp.MaNH) != -1 || TimMaXH(XH, c, Temp.MaNH) != -1);
		do{
			setText(x + 2 + 20, y + 3 + dem%limit * 2, 20, Temp.NguoiNhap);

			if (strlen(Temp.NguoiNhap) == 0){
				gotoxy(10, 27); printf("Khong duoc de trong");
			}
		} while (strlen(Temp.NguoiNhap) == 0);
		do{
			setText(x + 2 + 43, y + 3 + dem%limit * 2, 15, Temp.NguonNhap);

			if (strlen(Temp.NguonNhap) == 0){
				gotoxy(10, 27); printf("Khong duoc de trong");
			}
		} while (strlen(Temp.NguonNhap) == 0);
		do{
			gotoxy(x + 2 + 63, y + 3 + dem%limit * 2); printf("/");
			gotoxy(x + 2 + 66, y + 3 + dem%limit * 2); printf("/");
			setNumber(x + 2 + 61, y + 3 + dem%limit * 2, 2, &Temp.NgayNhap.ngay);
			setNumber(x + 2 + 64, y + 3 + dem%limit * 2, 2, &Temp.NgayNhap.thang);
			setNumber(x + 2 + 67, y + 3 + dem%limit * 2, 4, &Temp.NgayNhap.nam);
			if (isDate(Temp.NgayNhap.ngay, Temp.NgayNhap.thang, Temp.NgayNhap.nam) == 0){
				gotoxy(10, 27); printf("Nhap sai!");
			}
		} while (isDate(Temp.NgayNhap.ngay, Temp.NgayNhap.thang, Temp.NgayNhap.nam) == 0);

		setNumber(x + 2 + 74, y + 3 + dem%limit * 2, 9, &Temp.SLN);
		Temp.ThanhTien = Temp.SLN * MH[TimMaMH(MH, a, Temp.MaMH)].GiaMua;
		gotoxy(x + 2 + 89, y + 3 + dem%limit * 2); printf("%d", Temp.ThanhTien);

		NH[++(*b)] = Temp;
		MH[TimMaMH(MH, a, Temp.MaMH)].SL += Temp.SLN;
		W_DATA(MH, NH, XH, a, *b, c);
		dem++;
	};
}
// NHAP XUAT HANG
void addXuatHang(MATHANG MH[], XUATHANG XH[], int a, int *c) {
	int x = 12, y = 5, i = 0, dem = 0;
	int array[] = { 10, 10, 23, 23, 14, 12, 12, 0 };
	setCenter(&x, array);
	XUATHANG Temp;
	int limit = 6;
	int page = (*c + 1) / limit + 1;
	int length = page*limit;
	clrscr();
	// Hien thi du lieu trang cuoi
	for (i = (page - 1)*limit; i < length; i++){
		if (i < *c + 1){
			gotoxy(x + 2, y + 3 + i%limit * 2); printf(XH[i].MaMH);
			gotoxy(x + 2 + 10, y + 3 + i%limit * 2); printf(XH[i].MaXH);
			gotoxy(x + 2 + 20, y + 3 + i%limit * 2); printf(XH[i].NguoiBan);
			gotoxy(x + 2 + 43, y + 3 + i%limit * 2); printf(XH[i].KhachHang);
			gotoxy(x + 2 + 66, y + 3 + i%limit * 2);
			printf("%.2d", XH[i].NgayXuat.ngay);
			gotoxy(x + 2 + 68, y + 3 + i%limit * 2); printf("/");
			gotoxy(x + 2 + 69, y + 3 + i%limit * 2);
			printf("%.2d", XH[i].NgayXuat.thang);
			gotoxy(x + 2 + 71, y + 3 + i%limit * 2); printf("/");
			gotoxy(x + 2 + 72, y + 3 + i%limit * 2);
			printf("%d", XH[i].NgayXuat.nam);
			gotoxy(x + 2 + 80, y + 3 + i%limit * 2);
			printf("%d", XH[i].SLX);
			gotoxy(x + 2 + 92, y + 3 + i%limit * 2);
			printf("%d", XH[i].ThanhTien);
			dem++;
		}
	}
	while (1){
		if (dem == 6){
			dem = 0;
			page++;
			clrscr();
		}
		ShowCur(1);
		// Hien thi bang va xu ly du lieu
		drawTable(7, x, y, array, 1); setColor(28);
		gotoxy(x + 1, y + 3 + 6 * 2); printf("                                               ");
		gotoxy(x + 1, y + 4 + 6 * 2); printf("                                               ");
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("MA XH");
		gotoxy(x + 2 + 20, y + 1); printf("NGUOI BAN");
		gotoxy(x + 2 + 43, y + 1); printf("KHACH HANG");
		gotoxy(x + 2 + 66, y + 1); printf("NGAY XUAT");
		gotoxy(x + 2 + 80, y + 1); printf("SL BAN");
		gotoxy(x + 2 + 92, y + 1); printf("THANH TIEN"); setColor(15);

		gotoxy(x + 1, 20);
		printf("%c %d %c   Tong Trang: %d", 174, page, 175, page);

		do{
			setCode(x + 2, y + 3 + dem%limit * 2, Temp.MaMH);
			if (strlen(Temp.MaMH) != 5){
				gotoxy(10, 27); printf("Phai nhap 5 ki tu");
			}
			else if (TimMaMH(MH, a, Temp.MaMH) == -1){
				gotoxy(10, 27); printf("Ma MH khong ton tai");
			}
		} while (strlen(Temp.MaMH) != 5 || TimMaMH(MH, a, Temp.MaMH) == -1);
		do{
			setCode(x + 2 + 10, y + 3 + dem%limit * 2, Temp.MaXH);
			if (strlen(Temp.MaXH) != 5){
				gotoxy(10, 27); printf("Phai nhap 5 ki tu");
			}
			if (TimMaMH(MH, a, Temp.MaXH) != -1 || TimMaNH(NH, b, Temp.MaXH) != -1 || TimMaXH(XH, *c, Temp.MaXH) != -1){
				gotoxy(10, 27); printf("Ma da ton tai");
			}
		} while (strlen(Temp.MaXH) != 5 || TimMaMH(MH, a, Temp.MaXH) != -1 || TimMaNH(NH, b, Temp.MaXH) != -1 || TimMaXH(XH, *c, Temp.MaXH) != -1);
		do{
			setText(x + 2 + 20, y + 3 + dem%limit * 2, 20, Temp.NguoiBan);
			if (strlen(Temp.NguoiBan) == 0){
				gotoxy(10, 27); printf("Khong duoc de trong");
			}
		} while (strlen(Temp.NguoiBan) == 0);
		do{
			setText(x + 2 + 43, y + 3 + dem%limit * 2, 20, Temp.KhachHang);
			if (strlen(Temp.KhachHang) == 0){
				gotoxy(10, 27); printf("Khong duoc de trong");
			}
		} while (strlen(Temp.KhachHang) == 0);
		do{
			gotoxy(x + 2 + 68, y + 3 + dem%limit * 2); printf("/");
			gotoxy(x + 2 + 71, y + 3 + dem%limit * 2); printf("/");
			setNumber(x + 2 + 66, y + 3 + dem%limit * 2, 2, &Temp.NgayXuat.ngay);
			setNumber(x + 2 + 69, y + 3 + dem%limit * 2, 2, &Temp.NgayXuat.thang);
			setNumber(x + 2 + 72, y + 3 + dem%limit * 2, 4, &Temp.NgayXuat.nam);
			if (isDate(Temp.NgayXuat.ngay, Temp.NgayXuat.thang, Temp.NgayXuat.nam) == 0){
				gotoxy(10, 27); printf("Nhap sai!");
			}
		} while (isDate(Temp.NgayXuat.ngay, Temp.NgayXuat.thang, Temp.NgayXuat.nam) == 0);
		do{
			setNumber(x + 2 + 80, y + 3 + dem%limit * 2, 9, &Temp.SLX);
			if (Temp.SLX > MH[TimMaMH(MH, a, Temp.MaMH)].SL){
				gotoxy(10, 27); printf("So luong xuat phai nho hon ton kho( %d ).", MH[TimMaMH(MH, a, Temp.MaMH)].SL);
			}
		} while (Temp.SLX > MH[TimMaMH(MH, a, Temp.MaMH)].SL);

		MH[TimMaMH(MH, a, Temp.MaMH)].SL -= Temp.SLX;
		Temp.ThanhTien = Temp.SLX*MH[TimMaMH(MH, a, Temp.MaMH)].GiaBan;
		gotoxy(x + 2 + 92, y + 3 + dem%limit * 2); printf("%d", Temp.ThanhTien);

		XH[++(*c)] = Temp;
		W_DATA(MH, NH, XH, a, b, *c);
		dem++;
	};
}
/* QUAN LY MAT HANG
* Tinh so record tren 1 trang (limit)
* Tinh so trang , tong trang
* Bat Phim De chon trang hoac record
* Hien Thi Menu chuc nang THEM, SUA, XOA
*/

void Highlight(int x, int y, int dong, int vitri, MATHANG MH[], NHAPHANG NH[], XUATHANG XH[], int opt){
	if (opt == 1){
		// Neu la mat hang
		setColor(25);
		gotoxy(x + 2, y + dong + 3); printf(MH[vitri].MaMH);
		gotoxy(x + 2 + 10, y + dong + 3); printf(MH[vitri].TenMH);
		gotoxy(x + 2 + 33, y + dong + 3); printf(MH[vitri].Loai);
		gotoxy(x + 2 + 51, y + dong + 3);
		printf("%d", MH[vitri].GiaMua);
		gotoxy(x + 2 + 63, y + dong + 3);
		printf("%d", MH[vitri].GiaBan);
		gotoxy(x + 2 + 75, y + dong + 3);
		printf("%d", MH[vitri].SL);
		setColor(15);
	}
	else if (opt == 2){
		setColor(25);
		// Neu la nhap hang
		gotoxy(x + 2, y + dong + 3); printf(NH[vitri].MaMH);
		gotoxy(x + 2 + 10, y + dong + 3); printf(NH[vitri].MaNH);
		gotoxy(x + 2 + 20, y + dong + 3); printf(NH[vitri].NguoiNhap);
		gotoxy(x + 2 + 42, y + dong + 3); printf(NH[vitri].NguonNhap);
		gotoxy(x + 2 + 60, y + dong + 3); printf("/");
		gotoxy(x + 2 + 63, y + dong + 3); printf("/");
		gotoxy(x + 2 + 58, y + dong + 3);
		printf("%.2d", NH[vitri].NgayNhap.ngay);
		gotoxy(x + 2 + 61, y + dong + 3);
		printf("%.2d", NH[vitri].NgayNhap.thang);
		gotoxy(x + 2 + 64, y + dong + 3);
		printf("%d", NH[vitri].NgayNhap.nam);
		gotoxy(x + 2 + 70, y + dong + 3);
		printf("%d", NH[vitri].SLN);
		gotoxy(x + 2 + 82, y + dong + 3);
		printf("%d", NH[vitri].ThanhTien);
		setColor(15);
	}
	else if (opt == 3){
		setColor(25);
		// Neu la xuat hang
		gotoxy(x + 2, y + dong + 3); printf(XH[vitri].MaMH);
		gotoxy(x + 2 + 10, y + dong + 3); printf(XH[vitri].MaXH);
		gotoxy(x + 2 + 20, y + dong + 3); printf(XH[vitri].NguoiBan);
		gotoxy(x + 2 + 42, y + dong + 3); printf(XH[vitri].KhachHang);
		gotoxy(x + 2 + 66, y + dong + 3); printf("/");
		gotoxy(x + 2 + 69, y + dong + 3); printf("/");
		gotoxy(x + 2 + 64, y + dong + 3);
		printf("%.2d", XH[vitri].NgayXuat.ngay);
		gotoxy(x + 2 + 67, y + dong + 3);
		printf("%.2d", XH[vitri].NgayXuat.thang);
		gotoxy(x + 2 + 70, y + dong + 3);
		printf("%d", XH[vitri].NgayXuat.nam);
		gotoxy(x + 2 + 76, y + dong + 3);
		printf("%d", XH[vitri].SLX);
		gotoxy(x + 2 + 88, y + dong + 3);
		printf("%d", XH[vitri].ThanhTien);
		setColor(15);
	}
	else{
		return;
	}
}
//Hien thi mat hang
void viewMatHang(MATHANG MH[], int n) {
	int x = 12, y = 4, i = 0, dong = 0, vitri = 0;
	int page = 1;
	n++;
	int limit = 7;
	int total_page = 0, length = 0;
	length = page*limit;

	int key, array[] = { 10, 23, 18, 12, 12, 12, 0 };
	setCenter(&x, array);

	do{
		clrscr();
		// Tinh so trang va so record tren 1 trang
		//Trang cuoi 
		if ((n > limit) && (n%limit != 0) && (page == total_page)){
			length = page*limit - limit + n%limit;
			total_page = n / limit + 1;
		}
		// khong phai trang cuoi
		else if (n > limit){
			length = page*limit;
			total_page = n / limit + 1;
		}
		// Trang dau
		else{
			length = n;
			total_page = 1;
		}

		// Ve bang Quan Ly Mat Hang
		drawTable(limit + 1, x, y, array, 1);
		gotoxy(50, 2); printf("QUAN LY MAT HANG");
		setColor(28);

		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("TEN MAT HANG");
		gotoxy(x + 2 + 33, y + 1); printf("LOAI");
		gotoxy(x + 2 + 51, y + 1); printf("GIA MUA");
		gotoxy(x + 2 + 63, y + 1); printf("GIA BAN");
		gotoxy(x + 2 + 75, y + 1); printf("SL TON");
		setColor(15);

		// Khung va Menu chuc nang
		int mang[] = { 4, 10, 0 };
		drawTable(1, 12, 24, mang, 0); gotoxy(14, 25); printf("1"); gotoxy(19, 25); printf("THEM");
		drawTable(1, 52, 24, mang, 0); gotoxy(54, 25); printf("2"); gotoxy(59, 25); printf("SUA");
		drawTable(1, 92, 24, mang, 0); gotoxy(94, 25); printf("3"); gotoxy(99, 25); printf("XOA");
		gotoxy(3, 0); printf("Su Dung Phim Len Xuong Trai Phai va So 1,2,3.");
		vitri = (dong / 2) + (page - 1)*limit;

		setColor(15);


		// Hien thi du lieu
		for (i = (page - 1)*limit; i < length; i++){

			gotoxy(x + 2, y + 3 + i%limit * 2); printf(MH[i].MaMH);
			gotoxy(x + 2 + 10, y + 3 + i%limit * 2); printf(MH[i].TenMH);
			gotoxy(x + 2 + 33, y + 3 + i%limit * 2); printf(MH[i].Loai);
			gotoxy(x + 2 + 51, y + 3 + i%limit * 2);
			printf("%d", MH[i].GiaMua);
			gotoxy(x + 2 + 63, y + 3 + i%limit * 2);
			printf("%d", MH[i].GiaBan);
			gotoxy(x + 2 + 75, y + 3 + i%limit * 2);
			printf("%d", MH[i].SL);

		}

		// To sang vung duoc chon
		if (n != 0)
			Highlight(x, y, dong, vitri, MH, NH, XH, 1);
		gotoxy(x + 1, y + limit * 2 + 3);
		printf("%c %d %c   Tong Trang: %d", 174, page, 175, total_page);
		gotoxy(0, 0);

		// Bat phim dieu khien
		key = _getch();
		if (key == 75){
			page--;
			dong = 0;
		}
		else if (key == 77){
			page++;
			dong = 0;
		}
		else if (key == 72 && dong != 0){
			dong = dong - 2;
		}
		else if (key == 80 && dong < limit * 2 - 2 && vitri < a){
			dong = dong + 2;
		}
		else if (key == 27){
			Thoat();
		}
		else if (key == '1'){
			addMatHang(MH, &a);
		}
		else if (key == '2'){
			editMatHang(MH, a, vitri);
		}
		else if (key == '3'){
			delMatHang(MH, &a, vitri);
		}
		else{
			continue;
		}

		if (0 == page){
			page = 1;
		}
		else if (page >= total_page){
			page = total_page;
		}
	} while (1);
}
// QUAN LY NHAP HANG
void viewNhapHang(NHAPHANG NH[], int n) {
	int x = 12, y = 5, i = 0, j = 0, dong = 0, vitri = 0;
	int page = 1;
	int limit = 7;
	n++;
	int total_page = 0, length = 0;
	length = page*limit;

	int key, array[] = { 10, 10, 22, 16, 12, 12, 12, 0 };
	setCenter(&x, array);
	do{
		clrscr();
		// Tinh trang va so record tren trang do
		if ((n > limit) && (n%limit != 0) && (page == total_page)){
			length = page*limit - limit + n%limit;
			total_page = n / limit + 1;
		}
		else if (n > limit&&n%limit != 0){
			length = page*limit;
			total_page = n / limit + 1;
		}
		else if (n > limit&&n%limit == 0){
			length = page*limit;
			total_page = n / limit;
		}
		else{
			length = n;
			total_page = 1;
		}
		//Ve bang 
		gotoxy(50, 2); printf("QUAN LY NHAP HANG");
		drawTable(limit + 1, x, y, array, 1); setColor(28);
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("MA NH");
		gotoxy(x + 2 + 20, y + 1); printf("NGUOI NHAP");
		gotoxy(x + 2 + 42, y + 1); printf("NGUON NHAP");
		gotoxy(x + 2 + 58, y + 1); printf("THOI GIAN");
		gotoxy(x + 2 + 70, y + 1); printf("SL NHAP");
		gotoxy(x + 2 + 82, y + 1); printf("THANH TIEN");

		// Men chuc nang
		int mang[] = { 4, 10, 0 };
		drawTable(1, 12, 24, mang, 0); gotoxy(14, 25); printf("1"); gotoxy(19, 25); printf("THEM");
		drawTable(1, 52, 24, mang, 0); gotoxy(54, 25); printf("2"); gotoxy(59, 25); printf("SUA");
		drawTable(1, 92, 24, mang, 0); gotoxy(94, 25); printf("3"); gotoxy(99, 25); printf("XOA");
		gotoxy(10, 0); printf("Su Dung Phim Len Xuong Trai Phai va So 1,2,3.");
		vitri = (dong / 2) + (page - 1)*limit;


		setColor(15);

		// hien thi du lieu
		for (i = (page - 1)*limit; i < length; i++){
			gotoxy(x + 2, y + 3 + i%limit * 2); printf(NH[i].MaMH);
			gotoxy(x + 2 + 10, y + 3 + i%limit * 2); printf(NH[i].MaNH);
			gotoxy(x + 2 + 20, y + 3 + i%limit * 2); printf(NH[i].NguoiNhap);
			gotoxy(x + 2 + 42, y + 3 + i%limit * 2); printf(NH[i].NguonNhap);
			gotoxy(x + 2 + 58, y + 3 + i%limit * 2);
			printf("%.2d", NH[i].NgayNhap.ngay);
			gotoxy(x + 2 + 60, y + 3 + i%limit * 2); printf("/");
			gotoxy(x + 2 + 61, y + 3 + i%limit * 2);
			printf("%.2d", NH[i].NgayNhap.thang);
			gotoxy(x + 2 + 64, y + 3 + i%limit * 2);
			gotoxy(x + 2 + 63, y + 3 + i%limit * 2); printf("/");
			printf("%d", NH[i].NgayNhap.nam);
			gotoxy(x + 2 + 70, y + 3 + i%limit * 2);
			printf("%d", NH[i].SLN);
			gotoxy(x + 2 + 82, y + 3 + i%limit * 2);
			printf("%d", NH[i].ThanhTien);
		}

		if (n != 0){
			Highlight(x, y, dong, vitri, MH, NH, XH, 2);
		}

		gotoxy(x + 1, y + limit * 2 + 3);
		printf("%c %d %c   Tong Trang: %d", 174, page, 175, total_page);
		gotoxy(0, 0);

		//Bat phim dieu khien
		key = _getch();
		if (key == 75){
			page--;
			dong = 0;
		}
		else if (key == 77){
			page++;
			dong = 0;
		}
		else if (key == 72 && dong != 0){
			dong = dong - 2;
		}
		else if (key == 80 && dong < limit * 2 - 2 && vitri < b){
			dong = dong + 2;
		}
		else if (key == 27){
			Thoat();
		}
		else if (key == '1'){
			system("cls");
			addNhapHang(MH, NH, a, &b);
		}
		else if (key == '2'){
			system("cls");
			editNhapHang(MH, NH, a, b, vitri);
		}
		else if (key == '3'){
			system("cls");
			delNhapHang(NH, &b, vitri);
		}
		else{
			continue;
		}

		if (0 == page){
			page = 1;
		}
		else if (page >= total_page){
			page = total_page;
		}
	} while (key != 13);
}
// QUAN LY XUAT HANG
void viewXuatHang(XUATHANG XH[], int n) {
	int x = 12, y = 5, i = 0, j = 0, dong = 0, vitri = 0;
	int page = 1;
	int limit = 7;
	n++;
	int total_page = 0, length = 0;
	length = page*limit;

	int key, array[] = { 10, 10, 22, 22, 12, 12, 12, 0 };
	setCenter(&x, array);
	do{
		clrscr();
		// Tinh so trang va so record tren 1 trang
		if ((n > limit) && (n%limit != 0) && (page == total_page)){
			length = page*limit - limit + n%limit;
			total_page = n / limit + 1;
		}
		else if (n > limit&&n%limit != 0){
			length = page*limit;
			total_page = n / limit + 1;
		}
		else if (n > limit&&n%limit == 0){
			length = page*limit;
			total_page = n / limit;
		}
		else{
			length = n;
			total_page = 1;
		}
		// Ve bang Quan Ly Xuat Hang
		gotoxy(50, 2); printf("QUAN LY XUAT HANG");
		drawTable(limit + 1, x, y, array, 1); setColor(28);
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("MA XH");
		gotoxy(x + 2 + 20, y + 1); printf("NGUOI BAN");
		gotoxy(x + 2 + 42, y + 1); printf("KHACH HANG");
		gotoxy(x + 2 + 64, y + 1); printf("THOI GIAN");
		gotoxy(x + 2 + 76, y + 1); printf("SL XUAT");
		gotoxy(x + 2 + 88, y + 1); printf("THANH TIEN");

		// Menu chuc nang
		int mang[] = { 4, 10, 0 };
		drawTable(1, 12, 24, mang, 0); gotoxy(14, 25); printf("1"); gotoxy(19, 25); printf("THEM");
		drawTable(1, 52, 24, mang, 0); gotoxy(54, 25); printf("2"); gotoxy(59, 25); printf("SUA");
		drawTable(1, 92, 24, mang, 0); gotoxy(94, 25); printf("3"); gotoxy(99, 25); printf("XOA");
		gotoxy(10, 0); printf("Su Dung Phim Len Xuong Trai Phai va So 1,2,3.");
		vitri = (dong / 2) + (page - 1)*limit;

		setColor(15);

		// Hien thi du lieu
		for (i = (page - 1)*limit; i < length; i++){
			gotoxy(x + 2, y + 3 + i%limit * 2); printf(XH[i].MaMH);
			gotoxy(x + 2 + 10, y + 3 + i%limit * 2); printf(XH[i].MaXH);
			gotoxy(x + 2 + 20, y + 3 + i%limit * 2); printf(XH[i].NguoiBan);
			gotoxy(x + 2 + 42, y + 3 + i%limit * 2); printf(XH[i].KhachHang);
			gotoxy(x + 2 + 64, y + 3 + i%limit * 2);
			printf("%.2d", XH[i].NgayXuat.ngay);
			gotoxy(x + 2 + 66, y + 3 + i%limit * 2); printf("/");
			gotoxy(x + 2 + 67, y + 3 + i%limit * 2);
			printf("%.2d", XH[i].NgayXuat.thang);
			gotoxy(x + 2 + 69, y + 3 + i%limit * 2); printf("/");
			gotoxy(x + 2 + 70, y + 3 + i%limit * 2);
			printf("%d", XH[i].NgayXuat.nam);
			gotoxy(x + 2 + 76, y + 3 + i%limit * 2);
			printf("%d", XH[i].SLX);
			gotoxy(x + 2 + 88, y + 3 + i%limit * 2);
			printf("%d", XH[i].ThanhTien);
		}

		// To mau dang dang chon
		if (n != 0)
			Highlight(x, y, dong, vitri, MH, NH, XH, 3);
		gotoxy(x + 1, y + limit * 2 + 3);
		printf("%c %d %c   Tong Trang: %d", 174, page, 175, total_page);
		// Bat phim dieu khien
		gotoxy(0, 0);
		key = _getch();
		gotoxy(20, 0);
		printf("%d", key);
		if (key == 75){
			page--;
			dong = 0;
		}
		else if (key == 77){
			page++;
			dong = 0;
		}
		else if (key == 72 && dong != 0){
			dong = dong - 2;
		}
		else if (key == 80 && dong < limit * 2 - 2 && vitri < c){
			dong = dong + 2;
		}
		else if (key == 27){
			Thoat();
		}
		else if (key == '1'){
			system("cls");
			addXuatHang(MH, XH, a, &c);
		}
		else if (key == '2'){
			system("cls");
			editXuatHang(MH, XH, a, c, vitri);
		}
		else if (key == '3'){
			system("cls");
			delXuatHang(XH, &c, vitri);
		}
		else{
			continue;
		}

		if (0 == page){
			page = 1;
		}
		else if (page >= total_page){
			page = total_page;
		}
	} while (key != 13);
}

/* CHINH SUA MAT HANG
* Menu chuc nang chon TRUONG can sua
* Bat loi nhap du lieu
*/
void editMatHang(MATHANG MH[], int n, int vitri) {
	int x = 72, y = 3, key;
	int array[] = { 30, 30, 30, 0 }, mang[] = { 4, 37, 0 };
	setCenter(&x, array);
	while (1){
		system("cls");
		ShowCur(0);
		int chuoi[] = { 10, 22, 16, 12, 12, 12, 0 };
		MATHANG Temp = MH[vitri];
		// HIEN THI THONG TIN MAT HANG
		drawTable(2, x, y, chuoi, 1);
		gotoxy(x + 2, y - 1); printf("Du Lieu Duoc Chon: "); setColor(28);
		gotoxy(x + 5, y + 1); printf("MA MH");
		gotoxy(x + 5 + 10, y + 1); printf("TEN MAT HANG");
		gotoxy(x + 5 + 32, y + 1); printf("LOAI");
		gotoxy(x + 5 + 48, y + 1); printf("GIA MUA");
		gotoxy(x + 5 + 60, y + 1); printf("GIA BAN");
		gotoxy(x + 5 + 72, y + 1); printf("SL TON"); setColor(15);

		gotoxy(x + 5, y + 3); printf(Temp.MaMH);
		gotoxy(x + 5 + 10, y + 3); printf(Temp.TenMH);
		gotoxy(x + 5 + 32, y + 3); printf(Temp.Loai);
		gotoxy(x + 5 + 48, y + 3);
		printf("%d", Temp.GiaMua);
		gotoxy(x + 5 + 60, y + 3);
		printf("%d", Temp.GiaBan);
		gotoxy(x + 5 + 72, y + 3);
		printf("%d", Temp.SL);

		// VE MENU DIEU KHIEN
		drawTable(5, 40, 9, mang, 1);
		gotoxy(41, 10); printf("1"); gotoxy(48, 10); printf("SUA TEN MAT HANG");
		gotoxy(41, 12); printf("2"); gotoxy(48, 12); printf("SUA LOAI MAT HANG");
		gotoxy(41, 14); printf("3"); gotoxy(48, 14); printf("SUA GIA BAN");
		gotoxy(41, 16); printf("4"); gotoxy(48, 16); printf("SUA GIA MUA");
		gotoxy(40, 18); printf("ESC"); gotoxy(48, 18); printf("QUAY LAI MENU");

		// BAT PHIM DIEU KHIEN
		key = _getch();
		if (key == '1'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("TEN MAT HANG");
			gotoxy(x + 32, y + 3); printf(MH[vitri].TenMH);
			do{
				setText(x + 62, y + 3, 20, MH[vitri].TenMH);
				if (strlen(MH[vitri].TenMH) == 0){
					gotoxy(10, 27); printf("Khong duoc de trong");
				}
			} while (strlen(MH[vitri].TenMH) == 0);

			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '2'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("LOAI");
			gotoxy(x + 32, y + 3); printf(MH[vitri].Loai);
			do{
				setText(x + 62, y + 3, 20, MH[vitri].Loai);
				if (strlen(MH[vitri].Loai) == 0){
					gotoxy(10, 27); printf("Khong duoc de trong");
				}
			} while (strlen(MH[vitri].Loai) == 0);

			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '3'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("GIA BAN");
			gotoxy(x + 32, y + 3); printf("%d", MH[vitri].GiaBan);
			setNumber(x + 62, y + 3, 20, &MH[vitri].GiaBan);
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '4'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("TEN MAT HANG");
			gotoxy(x + 32, y + 3); printf("%d", MH[vitri].GiaMua);
			setNumber(x + 62, y + 3, 20, &MH[vitri].GiaMua);
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == 27){
			Thoat();
		}
		else{
			continue;
		}
	}
}

// CHINH SUA HANG NHAP
void editNhapHang(MATHANG MH[], NHAPHANG NH[], int a, int b, int vitri) {

	int x = 70, y = 3, key;
	int array[] = { 30, 30, 30, 0 }, mang[] = { 4, 37, 0 };
	setCenter(&x, array);
	
	while (1){
		system("cls");
		ShowCur(0);
		NHAPHANG Temp = NH[vitri];
		int chuoi[] = { 10, 10, 22, 16, 12, 12, 12, 0 };
		// BANG DU LIEU DUOC CHON
		drawTable(2, x, y, chuoi, 1);
		gotoxy(x + 2, y - 1); printf("Du Lieu Duoc Chon: "); setColor(28);
		gotoxy(x, y + 1); printf("MA MH");
		gotoxy(x + 10, y + 1); printf("MA NH");
		gotoxy(x + 20, y + 1); printf("NGUOI NHAP");
		gotoxy(x + 42, y + 1); printf("NGUON NHAP");
		gotoxy(x + 58, y + 1); printf("THOI GIAN");
		gotoxy(x + 70, y + 1); printf("SL NHAP");
		gotoxy(x + 82, y + 1); printf("THANH TIEN"); setColor(15);

		gotoxy(x, y + 3); printf(Temp.MaMH);
		gotoxy(x + 10, y + 3); printf(Temp.MaNH);
		gotoxy(x + 20, y + 3); printf(Temp.NguoiNhap);
		gotoxy(x + 42, y + 3); printf(Temp.NguonNhap);
		gotoxy(x + 58, y + 3);
		printf("%.2d", Temp.NgayNhap.ngay);
		gotoxy(x + 60, y + 3); printf("/");
		gotoxy(x + 61, y + 3);
		printf("%.2d", Temp.NgayNhap.thang);
		gotoxy(x + 63, y + 3); printf("/");
		gotoxy(x + 64, y + 3);
		printf("%d", Temp.NgayNhap.nam);
		gotoxy(x + 70, y + 3);
		printf("%d", Temp.SLN);
		gotoxy(x + 82, y + 3);
		printf("%d", Temp.ThanhTien);

		// VE MENU DIEU KHIEN 
		drawTable(6, 40, 9, mang, 1);
		gotoxy(41, 10); printf("1"); gotoxy(48, 10); printf("SUA MA MAT HANG");
		gotoxy(41, 12); printf("2"); gotoxy(48, 12); printf("SUA NGUOI NHAP");
		gotoxy(41, 14); printf("3"); gotoxy(48, 14); printf("SUA NGUON NHAP");
		gotoxy(41, 16); printf("4"); gotoxy(48, 16); printf("SUA THOI GIAN");
		gotoxy(41, 18); printf("5"); gotoxy(48, 18); printf("SUA SO LUONG NHAP");
		gotoxy(40, 20); printf("ESC"); gotoxy(48, 20); printf("QUAY LAI MENU");

		// BAT PHIM DIEU KHIEN
		key = _getch();
		if (key == '1'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("MA MAT HANG");
			gotoxy(x + 32, y + 3); printf(NH[vitri].MaMH);
			do{
				setCode(x + 62, y + 3, NH[vitri].MaMH);
				if (TimMaMH(MH, a, NH[vitri].MaMH) == -1){
					gotoxy(10, 27); printf("Ma MH khong ton tai.");
				}
			} while (TimMaMH(MH, a, NH[vitri].MaMH) == -1);
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '2'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("NGUOI NHAP");
			gotoxy(x + 32, y + 3); printf(NH[vitri].NguoiNhap);
			do{
				setText(x + 62, y + 3, 20, NH[vitri].NguoiNhap);
				if (strlen(NH[vitri].NguoiNhap) == 0){
					gotoxy(10, 27); printf("Khong duoc de trong.");
				}
			} while (strlen(NH[vitri].NguoiNhap) == 0);

			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '3'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("NGUON NHAP");
			gotoxy(x + 32, y + 3); printf(NH[vitri].NguonNhap);
			do{
				setText(x + 62, y + 3, 20, NH[vitri].NguonNhap);
				if (strlen(NH[vitri].NguonNhap) == 0){
					gotoxy(10, 27); printf("Khong duoc de trong.");
				}
			} while (strlen(NH[vitri].NguonNhap) == 0);

			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '4'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("THOI GIAN");
			gotoxy(x + 34, y + 3); printf("/");
			gotoxy(x + 37, y + 3); printf("/");
			gotoxy(x + 32, y + 3);
			printf("%.2d", NH[vitri].NgayNhap.ngay);
			gotoxy(x + 35, y + 3);
			printf("%.2d", NH[vitri].NgayNhap.thang);
			gotoxy(x + 38, y + 3);
			printf("%d", NH[vitri].NgayNhap.nam);
			do{
				gotoxy(x + 64, y + 3); printf("/");
				gotoxy(x + 67, y + 3); printf("/");
				setNumber(x + 62, y + 3, 2, &NH[vitri].NgayNhap.ngay);
				setNumber(x + 65, y + 3, 2, &NH[vitri].NgayNhap.thang);
				setNumber(x + 68, y + 3, 4, &NH[vitri].NgayNhap.nam);
				if (isDate(NH[vitri].NgayNhap.ngay, NH[vitri].NgayNhap.thang, NH[vitri].NgayNhap.nam) == 0){
					gotoxy(10, 27); printf("Nhap sai!");
				}
			} while (isDate(NH[vitri].NgayNhap.ngay, NH[vitri].NgayNhap.thang, NH[vitri].NgayNhap.nam) == 0);
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '5'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("SO LUONG NHAP");
			gotoxy(x + 32, y + 3); printf("%d", NH[vitri].SLN);
			Temp.SLN = NH[vitri].SLN;
			setNumber(x + 62, y + 3, 9, &NH[vitri].SLN);
			NH[vitri].ThanhTien = NH[vitri].SLN*MH[TimMaMH(MH, a, NH[vitri].MaMH)].GiaMua;
			MH[TimMaMH(MH, a, NH[vitri].MaMH)].SL = MH[TimMaMH(MH, a, NH[vitri].MaMH)].SL + NH[vitri].SLN - Temp.SLN;
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == 27){
			Thoat();
		}
		else{
			continue;
		}
	}
}

// CHINH SUA XUAT HANG
void editXuatHang(MATHANG MH[], XUATHANG XH[], int a, int c, int vitri) {
	int x = 70, y = 3, key;
	int array[] = { 30, 30, 30, 0 }, mang[] = { 4, 37, 0 };
	setCenter(&x, array);
	XUATHANG Temp = XH[vitri];
	while (1){
		system("cls");
		ShowCur(0);
		int chuoi[] = { 10, 10, 22, 16, 12, 12, 12, 0 };
		// Hien thi du lieu duoc chon
		drawTable(2, x, y, chuoi, 1);
		gotoxy(x + 2, y - 1); printf("Du Lieu Duoc Chon: "); setColor(28);
		gotoxy(x, y + 1); printf("MA MH");
		gotoxy(x + 10, y + 1); printf("MA NH");
		gotoxy(x + 20, y + 1); printf("NGUOI BAN");
		gotoxy(x + 42, y + 1); printf("KHACH HANG");
		gotoxy(x + 58, y + 1); printf("THOI GIAN");
		gotoxy(x + 70, y + 1); printf("SL XUAT");
		gotoxy(x + 82, y + 1); printf("THANH TIEN"); setColor(15);

		gotoxy(x, y + 3); printf(Temp.MaMH);
		gotoxy(x + 10, y + 3); printf(Temp.MaXH);
		gotoxy(x + 20, y + 3); printf(Temp.NguoiBan);
		gotoxy(x + 42, y + 3); printf(Temp.KhachHang);
		gotoxy(x + 58, y + 3);
		printf("%.2d", Temp.NgayXuat.ngay);
		gotoxy(x + 60, y + 3); printf("/");
		gotoxy(x + 61, y + 3);
		printf("%.2d", Temp.NgayXuat.thang);
		gotoxy(x + 63, y + 3); printf("/");
		gotoxy(x + 64, y + 3);
		printf("%d", Temp.NgayXuat.nam);
		gotoxy(x + 70, y + 3);
		printf("%d", Temp.SLX);
		gotoxy(x + 82, y + 3);
		printf("%d", Temp.ThanhTien);

		//VE MENU CHUC NANG
		drawTable(6, 40, 9, mang, 1);
		gotoxy(41, 10); printf("1"); gotoxy(48, 10); printf("SUA MA MAT HANG");
		gotoxy(41, 12); printf("2"); gotoxy(48, 12); printf("SUA NGUOI BAN");
		gotoxy(41, 14); printf("3"); gotoxy(48, 14); printf("SUA KHACH HANG");
		gotoxy(41, 16); printf("4"); gotoxy(48, 16); printf("SUA THOI GIAN");
		gotoxy(41, 18); printf("5"); gotoxy(48, 18); printf("SUA SO LUONG XUAT");
		gotoxy(40, 20); printf("ESC"); gotoxy(48, 20); printf("QUAY LAI MENU");

		key = _getch();
		if (key == '1'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("MA MAT HANG");
			gotoxy(x + 32, y + 3); printf(XH[vitri].MaMH);
			do{
				setCode(x + 62, y + 3, XH[vitri].MaMH);
				if (TimMaMH(MH, a, XH[vitri].MaMH) == -1){
					gotoxy(10, 27); printf("Ma MH khong ton tai");
				}
			} while (TimMaMH(MH, a, XH[vitri].MaMH) == -1);
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '2'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("NGUOI BAN");
			gotoxy(x + 32, y + 3); printf(XH[vitri].NguoiBan);
			do{
				setText(x + 62, y + 3, 20, XH[vitri].NguoiBan);
				if (strlen(XH[vitri].NguoiBan) == 0){
					gotoxy(10, 27); printf("Khong duoc de trong");
				}
			} while (strlen(XH[vitri].NguoiBan) == 0);

			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '3'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("KHACH HANG");
			gotoxy(x + 32, y + 3); printf(XH[vitri].KhachHang);
			do{
				setText(x + 62, y + 3, 20, XH[vitri].KhachHang);
				if (strlen(XH[vitri].KhachHang) == 0){
					gotoxy(10, 27); printf("Khong duoc de trong");
				}
			} while (strlen(XH[vitri].KhachHang) == 0);
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '4'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("THOI GIAN");
			gotoxy(x + 32, y + 3);
			printf("%.2d", XH[vitri].NgayXuat.ngay);
			gotoxy(x + 34, y + 3); printf("/");
			gotoxy(x + 35, y + 3);
			printf("%.2d", XH[vitri].NgayXuat.thang);
			gotoxy(x + 37, y + 3); printf("/");
			gotoxy(x + 38, y + 3);
			printf("%d", XH[vitri].NgayXuat.nam);
			do{
				gotoxy(x + 64, y + 3); printf("/");
				gotoxy(x + 67, y + 3); printf("/");
				setNumber(x + 62, y + 3, 2, &XH[vitri].NgayXuat.ngay);
				setNumber(x + 65, y + 3, 2, &XH[vitri].NgayXuat.thang);
				setNumber(x + 68, y + 3, 4, &XH[vitri].NgayXuat.nam);
				if (isDate(XH[vitri].NgayXuat.ngay, XH[vitri].NgayXuat.thang, XH[vitri].NgayXuat.nam) == 0){
					gotoxy(10, 27); printf("Nhap sai!");
				}
			} while (isDate(XH[vitri].NgayXuat.ngay, XH[vitri].NgayXuat.thang, XH[vitri].NgayXuat.nam) == 0);
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == '5'){
			system("cls");
			ShowCur(1);
			drawTable(2, x, y, array, 1);
			gotoxy(x + 32, y + 1); printf("HIEN TAI");
			gotoxy(x + 62, y + 1); printf("CHINH SUA");
			gotoxy(x + 2, y + 3); printf("SO LUONG XUAT");
			gotoxy(x + 32, y + 3); printf("%d", XH[vitri].SLX);
			Temp.SLX = XH[vitri].SLX;
			do{
				setNumber(x + 62, y + 3, 9, &XH[vitri].SLX);
				if (XH[vitri].SLX > MH[TimMaMH(MH, a, XH[vitri].MaMH)].SL){
					gotoxy(10, 27); printf("So luong xuat phai ho hon ton kho ( %d ).", MH[TimMaMH(MH, a, XH[vitri].MaMH)].SL);
				}
			} while (XH[vitri].SLX > MH[TimMaMH(MH, a, XH[vitri].MaMH)].SL);

			XH[vitri].ThanhTien = XH[vitri].SLX*MH[TimMaMH(MH, a, XH[vitri].MaMH)].GiaBan;
			MH[TimMaMH(MH, a, XH[vitri].MaMH)].SL = MH[TimMaMH(MH, a, XH[vitri].MaMH)].SL - XH[vitri].SLX + Temp.SLX;
			W_DATA(MH, NH, XH, a, b, c);
		}
		else if (key == 27){
			Thoat();
		}
		else{
			continue;
		}
	}
}
/* XOA MAT HANG
* Lay vi tri mat hang can xoa tu ViewMatHang()
* Hien Thi du lieu truoc khi xoa
* Bat phim de xoa record
*/
void delMatHang(MATHANG MH[], int *n, int vitri) {
	int x = 20, y = 2, key, i;
	int array[] = { 10, 22, 16, 12, 12, 12, 0 };
	setCenter(&x, array);
	MATHANG Temp;


	clrscr();

	if (vitri <= a){
	Loop:
		Temp = MH[vitri];
		// Hien thi du lieu duoc chon
		drawTable(2, x, y, array, 1);
		gotoxy(x + 2, y - 1); printf("Du Lieu Duoc Chon: "); setColor(28);
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("TEN MAT HANG");
		gotoxy(x + 2 + 32, y + 1); printf("LOAI");
		gotoxy(x + 2 + 48, y + 1); printf("GIA MUA");
		gotoxy(x + 2 + 60, y + 1); printf("GIA BAN");
		gotoxy(x + 2 + 72, y + 1); printf("SL TON"); setColor(15);

		gotoxy(x + 2, y + 3); printf(Temp.MaMH);
		gotoxy(x + 2 + 10, y + 3); printf(Temp.TenMH);
		gotoxy(x + 2 + 32, y + 3); printf(Temp.Loai);
		gotoxy(x + 2 + 48, y + 3);
		printf("%d", Temp.GiaMua);
		gotoxy(x + 2 + 60, y + 3);
		printf("%d", Temp.GiaBan);
		gotoxy(x + 2 + 72, y + 3);
		printf("%d", Temp.SL);

		// Hop thoai xoa du lieu
		setBGColor(4);
		gotoxy(42, y + 6); printf("                                      ");
		gotoxy(42, y + 7); printf("                                      ");
		gotoxy(42, y + 8); printf("                                      ");
		gotoxy(42, y + 9); printf("                                      ");
		gotoxy(42, y + 10); printf("                                      ");
		gotoxy(42, y + 11); printf("                                      ");
		gotoxy(48, y + 7); printf("Ban co muon xoa khong?");
		setColor(10);
		gotoxy(52, y + 9); printf("YES(Y)");
		gotoxy(63, y + 9); printf("NO(N)");

	}
	else{
		gotoxy(x + 2, y + 3); printf("Noi dung xoa KHONG con");
	}

	// Bat phim dieu khien
	key = _getch();
	if (key == 'Y' || key == 'y'){
		for (i = vitri; i < *n; i++) {
			MH[i] = MH[i + 1];
		}
		*n = *n - 1;
		W_DATA(MH, NH, XH, *n, b, c);
		setBGDefault();
		drawMenu();
	}
	else if (key == 'N' || key == 'n'){
		setBGDefault();
		drawMenu();
	}
	else if (key == 27){
		setBGDefault();
		drawMenu();
	}
	else {
		setBGDefault();
		goto Loop;

	}

}

//XOA NHAP HANG
void delNhapHang(NHAPHANG NH[], int *n, int vitri) {
	int x = 20, y = 2;
	int array[] = { 10, 10, 22, 16, 12, 12, 12, 0 };
	setCenter(&x, array);
	int key, index = 0, i;
	NHAPHANG Temp;

	clrscr();
	if (vitri <= b){
		Temp = NH[index];
	Loop:
		// Hien thi du lieu duoc chon
		drawTable(2, x, y, array, 1);
		gotoxy(x + 2, y - 1); printf("Du Lieu Duoc Chon: "); setColor(28);
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("MA NH");
		gotoxy(x + 2 + 20, y + 1); printf("NGUOI NHAP");
		gotoxy(x + 2 + 42, y + 1); printf("NGUON NHAP");
		gotoxy(x + 2 + 58, y + 1); printf("THOI GIAN");
		gotoxy(x + 2 + 70, y + 1); printf("SL NHAP");
		gotoxy(x + 2 + 82, y + 1); printf("THANH TIEN"); setColor(15);

		gotoxy(x + 2, y + 3); printf(Temp.MaMH);
		gotoxy(x + 2 + 10, y + 3); printf(Temp.MaNH);
		gotoxy(x + 2 + 20, y + 3); printf(Temp.NguoiNhap);
		gotoxy(x + 2 + 42, y + 3); printf(Temp.NguonNhap);
		gotoxy(x + 2 + 58, y + 3);
		printf("%.2d", Temp.NgayNhap.ngay);
		gotoxy(x + 62, y + 3); printf("/");
		gotoxy(x + 2 + 61, y + 3);
		printf("%.2d", Temp.NgayNhap.thang);
		gotoxy(x + 65, y + 3); printf("/");
		gotoxy(x + 2 + 64, y + 3);
		printf("%d", Temp.NgayNhap.nam);
		gotoxy(x + 2 + 70, y + 3);
		printf("%d", Temp.SLN);
		gotoxy(x + 2 + 82, y + 3);
		printf("%d", Temp.ThanhTien);

		//Hop thoai thong bao xoa
		setBGColor(4);
		gotoxy(42, y + 6); printf("                                      ");
		gotoxy(42, y + 7); printf("                                      ");
		gotoxy(42, y + 8); printf("                                      ");
		gotoxy(42, y + 9); printf("                                      ");
		gotoxy(42, y + 10); printf("                                      ");
		gotoxy(42, y + 11); printf("                                      ");
		gotoxy(48, y + 7); printf("Ban co muon xoa khong?");
		setColor(10);
		gotoxy(52, y + 9); printf("YES(Y)");
		gotoxy(63, y + 9); printf("NO(N)");
	}
	else{
		gotoxy(x + 2, y + 3); printf("Noi dung xoa KHONG con");
	}
	// Bat phim dieu khien
	key = _getch();
	if (key == 'Y' || key == 'y'){
		for (i = index; i < *n; i++) {
			NH[i] = NH[i + 1];
		}
		*n = *n - 1;
		W_DATA(MH, NH, XH, a, *n, c);
		setBGDefault();
		drawMenu();
	}
	else if (key == 'N' || key == 'n'){
		setBGDefault();
		drawMenu();
	}
	else if (key == 27){
		setBGDefault();
		drawMenu();
	}
	else {
		setBGDefault();
		goto Loop;
	}

}
// XOA XUAT HANG
void delXuatHang(XUATHANG XH[], int *n, int vitri) {
	int x = 20, y = 2;
	int array[] = { 10, 10, 22, 16, 12, 12, 12, 0 };
	setCenter(&x, array);
	int key, index = 0, i;
	XUATHANG Temp;

	clrscr();
	if (vitri <= b){
		Temp = XH[vitri];
	Loop:
		// hien thi du lieu duoc chon
		drawTable(2, x, y, array, 1);
		gotoxy(x + 2, y - 1); printf("Du Lieu Duoc Chon: "); setColor(28);
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("MA NH");
		gotoxy(x + 2 + 20, y + 1); printf("NGUOI BAN");
		gotoxy(x + 2 + 42, y + 1); printf("KHACH HANG");
		gotoxy(x + 2 + 58, y + 1); printf("THOI GIAN");
		gotoxy(x + 2 + 70, y + 1); printf("SL XUAT");
		gotoxy(x + 2 + 82, y + 1); printf("THANH TIEN"); setColor(15);

		gotoxy(x + 2, y + 3); printf(Temp.MaMH);
		gotoxy(x + 2 + 10, y + 3); printf(Temp.MaXH);
		gotoxy(x + 2 + 20, y + 3); printf(Temp.NguoiBan);
		gotoxy(x + 2 + 42, y + 3); printf(Temp.KhachHang);
		gotoxy(x + 2 + 58, y + 3);
		printf("%.2d", Temp.NgayXuat.ngay);
		gotoxy(x + 62, y + 3); printf("/");
		gotoxy(x + 2 + 61, y + 3);
		printf("%.2d", Temp.NgayXuat.thang);
		gotoxy(x + 65, y + 3); printf("/");
		gotoxy(x + 2 + 64, y + 3);
		printf("%d", Temp.NgayXuat.nam);
		gotoxy(x + 2 + 70, y + 3);
		printf("%d", Temp.SLX);
		gotoxy(x + 2 + 82, y + 3);
		printf("%d", Temp.ThanhTien);

		// Hop thoai xoa du lieu
		setBGColor(4);
		gotoxy(42, y + 6); printf("                                      ");
		gotoxy(42, y + 7); printf("                                      ");
		gotoxy(42, y + 8); printf("                                      ");
		gotoxy(42, y + 9); printf("                                      ");
		gotoxy(42, y + 10); printf("                                      ");
		gotoxy(42, y + 11); printf("                                      ");
		gotoxy(48, y + 7); printf("Ban co muon xoa khong?");
		setColor(10);
		gotoxy(52, y + 9); printf("YES(Y)");
		gotoxy(63, y + 9); printf("NO(N)");
	}
	else{
		gotoxy(x + 2, y + 3); printf("Noi dung xoa KHONG con");
	}

	// Bat phim dieu khien
	key = _getch();
	if (key == 'Y' || key == 'y'){
		for (i = index; i < *n; i++) {
			XH[i] = XH[i + 1];
		}
		*n = *n - 1;
		W_DATA(MH, NH, XH, a, b, *n);
		system("cls");
		setBGColor(9);
		gotoxy(42, 9); printf("                                            ");
		gotoxy(42, 10); printf("                                            ");
		gotoxy(42, 11); printf("                                            ");
		gotoxy(48, 10); printf("Xoa Thanh Cong! Dang Quay lai Menu...");
		Sleep(3000);
		setBGDefault();
		drawMenu();
	}
	else if (key == 'N' || key == 'n'){
		setBGDefault();
		drawMenu();
	}
	else if (key == 27){
		setBGDefault();
		drawMenu();
	}
	else {
		setBGDefault();
		goto Loop;
	}

}

void KiemTra(MATHANG MH[], NHAPHANG NH[], XUATHANG XH[], int a, int b, int c) {
	char s[10];
	printf("Nhap Ma MH: "); fflush(stdin);
	gets(s);
	if (TimMaMH(MH, a, s) != -1) {
		int i = TimMaMH(MH, a, s);
		printf("%-10s%-15s%-10s%-8s%-8s%-15s\n", "Ma MH", "Ten MH", "Loai", "Gia Mua", "Gia Ban", "So Luong Ton");
		printf("%-10s%-15s%-10s%-8.2lf%-8.2lf%-15.2lf\n", MH[i].MaMH, MH[i].TenMH, MH[i].Loai, MH[i].GiaMua, MH[i].GiaBan, MH[i].SL);
	}
	else {
		printf("MAT HANG KHONG TON TAI.");
	}
}
void ThongKe_SL_Max(MATHANG MH[], int a){
	int i, j, x = 20, y = 7;
	int array[] = { 10, 22, 16, 12, 12, 12, 0 };
	MATHANG Temp;
	for (i = 0; i <= a; i++){
		for (j = i + 1; j <= a; j++){
			if (MH[i].SL < MH[j].SL){
				Temp = MH[i];
				MH[i] = MH[j];
				MH[j] = Temp;
			}
		}
	}
	drawTable(11, x, y, array, 1);
	setColor(28);
	gotoxy(x, y + 1); printf("MA MH");
	gotoxy(x + 10, y + 1); printf("TEN MAT HANG");
	gotoxy(x + 32, y + 1); printf("LOAI");
	gotoxy(x + 48, y + 1); printf("GIA MUA");
	gotoxy(x + 60, y + 1); printf("GIA BAN");
	gotoxy(x + 72, y + 1); printf("SL TON"); setColor(15);
	gotoxy(47, 4); printf("THONG KE 10 MAT HANG TON NHIEU NHAT");

	for (i = 0; i < 10; i++){
		if (i <= a){
			gotoxy(x, y + 3); printf(MH[i].MaMH);
			gotoxy(x + 10, y + 3); printf(MH[i].TenMH);
			gotoxy(x + 32, y + 3); printf(MH[i].Loai);
			gotoxy(x + 48, y + 3);
			printf("%d", MH[i].GiaMua);
			gotoxy(x + 60, y + 3);
			printf("%d", MH[i].GiaBan);
			gotoxy(x + 72, y + 3);
			printf("%d", MH[i].SL);
			y = y + 2;
		}
	}
	int key;
	do{
		key = _getch();

	} while (key != 27);

}

void ThongKe_Lai(MATHANG MH[], NHAPHANG NH[], XUATHANG XH[], int a, int b, int c){
	int i, j, x = 6, y = 7;
	int ban[100], mua[100];
	int array[] = { 10, 22, 16, 12, 12, 12, 12, 12, 0 };
	int tong_mua = 0, tong_ban = 0, SLM = 0, SLB[100], Lai = 0;
	int key;
	do{
		// Tong So Tien Ban Duoc Hang
		for (i = 0; i <= c; i++){
			tong_ban = tong_ban + XH[i].ThanhTien;

		}
		//Tinh So Tien Lai
		for (i = 0; i <= a; i++){
			ban[i] = 0; mua[i] = 0; SLB[i] = 0;
			for (j = 0; j < b; j++){
				if (strcmp(MH[i].MaMH, NH[j].MaMH) == 0){
					mua[i] = mua[i] + NH[j].SLN;
				}
				//tong_mua = tong_mua + NH[i].ThanhTien;
			}
			for (j = 0; j <= c; j++){
				if (strcmp(MH[i].MaMH, XH[j].MaMH) == 0){
					ban[i] = ban[i] + XH[j].SLX;
					SLB[i] = SLB[i] + XH[j].SLX;
				}
				//tong_ban = tong_ban + XH[i].ThanhTien;
			}
			Lai += (ban[i] * MH[i].GiaBan - ban[i] * MH[i].GiaMua);
		}
		gotoxy(55, 4); printf("THONG KE TIEN LAI");
		// In so Tien Lai
		drawTable(a + 1, x, y, array, 1);
		setColor(28);
		gotoxy(x + 2, y + 1); printf("MA MH");
		gotoxy(x + 2 + 10, y + 1); printf("TEN MAT HANG");
		gotoxy(x + 2 + 32, y + 1); printf("SL BAN");
		gotoxy(x + 2 + 48, y + 1); printf("GIA MUA");
		gotoxy(x + 2 + 60, y + 1); printf("GIA BAN");
		gotoxy(x + 2 + 72, y + 1); printf("TIEN NHAP");
		gotoxy(x + 2 + 84, y + 1); printf("TIEN BAN");
		gotoxy(x + 2 + 96, y + 1); printf("TIEN LAI");
		setColor(15);


		for (i = 0; i < a; i++){
			if (i < a){
				gotoxy(x + 2, y + 3); printf(MH[i].MaMH);
				gotoxy(x + 2 + 10, y + 3); printf(MH[i].TenMH);
				gotoxy(x + 2 + 32, y + 3); printf("%d", SLB[i]);
				gotoxy(x + 2 + 48, y + 3);
				printf("%d", MH[i].GiaMua);
				gotoxy(x + 2 + 60, y + 3);
				printf("%d", MH[i].GiaBan);
				gotoxy(x + 2 + 72, y + 3);
				printf("%d", (ban[i] * MH[i].GiaMua));
				gotoxy(x + 2 + 84, y + 3);

				printf("%d", (ban[i] * MH[i].GiaBan));
				gotoxy(x + 2 + 96, y + 3);
				printf("%d", (ban[i] * MH[i].GiaBan - ban[i] * MH[i].GiaMua));
				y = y + 2;
			}
			setColor(25);

			gotoxy(x + 2, 10 + a * 2); printf("TONG:");
			gotoxy(x + 2 + 84, 10 + a * 2);
			printf("%d", tong_ban);
			gotoxy(x + 2 + 96, 10 + a * 2);
			printf("%d", Lai);
			setColor(15);
		}
		key = _getch();
		if (key == 27){
			system("cls");
			drawMenu();
		}
	} while (1);


}
/* TIM MA MAT HANG
* truyen vao du lieu Mang, do dai, chuoi can tim kiem
* tra ve -1 neu khong thay
* tra ve thu tu trong Mang cua no neu tim thay
*/
int TimMaMH(MATHANG MH[], int n, char s[]) {
	int i;
	for (i = 0; i <= n; i++) {
		if (strcmp(MH[i].MaMH, s) == 0) return i;
	}
	return -1;
}

// Tim Ma Mat Hang
int TimMaNH(NHAPHANG NH[], int n, char s[]) {
	int i = -1;

	for (i = 0; i <= n; i++) {
		if (strcmp(NH[i].MaNH, s) == 0) return i;
	}
	return -1;
}

//Tim Ma Xuat Hang
int TimMaXH(XUATHANG XH[], int n, char s[]) {
	int i = -1;
	for (i = 0; i <= n; i++) {
		if (strcmp(XH[i].MaXH, s) == 0) return i;
	}
	return -1;
}

// Tim ten Mat Hang
int TimTenMH(MATHANG MH[], int n, char s[]) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(MH[i].TenMH, s) == 0) return i;
	}
	return -1;
}

// Tim Mat Hang Ban
void TimMatHangNhap(MATHANG MH[], NHAPHANG NH[], int a, int b){
	int i, dem = 1;

	char chuoi[30];
	ShowCur(1);
	while (1){
		dem = 1;
		int x = 20, y = 7;
		gotoxy(10, 3); printf("Nhap Ma MH hoac Ten Mat Hang:"); fflush(stdin);
		setVB(40, 3, 25, chuoi);

		int array[] = { 10, 10, 22, 16, 12, 12, 12, 0 };
		setCenter(&x, array);
		system("cls");
		gotoxy(50, 5); printf("TIM DON HANG NHAP");
		if (TimMaMH(MH, a, chuoi) != -1){
			for (i = 0; i <= b; i++){

				if (strcmp(chuoi, NH[i].MaMH) == 0){

					NHAPHANG Temp = NH[i];
					gotoxy(x + 2, y + 3); printf(Temp.MaMH);
					gotoxy(x + 2 + 10, y + 3); printf(Temp.MaNH);
					gotoxy(x + 2 + 20, y + 3); printf(Temp.NguoiNhap);
					gotoxy(x + 2 + 42, y + 3); printf(Temp.NguonNhap);
					gotoxy(x + 2 + 58, y + 3);
					printf("%d", Temp.NgayNhap.ngay);
					gotoxy(x + 2 + 61, y + 3);
					printf("%d", Temp.NgayNhap.thang);
					gotoxy(x + 2 + 64, y + 3);
					printf("%d", Temp.NgayNhap.nam);
					gotoxy(x + 2 + 70, y + 3);
					printf("%d", Temp.SLN);
					gotoxy(x + 2 + 82, y + 3);
					printf("%d", Temp.ThanhTien);
					y += 2;
					dem++;
				}

			}
		}
		else if (TimTenMH(MH, a, chuoi) != -1){
			for (i = 0; i <= b; i++){
				if (strcmp(MH[TimTenMH(MH, a, chuoi)].MaMH, NH[i].MaMH) == 0){
					NHAPHANG Temp = NH[i];
					gotoxy(x + 2, y + 3); printf(Temp.MaMH);
					gotoxy(x + 2 + 10, y + 3); printf(Temp.MaNH);
					gotoxy(x + 2 + 20, y + 3); printf(Temp.NguoiNhap);
					gotoxy(x + 2 + 42, y + 3); printf(Temp.NguonNhap);
					gotoxy(x + 2 + 58, y + 3);
					printf("%d", Temp.NgayNhap.ngay);
					gotoxy(x + 2 + 61, y + 3);
					printf("%d", Temp.NgayNhap.thang);
					gotoxy(x + 2 + 64, y + 3);
					printf("%d", Temp.NgayNhap.nam);
					gotoxy(x + 2 + 70, y + 3);
					printf("%d", Temp.SLN);
					gotoxy(x + 2 + 82, y + 3);
					printf("%d", Temp.ThanhTien);
					y += 2;
					dem++;
				}
			}
		}
		else{
			gotoxy(70, 3); printf("Khong Tim Thay - Phan biet chu hoa, chu thuong");
		}

		drawTable(dem, x, 7, array, 1);
		setColor(28);
		gotoxy(x + 2, 8); printf("MA MH");
		gotoxy(x + 2 + 10, 8); printf("MA NH");
		gotoxy(x + 2 + 20, 8); printf("NGUOI NHAP");
		gotoxy(x + 2 + 42, 8); printf("NGUON NHAP");
		gotoxy(x + 2 + 58, 8); printf("THOI GIAN");
		gotoxy(x + 2 + 70, 8); printf("SL NHAP");
		gotoxy(x + 2 + 82, 8); printf("THANH TIEN"); setColor(15);
	}
}

void TimMatHangXuat(MATHANG MH[], XUATHANG XH[], int a, int c){
	int i, dem = 1;

	char chuoi[30];
	ShowCur(1);
	while (1){
		dem = 1;
		int x = 20, y = 7;
		gotoxy(10, 3); printf("Nhap Ma MH hoac Ten Mat Hang:"); fflush(stdin);
		setVB(40, 3, 25, chuoi);
		int array[] = { 10, 10, 22, 16, 12, 12, 12, 0 };
		setCenter(&x, array);
		system("cls");
		gotoxy(50, 5); printf("TIM DON HANG BAN");
		if (TimMaMH(MH, a, chuoi) != -1){
			for (i = 0; i <= c; i++){

				if (strcmp(chuoi, XH[i].MaMH) == 0){

					XUATHANG Temp = XH[i];
					gotoxy(x + 2, y + 3); printf(Temp.MaMH);
					gotoxy(x + 2 + 10, y + 3); printf(Temp.MaXH);
					gotoxy(x + 2 + 20, y + 3); printf(Temp.NguoiBan);
					gotoxy(x + 2 + 42, y + 3); printf(Temp.KhachHang);
					gotoxy(x + 2 + 58, y + 3);
					printf("%d", Temp.NgayXuat.ngay);
					gotoxy(x + 2 + 61, y + 3);
					printf("%d", Temp.NgayXuat.thang);
					gotoxy(x + 2 + 64, y + 3);
					printf("%d", Temp.NgayXuat.nam);
					gotoxy(x + 2 + 70, y + 3);
					printf("%d", Temp.SLX);
					gotoxy(x + 2 + 82, y + 3);
					printf("%d", Temp.ThanhTien);
					y += 2;
					dem++;
				}

			}
		}
		else if (TimTenMH(MH, a, chuoi) != -1){
			for (i = 0; i <= b; i++){
				if (strcmp(MH[TimTenMH(MH, a, chuoi)].MaMH, XH[i].MaMH) == 0){
					XUATHANG Temp = XH[i];
					gotoxy(x + 2, y + 3); printf(Temp.MaMH);
					gotoxy(x + 2 + 10, y + 3); printf(Temp.MaXH);
					gotoxy(x + 2 + 20, y + 3); printf(Temp.NguoiBan);
					gotoxy(x + 2 + 42, y + 3); printf(Temp.KhachHang);
					gotoxy(x + 2 + 58, y + 3);
					printf("%d", Temp.NgayXuat.ngay);
					gotoxy(x + 2 + 61, y + 3);
					printf("%d", Temp.NgayXuat.thang);
					gotoxy(x + 2 + 64, y + 3);
					printf("%d", Temp.NgayXuat.nam);
					gotoxy(x + 2 + 70, y + 3);
					printf("%d", Temp.SLX);
					gotoxy(x + 2 + 82, y + 3);
					printf("%d", Temp.ThanhTien);
					y += 2;
					dem++;
				}
			}
		}
		else{
			gotoxy(70, 3); printf("Khong Tim Thay - Phan biet chu hoa, chu thuong");
		}

		drawTable(dem, x, 7, array, 1);
		setColor(28);
		gotoxy(x + 2, 8); printf("MA MH");
		gotoxy(x + 2 + 10, 8); printf("MA NH");
		gotoxy(x + 2 + 20, 8); printf("NGUOI BAN");
		gotoxy(x + 2 + 42, 8); printf("NGUON MUA");
		gotoxy(x + 2 + 58, 8); printf("THOI GIAN");
		gotoxy(x + 2 + 70, 8); printf("SL BAN");
		gotoxy(x + 2 + 82, 8); printf("THANH TIEN"); setColor(15);
	}
}

/* GHI DU LIEU
* Ghi so luong phan tu Mang max
* Ghi du lieu theo struct
*/
void chuyen_(char *s){
	int length = strlen(s);
	int i;
	for (i = 0; i < length; i++){
		if (s[i] == ' '){
			s[i] = '_';
		}
	}
}
void chuyen(char *s){
	int length = strlen(s);
	int i;
	for (i = 0; i < length; i++){
		if (s[i] == '_'){
			s[i] = ' ';
		}
	}
}
void W_DATA(MATHANG MH[], NHAPHANG NH[], XUATHANG XH[], int a, int b, int c) {
	FILE *A, *B, *C, *D;
	int i;

	D = fopen("DATA.txt", "wt");
	fprintf(D, "%-10d%-10d%-10d", a, b, c);
	fclose(D);

	A = fopen("MATHANG.txt", "wt");
	for (i = 0; i <= a; i++) {
		chuyen_(MH[i].TenMH);
		chuyen_(MH[i].Loai);
		fprintf(A, "%-10s%-16s%-22s%-11d%-11d%-11d\n", MH[i].MaMH,MH[i].Loai, MH[i].TenMH, MH[i].GiaMua, MH[i].GiaBan, MH[i].SL);
	}
	fclose(A);

	B = fopen("NHAPHANG.txt", "wt");
	for (i = 0; i <= b; i++) {
		chuyen_(NH[i].NguoiNhap);
		chuyen_(NH[i].NguonNhap);
		fprintf(B, "%-10s%-10s%-25s%-16s%-3d%-3d%-5d%-11d%-11d\n", NH[i].MaMH, NH[i].MaNH, NH[i].NguoiNhap, NH[i].NguonNhap, NH[i].NgayNhap.ngay, NH[i].NgayNhap.thang, NH[i].NgayNhap.nam, NH[i].SLN, NH[i].ThanhTien);
	}
	fclose(B);

	C = fopen("XUATHANG.txt", "wt");
	for (i = 0; i <= c; i++) {
		chuyen_(XH[i].NguoiBan);
		chuyen_(XH[i].KhachHang);
		fprintf(C, "%-10s%-10s%-21s%-21s%-3d%-3d%-5d%-11d%-11d\n", XH[i].MaMH, XH[i].MaXH, XH[i].NguoiBan, XH[i].KhachHang, XH[i].NgayXuat.ngay, XH[i].NgayXuat.thang, XH[i].NgayXuat.nam, XH[i].SLX, XH[i].ThanhTien);
	}
	fclose(C);

}

// Doc Du Lieu
void R_DATA(MATHANG MH[], NHAPHANG NH[], XUATHANG XH[], int *a, int *b, int *c) {
	FILE *A, *B, *C, *D;
	int i;

	D = fopen("DATA.txt", "rt");
	if (!D) {
		printf("Tu tao file");
	}
	else {
		fscanf(D, "%d%d%d", a, b, c);
	}
	if (*a < 0){
		*a = -1;
	}
	if (*b < 0){
		*b = -1;
	}
	if (*c < 0){
		*c = -1;
	}
	fclose(D);
	A = fopen("MATHANG.txt", "rt");
	if (!A) {
		printf("Tu tao file");
	}
	else {
		for (i = 0; i <= *a; i++) {
			
			fscanf(A, "%s%s%s%d%d%d", &MH[i].MaMH, &MH[i].Loai, &MH[i].TenMH, &MH[i].GiaMua, &MH[i].GiaBan, &MH[i].SL);
			chuyen(MH[i].TenMH);
			chuyen(MH[i].Loai);
		}
	}
	fclose(A);
	B = fopen("NHAPHANG.txt", "rt");
	if (!B) {
		printf("Tu tao file");
	}
	else {
		for (i = 0; i <= *b; i++) {
			
			fscanf(B, "%s%s%s%s%d%d%d%d%d", &NH[i].MaMH, &NH[i].MaNH, &NH[i].NguoiNhap, &NH[i].NguonNhap, &NH[i].NgayNhap.ngay, &NH[i].NgayNhap.thang, &NH[i].NgayNhap.nam, &NH[i].SLN, &NH[i].ThanhTien);
			chuyen(NH[i].NguoiNhap);
			chuyen(NH[i].NguonNhap);
		}
	}
	fclose(B);
	C = fopen("XUATHANG.txt", "rt");
	if (!C) {
		printf("Tu tao file");
	}
	else {
		for (i = 0; i <= *c; i++) {
			fscanf(C, "%s%s%s%s%d%d%d%d%d", &XH[i].MaMH, &XH[i].MaXH, &XH[i].NguoiBan, &XH[i].KhachHang, &XH[i].NgayXuat.ngay, &XH[i].NgayXuat.thang, &XH[i].NgayXuat.nam, &XH[i].SLX, &XH[i].ThanhTien);
			chuyen(XH[i].NguoiBan);
			chuyen(XH[i].KhachHang);
		}
	}
	fclose(C);
}
void duongThang(int n) {
	int i;
	for (i = 0; i <= n; i++) {
		printf("%c", 196);
	}
}

/* VE BANG
* Can giua bang ra man hinh 120*30
* Set mau cho bang
* Ve khung cot -  bat toa do
* Ve col raw theo array
*/
void drawTable(int height, int cot, int dong, int array[], int pos) {
	int i, j;
	int length;
	int width = 0;
	for (j = 0; j < Length(array); j++){
		width += array[j];
	}
	if (pos == 1){
		cot = (120 - width) / 2;
	}

	setColor(18);
	for (i = 0; i <= height * 2; i++) {
		length = 0;
		if (i == 0) {
			gotoxy(cot, dong + i);
			duongThang(width);
			gotoxy(cot, dong + i);
			printf("%c", 218);
			gotoxy(cot + width, dong + i);
			printf("%c", 191);
			for (j = 0; j < Length(array); j++){
				length += array[j];
				if (j != Length(array) - 1){
					gotoxy(cot + length, dong + i);
					printf("%c", 194);
				}
			}
		}
		else if (i % 2 == 0 && i != height * 2) {
			gotoxy(cot, dong + i);
			duongThang(width);
			gotoxy(cot + width, dong + i);
			printf("%c", 180);
			gotoxy(cot, dong + i);
			printf("%c", 195);
			for (j = 0; j < Length(array); j++){
				length += array[j];
				if (j != Length(array) - 1){
					gotoxy(cot + length, dong + i);
					printf("%c", 197);
				}
			}
		}
		else if (i == height * 2) {
			gotoxy(cot, dong + i);
			duongThang(width);
			gotoxy(cot, dong + i);
			printf("%c", 192);
			gotoxy(cot + width, dong + i);
			printf("%c", 217);
			for (j = 0; j < Length(array); j++){
				length += array[j];
				if (j != Length(array) - 1){
					gotoxy(cot + length, dong + i);
					printf("%c", 193);
				}
			}
		}
		else {
			gotoxy(cot, dong + i);
			printf("%c", 179);
			gotoxy(cot + width, dong + i);
			printf("%c", 179);
			for (j = 0; j < Length(array); j++){
				length += array[j];
				gotoxy(cot + length, dong + i);
				printf("%c", 179);
			}
		}
	}
	setColor(15);
}

// Ve Menu Duoi
void drawFooter() {
	int mang[] = { 6, 10, 0 };
	drawTable(1, 102, 27, mang, 0); gotoxy(104, 28); printf("ESC"); gotoxy(111, 28); printf("THOAT");
}
void Hightlight_Menu(int dong){
	if (dong == 0){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("1"); gotoxy(45, 6 + dong * 2); printf("QUAN LY MAT HANG");
		setColor(15);
	}
	else if (dong == 1){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("2"); gotoxy(45, 6 + dong * 2); printf("QUAN LY BAN HANG");
		setColor(15);
	}
	else if (dong == 2){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("3"); gotoxy(45, 6 + dong * 2); printf("QUAN LY NHAP HANG");
		setColor(15);
	}
	else if (dong == 3){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("4"); gotoxy(45, 6 + dong * 2); printf("TIM KIEM - THONG KE");
		setColor(15);
	}
	else if (dong == 4){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("5"); gotoxy(45, 6 + dong * 2); printf("THOAT CHUONG TRINH");
		setColor(15);
	}
	return;
}

void HL_ThongKe(int dong){
	if (dong == 0){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("1"); gotoxy(45, 6 + dong * 2); printf("TIM KIEM DON HANG NHAP");
		setColor(15);
	}else if (dong == 1){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("2"); gotoxy(45, 6 + dong * 2); printf("TIM KIEM DON HANG BAN");
		setColor(15);
	}
	else if (dong == 2){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("3"); gotoxy(45, 6 + dong * 2); printf("THONG KE SLT MAX");
		setColor(15);
	}
	else if (dong == 3){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("4"); gotoxy(45, 6 + dong * 2); printf("THONG KE LAI XUAT");
		setColor(15);
	}
	else if (dong == 4){
		setColor(25);
		gotoxy(41, 6 + dong * 2); printf("5"); gotoxy(45, 6 + dong * 2); printf("THOAT THONG KE");
		setColor(15);
	}
}
// VE MENU CHINH CHO CHUONG TRINH
void drawMenu() {
	int chon, dong = 0, dong1 = 0, chon2, thoat;

	while (1){
		clrscr();
		R_DATA(MH, NH, XH, &a, &b, &c);
		int array[] = { 4, 37, 0 }, x = 0;
		setCenter(&x, array);
		gotoxy(46, 3); printf("QUAN LY CUA HANG DIEN DAN DUNG");
		drawTable(5, x, 5, array, 1);
		gotoxy(3, 0); printf("Su Dung Phim Mui Ten va So 1,2,3,4,5.");
		gotoxy(x + 2, 6); printf("1"); gotoxy(x + 6, 6); printf("QUAN LY MAT HANG");
		gotoxy(x + 2, 8); printf("2"); gotoxy(x + 6, 8); printf("QUAN LY BAN HANG");
		gotoxy(x + 2, 10); printf("3"); gotoxy(x + 6, 10); printf("QUAN LY NHAP HANG");
		gotoxy(x + 2, 12); printf("4"); gotoxy(x + 6, 12); printf("TIM KIEM - THONG KE");
		gotoxy(x + 2, 14); printf("5"); gotoxy(x + 6, 14); printf("THOAT CHUONG TRINH");
		Hightlight_Menu(dong);
		gotoxy(0, 0);
		chon = _getch();
		if (chon == 72 && dong > 0){
			dong--;
		}
		else if (chon == 80 && dong < 4){
			dong++;
		}
		else if (chon == 13){
			chon = dong + 49;
		}
		switch (chon) {
		case '1':
			system("cls");
			viewMatHang(MH, a);
		case '2':
			system("cls");
			viewXuatHang(XH, c);
		case '3':
			system("cls");
			viewNhapHang(NH, b);
		case '4':
			do{
				system("cls");
				drawTable(5, x, 5, array, 1);
				gotoxy(3, 0); printf("Su Dung Phim So 1,2,3,4,5.");
				gotoxy(50, 3); printf("TIM KIEM - THONG KE");
				gotoxy(x + 2, 6); printf("1"); gotoxy(x + 6, 6); printf("TIM KIEM DON HANG NHAP");
				gotoxy(x + 2, 8); printf("2"); gotoxy(x + 6, 8); printf("TIM KIEM DON HANG BAN");
				gotoxy(x + 2, 10); printf("3"); gotoxy(x + 6, 10); printf("THONG KE SLT MAX");
				gotoxy(x + 2, 12); printf("4"); gotoxy(x + 6, 12); printf("THONG KE LAI XUAT");
				gotoxy(x + 2, 14); printf("5"); gotoxy(x + 6, 14); printf("THOAT THONG KE");
				HL_ThongKe(dong1);
				gotoxy(0, 0);
				chon2 = _getch();
				if (chon2 == 72 && dong1 > 0){
					dong1--;
				}
				else if (chon2 == 80 && dong1 < 4){
					dong1++;
				}
				else if (chon2 == 13){
					chon2 = dong1+49;
				}
				else if (chon2 == 27){
					system("cls");
					drawMenu();
				}
				switch (chon2){
				case '1':
					system("cls");
					TimMatHangNhap(MH, NH, a, b);
					break;
				case '2':
					system("cls");
					TimMatHangXuat(MH, XH, a, c);
					break;
				case '3':
					system("cls");
					ThongKe_SL_Max(MH, a);
					break;
				case '4':
					system("cls");
					ThongKe_Lai(MH, NH, XH, a, b, c);
					break;
				case '5': 
					system("cls");
					drawMenu();
				default: continue;
				}
			} while (1);
			
			break;
		case '5':
			while (1){
				clrscr();
				setBGColor(4);
				gotoxy(42, 9); printf("                                      ");
				gotoxy(42, 10); printf("                                      ");
				gotoxy(42, 11); printf("                                      ");
				gotoxy(42, 12); printf("                                      ");
				gotoxy(42, 13); printf("                                      ");
				gotoxy(42, 14); printf("                                      ");
				gotoxy(48, 10); printf("Ban co muon thoat khong?");
				setColor(10);
				gotoxy(52, 12); printf("YES(Y)");
				gotoxy(63, 12); printf("NO(N)");

				thoat = _getch();
				if (thoat == 'y' || thoat == 'Y'){
					exit(0);
				}
				else if (thoat == 'n' || thoat == 'N'){
					setBGDefault();
					drawMenu();
				}
				else if (thoat == 27){
					setBGDefault();
					drawMenu();
				}
				else{
					setBGDefault();
					continue;
				}
			};

			break;
		default:
			break;
		}
	}
}


//HAM MAIN
int main() {
	drawMenu();
	return 0;
}
