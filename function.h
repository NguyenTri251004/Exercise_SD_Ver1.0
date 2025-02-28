#pragma once
#include "Student.h"
#include "Logger.h"
#include <unordered_map>
#include <vector>
#include <string>

void xemPhienBan();
bool kiemTraEmailHopLe(const std::string& email);
bool kiemTraSDTHopLe(const std::string& sdt);
bool kiemTraTinhTrang(const std::string& oldTinhTrang, const std::string& newTinhTrang);
void themKhoa();
void doiTenKhoa();
void themTinhTrang();
void doiTenTinhTrang();
void themChuongTrinh();
void doiTenChuongTrinh();
void hienThiDanhSachKhoaTinhTrangChuongTrinh();
void luuDanhSachSinhVien();
void docDanhSachSinhVien();
void luuDanhSachSinhVienCSV();
void docDanhSachSinhVienCSV();
void themSinhVien();
void xoaSinhVien();
void capNhatSinhVien();
void timKiemSinhVienTheoMSSV();
void timKiemSinhVienTheoHoTen();
void hienThiDanhSachSinhVien();
void timKiemSinhVienTheoKhoa();
void timKiemSinhVienTheoKhoaVaTen();
void menu();

