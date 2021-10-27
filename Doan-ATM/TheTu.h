#pragma once
#include <iostream>

using namespace std;

class TheTu {
	string _tk, _mk;

public:
	TheTu(string TK = "", string MK = "123456") {
		_tk = TK;
		_mk = MK;
	};

	string getTK() {
		return _tk;
	}

	string getMK() {
		return _mk;
	}

	void doimaPIN(string p) {
		_mk = p;
	}

	friend bool operator* (TheTu a, TheTu b) {
		return (a.getTK() == b.getTK() && a.getMK() == b.getMK());
	}

	friend bool operator==(TheTu a, TheTu b) {
		return (a.getTK() == b.getTK());
	}

	friend bool operator!=(TheTu a, TheTu b) {
		return (a.getTK() != b.getTK());
	}

	void operator*= (TheTu a) {
		_mk = a.getMK();
	}

	friend ostream& operator<< (ostream& os, TheTu a) {
		os << a._tk << " " << a._mk;
		return os;
	}
};
