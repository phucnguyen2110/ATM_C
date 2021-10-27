#pragma once
#pragma once
#include <iostream>

using namespace std;

class User {
	string _tk, _ten;
	long long _vi;
	string _sType;

public:
	User() {}

	User(const User& a) {
		_tk = a._tk;
		_ten = a._ten;
		_vi = a._vi;
		_sType = a._sType;
	}

	User(string TK, string Ten, long long Vi, string _Type) {
		_tk = TK;
		_ten = Ten;
		_vi = Vi;
		_sType = _Type;
	};

	friend ostream& operator<<(ostream& os, User a) {
		os << a._tk << endl << a._ten << endl << a._vi << endl << a._sType;
		return os;
	}

	string getTK() {
		return _tk;
	}

	string getTen() {
		return _ten;
	}

	long long getVi() {
		return _vi;
	}

	void TruTien(long long l) {
		_vi -= l;
	}

	void CongTien(long long l) {
		_vi += l;
	}

	string getType() {
		return _sType;
	}

	friend bool operator*(User a, User b) {
		return (a.getTK() == b.getTK());
	}

	void operator*=(User a) {
		_vi = a.getVi();
	}

	friend bool operator==(User a, User b) {
		return (a.getTK() == b.getTK());
	}

	friend bool operator!=(User a, User b) {
		return (a.getTK() != b.getTK());
	}
};

