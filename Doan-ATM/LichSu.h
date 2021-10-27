#pragma once
#include <iostream>

using namespace std;

class LichSu {
	string _noti;
	string NguoiGui;
	string NguoiNhan;

public:
	LichSu() {};

	LichSu(const LichSu& l) {
		_noti = l._noti;
		NguoiGui = l.NguoiGui;
		NguoiNhan = l.NguoiNhan;
	}

	LichSu(string noti, string Gui, string Nhan) {
		_noti = noti;
		NguoiGui = Gui;
		NguoiNhan = Nhan;
	}

	friend bool operator!=(LichSu l1, LichSu l2) {
		return (l1.NguoiGui == l2.NguoiGui || l1.NguoiNhan == l2.NguoiNhan);
	}

	string getNoti() {
		return _noti;
	}

	string getGui() {
		return NguoiGui;
	}

	string getNhan() {
		return NguoiNhan;
	}

	void operator[](int i) {
		cout << _noti << endl;
	}

	friend ostream& operator<<(ostream& os, LichSu l) {
		os << l._noti << endl << l.NguoiGui << endl << l.NguoiNhan;
		return os;
	}
};
