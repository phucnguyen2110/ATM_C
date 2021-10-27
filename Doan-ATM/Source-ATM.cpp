#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "LienKetFiles.h"
#include "Design.h"

using namespace std;

#pragma warning(disable:4996)
#pragma execution_character_set("utf-8")
#define DSADMIN LienKetFiles<Admin> dsAdmin, LienKetFiles<User> dsUser, LienKetFiles<TheTu> dsTheTu, LienKetFiles<LichSu> dsLog, LienKetFiles<TrangThaiTK> dsTrangThaiTK
#define GOIADMIN dsAdmin, dsUser, dsTheTu, dsLog, dsTrangThaiTK
#define XoaManHinh system("cls");


//   Hàm đọc từ file khác   //
void loadAdmin(LienKetFiles<Admin>& dsAdmin);
void loadTheTu(LienKetFiles<TheTu>& dsTheTu);
void loadID(LienKetFiles<User>& dsUser);
void loadTrangThaiTK(LienKetFiles<TrangThaiTK>& dsTrangThaiTK);
void loadLog(LienKetFiles<LichSu>& dsLog);


//      //
void inputDK(string& s, int sl);
void inputPassword(string& pw);
void traVe(DSADMIN);


//   Admin   //
void showAccessAdmin(DSADMIN);												//Hiển thị quyền admin sau khi đăng nhập
void LoginAdmin(DSADMIN);													//Hiển thị giao diện admin
bool checkLoginAdmin(string tk, string mk, LienKetFiles<Admin> dsAdmin);	//Hàm kiểm tra login cho admin 
void ThongTinKhachHang(DSADMIN);
void ThemTaiKhoan(DSADMIN);
void XoaTaiKhoan(DSADMIN);
void MoKhoaTaiKhoan(DSADMIN);


//   User   //
void showAccessUser(DSADMIN, string _User);				//Hiển thị giao diện chính sau khi đăng nhập
void LoginUser(DSADMIN);								//Hiển thị giao diện chính của Bank
bool checkLoginUser(string tk, string mk, DSADMIN);		//Hàm kiểm tra login cho User
void checkRutTien(DSADMIN, long long vi, User tmp);
void ThongTinTaiKhoan(DSADMIN, string _User);
void RutTien(DSADMIN, string _User);
void ChuyenTien(DSADMIN, string _User);
void NoiDungGiaoDich(DSADMIN, string _User);
void DoiMaPIN(DSADMIN, string _User);


//   Update txt   //
void updateLichSu(DSADMIN);
void updateID(DSADMIN);
void updateTheTu(DSADMIN);
void updatedsTrangThaiTK(DSADMIN);




//    Hàm trả về màn hình chính    //
void traVe(DSADMIN) {
	GoTo(65, 33); SetColor(0, 15); cout << "Nhấn [z] trở về màn hình chính";
	char a = _getch();
	if (a == 'z') {
		XoaManHinh
			showAccessAdmin(GOIADMIN);
	}
}


//   Hàm thời gian   //
const string DateTime() {
	time_t     hientai = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&hientai);
	strftime(buf, sizeof(buf), "%d-%m-%Y.%X", &tstruct);
	return buf;
}


//      //
void loadAdmin(LienKetFiles<Admin>& dsAdmin) {
	ifstream f;
	f.open("Admin.txt");	//Đọc file Admin.txt 
	while (!f.eof()) {		//duyệt đến khi hết dòng 
		bool a = false;
		string tk_, mk_, tmp;
		getline(f, tmp);
		for (int i = 0; i < tmp.size(); i++) {
			if (tmp[i] == ' ')		a = true;
			else if (a == false)	tk_.push_back(tmp[i]);
			else					mk_.push_back(tmp[i]);
		}
		Admin tmp_(tk_, mk_);
		dsAdmin.addTail(tmp_);
	}
	//listAdmin.display();
	f.close();
}

void loadID(LienKetFiles<User>& dsUser) {
	ifstream f;
	f.open("[ID].txt");
	string _tk, _ten, sType; //tmp : sử dụng làm biến tạm, sNumber, sName, sWallet,sType : dùng để gán us và pw;
	long _vi;
	while (!f.eof()) {
		_tk = "";
		_ten = "";
		_vi = 0;
		sType = "";
		f >> _tk;
		f.ignore();
		getline(f, _ten);
		f >> _vi;
		f >> sType;
		User tmp_(_tk, _ten, _vi, sType);
		dsUser.addTail(tmp_);
		f.ignore();
	}
	f.close();
}

void loadTheTu(LienKetFiles<TheTu>& dsTheTu) {
	ifstream f;
	f.open("TheTu.txt");
	string tk_, mk_, tmp;
	while (!f.eof()) {
		tk_ = "";
		mk_ = "";
		bool a = false;
		getline(f, tmp);
		for (int i = 0; i < tmp.size(); i++) {
			if (tmp[i] == ' ') a = true;
			else if (a == false) tk_.push_back(tmp[i]);
			else mk_.push_back(tmp[i]);
		}
		TheTu tmp_(tk_, mk_);
		dsTheTu.addTail(tmp_);
	}
	f.close();
}

void loadLog(LienKetFiles<LichSu>& dsLog) {
	ifstream f;
	f.open("[LichSuID].txt");
	string tmp;
	string sNoti, Gui, Nhan;
	while (!f.eof()) {
		Gui = "";
		Nhan = "";
		sNoti = "";
		getline(f, sNoti);
		f >> Gui;
		f >> Nhan;
		f.ignore();
		LichSu l(sNoti, Gui, Nhan);
		dsLog.addTail(l);
	}
	f.close();
}

void loadTrangThaiTK(LienKetFiles<TrangThaiTK>& dsTrangThaiTK) {
	ifstream f;
	f.open("dsTrangThaiTK.txt");
	string TaiKhoan;
	string TrangThai;
	while (!f.eof()) {
		f >> TaiKhoan;
		f >> TrangThai;
		TrangThaiTK user(TaiKhoan, TrangThai);
		dsTrangThaiTK.addTail(user);
	}
	f.close();
}


//      //
bool checkLoginAdmin(string tk, string mk, LienKetFiles<Admin> dsAdmin) { //Hàm dùng kiểm tra login cho admin 
	Admin z(tk, mk);
	return (dsAdmin.checkAdmin(z));
}

bool checkLoginUser(string tk, string mk, DSADMIN) { //Hàm dùng kiểm tra login cho user
	TheTu z(tk, mk);
	return (dsTheTu.checkUser(z));
}


//      //
void inputDK(string& s, int sl) {
START:
	char pass[30];
	int i = 0;
	char a;
	for (i = 0;;) {
		a = _getch();
		if (a >= '0' && a <= '9') {
			pass[i] = a;
			++i;
			cout << a;
		}
		if (a == '\b' && i >= 1) {
			cout << "\b \b";
			--i;
		}
		if (a == '\r') {
			pass[i] = '\0';
			break;
		}
	}
	if (i != sl) {
		cout << "# Vui lòng nhập đủ " << sl << "  ký tự!";
		goto START;
	}
	for (int z = 0; z < i; z++) {
		s.push_back(pass[z]);
	}
}

void inputPassword(string& pw) {
	char pass[32];
	int i = 0;
	char a;
	for (i = 0;;) {
		a = _getch();
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {
			pass[i] = a;
			++i;
			cout << "*";
		}
		if (a == '\b' && i >= 1) {
			cout << "\b \b";
			--i;
		}
		if (a == '\r') {
			pass[i] = '\0';
			break;
		}
	}
	for (int z = 0; z < i; z++) {
		pw.push_back(pass[z]);
	}
}


// Hàm update vào file txt    //
void updateLichSu(DSADMIN) {
	dsLog.displayLichSu();
}

void updateID(DSADMIN) {
	dsUser.displayID();
}

void updateTheTu(DSADMIN) {
	dsTheTu.displayTheTu();
}

void updatedsTrangThaiTK(DSADMIN) {
	dsTrangThaiTK.displayTrangThaiTK();
}



int main() {
	SetConsoleOutputCP(65001);
	SetWindowSize(107, 35);
	SetScreenBufferSize(107, 35);
	SetFontSize(17);
	SetConsoleTitle(L"DoAn - ATM - Nhom 2");

	LienKetFiles<Admin> dsAdmin;
	LienKetFiles<User> dsUser;
	LienKetFiles<TheTu> dsTheTu;
	LienKetFiles<LichSu> dsLog;
	LienKetFiles<TrangThaiTK> dsTrangThaiTK;

	loadAdmin(dsAdmin);
	loadTheTu(dsTheTu);
	loadLog(dsLog);
	loadID(dsUser);
	loadTrangThaiTK(dsTrangThaiTK);

	LoginAdmin(GOIADMIN);
	//LoginUser(GOIADMIN);
	system("cls");
}





//   Giao dien dang nhap admin   //
void LoginAdmin(DSADMIN) {
	bool a = false;
	while (!a) {

		SetColor(0, 11);
		GoTo(42, 12);						cout << "   ---------------------";
		GoTo(42, 13);						cout << "   |  "; SetColor(0, 14);  cout << "ĐĂNG NHẬP ADMIN";		SetColor(0, 11);	cout << "  |" << endl;
		GoTo(42, 14);						cout << "   ---------------------";
		GoTo(42, 16); SetColor(0, 6);		cout << "ID     :";
		GoTo(42, 18); SetColor(0, 6);		cout << "PIN    :";

		GoTo(50, 30); SetColor(0, 15); cout << "Nhấn [z] để chuyển qua 'ĐĂNG NHẬP USER'";
		char b = _getch();
		if (b == 'z') {
			XoaManHinh
				LoginUser(GOIADMIN);
		}

		GoTo(52, 16); SetColor(0, 7);		string user = "";		cin >> user;
		GoTo(52, 18); SetColor(0, 7);		string password;		inputPassword(password);

		GoTo(41, 20);
		if (checkLoginAdmin(user, password, dsAdmin)) {
		SetColor(0, 2);		cout << "     Đăng nhập thành công!";		a = true;
		Sleep(1000);
		XoaManHinh								//xóa màn hình sau khi nhập đúng
			showAccessAdmin(GOIADMIN);
		}
		else {
			SetColor(0, 4);			cout << "      # Vui lòng nhập lại! ";
			Sleep(1000);
			XoaManHinh							//xóa màn hình sau khi nhập sai 
		}
	}
}


//   Chức năng của Admin   //
void showAccessAdmin(DSADMIN) {
	GoTo(32, 11); SetColor(0, 11);  cout << "                THỰC HIỆN DỊCH VỤ          ";
	GoTo(40, 12);  SetColor(0, 11); cout << "         ---------------       ";

	GoTo(40, 14); SetColor(7, 13); cout << "1. Xem danh sách tài khoản";
	GoTo(40, 16); SetColor(0, 13);  cout << "2. Thêm tài khoản";
	GoTo(40, 18); SetColor(0, 13);  cout << "3. Xóa tài khoản";
	GoTo(40, 20); SetColor(0, 13);  cout << "4. Mở khóa tài khoản";
	GoTo(40, 22); SetColor(0, 13);  cout << "5. Exit";

	int chon = 0;
	int toado = 14;
	do {
		char a = _getch();
		if (a == 80) chon = 1; //bắt sự kiện nút lên 
		else if (a == 72) chon = 2;//bắt sự kiện nút enter  
		else if (a == 13) chon = 3; // //bắt sự kiện nút xuống
		else chon = 0;
		if (chon == 1 && toado < 18) toado++;
		else if (chon == 2 && toado > 14) toado--;
		if (toado == 14) {
			GoTo(40, 14); SetColor(7, 13); cout << "1. Xem danh sách tài khoản";
			GoTo(40, 16); SetColor(0, 13);  cout << "2. Thêm tài khoản";
			GoTo(40, 18); SetColor(0, 13);  cout << "3. Xóa tài khoản";
			GoTo(40, 20); SetColor(0, 13);  cout << "4. Mở khóa tài khoản";
			GoTo(40, 22); SetColor(0, 13);  cout << "5. Exit";
		}
		if (toado == 15) {
			GoTo(40, 14); SetColor(0, 13); cout << "1. Xem danh sách tài khoản";
			GoTo(40, 16); SetColor(7, 13);  cout << "2. Thêm tài khoản";
			GoTo(40, 18); SetColor(0, 13);  cout << "3. Xóa tài khoản";
			GoTo(40, 20); SetColor(0, 13);  cout << "4. Mở khóa tài khoản";
			GoTo(40, 22); SetColor(0, 13);  cout << "5. Exit";
		}
		if (toado == 16) {
			GoTo(40, 14); SetColor(0, 13); cout << "1. Xem danh sách tài khoản";
			GoTo(40, 16); SetColor(0, 13);  cout << "2. Thêm tài khoản";
			GoTo(40, 18); SetColor(7, 13);  cout << "3. Xóa tài khoản";
			GoTo(40, 20); SetColor(0, 13);  cout << "4. Mở khóa tài khoản";
			GoTo(40, 22); SetColor(0, 13);  cout << "5. Exit";
		}
		if (toado == 17) {
			GoTo(40, 14); SetColor(0, 13); cout << "1. Xem danh sách tài khoản";
			GoTo(40, 16); SetColor(0, 13);  cout << "2. Thêm tài khoản";
			GoTo(40, 18); SetColor(0, 13);  cout << "3. Xóa tài khoản";
			GoTo(40, 20); SetColor(7, 13);  cout << "4. Mở khóa tài khoản";
			GoTo(40, 22); SetColor(0, 13);  cout << "5. Exit";
		}
		if (toado == 18) {
			GoTo(40, 14); SetColor(0, 13); cout << "1. Xem danh sách tài khoản";
			GoTo(40, 16); SetColor(0, 13);  cout << "2. Thêm tài khoản";
			GoTo(40, 18); SetColor(0, 13);  cout << "3. Xóa tài khoản";
			GoTo(40, 20); SetColor(0, 13);  cout << "4. Mở khóa tài khoản";
			GoTo(40, 22); SetColor(7, 13);  cout << "5. Exit";
		}
	} while (chon != 3);
	XoaManHinh
		if (toado == 14) {
			SetColor(0, 7);
			dsUser.display();
			traVe(GOIADMIN);
		}
		else if (toado == 15) ThemTaiKhoan(GOIADMIN);
		else if (toado == 16) XoaTaiKhoan(GOIADMIN);
		else if (toado == 17) MoKhoaTaiKhoan(GOIADMIN);
	SetColor(0, 0);
}

void ThemTaiKhoan(DSADMIN) {
	string ten;
	string STK;
	string sType;
	cin.ignore();
	long long vi = 0;

	GoTo(32, 11);  SetColor(0, 13); cout << "            THÊM TÀI KHOẢN          ";
	GoTo(35, 12);  SetColor(0, 13); cout << "         --------------       ";

	GoTo(37, 14);  SetColor(0, 3);  cout << "Họ & Tên      :";
	GoTo(37, 16);  SetColor(0, 3);  cout << "Số tài khoản  :";
	GoTo(37, 18);  SetColor(0, 3);  cout << "Số tiền       :";
	GoTo(37, 20);  SetColor(0, 3);  cout << "Loại tiền     :";

	GoTo(55, 14); SetColor(0, 7); getline(cin, ten);
	GoTo(55, 16); SetColor(0, 7); cin >> STK;
	GoTo(55, 18); SetColor(0, 7); cin >> vi;
	GoTo(55, 20); SetColor(0, 7); cin >> sType;


	if (vi < 50000) vi = 50000;
	TheTu tmp(STK, "123456");
	if (dsTheTu.search1(tmp.getTK())) {
		GoTo(40, 22); SetColor(0, 4); cout << "# Trùng với tài khoản đã tồn tại!";
		Sleep(1000);
		XoaManHinh
			showAccessAdmin(GOIADMIN);
	}
	else if (STK.length() != 14) {
		GoTo(40, 22); SetColor(0, 4); cout << "# Số tài khoản chưa đủ 14 số!";
		Sleep(1000);
		XoaManHinh
			showAccessAdmin(GOIADMIN);
	}
	else {
		TrangThaiTK tmp11(STK, "Active");
		dsTrangThaiTK.addTail(tmp11);
		updatedsTrangThaiTK(GOIADMIN);
		User tmp1(STK, ten, vi, sType);
		dsUser.addTail(tmp1);
		dsTheTu.addTail(tmp);
		string noti = "[" + STK + "] - [" + ten + "]" + "- [" + to_string(vi) + sType + "] được tạo bởi ADMIN vào lúc" + DateTime();
		LichSu notii(noti, "ADMIN", "TaikhoanMoi");
		dsLog.addTail(notii);
		updateLichSu(GOIADMIN);
		updateID(GOIADMIN);
		updateTheTu(GOIADMIN);
		GoTo(40, 22); SetColor(0, 2); cout << "Tạo thành công!!!!";
		Sleep(2000);
		XoaManHinh;
		showAccessAdmin(GOIADMIN);
		cin.ignore();
	}
}

void XoaTaiKhoan(DSADMIN) {
	GoTo(32, 11); SetColor(0, 13); cout << "                 HỦY TÀI KHOẢN          ";
	GoTo(40, 12); SetColor(0, 13); cout << "        ---------------       ";

	GoTo(36, 14); SetColor(0, 3);  cout << "Số tài khoản cần hủy  : ";
	GoTo(36, 16); SetColor(0, 3);  cout << "Lý do hủy tài khoản   : ";

	string STK;
	GoTo(60, 14); SetColor(0, 7); cin >> STK;
	User tmp1(STK, "", 0, "");
	TheTu tmp2(STK, "");
	TrangThaiTK tmp3(STK, "");
	if (dsTheTu.search5(tmp2)) {
		dsUser.remove(tmp1);
		dsTheTu.remove(tmp2);
		dsTrangThaiTK.remove(tmp3);
		updateTheTu(GOIADMIN);
		updateID(GOIADMIN);
		updatedsTrangThaiTK(GOIADMIN);
		string lido, noti;
		GoTo(60, 16); SetColor(0, 7); cin >> lido;
		noti = "ADMIN vừa hủy ID: " + STK + " với lý do: " + lido + "vào lúc" + DateTime();
		LichSu noti1(noti, "ADMIN", STK);
		dsLog.addTail(noti1);
		updateLichSu(GOIADMIN);
		Sleep(500);
		GoTo(32, 18); SetColor(0, 2); cout << "Đã xóa " + STK + " thành công!";
		Sleep(1000);
		XoaManHinh
			showAccessAdmin(GOIADMIN);
	}
	else {
		GoTo(32, 18); SetColor(0, 4); cout << "# Số tài khoản này không có trong dữ liệu!";
		Sleep(1000);
		XoaManHinh
			showAccessAdmin(GOIADMIN);
	}
}

void MoKhoaTaiKhoan(DSADMIN) {
	GoTo(37, 11); SetColor(0, 13); cout << "          MỞ TÀI KHOẢN          ";
	GoTo(37, 12); SetColor(0, 13); cout << "        ----------------       ";

	GoTo(36, 14); SetColor(0, 13); cout << "Số tài khoản cần mở : ";
	GoTo(36, 16); SetColor(0, 13); cout << "Trạng thái          : ";

	string STK;
	GoTo(60, 14); SetColor(0, 7); cin >> STK;
	TrangThaiTK tmp_(STK, "");
	if (dsTrangThaiTK.search(tmp_)) {
		TrangThaiTK tmp = dsTrangThaiTK.search4(tmp_);
		if (tmp.getTT() == "Active") {
			GoTo(60, 16); SetColor(0, 2); cout << "Active";
			Sleep(2000);
			XoaManHinh
				showAccessAdmin(GOIADMIN);
		}
		else {
			GoTo(60, 16); SetColor(0, 4); cout << "Ban";
			Sleep(1000);
			GoTo(36, 18); SetColor(0, 4); cout << "Mở khóa thành công!";
			TrangThaiTK tmp1(STK, "Active");
			dsTrangThaiTK.changeValue1(tmp1);
			updatedsTrangThaiTK(GOIADMIN);
			Sleep(1000);
			XoaManHinh
				showAccessAdmin(GOIADMIN);
		}
	}
	else {
		GoTo(36, 18); SetColor(0, 4); cout << "# Số tài khoản được nhập không tồn tại!";
		Sleep(1000);
		XoaManHinh
			showAccessAdmin(GOIADMIN);
	}
}





//   Giao diện đăng nhập user   //
void LoginUser(DSADMIN) {
	bool a = false;
	while (!a) {
		SetColor(0, 11);
		GoTo(42, 12);	cout << "   --------------------";
		GoTo(42, 13);	cout << "   |  "; SetColor(0, 14); cout << "ĐĂNG NHẬP USER";			SetColor(0, 11);	cout << "  |" << endl;
		GoTo(42, 14);	cout << "   --------------------";

		GoTo(42, 16); SetColor(0, 6);	cout << "ID    :";
		GoTo(42, 18); SetColor(0, 6);	cout << "PIN   :";

		GoTo(50, 30); SetColor(0, 15); cout << "Nhấn [z] để chuyển qua 'ĐĂNG NHẬP ADMIN'";
		char b = _getch();
		if (b == 'z') {
			XoaManHinh
				LoginAdmin(GOIADMIN);
		}

		GoTo(52, 16); SetColor(0, 7); string user = "";		cin >> user;
		GoTo(52, 18); SetColor(0, 7); string password;		inputPassword(password);

		GoTo(41, 20);
		if (checkLoginUser(user, password, GOIADMIN)) {
			SetColor(0, 2);		cout << "     Đăng nhập thành công! ";		a = true;
			Sleep(1000);
			XoaManHinh						
				string _User = user;
			showAccessUser(GOIADMIN, _User);
		}
		else {
			SetColor(0, 4);			cout << "      # Vui lòng nhập lại! ";
			Sleep(1000);
			XoaManHinh				
		}
	}
}


//   Chức năng của User   //
void showAccessUser(DSADMIN, string _User) {
	GoTo(30, 11); SetColor(0, 4); cout << "		MỜI QUÝ KHÁCH THỰC HIỆN DỊCH VỤ	";
	GoTo(37, 12); SetColor(0, 4); cout << "        ----------------------       ";

	GoTo(40, 14); SetColor(7, 9); cout << "1. Truy vấn tài khoản";
	GoTo(40, 16); SetColor(0, 9); cout << "2. Rút tiền";
	GoTo(40, 18); SetColor(0, 9); cout << "3. Chuyển tiền";
	GoTo(40, 20); SetColor(0, 9); cout << "4. Xem nội dung giao dịch";
	GoTo(40, 22); SetColor(0, 9); cout << "5. Đổi PIN";
	GoTo(40, 24); SetColor(0, 9); cout << "6. Exit";

	int chon = 0;
	int toado = 14;
	do {
		char a = _getch();
		if (a == 80) chon = 1; //bắt sự kiện nút lên 
		else if (a == 72) chon = 2;//bắt sự kiện nút enter  
		else if (a == 13) chon = 3; // //bắt sự kiện nút xuống
		else chon = 0;
		if (chon == 1 && toado < 19) toado++;
		else if (chon == 2 && toado > 14) toado--;
		if (toado == 14) {
			GoTo(40, 14); SetColor(7, 9); cout << "1. Truy vấn tài khoản";
			GoTo(40, 16); SetColor(0, 9); cout << "2. Rút tiền";
			GoTo(40, 18); SetColor(0, 9); cout << "3. Chuyển tiền";
			GoTo(40, 20); SetColor(0, 9); cout << "4. Xem nội dung giao dịch";
			GoTo(40, 22); SetColor(0, 9); cout << "5. Đổi PIN";
			GoTo(40, 24); SetColor(0, 9); cout << "6. Exit";
		}
		if (toado == 15) {
			GoTo(40, 14); SetColor(0, 9); cout << "1. Truy vấn tài khoản";
			GoTo(40, 16); SetColor(7, 9); cout << "2. Rút tiền";
			GoTo(40, 18); SetColor(0, 9); cout << "3. Chuyển tiền";
			GoTo(40, 20); SetColor(0, 9); cout << "4. Xem nội dung giao dịch";
			GoTo(40, 22); SetColor(0, 9); cout << "5. Đổi PIN";
			GoTo(40, 24); SetColor(0, 9); cout << "6. Exit";
		}
		if (toado == 16) {
			GoTo(40, 14); SetColor(0, 9); cout << "1. Truy vấn tài khoản";
			GoTo(40, 16); SetColor(0, 9); cout << "2. Rút tiền";
			GoTo(40, 18); SetColor(7, 9); cout << "3. Chuyển tiền";
			GoTo(40, 20); SetColor(0, 9); cout << "4. Xem nội dung giao dịch";
			GoTo(40, 22); SetColor(0, 9); cout << "5. Đổi PIN";
			GoTo(40, 24); SetColor(0, 9); cout << "6. Exit";
		}
		if (toado == 17) {
			GoTo(40, 14); SetColor(0, 9); cout << "1. Truy vấn tài khoản";
			GoTo(40, 16); SetColor(0, 9); cout << "2. Rút tiền";
			GoTo(40, 18); SetColor(0, 9); cout << "3. Chuyển tiền";
			GoTo(40, 20); SetColor(7, 9); cout << "4. Xem nội dung giao dịch";
			GoTo(40, 22); SetColor(0, 9); cout << "5. Đổi PIN";
			GoTo(40, 24); SetColor(0, 9); cout << "6. Exit";
		}
		if (toado == 18) {
			GoTo(40, 14); SetColor(0, 9); cout << "1. Truy vấn tài khoản";
			GoTo(40, 16); SetColor(0, 9); cout << "2. Rút tiền";
			GoTo(40, 18); SetColor(0, 9); cout << "3. Chuyển tiền";
			GoTo(40, 20); SetColor(0, 9); cout << "4. Xem nội dung giao dịch";
			GoTo(40, 22); SetColor(7, 9); cout << "5. Đổi PIN";
			GoTo(40, 24); SetColor(0, 9); cout << "6. Exit";
		}
		if (toado == 19) {
			GoTo(40, 14); SetColor(0, 9); cout << "1. Truy vấn tài khoản";
			GoTo(40, 16); SetColor(0, 9); cout << "2. Rút tiền";
			GoTo(40, 18); SetColor(0, 9); cout << "3. Chuyển tiền";
			GoTo(40, 20); SetColor(0, 9); cout << "4. Xem nội dung giao dịch";
			GoTo(40, 22); SetColor(0, 9); cout << "5. Đổi PIN";
			GoTo(40, 24); SetColor(7, 9); cout << "6. Exit";
		}
	} while (chon != 3);
	XoaManHinh
		if (toado == 14) ThongTinTaiKhoan(GOIADMIN, _User);
		else if (toado == 15) RutTien(GOIADMIN, _User);
		else if (toado == 16) ChuyenTien(GOIADMIN, _User);
		else if (toado == 17) NoiDungGiaoDich(GOIADMIN, _User);
		else if (toado == 18) DoiMaPIN(GOIADMIN, _User);
	SetColor(0, 0);
}

void ThongTinTaiKhoan(DSADMIN, string _User) {
	string tk, ten, vi, type;
	User tmp_(_User, "", 0, "");
	User tmp = dsUser.search2(tmp_);
	GoTo(35, 11); SetColor(0, 4); cout << "	       THÔNG TIN TÀI KHOẢN	 ";
	GoTo(39, 12); SetColor(0, 4); cout << "          ---------------     ";

	GoTo(38, 14); SetColor(0, 6); cout << "1. ID          :  ";
	GoTo(38, 16); SetColor(0, 6); cout << "2. Họ & Tên    :  ";
	GoTo(38, 18); SetColor(0, 6); cout << "3. Số tiền     :  ";
	GoTo(38, 20); SetColor(0, 6); cout << "4. Trạng thái  :  ";

	
	Sleep(200); GoTo(54, 14); SetColor(0, 8); cout << tmp.getTK();
	Sleep(200); GoTo(54, 16); SetColor(0, 7); cout << tmp.getTen();
	Sleep(200); GoTo(54, 18); SetColor(0, 2); cout << tmp.getVi();	 cout << " " + tmp.getType();
	Sleep(200); GoTo(54, 20); SetColor(0, 7); cout << "Đang hoạt động!";
	
	GoTo(65, 33); SetColor(0, 15); cout << "Nhấn [z] trở về màn hình chính";
	char a = _getch();
	if (a == 'z') {
		XoaManHinh
			showAccessUser(GOIADMIN, _User);
	}
}

void RutTien(DSADMIN, string _User) {
	string tk, ten, vi, type;
	User tmp_(_User, "", 0, "");
	User tmp = dsUser.search2(tmp_);
	GoTo(31, 11); SetColor(0, 4); cout << "		XIN VUI LÒNG LỰA CHỌN SỐ TIỀN	 ";
	GoTo(36, 12); SetColor(0, 4); cout << "        ----------------------       ";

	GoTo(34, 14); SetColor(2, 7); cout << "[50000] ";
	GoTo(34, 16); SetColor(0, 7); cout << "[100000]";
	GoTo(34, 18); SetColor(0, 7); cout << "[200000]";
	GoTo(65, 14); SetColor(0, 7); cout << "[500000]";
	GoTo(65, 16); SetColor(0, 7); cout << "[1000000]";
	GoTo(64, 18); SetColor(0, 7); cout << " SỐ KHÁC ";
	GoTo(50, 16); SetColor(0, 7); cout << " Exit ";

	int chon = 0;
	int toado = 14;
	do {
		char a = _getch();
		if (a == 80) chon = 1;
		else if (a == 72) chon = 2;
		else if (a == 13) chon = 3;
		else chon = 0;
		if (chon == 1 && toado < 20) toado++;
		else if (chon == 2 && toado > 14) toado--;
		if (toado == 14) {
			GoTo(34, 14); SetColor(2, 7); cout << "[50000] ";
			GoTo(34, 16); SetColor(0, 7); cout << "[100000]";
			GoTo(34, 18); SetColor(0, 7); cout << "[200000]";
			GoTo(65, 14); SetColor(0, 7); cout << "[500000]";
			GoTo(65, 16); SetColor(0, 7); cout << "[1000000]";
			GoTo(64, 18); SetColor(0, 7); cout << " SỐ KHÁC ";
			GoTo(50, 16); SetColor(0, 7); cout << " Exit ";
		}
		if (toado == 15) {
			GoTo(34, 14); SetColor(0, 7); cout << "[50000] ";
			GoTo(34, 16); SetColor(2, 7); cout << "[100000]";
			GoTo(34, 18); SetColor(0, 7); cout << "[200000]";
			GoTo(65, 14); SetColor(0, 7); cout << "[500000]";
			GoTo(65, 16); SetColor(0, 7); cout << "[1000000]";
			GoTo(64, 18); SetColor(0, 7); cout << " SỐ KHÁC ";
			GoTo(50, 16); SetColor(0, 7); cout << " Exit ";
		}
		if (toado == 16) {
			GoTo(34, 14); SetColor(0, 7); cout << "[50000] ";
			GoTo(34, 16); SetColor(0, 7); cout << "[100000]";
			GoTo(34, 18); SetColor(2, 7); cout << "[200000]";
			GoTo(65, 14); SetColor(0, 7); cout << "[500000]";
			GoTo(65, 16); SetColor(0, 7); cout << "[1000000]";
			GoTo(64, 18); SetColor(0, 7); cout << " SỐ KHÁC ";
			GoTo(50, 16); SetColor(0, 7); cout << " Exit ";
		}
		if (toado == 17) {
			GoTo(34, 14); SetColor(0, 7); cout << "[50000] ";
			GoTo(34, 16); SetColor(0, 7); cout << "[100000]";
			GoTo(34, 18); SetColor(0, 7); cout << "[200000]";
			GoTo(65, 14); SetColor(2, 7); cout << "[500000]";
			GoTo(65, 16); SetColor(0, 7); cout << "[1000000]";
			GoTo(64, 18); SetColor(0, 7); cout << " SỐ KHÁC ";
			GoTo(50, 16); SetColor(0, 7); cout << " Exit ";
		}
		if (toado == 18) {
			GoTo(34, 14); SetColor(0, 7); cout << "[50000] ";
			GoTo(34, 16); SetColor(0, 7); cout << "[100000]";
			GoTo(34, 18); SetColor(0, 7); cout << "[200000]";
			GoTo(65, 14); SetColor(0, 7); cout << "[500000]";
			GoTo(65, 16); SetColor(2, 7); cout << "[1000000]";
			GoTo(64, 18); SetColor(0, 7); cout << " SỐ KHÁC ";
			GoTo(50, 16); SetColor(0, 7); cout << " Exit ";
		}
		if (toado == 19) {
			GoTo(34, 14); SetColor(0, 7); cout << "[50000] ";
			GoTo(34, 16); SetColor(0, 7); cout << "[100000]";
			GoTo(34, 18); SetColor(0, 7); cout << "[200000]";
			GoTo(65, 14); SetColor(0, 7); cout << "[500000]";
			GoTo(65, 16); SetColor(0, 7); cout << "[1000000]";
			GoTo(64, 18); SetColor(2, 7); cout << " SỐ KHÁC ";
			GoTo(50, 16); SetColor(0, 7); cout << " Exit ";
		}
		if (toado == 20) {
			GoTo(34, 14); SetColor(0, 7); cout << "[50000] ";
			GoTo(34, 16); SetColor(0, 7); cout << "[100000]";
			GoTo(34, 18); SetColor(0, 7); cout << "[200000]";
			GoTo(65, 14); SetColor(0, 7); cout << "[500000]";
			GoTo(65, 16); SetColor(0, 7); cout << "[1000000]";
			GoTo(64, 18); SetColor(0, 7); cout << " SỐ KHÁC ";
			GoTo(50, 16); SetColor(0, 2); cout << " Exit ";
		}
	} while (chon != 3);
	if (toado == 14) checkRutTien(GOIADMIN, 50000, tmp);
	else if (toado == 15) checkRutTien(GOIADMIN, 100000, tmp);
	else if (toado == 16) checkRutTien(GOIADMIN, 200000, tmp);
	else if (toado == 17) checkRutTien(GOIADMIN, 500000, tmp);
	else if (toado == 18) checkRutTien(GOIADMIN, 1000000, tmp);
	else if (toado == 19) {
		GoTo(73, 20); int wallet = 0;			cout << "Nhập số tiền: ";			cin >> wallet;
		checkRutTien(GOIADMIN, wallet, tmp);
	}
	else if (toado == 20) { XoaManHinh showAccessUser(GOIADMIN, _User); }
}

void ChuyenTien(DSADMIN, string _User) {
	User tmp1(_User, "", 0, "");
	User tmp11 = dsUser.search2(tmp1);
	string _NguoiNhan = "";
	long long soTienChuyen;
	GoTo(32, 11); SetColor(0, 4); cout << "	       DỊCH VỤ CHUYỂN TIỀN  	 ";
	GoTo(40, 12); SetColor(0, 4); cout << "         ----------------        ";

	GoTo(34, 14); SetColor(0, 6); cout << "Số dư hiện tại    :";
	GoTo(34, 16); SetColor(0, 6); cout << "ID người nhận     :";
	GoTo(34, 18); SetColor(0, 6); cout << "Tên người nhận    :";
	GoTo(34, 20); SetColor(0, 6); cout << "Số tiền           :";

	GoTo(55, 16); SetColor(0, 7); cin >> _NguoiNhan;
	GoTo(55, 14); SetColor(0, 7); cout << tmp11.getVi() << " " << tmp11.getType();

	User tmp2(_NguoiNhan, "", 0, "");
	if (dsUser.search1(tmp2) && _User != _NguoiNhan) {
		User tmp22 = dsUser.search2(tmp2);
		GoTo(55, 18); SetColor(0, 3); cout << tmp22.getTen();
		GoTo(55, 20); SetColor(0, 7); cin >> soTienChuyen;
		if (soTienChuyen >= 50000 && soTienChuyen <= tmp11.getVi() - 50000 && soTienChuyen % 50000 == 0) {
			string noti = tmp11.getTen() + " vừa chuyển " + to_string(soTienChuyen) + " đến " + tmp22.getTen() + " vào lúc " + DateTime();
			LichSu noti1(noti, tmp11.getTK(), tmp22.getTK());
			dsLog.addTail(noti1);
			tmp11.TruTien(soTienChuyen);
			tmp22.CongTien(soTienChuyen);
			updateLichSu(GOIADMIN);
			dsUser.changeValue(tmp11);
			dsUser.changeValue(tmp22);
			updateID(GOIADMIN);
			Sleep(500);
			GoTo(34, 22); SetColor(0, 2); cout << "          Chuyển thành công! ";
			Sleep(1000);
			XoaManHinh
				showAccessUser(GOIADMIN, tmp11.getTK());
		}
		else {
			GoTo(34, 22); SetColor(0, 4); cout << "# Vui lòng nhập lại! Tiền bạn chưa đủ hoặc không phải bôi 50000";
			Sleep(1000);
			XoaManHinh
				showAccessUser(GOIADMIN, _User);
		}
	}
	else {
		GoTo(34, 21); SetColor(0, 4); cout << "          # Sai số ID!!!";
		Sleep(1000);
		XoaManHinh
			showAccessUser(GOIADMIN, _User);
	}
}

void NoiDungGiaoDich(DSADMIN, string _User) {
	GoTo(25, 2); SetColor(0, 4); cout << "	       NỘI DUNG GIAO DỊCH CỦA BẠN  	 ";
	GoTo(35, 3); SetColor(0, 4); cout << "         ----------------        ";

	GoTo(0, 5); SetColor(0, 7);
	LichSu noti1("", _User, _User);
	dsLog.search3(noti1);
	char a = _getch();
	if (a != 'z') {
		XoaManHinh
			showAccessUser(GOIADMIN, _User);
	}
}

void DoiMaPIN(DSADMIN, string _User) {
	TheTu a(_User, "");
	a = dsTheTu.search4(a);
	string pinHientai = a.getMK();
	TheTu tmp_(_User, a.getMK());
	TheTu tmp = dsTheTu.search2(tmp_);
	string pinCu;
	string pinMoi1, pinMoi2;

	GoTo(37, 11); SetColor(0, 4); cout << "        THỰC HIỆN ĐỔI MÃ PIN	 ";
	GoTo(37, 12); SetColor(0, 4); cout << "       ----------------------       ";

	GoTo(34, 14); SetColor(0, 6); cout << "PIN hiện tại    :";
	GoTo(34, 16); SetColor(0, 6); cout << "PIN mới         :";
	GoTo(34, 18); SetColor(0, 6); cout << "Nhập lại PIN mới:";

	GoTo(55, 14); SetColor(0, 7); cin >> pinCu;
	if (pinCu == pinHientai) {
		GoTo(55, 16); SetColor(0, 7); cin >> pinMoi1;
		GoTo(55, 18); SetColor(0, 7); cin >> pinMoi2;
		if (pinMoi1 != pinMoi2) {
			GoTo(40, 20); SetColor(0, 4); cout << "# 2 mã PIN mới khác nhau!!";
		}
		else {
			GoTo(40, 20); SetColor(0, 2); cout << "Đổi PIN thành công!!";
			tmp.doimaPIN(pinMoi1);
			dsTheTu.changeValue1(tmp);
			updateTheTu(GOIADMIN);
		}
		Sleep(1000);
		XoaManHinh
			showAccessUser(GOIADMIN, _User);
	}
	else {
		GoTo(40, 20); SetColor(0, 4); cout << "# PIN hiện tại nhập sai!!";
		Sleep(1000);
		XoaManHinh
			showAccessUser(GOIADMIN, _User);
	}
}

void checkRutTien(DSADMIN, long long vi, User tmp) {
	long long soDu = tmp.getVi();
	if (vi >= 50 && vi <= soDu - 50000 && vi % 50000 == 0) {
		GoTo(40, 21); SetColor(0, 2); cout << "     Loading...";
		tmp.TruTien(vi);
		string noti = tmp.getTen() + " vừa rút thành công " + to_string(vi) + " vào lúc " + DateTime();
		LichSu noti1(noti, tmp.getTK(), "0");
		dsLog.addTail(noti1);
		updateLichSu(GOIADMIN);
		dsUser.changeValue(tmp);
		updateID(GOIADMIN);
		Sleep(1000);
		GoTo(38, 23); SetColor(0, 2); cout << "Rút thành công! " + to_string(vi);
		Sleep(1000);
		XoaManHinh
			showAccessUser(GOIADMIN, tmp.getTK());
	}
	else {
		GoTo(20, 23); SetColor(0, 4); cout << "# Vui lòng nhập lại! Tiền bạn chưa đủ hoặc không phải bội số 50000";
		Sleep(1000);
		XoaManHinh
			showAccessUser(GOIADMIN, tmp.getTK());
	}
}