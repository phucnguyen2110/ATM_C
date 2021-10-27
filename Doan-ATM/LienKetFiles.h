#pragma once
#include <iostream>
#include "Admin.h"
#include "TheTu.h"
#include "User.h"
#include "TrangThaiTK.h"
#include "LichSu.h"

using namespace std;

template <class DataType>
class Node {
public:
	DataType data;
	Node* next;
	Node(DataType _data) {
		data = _data;
		next = NULL;
	}
	void display() {
		cout << data << endl;
	}
};

template <class DataType>
class LienKetFiles {
	Node<DataType>* head;
	Node<DataType>* tail;
	int _iSize;

public:
	LienKetFiles() {
		head = NULL;
		tail = NULL;
		_iSize = 0;
	};

	void addHead(DataType _data) {
		Node<DataType>* lAdd = new Node<DataType>(_data);
		if (head == NULL) head = tail = lAdd;
		else {
			lAdd->next = head;
			head = lAdd;
		}
		_iSize++;
	}

	void addTail(DataType _data) {
		Node<DataType>* lAdd = new Node<DataType>(_data);
		if (head == NULL) head = tail = lAdd;
		else {
			tail->next = lAdd;
			tail = lAdd;
		}
		_iSize++;
	}

	void display() {
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			Walker->display();
			Walker = Walker->next;
		}
	}

	void displayID() {
		ofstream f("[ID].txt");
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker == tail)
				f << Walker->data;
			else f << Walker->data << endl;
			Walker = Walker->next;
		}
	}

	void displayLichSu() {
		ofstream f("[LichSuID].txt");
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker == tail)
				f << Walker->data;
			else f << Walker->data << endl;
			Walker = Walker->next;
		}
	}

	void displayTheTu() {
		ofstream f("TheTu.txt");
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker == tail)
				f << Walker->data;
			else f << Walker->data << endl;
			Walker = Walker->next;
		}
	}

	void displayTrangThaiTK() {
		ofstream f("dsTrangThaiTK.txt");
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker == tail)
				f << Walker->data;
			else f << Walker->data << endl;
			Walker = Walker->next;
		}
	}

	void remove(DataType _data) {
		Node<DataType>* Walker = head, * lTemp = NULL;
		while ((Walker != NULL) && (Walker->data != _data)) {
			lTemp = Walker;	Walker = Walker->next;
		}
		if (Walker == NULL) return;
		if (lTemp != NULL) {
			if (Walker == tail)
			{
				tail = lTemp;
				tail->next = NULL;
			}
			lTemp->next = Walker->next;
			delete Walker;
			_iSize--;
		}
	}

	bool checkAdmin(DataType _data) {
		Node<DataType>* Walker = head;
		Node<DataType>* tmp = new Node<DataType>(_data);
		while (Walker != NULL) {
			if (Walker->data == tmp->data) return true;
			Walker = Walker->next;
		}
		return false;
	}

	bool checkUser(DataType _data) {
		Node<DataType>* Walker = head;
		Node<DataType>* tmp = new Node<DataType>(_data);
		while (Walker != NULL) {
			if (Walker->data * tmp->data) return true;
			Walker = Walker->next;
		}
		return false;
	}

	bool search(DataType _data) {
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker->data == _data) return true;
			Walker = Walker->next;
		}
		return false;
	}

	// bool search *
	bool search1(DataType _data) {
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker->data * _data) return true;
			Walker = Walker->next;
		}
		return false;
	}

	// Data search *
	DataType search2(DataType _data) {
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker->data * _data) return Walker->data;
			Walker = Walker->next;
		}
	}

	// void search 
	void search3(DataType _data) {
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker->data != _data) Walker->data[1];
			Walker = Walker->next;
		}
	}

	// Data search ==
	DataType search4(DataType _data) {
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker->data == _data) return Walker->data;
			Walker = Walker->next;
		}
	}

	// bool search ==
	bool search5(DataType _data) {
		Node<DataType>* Walker = head;
		while (Walker != NULL) {
			if (Walker->data == _data) return true;
			Walker = Walker->next;
		}
		return false;
	}

	// change tìm kiếm * gán *=
	void changeValue(DataType _data) {
		for (Node<DataType>* Walker = head; Walker; Walker = Walker->next) {
			if (Walker->data * _data) {
				Walker->data *= _data;
				return;
			}
		}
	}
	// change tìm kiếm == gán *=
	void changeValue1(DataType _data) {
		for (Node<DataType>* Walker = head; Walker; Walker = Walker->next) {
			if (Walker->data == _data) {
				Walker->data *= _data;
				return;
			}
		}
	}

	//Hàm fake Mảng 
	DataType operator[](int i) {
		Node<DataType>* Walker = head;
		int ii = 0;
		for (Node<DataType>* Walker = head; Walker; Walker = Walker->next) {
			if (ii == i)
				return Walker->data;
			else ii++;
		}
	}

	int getSize() {
		return _iSize;
	}
};

