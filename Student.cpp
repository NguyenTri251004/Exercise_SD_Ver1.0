﻿#include "Student.h"
bool Student::checkEmail(const string& email) {
    const regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

bool Student::checkSDT(const std::string& sdt) {
    const regex pattern(R"(^0[0-9]{9}$)"); 
    return regex_match(sdt, pattern);
}

bool Student::checkKhoa(const string& khoa) {
    vector<string> cacKhoa = { "Khoa Luat", "Khoa Tieng Anh thuong mai", "Khoa Tieng Nhat", "Khoa Tieng Phap" };
    return find(cacKhoa.begin(), cacKhoa.end(), khoa) != cacKhoa.end();
}

bool Student::checkTinhTrang(const string& tinhtrang) {
    std::vector<std::string> cacTinhTrang = { "Dang hoc", "Da tot nghiep", "Da thoi hoc", "Tam dung hoc" };
    return find(cacTinhTrang.begin(), cacTinhTrang.end(), tinhtrang) != cacTinhTrang.end();
}
// Constructor
Student::Student() : MSSV(0), hoten(""), ngaysinh(""), gioitinh(""), khoa(""),
nienkhoa(0), chuongtrinh(""), diachi(""), email(""), sdt(""), tinhtrang("") {}
Student::Student(int MSSV, const string& hoten, const string& ngaysinh, const string& gioitinh, const string& khoa,
    int nienkhoa, const string& chuongtrinh, const string& diachi, const string& email, const string& sdt, const string& tinhtrang) {
    this->MSSV = MSSV;
    this->hoten = hoten;
    this->ngaysinh = ngaysinh;
    this->gioitinh = gioitinh;
    this->khoa = khoa;
    this->nienkhoa = nienkhoa;
    this->chuongtrinh = chuongtrinh;
    this->diachi = diachi;
    this->email = email;
    this->sdt = sdt;
    this->tinhtrang = tinhtrang;

}
// Getters
int Student::getMSSV() const { return MSSV; }
string Student::getHoten() const { return hoten; }
string Student::getNgaysinh() const { return ngaysinh; }
string Student::getGioitinh() const { return gioitinh; }
string Student::getKhoa() const { return khoa; }
int Student::getNienkhoa() const { return nienkhoa; }
string Student::getChuongtrinh() const { return chuongtrinh; }
string Student::getDiachi() const { return diachi; }
string Student::getEmail() const { return email; }
string Student::getSdt() const { return sdt; }
string Student::getTinhtrang() const { return tinhtrang; }

// Setters
void Student::setHoten(const string& hoten) { this->hoten = hoten; }
void Student::setNgaysinh(const string& ngaysinh) { this->ngaysinh = ngaysinh; }
void Student::setGioitinh(const string& gioitinh) { this->gioitinh = gioitinh; }
void Student::setKhoa(const string& khoa) { 
    if (!checkKhoa(khoa)) {
        throw invalid_argument("Khoa nhap khong hop le!");
    }
    this->khoa = khoa; 
}
void Student::setNienkhoa(int nienkhoa) { this->nienkhoa = nienkhoa; }
void Student::setChuongtrinh(const string& chuongtrinh) { this->chuongtrinh = chuongtrinh; }
void Student::setDiachi(const string& diachi) { this->diachi = diachi; }
void Student::setEmail(const string& email) { 
    if (!checkEmail(email)) {
        throw invalid_argument("Email nhap không hop le!");
    }
    this->email = email; 
}
void Student::setSdt(const string& sdt) {
    if (!checkSDT(sdt)) {
        throw invalid_argument("So dien thoai nhap khong hop le!");
    }
    this->sdt = sdt; 
}
void Student::setTinhtrang(const string& tinhtrang) { 
    if (!checkTinhTrang(tinhtrang)) {
        throw invalid_argument("Tinh trang sinh vien nhap khong hop le!");
    }
    this->tinhtrang = tinhtrang; 
}

// Display
void Student::display() const {
    cout << "MSSV: " << MSSV << "\nHo ten: " << hoten << "\nNgay sinh: " << ngaysinh
        << "\nGioi tinh: " << gioitinh << "\nKhoa: " << khoa << "\nNien khoa: " << nienkhoa
        << "\nChuong trinh: " << chuongtrinh << "\nDia chi: " << diachi
        << "\nEmail: " << email << "\nSo dien thoai: " << sdt
        << "\nTinh trang: " << tinhtrang << endl;
}
