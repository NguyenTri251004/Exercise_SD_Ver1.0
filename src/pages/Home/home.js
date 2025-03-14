import "./home.scss";
import { useState, useEffect } from "react";
import jsPDF from "jspdf";

const CONFIG = {
  emailDomain: "@student.university.edu.vn", 
  phoneRegex: /^(0[3|5|7|8|9]|(\+84))[0-9]{8}$/, 
  statusTransitions: {
    "Đang học": ["Bảo lưu", "Tốt nghiệp", "Đình chỉ"],
    "Bảo lưu": ["Đang học", "Đình chỉ"],
    "Tốt nghiệp": [], 
    "Đình chỉ": ["Đang học"]
  },
  deleteTimeLimit: 30 * 60 * 1000, 
  universityName: "Trường Đại học Khoa học tự nhiên",
  universityAddress: "227 Đường Nguyễn Văn Cừ, Quận 5, TP.HCM",
  universityPhone: "(028) 62884499",
  universityEmail: "info@hcmus.edu.vn"
};
const RULES = {
  uniqueMssv: true,
  emailDomain: true,
  phoneFormat: true,
  statusTransition: true,
  deleteTimeLimit: true
};
function Home() {
  const [modal, setModal] = useState(null);
  const [studentData, setStudentData] = useState({
    mssv: "",
    name: "",
    dob: "",
    gender: "",
    department: "",
    course: "",
    program: "",
    address: "",
    email: "",
    phone: "",
    status: ""
  });
  const [deleteMssv, setDeleteMssv] = useState("");
  const [updateMssv, setUpdateMssv] = useState("");
  const [searchQuery, setSearchQuery] = useState("");
  const [searchDepartment, setSearchDepartment] = useState("");
  const [searchResults, setSearchResults] = useState([]);
  const [departments, setDepartments] = useState([]);
  const [studentStatuses, setStudentStatuses] = useState([]);
  const [programs, setPrograms] = useState([]);
  const [newOption, setNewOption] = useState("");
  const [editOptionType, setEditOptionType] = useState("");
  const [selectedOption, setSelectedOption] = useState("");
  const [importFile, setImportFile] = useState(null);
  const [logs, setLogs] = useState([]);
  const [existingMssvList, setExistingMssvList] = useState([])
  const [certificatePurpose, setCertificatePurpose] = useState("");
  const [selectedStudent, setSelectedStudent] = useState(null); // State để lưu sinh viên được chọn
  const [allStudents, setAllStudents] = useState([])

  const appVersion = "4.0"; 
  const buildDate = new Date().toISOString().split('T')[0];

  const logAction = (action, details) => {
    const timestamp = new Date().toISOString();
    const logEntry = { timestamp, action, details };
    setLogs(prevLogs => [...prevLogs, logEntry]);
    console.log(`[${timestamp}] ${action}:`, details);
  };

  useEffect(() => {
    fetchDepartments();
    fetchStatuses();
    fetchPrograms();
    fetchExistingMssv();
    fetchAllStudents();
  }, []);
  const fetchAllStudents = async () => {
    try {
      const response = await fetch("http://localhost:3002/students");
      const data = await response.json();
      setAllStudents(data);
    } catch (error) {
      console.error("Lỗi khi tải danh sách sinh viên:", error);
    }
  };
  const fetchExistingMssv = async () => {
    try {
      const response = await fetch("http://localhost:3002/students");
      const data = await response.json();
      setExistingMssvList(data.map(student => student.mssv));
    } catch (error) {
      console.error("Lỗi khi tải danh sách MSSV:", error);
    }
  };
  const fetchDepartments = async () => {
    try {
      const response = await fetch("http://localhost:3002/departments");
      const data = await response.json();
      setDepartments(data.map(item => item.name));
      logAction("FETCH_DEPARTMENTS", { status: "success", count: data.length });
    } catch (error) {
      logAction("FETCH_DEPARTMENTS", { status: "error", error: error.message });
      console.error("Lỗi khi tải danh sách khoa:", error);
    }
  };

  const fetchStatuses = async () => {
    try {
      const response = await fetch("http://localhost:3002/statuses");
      const data = await response.json();
      setStudentStatuses(data.map(item => item.name));
      logAction("FETCH_STATUSES", { status: "success", count: data.length });
    } catch (error) {
      logAction("FETCH_STATUSES", { status: "error", error: error.message });
      console.error("Lỗi khi tải danh sách tình trạng:", error);
    }
  };

  const fetchPrograms = async () => {
    try {
      const response = await fetch("http://localhost:3002/programs");
      const data = await response.json();
      setPrograms(data.map(item => item.name));
      logAction("FETCH_PROGRAMS", { status: "success", count: data.length });
    } catch (error) {
      logAction("FETCH_PROGRAMS", { status: "error", error: error.message });
      console.error("Lỗi khi tải danh sách chương trình:", error);
    }
  };

  const validateStudentData = () => {
    const { mssv, email, phone, status } = studentData;

    if (RULES.uniqueMssv && !/^\d+$/.test(mssv)) {
      alert("MSSV phải là số!");
      return false;
    }
    if (RULES.uniqueMssv && modal === "addModal" && existingMssvList.includes(mssv)) {
      alert("MSSV đã tồn tại!");
      return false;
    }
    if (RULES.emailDomain && !email.endsWith(CONFIG.emailDomain)) {
      alert(`Email phải có đuôi ${CONFIG.emailDomain}!`);
      return false;
    }
    if (RULES.phoneFormat && !CONFIG.phoneRegex.test(phone)) {
      alert("Số điện thoại không đúng định dạng!");
      return false;
    }
    if (RULES.statusTransition && modal === "updateModal" && updateMssv) {
      const currentStudent = searchResults.find(s => s.mssv === updateMssv);
      if (currentStudent && currentStudent.status !== status) {
        const allowedTransitions = CONFIG.statusTransitions[currentStudent.status] || [];
        if (!allowedTransitions.includes(status)) {
          alert(`Không thể chuyển từ "${currentStudent.status}" sang "${status}"!`);
          return false;
        }
      }
    }
    return true;
  }

  const handleChange = (e) => {
    setStudentData({ ...studentData, [e.target.name]: e.target.value });
  };

  const handleDeleteChange = (e) => {
    setDeleteMssv(e.target.value);
  };

  const handleUpdateMssvChange = (e) => {
    setUpdateMssv(e.target.value);
  };

  const handleSearchChange = (e) => {
    setSearchQuery(e.target.value);
  };

  const handleSearchDepartmentChange = (e) => {
    setSearchDepartment(e.target.value);
  };

  const handleNewOptionChange = (e) => {
    setNewOption(e.target.value);
  };

  const handleSelectedOptionChange = (e) => {
    setSelectedOption(e.target.value);
    setNewOption(e.target.value);
  };

  const handleImportFileChange = (e) => {
    setImportFile(e.target.files[0]);
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!validateStudentData()) return;

    try {
      const response = await fetch("http://localhost:3002/students", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(studentData),
      });

      if (response.ok) {
        logAction("ADD_STUDENT", { status: "success", student: studentData });
        alert("Thêm sinh viên thành công!");
        setExistingMssvList([...existingMssvList, studentData.mssv]); // Cập nhật danh sách MSSV
        closeModal();
        setStudentData({
          mssv: "", name: "", dob: "", gender: "", department: "", course: "",
          program: "", address: "", email: "", phone: "", status: ""
        });
      } else {
        throw new Error("Có lỗi xảy ra khi thêm sinh viên");
      }
    } catch (error) {
      logAction("ADD_STUDENT", { status: "error", error: error.message });
      alert("Lỗi kết nối đến JSON Server!");
      console.error(error);
    }
  }

  const handleDeleteSubmit = async (e) => {
    e.preventDefault();

    try {
      const response = await fetch("http://localhost:3002/students");
      const students = await response.json();
      const studentToDelete = students.find(student => student.mssv === deleteMssv);

      if (!studentToDelete) {
        alert("Không tìm thấy sinh viên với MSSV này!");
        return;
      }

      if (RULES.deleteTimeLimit) {
        const createdAt = new Date(studentToDelete.createdAt).getTime();
        const now = new Date().getTime();
        if (now - createdAt > CONFIG.deleteTimeLimit) {
          logAction("DELETE_STUDENT", { status: "error", message: "Quá thời gian cho phép xóa", mssv: deleteMssv });
          alert("Không thể xóa! Sinh viên đã được tạo quá 30 phút.");
          return;
        }
      }

      const deleteResponse = await fetch(`http://localhost:3002/students/${studentToDelete.id}`, {
        method: "DELETE",
      });

      if (deleteResponse.ok) {
        setExistingMssvList(prev => prev.filter(mssv => mssv !== deleteMssv));
        alert("Xóa sinh viên thành công!");
        closeModal();
        setDeleteMssv("");
      } else {
        alert("Xóa thất bại!");
      }
    } catch (error) {
      alert("Lỗi kết nối đến JSON Server!");
      console.error(error);
    }
  };

  const handleUpdateSubmit = async (e) => {
    e.preventDefault();
  
    try {
      const response = await fetch("http://localhost:3002/students");
      const students = await response.json();
      const studentToUpdate = students.find(student => student.mssv === updateMssv);
  
      if (!studentToUpdate) {
        logAction("UPDATE_STUDENT", { status: "error", message: "Không tìm thấy sinh viên", mssv: updateMssv });
        alert("Không tìm thấy sinh viên với MSSV này!");
        return;
      }
  
      // Kiểm tra xem MSSV mới có trùng với MSSV khác không
      if (studentData.mssv !== updateMssv && existingMssvList.includes(studentData.mssv)) {
        logAction("UPDATE_STUDENT", { 
          status: "error", 
          message: "MSSV đã tồn tại", 
          mssv: studentData.mssv 
        });
        alert("MSSV đã tồn tại! Vui lòng chọn MSSV khác.");
        return;
      }
  
      if (!validateStudentData()) return;
  
      const updateResponse = await fetch(`http://localhost:3002/students/${studentToUpdate.id}`, {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(studentData)
      });
  
      if (updateResponse.ok) {
        logAction("UPDATE_STUDENT", { status: "success", mssv: updateMssv, updatedData: studentData });
        alert("Cập nhật thông tin sinh viên thành công!");
        // Cập nhật danh sách MSSV nếu MSSV thay đổi
        if (studentData.mssv !== updateMssv) {
          setExistingMssvList(prevList => 
            prevList.map(mssv => mssv === updateMssv ? studentData.mssv : mssv)
          );
        }
        closeModal();
        setUpdateMssv("");
        setStudentData({
          mssv: "", name: "", dob: "", gender: "", department: "", course: "",
          program: "", address: "", email: "", phone: "", status: ""
        });
      } else {
        throw new Error("Cập nhật thất bại");
      }
    } catch (error) {
      logAction("UPDATE_STUDENT", { status: "error", error: error.message });
      alert("Lỗi kết nối đến JSON Server!");
      console.error(error);
    }
  };

  const loadStudentData = async () => {
    try {
      const response = await fetch("http://localhost:3002/students");
      const students = await response.json();
      const student = students.find(student => student.mssv === updateMssv);

      if (student) {
        setStudentData(student);
        logAction("LOAD_STUDENT_DATA", { status: "success", mssv: updateMssv });
      } else {
        logAction("LOAD_STUDENT_DATA", { status: "error", message: "Không tìm thấy sinh viên", mssv: updateMssv });
        alert("Không tìm thấy sinh viên với MSSV này!");
      }
    } catch (error) {
      logAction("LOAD_STUDENT_DATA", { status: "error", error: error.message });
      alert("Lỗi kết nối đến JSON Server!");
      console.error(error);
    }
  };

  const handleSearchSubmit = async (e) => {
    e.preventDefault();

    try {
      const response = await fetch("http://localhost:3002/students");
      const students = await response.json();
      
      let results = students;
      
      if (searchDepartment) {
        results = results.filter(student => student.department === searchDepartment);
      }

      if (searchQuery) {
        results = results.filter(student => 
          student.mssv.includes(searchQuery) || 
          student.name.toLowerCase().includes(searchQuery.toLowerCase())
        );
      }

      if (results.length > 0) {
        logAction("SEARCH_STUDENTS", { status: "success", query: { searchDepartment, searchQuery }, resultCount: results.length });
        setSearchResults(results);
      } else {
        logAction("SEARCH_STUDENTS", { status: "success", query: { searchDepartment, searchQuery }, resultCount: 0 });
        setSearchResults([]);
        alert("Không tìm thấy sinh viên nào phù hợp!");
      }
    } catch (error) {
      logAction("SEARCH_STUDENTS", { status: "error", error: error.message });
      alert("Lỗi kết nối đến JSON Server!");
      console.error(error);
    }
  };

  const handleEditOptionsSubmit = async (e) => {
    e.preventDefault();
    if (!newOption.trim()) {
      alert("Vui lòng nhập giá trị!");
      return;
    }

    const endpoint = editOptionType === "department" ? "departments" :
                    editOptionType === "status" ? "statuses" : "programs";
    const currentList = editOptionType === "department" ? departments :
                       editOptionType === "status" ? studentStatuses : programs;

    try {
      if (selectedOption) {
        const response = await fetch(`http://localhost:3002/${endpoint}?name=${selectedOption}`);
        const data = await response.json();
        if (data.length > 0) {
          const itemId = data[0].id;
          if (newOption !== selectedOption) {
            await fetch(`http://localhost:3002/${endpoint}/${itemId}`, {
              method: "PUT",
              headers: { "Content-Type": "application/json" },
              body: JSON.stringify({ name: newOption })
            });
            alert("Cập nhật thành công!");
          }
        }
      } else {
        await fetch(`http://localhost:3002/${endpoint}`, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ name: newOption })
        });
        alert("Thêm mới thành công!");
      }

      if (editOptionType === "department") fetchDepartments();
      else if (editOptionType === "status") fetchStatuses();
      else fetchPrograms();
      closeModal();
    } catch (error) {
      alert("Lỗi khi cập nhật dữ liệu!");
      console.error(error);
    }
  };

  const handleDeleteOption = async () => {
    if (!selectedOption) {
      alert("Vui lòng chọn mục để xóa!");
      return;
    }

    const endpoint = editOptionType === "department" ? "departments" :
                    editOptionType === "status" ? "statuses" : "programs";

    try {
      const response = await fetch(`http://localhost:3002/students`);
      const students = await response.json();
      const isInUse = students.some(student => 
        (editOptionType === "department" && student.department === selectedOption) ||
        (editOptionType === "status" && student.status === selectedOption) ||
        (editOptionType === "program" && student.program === selectedOption)
      );

      if (isInUse) {
        alert(`Không thể xóa ${selectedOption} vì đang được sử dụng!`);
        return;
      }

      const optionResponse = await fetch(`http://localhost:3002/${endpoint}?name=${selectedOption}`);
      const data = await optionResponse.json();
      if (data.length > 0) {
        await fetch(`http://localhost:3002/${endpoint}/${data[0].id}`, {
          method: "DELETE"
        });
        alert("Xóa thành công!");
        if (editOptionType === "department") fetchDepartments();
        else if (editOptionType === "status") fetchStatuses();
        else fetchPrograms();
        closeModal();
      }
    } catch (error) {
      alert("Lỗi khi xóa!");
      console.error(error);
    }
  };

  const handleImportSubmit = async (e) => {
    e.preventDefault();
    if (!importFile) {
      logAction("IMPORT_DATA", { status: "error", message: "Chưa chọn file" });
      alert("Vui lòng chọn file để import!");
      return;
    }

    const fileReader = new FileReader();
    fileReader.onload = async (event) => {
      try {
        let students;
        if (importFile.name.endsWith(".csv")) {
          const csvText = event.target.result;
          students = csvToArray(csvText);
        } else if (importFile.name.endsWith(".json")) {
          students = JSON.parse(event.target.result);
        } else {
          throw new Error("Định dạng file không hỗ trợ");
        }

        // Kiểm tra MSSV trùng lặp trong file import
        const importMssvList = students.map(s => s.mssv);
        const duplicates = importMssvList.filter((mssv, index) => 
          importMssvList.indexOf(mssv) !== index || existingMssvList.includes(mssv)
        );
        
        if (duplicates.length > 0) {
          logAction("IMPORT_DATA", { status: "error", message: "Có MSSV trùng lặp", duplicates });
          alert(`Có MSSV trùng lặp: ${duplicates.join(", ")}`);
          return;
        }

        // Kiểm tra định dạng dữ liệu import
        for (const student of students) {
          if (!student.email.endsWith(CONFIG.emailDomain) || 
              !CONFIG.phoneRegex.test(student.phone)) {
            logAction("IMPORT_DATA", { status: "error", message: "Dữ liệu không hợp lệ", student });
            alert(`Dữ liệu không hợp lệ cho sinh viên ${student.mssv}`);
            return;
          }
        }

        for (const student of students) {
          await fetch("http://localhost:3002/students", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify(student),
          });
        }
        
        setExistingMssvList([...existingMssvList, ...importMssvList]);
        logAction("IMPORT_DATA", { status: "success", fileName: importFile.name, count: students.length });
        alert("Import dữ liệu thành công!");
        closeModal();
      } catch (error) {
        logAction("IMPORT_DATA", { status: "error", fileName: importFile.name, error: error.message });
        alert("Lỗi khi import dữ liệu!");
        console.error(error);
      }
    };

    if (importFile.name.endsWith(".csv") || importFile.name.endsWith(".json")) {
      fileReader.readAsText(importFile);
    }
  }

  const csvToArray = (csvText) => {
    const rows = csvText.split("\n").filter(row => row.trim() !== "");
    const headers = rows[0].split(",").map(header => header.trim());
    const result = [];

    for (let i = 1; i < rows.length; i++) {
      const values = rows[i].split(",").map(value => value.trim());
      const obj = {};
      headers.forEach((header, index) => {
        obj[header] = values[index];
      });
      result.push(obj);
    }
    return result;
  };

  const handleExportSubmit = async (format) => {
    try {
      const response = await fetch("http://localhost:3002/students");
      const students = await response.json();

      if (format === "csv") {
        const csvContent = [
          "mssv,name,dob,gender,department,course,program,address,email,phone,status",
          ...students.map(student => 
            `${student.mssv},${student.name},${student.dob},${student.gender},${student.department},${student.course},${student.program},${student.address},${student.email},${student.phone},${student.status}`
          )
        ].join("\n");
        downloadFile(csvContent, "students.csv", "text/csv");
      } else if (format === "json") {
        const jsonContent = JSON.stringify(students, null, 2);
        downloadFile(jsonContent, "students.json", "application/json");
      }
      logAction("EXPORT_DATA", { status: "success", format, count: students.length });
      alert("Export dữ liệu thành công!");
      closeModal();
    } catch (error) {
      logAction("EXPORT_DATA", { status: "error", format, error: error.message });
      alert("Lỗi khi export dữ liệu!");
      console.error(error);
    }
  };

  const downloadFile = (content, fileName, contentType) => {
    const blob = new Blob([content], { type: contentType });
    const url = window.URL.createObjectURL(blob);
    const link = document.createElement("a");
    link.href = url;
    link.download = fileName;
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    window.URL.revokeObjectURL(url);
  };

  const openModal = (modalId) => {
    setModal(modalId);
    if (modalId !== "searchModal") {
      setSearchResults([]);
    }
    if (modalId.startsWith("edit")) {
      setEditOptionType(modalId.replace("edit", "").toLowerCase());
    }
  };

  const closeModal = () => {
    setModal(null);
    setSearchResults([]);
    setSearchQuery("");
    setSearchDepartment("");
    setNewOption("");
    setEditOptionType("");
    setSelectedOption("");
    setImportFile(null);
    setCertificatePurpose("");
    setSelectedStudent(null); // Reset sinh viên được chọn
  };

  const handleStudentSelect = (e) => {
    const studentId = e.target.value;
    const student = allStudents.find(s => s.id === studentId);
    setSelectedStudent(student);
    setStudentData(student || {
      mssv: "", name: "", dob: "", gender: "", department: "", course: "",
      program: "", address: "", email: "", phone: "", status: "", createdAt: ""
    });
  };

  const generateCertificate = (student, format) => {
    if (!student) {
      alert("Vui lòng chọn sinh viên trước khi xuất giấy xác nhận!");
      return;
    }

    const currentDate = new Date().toLocaleDateString("vi-VN");
    const expiryDate = new Date();
    expiryDate.setMonth(expiryDate.getMonth() + 6);

    const content = `
      <div style="font-family: Arial, sans-serif; max-width: 800px; margin: 0 auto;">
        <div style="text-align: center;">
          <h2>${CONFIG.universityName}</h2>
          <h3>PHÒNG ĐÀO TẠO</h3>
          <p>📍 ${CONFIG.universityAddress}</p>
          <p>📞 ${CONFIG.universityPhone} | 📧 ${CONFIG.universityEmail}</p>
        </div>
        <hr />
        <h2 style="text-align: center;">GIẤY XÁC NHẬN TÌNH TRẠNG SINH VIÊN</h2>
        <p>Trường ${CONFIG.universityName} xác nhận:</p>
        <h3>1. Thông tin sinh viên:</h3>
        <ul>
          <li><strong>Họ và tên:</strong> ${student.name}</li>
          <li><strong>Mã số sinh viên:</strong> ${student.mssv}</li>
          <li><strong>Ngày sinh:</strong> ${new Date(student.dob).toLocaleDateString("vi-VN")}</li>
          <li><strong>Giới tính:</strong> ${student.gender}</li>
          <li><strong>Khoa:</strong> ${student.department}</li>
          <li><strong>Chương trình đào tạo:</strong> ${student.program}</li>
          <li><strong>Khóa:</strong> ${student.course}</li>
        </ul>
        <h3>2. Tình trạng sinh viên hiện tại:</h3>
        <p>- ${student.status}</p>
        <h3>3. Mục đích xác nhận:</h3>
        <p>- ${certificatePurpose || "Không xác định"}</p>
        <h3>4. Thời gian cấp giấy:</h3>
        <p>- Giấy xác nhận có hiệu lực đến ngày: ${expiryDate.toLocaleDateString("vi-VN")}</p>
        <p style="text-align: right;">📅 Ngày cấp: ${currentDate}</p>
        <p style="text-align: right;"><strong>Trưởng Phòng Đào Tạo</strong><br>(Ký, ghi rõ họ tên, đóng dấu)</p>
      </div>
    `;

    if (format === "html") {
      const blob = new Blob([content], { type: "text/html" });
      const url = window.URL.createObjectURL(blob);
      const link = document.createElement("a");
      link.href = url;
      link.download = `XacNhan_${student.mssv}.html`;
      link.click();
      window.URL.revokeObjectURL(url);
    } else if (format === "pdf") {
      const doc = new jsPDF();
      doc.html(content, {
        callback: function (doc) {
          doc.save(`XacNhan_${student.mssv}.pdf`);
        },
        x: 10,
        y: 10,
        width: 190,
        windowWidth: 800
      });
    }
  };

  const handleExportCertificate = (student) => {
    setModal("certificateModal");
    setStudentData(student);
  }

  return (
    <div>
      <div className="header">
        <h1>{CONFIG.universityName}</h1>
        <span>Phần mềm quản lý sinh viên</span>
      </div>
      <div className="menu">
        <div className="menu__add">
          <span>Thêm sinh viên:</span>
          <button onClick={() => openModal("addModal")}>Thêm</button>
        </div>
        <div className="menu__delete">
          <span>Xóa sinh viên:</span>
          <button onClick={() => openModal("deleteModal")}>Xóa</button>
        </div>
        <div className="menu__update">
          <span>Cập nhật thông tin sinh viên:</span>
          <button onClick={() => openModal("updateModal")}>Cập nhật</button>
        </div>
        <div className="menu__search">
          <span>Tìm kiếm thông tin sinh viên:</span>
          <button onClick={() => openModal("searchModal")}>Tìm kiếm</button>
        </div>
        <div className="menu__edit-options">
          <span>Quản lý danh sách:</span>
          <button onClick={() => openModal("editDepartment")}>Quản lý Khoa</button>
          <button onClick={() => openModal("editStatus")}>Quản lý Tình trạng</button>
          <button onClick={() => openModal("editProgram")}>Quản lý Chương trình</button>
        </div>
        <div className="menu__certificate">
          <span>Xuất giấy xác nhận:</span>
          <button onClick={() => openModal("certificateModal")}>Xuất giấy xác nhận</button>
        </div>
        <div className="menu__import-export">
          <span>Import/Export dữ liệu:</span>
          <button onClick={() => openModal("importModal")}>Import</button>
          <button onClick={() => openModal("exportModal")}>Export</button>
        </div>
        <div className="menu__version">
          <span>Thông tin ứng dụng:</span>
          <button onClick={() => openModal("versionModal")}>Xem Version</button>
        </div>
      </div>

      {modal && (
        <div className="modal">
          <div className="modal-content">
            <span className="close" onClick={closeModal}>×</span>
            <h2>
              {modal === "addModal" ? "Thêm sinh viên" :
               modal === "deleteModal" ? "Xóa sinh viên" :
               modal === "updateModal" ? "Cập nhật sinh viên" :
               modal === "searchModal" ? "Tìm kiếm sinh viên" :
               modal === "importModal" ? "Import dữ liệu" :
               modal === "exportModal" ? "Export dữ liệu" :
               modal === "versionModal" ? "Thông tin ứng dụng" :
               modal === "certificateModal" ? "Xuất giấy xác nhận" :
               modal === "editDepartment" ? "Quản lý Khoa" :
               modal === "editStatus" ? "Quản lý Tình trạng" :
               "Quản lý Chương trình"}
            </h2>
            <form onSubmit={
              modal === "deleteModal" ? handleDeleteSubmit : 
              modal === "updateModal" ? handleUpdateSubmit : 
              modal === "searchModal" ? handleSearchSubmit :
              modal === "importModal" ? handleImportSubmit :
              modal.startsWith("edit") ? handleEditOptionsSubmit :
              handleSubmit
            }>
              {modal === "addModal" && (
                <div>
                  <input type="text" name="mssv" placeholder="MSSV" value={studentData.mssv} onChange={handleChange} required />
                  <input type="text" name="name" placeholder="Họ tên" value={studentData.name} onChange={handleChange} required />
                  <input type="date" name="dob" placeholder="Ngày tháng năm sinh" value={studentData.dob} onChange={handleChange} required />
                  <div className="form-group">
                    <label>Giới tính:</label>
                    <select name="gender" value={studentData.gender} onChange={handleChange} required>
                      <option value="">Chọn giới tính</option>
                      <option value="Nam">Nam</option>
                      <option value="Nữ">Nữ</option>
                    </select>
                  </div>
                  <div className="form-group">
                    <label>Khoa:</label>
                    <select name="department" value={studentData.department} onChange={handleChange} required>
                      <option value="">Chọn khoa</option>
                      {departments.map((dept, index) => (
                        <option key={index} value={dept}>{dept}</option>
                      ))}
                    </select>
                  </div>
                  <input type="text" name="course" placeholder="Khóa" value={studentData.course} onChange={handleChange} required />
                  <div className="form-group">
                    <label>Chương trình:</label>
                    <select name="program" value={studentData.program} onChange={handleChange} required>
                      <option value="">Chọn chương trình</option>
                      {programs.map((prog, index) => (
                        <option key={index} value={prog}>{prog}</option>
                      ))}
                    </select>
                  </div>
                  <input type="text" name="address" placeholder="Địa chỉ" value={studentData.address} onChange={handleChange} required />
                  <input type="email" name="email" placeholder="Email" value={studentData.email} onChange={handleChange} required />
                  <input type="text" name="phone" placeholder="Số điện thoại" value={studentData.phone} onChange={handleChange} required />
                  <div className="form-group">
                    <label>Tình trạng:</label>
                    <select name="status" value={studentData.status} onChange={handleChange} required>
                      <option value="">Chọn tình trạng</option>
                      {studentStatuses.map((status, index) => (
                        <option key={index} value={status}>{status}</option>
                      ))}
                    </select>
                  </div>
                  <button type="submit">Xác nhận</button>
                </div>
              )}

              {modal === "certificateModal" && (
                <div>
                  <div className="form-group">
                    <label>Chọn sinh viên:</label>
                    <select value={selectedStudent ? selectedStudent.id : ""} onChange={handleStudentSelect} required>
                      <option value="">Chọn sinh viên</option>
                      {allStudents.map((student) => (
                        <option key={student.id} value={student.id}>
                          {student.mssv} - {student.name}
                        </option>
                      ))}
                    </select>
                  </div>
                  {selectedStudent && (
                    <div style={{ marginTop: '20px' }}>
                      <h3>Thông tin sinh viên:</h3>
                      <p><strong>Họ và tên:</strong> {selectedStudent.name}</p>
                      <p><strong>MSSV:</strong> {selectedStudent.mssv}</p>
                      <p><strong>Ngày sinh:</strong> {new Date(selectedStudent.dob).toLocaleDateString("vi-VN")}</p>
                      <p><strong>Giới tính:</strong> {selectedStudent.gender}</p>
                      <p><strong>Khoa:</strong> {selectedStudent.department}</p>
                      <p><strong>Chương trình:</strong> {selectedStudent.program}</p>
                      <p><strong>Khóa:</strong> {selectedStudent.course}</p>
                      <p><strong>Tình trạng:</strong> {selectedStudent.status}</p>
                    </div>
                  )}
                  <div className="form-group" style={{ marginTop: '20px' }}>
                    <label>Mục đích xác nhận:</label>
                    <select value={certificatePurpose} onChange={(e) => setCertificatePurpose(e.target.value)} required>
                      <option value="">Chọn mục đích</option>
                      <option value="Xác nhận đang học để vay vốn ngân hàng">Vay vốn ngân hàng</option>
                      <option value="Xác nhận làm thủ tục tạm hoãn nghĩa vụ quân sự">Hoãn nghĩa vụ quân sự</option>
                      <option value="Xác nhận làm hồ sơ xin việc / thực tập">Xin việc/thực tập</option>
                      <option value="Khác">Khác</option>
                    </select>
                  </div>
                  <div style={{ display: 'flex', gap: '10px', marginTop: '20px' }}>
                    <button type="button" onClick={() => generateCertificate(selectedStudent, "html")}>
                      Xuất HTML
                    </button>
                    <button type="button" onClick={() => generateCertificate(selectedStudent, "pdf")}>
                      Xuất PDF
                    </button>
                  </div>
                </div>
              )}

              {/* Giữ nguyên các modal khác */}
              {modal === "deleteModal" && (
                <div>
                  <input type="text" placeholder="Nhập MSSV để xóa" value={deleteMssv} onChange={(e) => setDeleteMssv(e.target.value)} required />
                  <button type="submit">Xác nhận</button>
                </div>
              )}
              {modal === "updateModal" && (
                <div>
                  <input type="text" placeholder="Nhập MSSV cần cập nhật" value={updateMssv} onChange={(e) => setUpdateMssv(e.target.value)} required />
                  <button type="button" onClick={loadStudentData} style={{ marginBottom: '10px' }}>Tìm sinh viên</button>
                  <input type="text" name="mssv" placeholder="MSSV" value={studentData.mssv} onChange={handleChange} required />
                  <input type="text" name="name" placeholder="Họ tên" value={studentData.name} onChange={handleChange} required />
                  <input type="date" name="dob" placeholder="Ngày tháng năm sinh" value={studentData.dob} onChange={handleChange} required />
                  <div className="form-group">
                    <label>Giới tính:</label>
                    <select name="gender" value={studentData.gender} onChange={handleChange} required>
                      <option value="">Chọn giới tính</option>
                      <option value="Nam">Nam</option>
                      <option value="Nữ">Nữ</option>
                    </select>
                  </div>
                  <div className="form-group">
                    <label>Khoa:</label>
                    <select name="department" value={studentData.department} onChange={handleChange} required>
                      <option value="">Chọn khoa</option>
                      {departments.map((dept, index) => (
                        <option key={index} value={dept}>{dept}</option>
                      ))}
                    </select>
                  </div>
                  <input type="text" name="course" placeholder="Khóa" value={studentData.course} onChange={handleChange} required />
                  <div className="form-group">
                    <label>Chương trình:</label>
                    <select name="program" value={studentData.program} onChange={handleChange} required>
                      <option value="">Chọn chương trình</option>
                      {programs.map((prog, index) => (
                        <option key={index} value={prog}>{prog}</option>
                      ))}
                    </select>
                  </div>
                  <input type="text" name="address" placeholder="Địa chỉ" value={studentData.address} onChange={handleChange} required />
                  <input type="email" name="email" placeholder="Email" value={studentData.email} onChange={handleChange} required />
                  <input type="text" name="phone" placeholder="Số điện thoại" value={studentData.phone} onChange={handleChange} required />
                  <div className="form-group">
                    <label>Tình trạng:</label>
                    <select name="status" value={studentData.status} onChange={handleChange} required>
                      <option value="">Chọn tình trạng</option>
                      {studentStatuses.map((status, index) => (
                        <option key={index} value={status}>{status}</option>
                      ))}
                    </select>
                  </div>
                  <button type="submit">Xác nhận</button>
                </div>
              )}
              {modal === "searchModal" && (
                <div>
                  <div className="form-group">
                    <label>Khoa:</label>
                    <select value={searchDepartment} onChange={(e) => setSearchDepartment(e.target.value)}>
                      <option value="">Tất cả khoa</option>
                      {departments.map((dept, index) => (
                        <option key={index} value={dept}>{dept}</option>
                      ))}
                    </select>
                  </div>
                  <input type="text" placeholder="Nhập MSSV hoặc tên để tìm kiếm" value={searchQuery} onChange={(e) => setSearchQuery(e.target.value)} />
                  <button type="submit">Xác nhận</button>
                  {searchResults.length > 0 && (
                    <div className="search-results" style={{ marginTop: '20px' }}>
                      <h3>Kết quả tìm kiếm:</h3>
                      <table style={{ width: '100%', borderCollapse: 'collapse' }}>
                        <thead>
                          <tr>
                            <th style={{ border: '1px solid #ddd', padding: '8px' }}>MSSV</th>
                            <th style={{ border: '1px solid #ddd', padding: '8px' }}>Họ tên</th>
                            <th style={{ border: '1px solid #ddd', padding: '8px' }}>Ngày sinh</th>
                            <th style={{ border: '1px solid #ddd', padding: '8px' }}>Khoa</th>
                            <th style={{ border: '1px solid #ddd', padding: '8px' }}>Tình trạng</th>
                            <th style={{ border: '1px solid #ddd', padding: '8px' }}>Hành động</th>
                          </tr>
                        </thead>
                        <tbody>
                          {searchResults.map((student) => (
                            <tr key={student.id}>
                              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{student.mssv}</td>
                              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{student.name}</td>
                              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{student.dob}</td>
                              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{student.department}</td>
                              <td style={{ border: '1px solid #ddd', padding: '8px' }}>{student.status}</td>
                              <td style={{ border: '1px solid #ddd', padding: '8px' }}>
                                <button type="button" onClick={() => { setSelectedStudent(student); setModal("certificateModal"); }}>
                                  Xuất giấy xác nhận
                                </button>
                              </td>
                            </tr>
                          ))}
                        </tbody>
                      </table>
                    </div>
                  )}
                </div>
              )}
              {(modal === "editDepartment" || modal === "editStatus" || modal === "editProgram") && (
                <div>
                  <div className="form-group">
                    <label>Danh sách hiện tại:</label>
                    <select value={selectedOption} onChange={(e) => { setSelectedOption(e.target.value); setNewOption(e.target.value); }}>
                      <option value="">Chọn để chỉnh sửa</option>
                      {modal === "editDepartment" && departments.map((item, index) => (
                        <option key={index} value={item}>{item}</option>
                      ))}
                      {modal === "editStatus" && studentStatuses.map((item, index) => (
                        <option key={index} value={item}>{item}</option>
                      ))}
                      {modal === "editProgram" && programs.map((item, index) => (
                        <option key={index} value={item}>{item}</option>
                      ))}
                    </select>
                  </div>
                  <input type="text" placeholder={`Nhập ${modal === "editDepartment" ? "khoa" : modal === "editStatus" ? "tình trạng" : "chương trình"} mới`} value={newOption} onChange={(e) => setNewOption(e.target.value)} />
                  <button type="submit">Xác nhận</button>
                  <button type="button" onClick={handleDeleteOption}>Xóa</button>
                </div>
              )}
              {modal === "importModal" && (
                <div>
                  <input type="file" accept=".csv,.json" onChange={(e) => setImportFile(e.target.files[0])} />
                  <p style={{ marginTop: '10px' }}>Hỗ trợ định dạng: CSV, JSON</p>
                  <button type="submit">Xác nhận</button>
                </div>
              )}
              {modal === "exportModal" && (
                <div style={{ display: 'flex', gap: '10px', flexDirection: 'column' }}>
                  <button type="button" onClick={() => handleExportSubmit("csv")}>Export sang CSV</button>
                  <button type="button" onClick={() => handleExportSubmit("json")}>Export sang JSON</button>
                </div>
              )}
              {modal === "versionModal" && (
                <div style={{ textAlign: 'center' }}>
                  <p>Phiên bản: {appVersion}</p>
                  <p>Ngày build: {buildDate}</p>
                </div>
              )}
            </form>
          </div>
        </div>
      )}
    </div>
  );
}

export default Home;