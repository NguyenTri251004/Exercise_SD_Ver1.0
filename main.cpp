// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Student.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

unordered_map<int, Student> studentList;
void luuDanhSachSinhVien() {
    ofstream file("sinhvien.txt");
    if (!file) {
        cout << "Loi mo file de luu!\n";
        return;
    }

    for (const auto& pair : studentList) {
        file << pair.first << ","
            << pair.second.getHoten() << ","
            << pair.second.getNgaysinh() << ","
            << pair.second.getGioitinh() << ","
            << pair.second.getKhoa() << ","
            << pair.second.getNienkhoa() << ","
            << pair.second.getChuongtrinh() << ","
            << pair.second.getDiachi() << ","
            << pair.second.getEmail() << ","
            << pair.second.getSdt() << ","
            << pair.second.getTinhtrang() << "\n";
    }

    file.close();
    cout << "Luu danh sach thanh cong!\n";
}

void docDanhSachSinhVien() {
    ifstream file("sinhvien.txt");
    if (!file) {
        cout << "Khong tim thay file du lieu, danh sach sinh vien se rong!\n";
        return;
    }

    studentList.clear();
    int MSSV, nienkhoa;
    string hoten, ngaysinh, gioitinh, khoa, chuongtrinh, diachi, email, sdt, tinhtrang;

    while (file >> MSSV) {
        file.ignore(); 

        getline(file, hoten, ',');
        getline(file, ngaysinh, ',');
        getline(file, gioitinh, ',');
        getline(file, khoa, ',');
        file >> nienkhoa;
        file.ignore(); 

        getline(file, chuongtrinh, ',');
        getline(file, diachi, ',');
        getline(file, email, ',');
        getline(file, sdt, ',');
        getline(file, tinhtrang);

        studentList[MSSV] = Student(MSSV, hoten, ngaysinh, gioitinh, khoa, nienkhoa, chuongtrinh, diachi, email, sdt, tinhtrang);
    }

    file.close();
    cout << "Doc danh sach sinh vien thanh cong!\n";
}
void themSinhVien() {
    int MSSV, nienkhoa;
    string hoten, ngaysinh, gioitinh, khoa, chuongtrinh, diachi, email, sdt, tinhtrang;

    cout << "Nhap MSSV: ";
    cin >> MSSV;
    cin.ignore();

    if (studentList.find(MSSV) != studentList.end()) {
        cout << "MSSV da ton tai!\n";
        return;
    }

    cout << "Nhap ho ten: ";
    getline(cin, hoten);

    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    getline(cin, ngaysinh);

    cout << "Nhap gioi tinh: ";
    getline(cin, gioitinh);

    vector<string> danhSachKhoa = { "Khoa Luat", "Khoa Tieng Anh thuong mai", "Khoa Tieng Nhat", "Khoa Tieng Phap" };
    while (true) {
        cout << "Nhap khoa: ";
        getline(cin, khoa);
        if (find(danhSachKhoa.begin(), danhSachKhoa.end(), khoa) != danhSachKhoa.end()) break;
        cout << "Khoa khong hop le! Vui long nhap lai.\n";
    }

    cout << "Nhap nien khoa: ";
    cin >> nienkhoa;
    cin.ignore();

    cout << "Nhap chuong trinh: ";
    getline(cin, chuongtrinh);

    cout << "Nhap dia chi: ";
    getline(cin, diachi);

    while (true) {
        cout << "Nhap email: ";
        getline(cin, email);
        if (email.find('@') != string::npos && email.find('.') != string::npos) break;
        cout << "Email khong hop le! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap so dien thoai: ";
        getline(cin, sdt);
        if (all_of(sdt.begin(), sdt.end(), ::isdigit) && sdt.length() >= 9 && sdt.length() <= 11) break;
        cout << "So dien thoai khong hop le! Vui long nhap lai.\n";
    }

    vector<string> danhSachTinhTrang = { "Dang hoc", "Da tot nghiep", "Da thoi hoc", "Tam dung hoc" };
    while (true) {
        cout << "Nhap tinh trang: ";
        getline(cin, tinhtrang);
        if (find(danhSachTinhTrang.begin(), danhSachTinhTrang.end(), tinhtrang) != danhSachTinhTrang.end()) break;
        cout << "Tinh trang khong hop le! Vui long nhap lai.\n";
    }

    Student sv(MSSV, hoten, ngaysinh, gioitinh, khoa, nienkhoa, chuongtrinh, diachi, email, sdt, tinhtrang);
    studentList[MSSV] = sv;
    cout << "Them sinh vien thanh cong!\n";
}

void xoaSinhVien() {
    int MSSV;
    cout << "Nhap MSSV can xoa: ";
    cin >> MSSV;

    if (studentList.erase(MSSV)) {
        cout << "Xoa sinh vien thanh cong!\n";
    }
    else {
        cout << "Khong tim thay sinh vien!\n";
    }
}

void capNhatSinhVien() {
    int MSSV;
    cout << "Nhap MSSV can cap nhat: ";
    cin >> MSSV;
    cin.ignore();

    if (studentList.find(MSSV) == studentList.end()) {
        cout << "Khong tim thay sinh vien!\n";
        return;
    }

    string hoten, ngaysinh, gioitinh, khoa, chuongtrinh, diachi, email, sdt, tinhtrang;
    int nienkhoa;

    cout << "Nhap ho ten moi: ";
    getline(cin, hoten);

    cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
    getline(cin, ngaysinh);

    cout << "Nhap gioi tinh moi: ";
    getline(cin, gioitinh);

    vector<string> danhSachKhoa = { "Khoa Luat", "Khoa Tieng Anh thuong mai", "Khoa Tieng Nhat", "Khoa Tieng Phap" };
    while (true) {
        cout << "Nhap khoa moi: ";
        getline(cin, khoa);
        if (find(danhSachKhoa.begin(), danhSachKhoa.end(), khoa) != danhSachKhoa.end()) break;
        cout << "Khoa khong hop le! Vui long nhap lai.\n";
    }

    cout << "Nhap nien khoa moi: ";
    cin >> nienkhoa;
    cin.ignore();

    cout << "Nhap chuong trinh moi: ";
    getline(cin, chuongtrinh);

    cout << "Nhap dia chi moi: ";
    getline(cin, diachi);

    while (true) {
        cout << "Nhap email: ";
        getline(cin, email);
        if (email.find('@') != string::npos && email.find('.') != string::npos) break;
        cout << "Email khong hop le! Vui long nhap lai.\n";
    }

    while (true) {
        cout << "Nhap so dien thoai: ";
        getline(cin, sdt);
        if (all_of(sdt.begin(), sdt.end(), ::isdigit) && sdt.length() >= 9 && sdt.length() <= 11) break;
        cout << "So dien thoai khong hop le! Vui long nhap lai.\n";
    }

    vector<string> danhSachTinhTrang = { "Dang hoc", "Da tot nghiep", "Da thoi hoc", "Tam dung hoc" };
    while (true) {
        cout << "Nhap tinh trang moi: ";
        getline(cin, tinhtrang);
        if (find(danhSachTinhTrang.begin(), danhSachTinhTrang.end(), tinhtrang) != danhSachTinhTrang.end()) break;
        cout << "Tinh trang khong hop le! Vui long nhap lai.\n";
    }

    studentList[MSSV] = Student(MSSV, hoten, ngaysinh, gioitinh, khoa, nienkhoa, chuongtrinh, diachi, email, sdt, tinhtrang);
    cout << "Cap nhat thong tin thanh cong!\n";
}

void timKiemSinhVienTheoMSSV() {
    int MSSV;
    cout << "Nhap MSSV can tim: ";
    cin >> MSSV;

    auto it = studentList.find(MSSV);
    if (it != studentList.end()) {
        it->second.display();
    }
    else {
        cout << "Khong tim thay sinh vien!\n";
    }
}

void timKiemSinhVienTheoHoTen() {
    string hoten;
    cout << "Nhap ho ten can tim: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, hoten);

    bool found = false;
    for (const auto& pair : studentList) {
        if (pair.second.getHoten() == hoten) {
            pair.second.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay sinh vien!\n";
    }
}

void hienThiDanhSachSinhVien() {
    if (studentList.empty()) {
        cout << "Danh sach sinh vien rong!\n";
        return;
    }

    for (const auto& pair : studentList) {
        pair.second.display();
        cout << "----------------------\n";
    }
}

void menu() {
    while (true) {
        cout << "\n=== CHUONG TRINH QUAN LY SINH VIEN ===\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Xoa sinh vien\n";
        cout << "3. Cap nhat sinh vien\n";
        cout << "4. Tim kiem sinh vien theo MSSV\n";
        cout << "5. Tim kiem sinh vien theo ho ten\n";
        cout << "6. Hien thi danh sach sinh vien\n";
        cout << "7. Luu danh sach sinh vien vao file\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            themSinhVien();
            break;
        case 2:
            xoaSinhVien();
            break;
        case 3:
            capNhatSinhVien();
            break;
        case 4:
            timKiemSinhVienTheoMSSV();
            break;
        case 5:
            timKiemSinhVienTheoHoTen();
            break;
        case 6:
            hienThiDanhSachSinhVien();
            break;
        case 7:
            luuDanhSachSinhVien();
            break;
        case 0:
            luuDanhSachSinhVien();
            cout << "Thoat chuong trinh!\n";
            return;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    }
}

int main() {
    docDanhSachSinhVien();
    menu();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
