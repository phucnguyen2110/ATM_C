#pragma once
#include <iostream>
#include <string>

using namespace std;

class TrangThaiTK{
	string TaiKhoan;
	string TrangThai;

public:
	TrangThaiTK(string TK = "", string TT = "") {
		TaiKhoan = TK;
		TrangThai = TT;
	};

	friend ostream& operator<<(ostream& os, TrangThaiTK b) {
		os << b.TaiKhoan << endl << b.TrangThai;
		return os;
	}

	string getTK() {
		return TaiKhoan;
	}

	string getTT() {
		return TrangThai;
	}

	friend bool operator==(TrangThaiTK b1, TrangThaiTK b2) {
		return (b1.getTK() == b2.getTK());
	}

	friend bool operator!=(TrangThaiTK b1, TrangThaiTK b2) {
		return (b1.getTK() != b2.getTK());
	}

	void operator*=(TrangThaiTK b) {
		TrangThai = b.getTT();
	}
};

