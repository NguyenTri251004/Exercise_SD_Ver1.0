// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Student.h"
#include "Logger.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>;

using namespace std;

unordered_map<int, Student> studentList;
vector<string> danhSachKhoa = { "Khoa Luat", "Khoa Tieng Anh thuong mai", "Khoa Tieng Nhat", "Khoa Tieng Phap" };
vector<string> danhSachTinhTrang = { "Dang hoc", "Da tot nghiep", "Da thoi hoc", "Tam dung hoc" };
vector<string> danhSachChuongTrinh = { "Dai hoc", "Cao dang", "Lien ket quoc te", "Dao tao tu xa" };
Logger logger("application.log");

const string version = "2.0.0";
const string buildDate = __DATE__ " " __TIME__;

void xemPhienBan() {
    cout << "Phien ban: " << version << endl;
    cout << "Ngay build: " << buildDate << endl;
}
void themKhoa() {
    string newKhoa;
    cout << "Nhap ten khoa moi: ";
    getline(cin, newKhoa);
    danhSachKhoa.push_back(newKhoa);
    cout << "Them khoa thanh cong!\n";
}

void doiTenKhoa() {
    string oldKhoa, newKhoa;
    cout << "Nhap ten khoa can doi: ";
    getline(cin, oldKhoa);
    auto it = find(danhSachKhoa.begin(), danhSachKhoa.end(), oldKhoa);
    if (it != danhSachKhoa.end()) {
        cout << "Nhap ten khoa moi: ";
        getline(cin, newKhoa);
        *it = newKhoa;
        cout << "Doi ten khoa thanh cong!\n";
    }
    else {
        cout << "Khoa khong ton tai!\n";
    }
}

void themTinhTrang() {
    string newTinhTrang;
    cout << "Nhap tinh trang sinh vien moi: ";
    getline(cin, newTinhTrang);
    danhSachTinhTrang.push_back(newTinhTrang);
    cout << "Them tinh trang thanh cong!\n";
}

void doiTenTinhTrang() {
    string oldTinhTrang, newTinhTrang;
    cout << "Nhap tinh trang can doi: ";
    getline(cin, oldTinhTrang);
    auto it = find(danhSachTinhTrang.begin(), danhSachTinhTrang.end(), oldTinhTrang);
    if (it != danhSachTinhTrang.end()) {
        cout << "Nhap tinh trang moi: ";
        getline(cin, newTinhTrang);
        *it = newTinhTrang;
        cout << "Doi ten tinh trang thanh cong!\n";
    }
    else {
        cout << "Tinh trang khong ton tai!\n";
    }
}

void themChuongTrinh() {
    string newChuongTrinh;
    cout << "Nhap chuong trinh dao tao moi: ";
    getline(cin, newChuongTrinh);
    danhSachChuongTrinh.push_back(newChuongTrinh);
    cout << "Them chuong trinh thanh cong!\n";
}

void doiTenChuongTrinh() {
    string oldChuongTrinh, newChuongTrinh;
    cout << "Nhap chuong trinh can doi: ";
    getline(cin, oldChuongTrinh);
    auto it = find(danhSachChuongTrinh.begin(), danhSachChuongTrinh.end(), oldChuongTrinh);
    if (it != danhSachChuongTrinh.end()) {
        cout << "Nhap chuong trinh moi: ";
        getline(cin, newChuongTrinh);
        *it = newChuongTrinh;
        cout << "Doi ten chuong trinh thanh cong!\n";
    }
    else {
        cout << "Chuong trinh khong ton tai!\n";
    }
}

void hienThiDanhSachKhoaTinhTrangChuongTrinh() {
    cout << "\n=== DANH SACH KHOA ===\n";
    for (const auto& khoa : danhSachKhoa) {
        cout << "- " << khoa << "\n";
    }

    cout << "\n=== DANH SACH TINH TRANG ===\n";
    for (const auto& tinhTrang : danhSachTinhTrang) {
        cout << "- " << tinhTrang << "\n";
    }

    cout << "\n=== DANH SACH CHUONG TRINH ===\n";
    for (const auto& chuongTrinh : danhSachChuongTrinh) {
        cout << "- " << chuongTrinh << "\n";
    }
}

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

void luuDanhSachSinhVienCSV() {
    ofstream file("sinhvien.csv");
    if (!file) {
        cout << "Loi mo file de luu!\n";
        return;
    }

    file << "MSSV,HoTen,NgaySinh,GioiTinh,Khoa,NienKhoa,ChuongTrinh,DiaChi,Email,SDT,TinhTrang\n";

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
    cout << "Luu danh sach sinh vien vao CSV thanh cong!\n";
}

void docDanhSachSinhVienCSV() {
    ifstream file("sinhvien.csv");
    if (!file) {
        cout << "Khong tim thay file du lieu, danh sach sinh vien se rong!\n";
        return;
    }

    studentList.clear();
    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int MSSV, nienkhoa;
        string hoten, ngaysinh, gioitinh, khoa, chuongtrinh, diachi, email, sdt, tinhtrang;

        getline(ss, token, ',');
        MSSV = stoi(token);
        getline(ss, hoten, ',');
        getline(ss, ngaysinh, ',');
        getline(ss, gioitinh, ',');
        getline(ss, khoa, ',');
        getline(ss, token, ',');
        nienkhoa = stoi(token);
        getline(ss, chuongtrinh, ',');
        getline(ss, diachi, ',');
        getline(ss, email, ',');
        getline(ss, sdt, ',');
        getline(ss, tinhtrang);

        studentList[MSSV] = Student(MSSV, hoten, ngaysinh, gioitinh, khoa, nienkhoa, chuongtrinh, diachi, email, sdt, tinhtrang);
    }

    file.close();
    cout << "Doc danh sach sinh vien tu CSV thanh cong!\n";
}

void themSinhVien() {
    int MSSV, nienkhoa;
    string hoten, ngaysinh, gioitinh, khoa, chuongtrinh, diachi, email, sdt, tinhtrang;
    logger.log(Logger::INFO, "Bat dau them sinh vien moi.");
    cout << "Nhap MSSV: ";
    cin >> MSSV;
    cin.ignore();

    if (studentList.find(MSSV) != studentList.end()) {
        logger.log(Logger::WARNING, "MSSV da ton tai : " + to_string(MSSV));
        cout << "MSSV da ton tai!\n";
        return;
    }

    cout << "Nhap ho ten: ";
    getline(cin, hoten);

    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    getline(cin, ngaysinh);

    cout << "Nhap gioi tinh: ";
    getline(cin, gioitinh);

    while (true) {
        cout << "Nhap khoa: ";
        getline(cin, khoa);
        if (find(danhSachKhoa.begin(), danhSachKhoa.end(), khoa) != danhSachKhoa.end()) break;
        cout << "Khoa khong hop le! Vui long nhap lai.\n";
    }

    cout << "Nhap nien khoa: ";
    cin >> nienkhoa;
    cin.ignore();

    while (true) {
        cout << "Nhap chuong trinh: ";
        getline(cin, chuongtrinh);
        if (find(danhSachChuongTrinh.begin(), danhSachChuongTrinh.end(), chuongtrinh) != danhSachChuongTrinh.end()) break;
        cout << "Chuong trinh khong hop le! Vui long nhap lai.\n";
    }

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

    while (true) {
        cout << "Nhap tinh trang: ";
        getline(cin, tinhtrang);
        if (find(danhSachTinhTrang.begin(), danhSachTinhTrang.end(), tinhtrang) != danhSachTinhTrang.end()) break;
        cout << "Tinh trang khong hop le! Vui long nhap lai.\n";
    }

    Student sv(MSSV, hoten, ngaysinh, gioitinh, khoa, nienkhoa, chuongtrinh, diachi, email, sdt, tinhtrang);
    studentList[MSSV] = sv;
    logger.log(Logger::INFO, "Them thanh cong sinh vien: " + hoten);
    cout << "Them sinh vien thanh cong!\n";
}

void xoaSinhVien() {
    int MSSV;
    cout << "Nhap MSSV can xoa: ";
    cin >> MSSV;

    if (studentList.erase(MSSV)) {
        logger.log(Logger::INFO, "Xoa thanh cong sinh vien MSSV: " + to_string(MSSV));
        cout << "Xoa sinh vien thanh cong!\n";
    }
    else {
        logger.log(Logger::WARNING, "Khong the xoa sinh vien MSSV: " + to_string(MSSV));
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

    while (true) {
        cout << "Nhap khoa moi: ";
        getline(cin, khoa);
        if (find(danhSachKhoa.begin(), danhSachKhoa.end(), khoa) != danhSachKhoa.end()) break;
        cout << "Khoa khong hop le! Vui long nhap lai.\n";
    }

    cout << "Nhap nien khoa moi: ";
    cin >> nienkhoa;
    cin.ignore();

    while (true) {
        cout << "Nhap chuong trinh moi: ";
        getline(cin, chuongtrinh);
        if (find(danhSachChuongTrinh.begin(), danhSachChuongTrinh.end(), chuongtrinh) != danhSachChuongTrinh.end()) break;
        cout << "Chuong trinh khong hop le! Vui long nhap lai.\n";
    }

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

void timKiemSinhVienTheoKhoa() {
    string khoa;
    cout << "Nhap khoa can tim: ";
    getline(cin, khoa);

    if (find(danhSachKhoa.begin(), danhSachKhoa.end(), khoa) == danhSachKhoa.end()) {
        cout << "Khoa khong ton tai!\n";
        return;
    }

    bool found = false;
    for (const auto& pair : studentList) {
        if (pair.second.getKhoa() == khoa) {
            pair.second.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay sinh vien trong khoa " << khoa << "!\n";
    }
}

void timKiemSinhVienTheoKhoaVaTen() {
    string khoa, hoten;
    cout << "Nhap khoa can tim: ";
    getline(cin, khoa);

    if (find(danhSachKhoa.begin(), danhSachKhoa.end(), khoa) == danhSachKhoa.end()) {
        cout << "Khoa khong ton tai!\n";
        return;
    }

    cout << "Nhap ho ten sinh vien can tim: ";
    getline(cin, hoten);

    bool found = false;
    for (const auto& pair : studentList) {
        if (pair.second.getKhoa() == khoa && pair.second.getHoten() == hoten) {
            pair.second.display();
            found = true;
        }
    }

    if (!found) {
        cout << "Khong tim thay sinh vien " << hoten << " trong khoa " << khoa << "!\n";
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
        cout << "8. Them khoa\n";
        cout << "9. Doi ten khoa\n";
        cout << "10. Them tinh trang\n";
        cout << "11. Doi ten tinh trang\n";
        cout << "12. Them chuong trinh\n";
        cout << "13. Doi ten chuong trinh\n";
        cout << "14. Xem danh sach khoa, chuong trinh, tinh trang\n";
        cout << "15. Tim kiem sinh vien theo khoa\n";
        cout << "16. Tim kiem sinh vien theo Khoa va ten\n";
        cout << "17. Luu danh sach sinh vien vao file CSV\n";
        cout << "0. Thoat\n";
        cout << "99. Xem phien ban va ngay build\n";
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
        case 8:
            themKhoa();
            break;
        case 9:
            doiTenKhoa();
            break;
        case 10:
            themTinhTrang();
            break;
        case 11:
            doiTenTinhTrang();
            break;
        case 12:
            themChuongTrinh();
            break;
        case 13:
            doiTenChuongTrinh();
            break;
        case 14:
            hienThiDanhSachKhoaTinhTrangChuongTrinh();
            break;
        case 15:
            timKiemSinhVienTheoKhoa();
            break;
        case 16:
            timKiemSinhVienTheoKhoaVaTen();
            break;
        case 17:
            luuDanhSachSinhVienCSV();
            break;
        case 0:
            luuDanhSachSinhVien();
            logger.log(Logger::INFO, "Thoat khoi chuong trinh.");
            cout << "Thoat chuong trinh!\n";
            return;
        case 99:
            xemPhienBan();
            break;
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
