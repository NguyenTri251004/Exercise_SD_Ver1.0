#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
private:
    int MSSV;
    string hoten;
    string ngaysinh;
    string gioitinh;
    string khoa;
    int nienkhoa;
    string chuongtrinh;
    string diachi;
    string email;
    string sdt;
    string tinhtrang;

public:
    //constructor
    Student();
    Student(int MSSV, const string& hoten, const string& ngaysinh, const string& gioitinh, const string& khoa,
        int nienkhoa, const string& chuongtrinh, const string& diachi, const string& email, const string& sdt, const string& tinhtrang);

    //getter
    int getMSSV() const;
    string getHoten() const;
    string getNgaysinh() const;
    string getGioitinh() const;
    string getKhoa() const;
    int getNienkhoa() const;
    string getChuongtrinh() const;
    string getDiachi() const;
    string getEmail() const;
    string getSdt() const;
    string getTinhtrang() const;

    //setter
    void setHoten(const string& hoten);
    void setNgaysinh(const string& ngaysinh);
    void setGioitinh(const string& gioitinh);
    void setKhoa(const string& khoa);
    void setNienkhoa(int nienkhoa);
    void setChuongtrinh(const string& chuongtrinh);
    void setDiachi(const string& diachi);
    void setEmail(const string& email);
    void setSdt(const string& sdt);
    void setTinhtrang(const string& tinhtrang);

    //display
    void display() const;
};
