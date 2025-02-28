#include <gtest/gtest.h>
#include "Student.h"

TEST(StudentTest, ConstructorAndGetters) {
    Student student(22127424, "Nguyen Van A", "01/01/2003", "Nam", "Khoa Luat", 2023, "Dai hoc", "HCM", "sv@example.edu.vn", "0123456789", "Dang hoc");

    EXPECT_EQ(student.getMSSV(), 22127424);
    EXPECT_EQ(student.getHoten(), "Nguyen Van A");
    EXPECT_EQ(student.getNgaysinh(), "01/01/2003");
    EXPECT_EQ(student.getGioitinh(), "Nam");
    EXPECT_EQ(student.getKhoa(), "Khoa Luat");
    EXPECT_EQ(student.getNienkhoa(), 2023);
    EXPECT_EQ(student.getChuongtrinh(), "Dai hoc");
    EXPECT_EQ(student.getDiachi(), "HCM");
    EXPECT_EQ(student.getEmail(), "sv@example.edu.vn");
    EXPECT_EQ(student.getSdt(), "0123456789");
    EXPECT_EQ(student.getTinhtrang(), "Dang hoc");
}



TEST(StudentTest, SettersWithValidation) {
    Student student;

    EXPECT_NO_THROW(student.setEmail("valid.email@student.university.edu.vn"));

    EXPECT_THROW(student.setEmail("invalid.email@.com"), std::invalid_argument);

    EXPECT_NO_THROW(student.setSdt("0123456789"));

    EXPECT_THROW(student.setSdt("123456789"), std::invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
