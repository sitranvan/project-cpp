#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <unordered_set>
#include <locale>

const double NGAY = 0.0416666667;
// overwrite do_thousands_sep, do_grouping
struct g3 : std::numpunct<char>
{
    char do_thousands_sep() const { return '.'; } // phân cách bằng dấu chấm (.)
    string do_grouping() const { return "\3"; }   // nhóm 3 chữ số
};
struct Date
{
    int ngay = 0;
    int thang = 0;
    int nam = 0;
};

struct NgayThamGia
{
    int ngay = 0;
    int thang = 0;
    int nam = 0;
};

struct NhanVien
{
    string maNV;
    string tenNV;
    string gioiTinh;
    Date ngaySinh;
    string queQuan;
    string email;
    string soDienThoai;
    string phongNhanSu;
    long luongCoBan = 0;
    int ngayCong = 0;
    int tangCa = 0;
    int soGioTangCa = 0;
    NgayThamGia ngaythamgia;
};
struct Node
{
    NhanVien data;
    Node* pNext = NULL;
};
struct List
{
    Node* pHead;
    Node* PTail;
};
void khoiTao(List& list)
{
    list.pHead = NULL;
    list.PTail = NULL;
}
Node* KhoiTaoNode(NhanVien x)
{
    Node* p = new Node;
    if (p == NULL)
    {
        return NULL;
    }
    else
    {
        p->data = x;
        p->pNext = NULL;
        return p;
    }
}
void themNhanVien(List& list, Node* p)
{
    if (list.pHead == NULL)
    {
        list.pHead = list.PTail = p;
    }
    else
    {
        list.PTail->pNext = p;
        list.PTail = p;
    }
}
void giaiPhong(List& list) {
    Node* k = list.pHead;
    while (k!=NULL)
    {
        k = list.pHead;
        list.pHead = list.pHead->pNext;
        delete k;
    }
}
string trim(const string& s)
{
    auto start = s.begin();
    while (start != s.end() && isspace(*start))
    {
        start++;
    }

    auto end = s.end();
    do
    {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));

    return string(start, end + 1);
}
string getTen(string s)
{
    string ten = "";

    while (s.back() != ' ')
    {
        ten.insert(ten.begin() + 0, s.back());
        s.pop_back();
    }
    s.pop_back();

    return ten;
}
string xuatNgaySinh(NhanVien& x)
{
    string ngay = to_string(x.ngaySinh.ngay);
    string thang = to_string(x.ngaySinh.thang);
    string nam = to_string(x.ngaySinh.nam);
    string date = trim(ngay) + "/" + trim(thang) + "/" + trim(nam);
    return date;
}

string xuatNgayThamGia(NhanVien& x)
{
    string ngay = to_string(x.ngaythamgia.ngay);
    string thang = to_string(x.ngaythamgia.thang);
    string nam = to_string(x.ngaythamgia.nam);
    string date = trim(ngay) + "/" + trim(thang) + "/" + trim(nam);
    return date;
}
void formatLuongCoBan(NhanVien x)
{
    cout.imbue(locale(cout.getloc(), new g3));
    if (x.tangCa == 0)
    {
        cout << "\t\tLuong tong ket: " << x.luongCoBan * x.ngayCong << "VND" << endl;
    }
    else
    {
        double chuyenDoi = (double)x.soGioTangCa * NGAY;
        long luongChuan = x.ngayCong * x.luongCoBan;
        long luongTangCa = (long)(chuyenDoi * x.luongCoBan * 1.5);
        long luongTongKet = luongChuan + luongTangCa;
        cout << "\t\tLuong tong ket: " << luongTongKet <<"VND"<< endl;
    }
}
string formatTangCa(NhanVien x)
{
    if (x.tangCa == 0)
    {
        return "Khong";
    }
    else
    {
        return "Co";
    }
}

void docDuLieuNgaySinh(ifstream& filein, Date& ngaySinh)
{
    filein >> ngaySinh.ngay;
    filein.seekg(1, 1);
    filein >> ngaySinh.thang;
    filein.seekg(1, 1);
    filein >> ngaySinh.nam;
}
void docDuLieuNgayThamGia(ifstream& filein, NgayThamGia& ngaythamgia)
{
    filein >> ngaythamgia.ngay;
    filein.seekg(1, 1);
    filein >> ngaythamgia.thang;
    filein.seekg(1, 1);
    filein >> ngaythamgia.nam;
}

void docDuLieuNhanVien(ifstream& filein, NhanVien& x)
{
    getline(filein, x.maNV, ',');
    filein.seekg(1, 1);
    getline(filein, x.tenNV, ',');
    filein.seekg(1, 1);
    getline(filein, x.gioiTinh, ',');
    filein.seekg(1, 1);
    docDuLieuNgaySinh(filein, x.ngaySinh);
    filein.seekg(1, 1);
    getline(filein, x.queQuan, ',');
    filein.seekg(1, 1);
    getline(filein, x.email, ',');
    filein.seekg(1, 1);
    getline(filein, x.soDienThoai, ',');
    filein.seekg(1, 1);
    getline(filein, x.phongNhanSu, ',');
    filein.seekg(1, 1);
    filein >> x.luongCoBan;
    filein.seekg(1, 1);
    filein >> x.ngayCong;
    filein.seekg(1, 1);
    filein >> x.tangCa;
    filein.seekg(1, 1);
    filein >> x.soGioTangCa;
    filein.seekg(1, 1);
    docDuLieuNgayThamGia(filein, x.ngaythamgia);
    string temp;
    getline(filein, temp);
}
void ghiDuLieuNhanVien(ofstream& fileout, NhanVien x) {
    fileout << x.maNV << ", ";
    fileout << x.tenNV << ", ";
    fileout << x.gioiTinh << ", ";
    fileout << x.ngaySinh.ngay <<"/"<<x.ngaySinh.thang<<"/"<<x.ngaySinh.nam<<", ";
    fileout << x.queQuan << ", ";

    fileout << x.email << ", ";
    fileout << x.soDienThoai << ", ";

    fileout << x.phongNhanSu << ", ";
    fileout << x.luongCoBan << ", ";
    fileout << x.ngayCong << ", ";

    fileout << x.tangCa << ", ";
    fileout << x.soGioTangCa << ", ";
    fileout << x.ngaythamgia.ngay << "/" << x.ngaythamgia.thang << "/" << x.ngaythamgia.nam<<endl;


}
void xuatThongTinNhanVien(NhanVien x)
{
    cout << "\n\n";
    cout << "\t\tMa: " << x.maNV << endl;
    cout << "\t\tTen nhan vien: " << x.tenNV << endl;
    cout << "\t\tGioi tinh: " << x.gioiTinh << endl;
    cout << "\t\tNgay sinh: " << xuatNgaySinh(x) << endl;
    cout << "\t\tQue quan: " << x.queQuan << endl;
    cout << "\t\tEmail: " << x.email << endl;
    cout << "\t\tSo dien thoai: " << x.soDienThoai << endl;
    cout << "\t\tPhong nhan su: " << x.phongNhanSu << endl;
    formatLuongCoBan(x);
    cout << "\t\tNgay cong: " << x.ngayCong << endl;
    cout << "\t\tTang ca: " << formatTangCa(x) << endl;
    cout << "\t\tSo gio tang ca: " << x.soGioTangCa << endl;
    cout << "\t\tNgay tham gia: " << xuatNgayThamGia(x) << endl;
    cout << "\n";
}

void docDuLieuDanhSachNhanVien(ifstream& filein, List& list)
{
   

    while (!filein.eof())
    {
        NhanVien x;
        docDuLieuNhanVien(filein, x);
        Node* p = KhoiTaoNode(x);
        themNhanVien(list, p);
    }

   
}
void xuatThongTinDanhSachNhanVien(List list)
{
    Node* p = list.pHead;
    while (p != NULL)
    {
        xuatThongTinNhanVien(p->data);
        p = p->pNext;
    }
}
void input(NhanVien& x)
{
    cout << "\n\t\tNhap ma so nhan vien: ";
    getline(cin, x.maNV);
    cout << "\n\t\tNhap ten nhan vien: ";
    getline(cin, x.tenNV);
    cout << "\n\t\tNhap gioi tinh nhan vien: ";
    getline(cin, x.gioiTinh);
    cout << "\n\t\tNhap ngay: ";
    cin >> x.ngaySinh.ngay;
    cout << "\n\t\tNhap thang: ";
    cin >> x.ngaySinh.thang;
    cout << "\n\t\tNhap nam: ";
    cin >> x.ngaySinh.nam;
    cin.ignore();
    cout << "\n\t\tNhap que quan: ";
    getline(cin, x.queQuan);
    cout << "\n\t\tNhap email: ";
    getline(cin, x.email);
    cout << "\n\t\tNhap so dien thoai: ";
    getline(cin, x.soDienThoai);
    cout << "\n\t\tNhap phong nhan su: ";
    getline(cin, x.phongNhanSu);
    cout << "\n\t\tNhap muc luong: ";
    cin >> x.luongCoBan;
    cout << "\n\t\tNhap ngay cong: ";
    cin >> x.ngayCong;
    cout << "\n\t\tTang ca nhap 0 khong tang ca, nguoc lai tang ca";
    cin >> x.tangCa;
    cout << "\n\t\tNhap so gio tang ca: ";
    cin >> x.soGioTangCa;
    cout << "\n\t\tNhap ngay tham gia: ";
    cin >> x.ngaythamgia.ngay;
    cout << "\n\t\tNhap thang tham gia: ";
    cin >> x.ngaythamgia.thang;
    cout << "\n\t\tNhap nam thang gia: ";
    cin >> x.ngaythamgia.nam;
    cin.ignore();
}

void inputNotID(NhanVien& x) {
    cout << "\n\t\tNhap ten nhan vien: ";
    getline(cin, x.tenNV);
    cout << "\n\t\tNhap gioi tinh nhan vien: ";
    getline(cin, x.gioiTinh);
    cout << "\n\t\tNhap ngay: ";
    cin >> x.ngaySinh.ngay;
    cout << "\n\t\tNhap thang: ";
    cin >> x.ngaySinh.thang;
    cout << "\n\t\tNhap nam: ";
    cin >> x.ngaySinh.nam;
    cin.ignore();
    cout << "\n\t\tNhap que quan: ";
    getline(cin, x.queQuan);
    cout << "\n\t\tNhap email: ";
    getline(cin, x.email);
    cout << "\n\t\tNhap so dien thoai: ";
    getline(cin, x.soDienThoai);
    cout << "\n\t\tNhap phong nhan su: ";
    getline(cin, x.phongNhanSu);
    cout << "\n\t\tNhap muc luong: ";
    cin >> x.luongCoBan;
    cout << "\n\t\tNhap ngay cong: ";
    cin >> x.ngayCong;
    cout << "\n\t\tTang ca nhap 0 khong tang ca, nguoc lai tang ca";
    cin >> x.tangCa;
    cout << "\n\t\tNhap so gio tang ca: ";
    cin >> x.soGioTangCa;
    cout << "\n\t\tNhap ngay tham gia: ";
    cin >> x.ngaythamgia.ngay;
    cout << "\n\t\tNhap thang tham gia: ";
    cin >> x.ngaythamgia.thang;
    cout << "\n\t\tNhap nam thang gia: ";
    cin >> x.ngaythamgia.nam;
    cin.ignore();
}

void nhapThongTinNhanVien(NhanVien& x,List list)
{
    input(x);
    for (Node* k = list.pHead; k !=NULL ; k=k->pNext)
    {
        if (k->data.maNV.compare(x.maNV) == 0) {
            cout << "\n\t\tMa nhan vien bi trung, vui long nhap lai....";
            input(x);
        }
    }
    if (x.maNV.empty())
    {
        cout << "\n\t\tMa nhan vien khong duoc bo trong, vui long nhap lai....";
        input(x);
    }
    if (x.tenNV.empty())
    {
        cout << "\n\t\tTen nhan vien khong duoc bo trong,vui long nhap lai....";
        input(x);
    }
    if (x.gioiTinh.empty())
    {
        cout << "\n\t\tGioi tinh khong duoc bo trong, vui long nhap lai....";
        input(x);
    }

    if (to_string(x.ngaySinh.ngay).empty() || to_string(x.ngaySinh.thang).empty() ||
        to_string(x.ngaySinh.nam).empty())
    {
        cout << "\n\t\tNgay sinh khong duoc bo trong, vui long nhap lai....";
        input(x);
    }

    if (x.queQuan.empty())
    {
        cout << "\n\t\tQue quan khong duoc bo trong, vui long nhap lai....";
        input(x);
    }
    if (x.email.empty())
    {
        cout << "\n\t\tEmail khong duoc bo trong, vui long nhap lai...";
        input(x);
    }

    if (x.soDienThoai.empty())
    {
        cout << "\n\t\tSo dien thoai khong duoc bo trong, vui long nhap lai....";
        input(x);
    }
    if (x.phongNhanSu.empty())
    {
        cout << "\n\t\tPhong ban khong duoc bo trong, vui long nhap lai....";
        input(x);
    }

    if (to_string(x.luongCoBan).empty())
    {
        cout << "\n\t\tMuc luong khong duoc bo trong, vui long nhap lai....";
        input(x);
    }

    if (to_string(x.ngayCong).empty())
    {
        cout << "\n\t\tNgay cong khong duoc bo trong, vui long nhap lai....";
        input(x);
    }

    if (to_string(x.tangCa).empty())
    {
        cout << "\n\t\tTang ca khong duoc bo trong, vui long nhap lai....";
        input(x);
    }
    if (to_string(x.soGioTangCa).empty())
    {
        cout << "\n\t\tSo gio khong duoc bo trong, vui long nhap lai....";
        input(x);
    }

    // check ngày sinh
    if (x.ngaySinh.nam >= 1900)
    {
        if (x.ngaySinh.thang >= 1 && x.ngaySinh.thang <= 12)
        {
            switch (x.ngaySinh.thang)
            {
            case 4:
            case 6:
            case 9:
            case 10:
                if (x.ngaySinh.ngay <= 0 || x.ngaySinh.ngay > 30)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    input(x);
                }

                break;

            case 1:
            case 3:
            case 5:
            case 7:
            case 11:
            case 12:

                if (x.ngaySinh.ngay <= 0 && x.ngaySinh.ngay > 31)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    input(x);
                }

                break;
            case 2:
                if (x.ngaySinh.nam % 4 == 0 || x.ngaySinh.nam % 400 == 0)
                {
                    if (x.ngaySinh.ngay <= 0 || x.ngaySinh.ngay > 28)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        input(x);
                    }
                }
                else
                {
                    if (x.ngaySinh.ngay <= 0 || x.ngaySinh.ngay > 29)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        input(x);
                    }
                }
            }
        }
        else
        {
            cout << "\n\t\tThang nhap khong hop le, vui long nhap lai....";
            input(x);
        }
    }
    else
    {
        cout << "\n\t\tNam phai lon hon 1900 ve sau, vui long nhap lai....";
        input(x);
    }

    // check ngày tham gia
    if (x.ngaythamgia.nam >= 1900)
    {
        if (x.ngaythamgia.thang >= 1 && x.ngaythamgia.thang <= 12)
        {
            switch (x.ngaythamgia.thang)
            {
            case 4:
            case 6:
            case 9:
            case 10:
                if (x.ngaythamgia.ngay <= 0 || x.ngaythamgia.ngay > 30)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    input(x);
                }

                break;

            case 1:
            case 3:
            case 5:
            case 7:
            case 11:
            case 12:

                if (x.ngaythamgia.ngay <= 0 && x.ngaythamgia.ngay > 31)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    input(x);
                }

                break;
            case 2:
                if (x.ngaythamgia.nam % 4 == 0 || x.ngaythamgia.nam % 400 == 0)
                {
                    if (x.ngaythamgia.ngay <= 0 || x.ngaythamgia.ngay > 28)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        input(x);
                    }
                }
                else
                {
                    if (x.ngaythamgia.ngay <= 0 || x.ngaythamgia.ngay > 29)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        input(x);
                    }
                }
            }
        }
        else
        {
            cout << "\n\t\tThang nhap khong hop le, vui long nhap lai....";
            input(x);
        }
    }
    else
    {
        cout << "\n\t\tNam phai lon hon 1900 ve sau, vui long nhap lai....";
        input(x);
    }
}

void suaThongTinNhanVien(NhanVien& x)
{
    inputNotID(x);
  
    if (x.tenNV.empty())
    {
        cout << "\n\t\tTen nhan vien khong duoc bo trong,vui long nhap lai....";
        inputNotID(x);
    }
    if (x.gioiTinh.empty())
    {
        cout << "\n\t\tGioi tinh khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }

    if (to_string(x.ngaySinh.ngay).empty() || to_string(x.ngaySinh.thang).empty() ||
        to_string(x.ngaySinh.nam).empty())
    {
        cout << "\n\t\tNgay sinh khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }

    if (x.queQuan.empty())
    {
        cout << "\n\t\tQue quan khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }
    if (x.email.empty())
    {
        cout << "\n\t\tEmail khong duoc bo trong, vui long nhap lai...";
        inputNotID(x);
    }

    if (x.soDienThoai.empty())
    {
        cout << "\n\t\tSo dien thoai khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }
    if (x.phongNhanSu.empty())
    {
        cout << "\n\t\tPhong ban khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }

    if (to_string(x.luongCoBan).empty())
    {
        cout << "\n\t\tMuc luong khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }

    if (to_string(x.ngayCong).empty())
    {
        cout << "\n\t\tNgay cong khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }

    if (to_string(x.tangCa).empty())
    {
        cout << "\n\t\tTang ca khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }
    if (to_string(x.soGioTangCa).empty())
    {
        cout << "\n\t\tSo gio khong duoc bo trong, vui long nhap lai....";
        inputNotID(x);
    }

    // check ngày sinh
    if (x.ngaySinh.nam >= 1900)
    {
        if (x.ngaySinh.thang >= 1 && x.ngaySinh.thang <= 12)
        {
            switch (x.ngaySinh.thang)
            {
            case 4:
            case 6:
            case 9:
            case 10:
                if (x.ngaySinh.ngay <= 0 || x.ngaySinh.ngay > 30)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    inputNotID(x);
                }

                break;

            case 1:
            case 3:
            case 5:
            case 7:
            case 11:
            case 12:

                if (x.ngaySinh.ngay <= 0 && x.ngaySinh.ngay > 31)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    inputNotID(x);
                }

                break;
            case 2:
                if (x.ngaySinh.nam % 4 == 0 || x.ngaySinh.nam % 400 == 0)
                {
                    if (x.ngaySinh.ngay <= 0 || x.ngaySinh.ngay > 28)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        inputNotID(x);
                    }
                }
                else
                {
                    if (x.ngaySinh.ngay <= 0 || x.ngaySinh.ngay > 29)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        inputNotID(x);
                    }
                }
            }
        }
        else
        {
            cout << "\n\t\tThang nhap khong hop le, vui long nhap lai....";
            inputNotID(x);
        }
    }
    else
    {
        cout << "\n\t\tNam phai lon hon 1900 ve sau, vui long nhap lai....";
        inputNotID(x);
    }

    // check ngày tham gia
    if (x.ngaythamgia.nam >= 1900)
    {
        if (x.ngaythamgia.thang >= 1 && x.ngaythamgia.thang <= 12)
        {
            switch (x.ngaythamgia.thang)
            {
            case 4:
            case 6:
            case 9:
            case 10:
                if (x.ngaythamgia.ngay <= 0 || x.ngaythamgia.ngay > 30)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    inputNotID(x);
                }

                break;

            case 1:
            case 3:
            case 5:
            case 7:
            case 11:
            case 12:

                if (x.ngaythamgia.ngay <= 0 && x.ngaythamgia.ngay > 31)
                {
                    cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                    inputNotID(x);
                }

                break;
            case 2:
                if (x.ngaythamgia.nam % 4 == 0 || x.ngaythamgia.nam % 400 == 0)
                {
                    if (x.ngaythamgia.ngay <= 0 || x.ngaythamgia.ngay > 28)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        inputNotID(x);
                    }
                }
                else
                {
                    if (x.ngaythamgia.ngay <= 0 || x.ngaythamgia.ngay > 29)
                    {
                        cout << "\n\t\tNgay khong hop le, vui long nhap lai....";
                        inputNotID(x);
                    }
                }
            }
        }
        else
        {
            cout << "\n\t\tThang nhap khong hop le, vui long nhap lai....";
            inputNotID(x);
        }
    }
    else
    {
        cout << "\n\t\tNam phai lon hon 1900 ve sau, vui long nhap lai....";
        inputNotID(x);
    }
}

void suaThongTinNhanVien(List& l, string manv)
{
    bool exist = true;
    int check;
    Node* p = l.pHead;
    while (p != NULL)
    {
        if (trim(p->data.maNV).compare(trim(manv)) == 0)
        {
            suaThongTinNhanVien(p->data);
            exist = true;
            break;
        }
        else
        {
            exist = false;
        }
        p = p->pNext;
    }
    if (exist == false)
    {
        cout << "\n\t\tMa nhan vien khong ton tai,hoac bi trung ban muon them moi?";
        cout << "\n\t\tNhan phim bat ki de them moi, 0 de thoat...";
        cin >> check;
        if (check == 0)
        {
            return;
        }
        else
        {
            NhanVien x;
            cin.ignore();
            nhapThongTinNhanVien(x,l);
            Node* p = KhoiTaoNode(x);
            themNhanVien(l, p);
            cout << "\n\t\tThem thanh cong...";
            return;
        }
    }
}
void xoaNhanVienDauTien(List& l)
{
    Node* p = l.pHead;
    if (l.pHead == NULL)
    {
        cout << "Nothing to delete";
    }
    else
    {
        l.pHead = p->pNext;
        delete p;
    }
}
void xoaNhanVienTheoMa(List& l, string manv)
{
    bool check = true;
    if (trim(l.pHead->data.maNV).compare(trim(manv)) == 0)
    {
        xoaNhanVienDauTien(l);
    }

    Node* p = new Node;
    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        if (trim(k->data.maNV).compare(trim(manv)) == 0)
        {
            p->pNext = k->pNext;
            delete k;
            cout << "\n\t\tXoa thanh cong...";
            return;
        }
        else
        {
            check = false;
        }
        p = k;
    }
    if (check == true)
    {
        cout << "\n\t\tMa khong ton tai...";
    }
}

long getLuongTongKet(NhanVien x)
{
    if (x.tangCa == 0)
    {
        return x.luongCoBan * x.ngayCong;
    }
    else
    {
        double chuyenDoi = (double)x.soGioTangCa * NGAY;
        long luongChuan = x.ngayCong * x.luongCoBan;
        long luongTangCa = (long)(chuyenDoi * x.luongCoBan * 1.5);
        return luongChuan + luongTangCa;
    }
}

void sapXepTangDanTheoLuongTongKet(List& l)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (getLuongTongKet(k->data) > getLuongTongKet(p->data))
            {
                swap(k->data, p->data);
            }
        }
    }
}
void sapXepTangDanTheoLuongCoBan(List& l)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (k->data.luongCoBan > p->data.luongCoBan)
            {
                swap(k->data, p->data);
            }
        }
    }
}
void sapXepTangDanTheoTen(List& l)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (getTen(k->data.tenNV).compare(getTen(p->data.tenNV)) > 0)
            {
                swap(k->data, p->data);
            }
        }
    }
}
void sapXepTangDanTheoNamSinh(List& l)
{
    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (k->data.ngaySinh.nam > k->data.ngaySinh.nam)
            {
                swap(k->data, p->data);
            }
        }
    }
}

void sapXepGiamDanTheoLuongTongKet(List& l)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (getLuongTongKet(k->data) < getLuongTongKet(p->data))
            {
                swap(k->data, p->data);
            }
        }
    }
}
void sapXepGiamDanTheoLuongCoBan(List& l)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (k->data.luongCoBan < p->data.luongCoBan)
            {
                swap(k->data, p->data);
            }
        }
    }
}
void sapXepGiamDanTheoTen(List& l)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (getTen(k->data.tenNV).compare(getTen(p->data.tenNV)) < 0)
            {
                swap(k->data, p->data);
            }
        }
    }
}
void sapXepGiamDanTheoNamSinh(List& l)
{
    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        for (Node* p = k->pNext; p != NULL; p = p->pNext)
        {

            if (k->data.ngaySinh.nam < k->data.ngaySinh.nam)
            {
                swap(k->data, p->data);
            }
        }
    }
}

Node* timKiemThongTinNhanVienTheoMa(List l, string manv)
{

    Node* p = l.pHead;
    while (p != NULL)
    {
        if (trim(p->data.maNV).compare(trim(manv)) == 0)
        {
            return p;
        }
        p = p->pNext;
    }
    return NULL;
}

int demSoLuongNhanVien(List l)
{
    int dem = 0;
    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        dem++;
    }
    return dem;
}

long long tongLuongToanBoNhanVien(List l)
{
    long long tong = 0;

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        tong += getLuongTongKet(k->data);
    }
    return tong;
}

Node* locNhanVienTheoTen(List l, string ten)
{
    Node* p = l.pHead;
    Node* check = NULL;
    while (p != NULL)
    {
        if (getTen(trim(p->data.tenNV)).compare(trim(ten)) == 0)
        {
            check = l.pHead;
            xuatThongTinNhanVien(p->data);
        }
        p = p->pNext;
    }
    return check;
}
Node* locNhanVienTheoNamSinh(List l, int nam)
{
    Node* p = l.pHead;
    Node* check = NULL;
    while (p != NULL)
    {
        if (p->data.ngaySinh.nam == nam)
        {
            check = l.pHead;
            xuatThongTinNhanVien(p->data);
        }
        p = p->pNext;
    }
    return check;
}

Node* locNhanVienTheoQueQuan(List l, string qq)
{
    Node* p = l.pHead;
    Node* check = NULL;
    while (p != NULL)
    {
        if (trim(p->data.queQuan).compare(trim(qq)) == 0)
        {
            check = l.pHead;
            xuatThongTinNhanVien(p->data);
        }
        p = p->pNext;
    }
    return check;
}

Node* locNhanVienTheoPhongNhanSu(List l, string pns)
{
    Node* p = l.pHead;
    Node* check = NULL;
    while (p != NULL)
    {
        if (trim(p->data.phongNhanSu).compare(trim(pns)) == 0)
        {
            check = l.pHead;
            xuatThongTinNhanVien(p->data);
        }
        p = p->pNext;
    }
    return check;
}

Node* locNhanVienTheoKhoangLuongTongKet(List l, long min, long max)
{
    Node* check = NULL;

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        if (getLuongTongKet(k->data) >= min && getLuongTongKet(k->data) <= max)
        {
            check = l.pHead;
            xuatThongTinNhanVien(k->data);
        }
    }
    return check;
}

void push(List& list, NhanVien x)
{
    Node* p = KhoiTaoNode(x);
    if (list.pHead == NULL)
    {
        list.pHead = list.PTail = p;
    }
    else
    {
        list.PTail->pNext = p;
        list.PTail = p;
    }
}

void thongKeSoLuongTheoQueQuan(List l)
{

    for (Node* p = l.pHead; p != NULL; p = p->pNext)
    {
        bool kt = true; // dùng kiểm tra phân biệt
        for (Node* k = p->pNext; k != NULL; k = k->pNext)
        {
            if (p->data.queQuan.compare(k->data.queQuan) == 0)
            {
                kt = false;

                break;
            }
        }

        if (kt == true)
        {
            int dem = 0;
            for (Node* u = l.pHead; u != NULL; u = u->pNext)
            {

                if (p->data.queQuan.compare(u->data.queQuan) == 0)
                {
                    dem++;
                }
            }
            cout << p->data.queQuan << ": " << dem << endl;
        }
    }
}

void thongKeSoLuongTheoTen(List l)
{

    for (Node* p = l.pHead; p != NULL; p = p->pNext)
    {
        bool kt = true; // dùng kiểm tra phân biệt
        for (Node* k = p->pNext; k != NULL; k = k->pNext)
        {
            if (getTen(p->data.tenNV).compare(getTen(k->data.tenNV)) == 0)
            {
                kt = false;
                break;
            }
        }

        if (kt == true)
        {
            int dem = 0;
            for (Node* u = l.pHead; u != NULL; u = u->pNext)
            {

                if (p->data.tenNV.compare(u->data.tenNV) == 0)
                {
                    dem++;
                }
            }
            cout << getTen(p->data.tenNV) << ": " << dem << endl;
        }
    }
}

void thongKeSoLuongTheoPhongNhanSu(List l)
{

    for (Node* p = l.pHead; p != NULL; p = p->pNext)
    {
        bool kt = true; // dùng kiểm tra phân biệt
        for (Node* k = p->pNext; k != NULL; k = k->pNext)
        {
            if (p->data.phongNhanSu.compare(k->data.phongNhanSu) == 0)
            {
                kt = false;
                break;
            }
        }

        if (kt == true)
        {
            int dem = 0;
            for (Node* u = l.pHead; u != NULL; u = u->pNext)
            {

                if (p->data.phongNhanSu.compare(u->data.phongNhanSu) == 0)
                {
                    dem++;
                }
            }

            cout << p->data.phongNhanSu << ": " << dem << endl;
        }
    }
}

void tachTheoQuy1(List& l, List& A)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.ngaythamgia.thang >= 1 && k->data.ngaythamgia.thang <= 3)
        {
            push(A, k->data);
        }
    }
    cout << "\n\t\tThong tin nhan vien thuoc quy 1";
    xuatThongTinDanhSachNhanVien(A);
}

void tachTheoQuy2(List& l, List& B)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.ngaythamgia.thang >= 4 && k->data.ngaythamgia.thang <= 6)
        {
            push(B, k->data);
        }
    }
    cout << "\n\t\tThong tin nhan vien thuoc quy 2";
    xuatThongTinDanhSachNhanVien(B);
}

void tachTheoQuy3(List& l, List& C)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.ngaythamgia.thang >= 7 && k->data.ngaythamgia.thang <= 9)
        {
            push(C, k->data);
        }
    }
    cout << "\n\t\tThong tin nhan vien thuoc quy 3";
    xuatThongTinDanhSachNhanVien(C);
}
void tachTheoQuy4(List& l, List& D)
{

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        if (k->data.ngaythamgia.thang >= 10 && k->data.ngaythamgia.thang <= 12)
        {
            push(D, k->data);
        }
    }
    cout << "\n\t\tThong tin nhan vien thuoc quy 3";
    xuatThongTinDanhSachNhanVien(D);
}

void ghiDanhSachSapXepTheoLuongTKTangDan(List &l) {
    ofstream fileout;
    fileout.open("SapXepTangDanTheoLuongTongKet.txt", ios::out);
    sapXepTangDanTheoLuongTongKet(l);

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        ghiDuLieuNhanVien(fileout, k->data);
    }
    fileout.close();
}
void ghiDanhSachSapXepTheoLuongTKGiamDan(List l) {
    ofstream fileout;
    fileout.open("SapXepGiamDanTheoLuongTongKet.txt", ios::out);
    sapXepGiamDanTheoLuongTongKet(l);

    for (Node* k = l.pHead; k != NULL; k = k->pNext)
    {
        ghiDuLieuNhanVien(fileout, k->data);
    }
    fileout.close();
}
void MENU(List l)
{
    int luaChon;
    NhanVien x;
    string manv;
    ifstream filein;
    filein.open("Data.txt", ios::in);
    docDuLieuDanhSachNhanVien(filein, l);
    // swich case
    // - biến lựa chọn kiểu số nguyên, khi nhập kí tự không xuất ra không hợp lệ và nhập lại
    // mà sẽ dừng chương trình hoặc bị lỗi
    // - biến lựa chọn kiểu kí tự, xử lí được các trường hợp nhưng chỉ case từ 0-9
    // case 11 sẽ hiểu là 1, dư thừa kí tự đầu tiên trong bộ nhớ đệm phải dùng cin.ignore để xóa

   
    while (true)
    {
        system("cls");
        cout << "\n\t\t\t\t\t\t\t\tDO AN TIN HOC";
        cout << "\n\t\t\t\t\t\t\tNguoi thuc hien: Tran Van Si";
        cout << "\n\t\t\t\t\t\t\tMSSV: DH52001793";
        cout << "\n\t\t\t\t\t\t\tGiao vien huong dan: Huynh Quang Duc"<<"\n\n\n";
        cout << "\n\t\t===========MENU===========\n";
        cout << "\n\t\t1. Xuat du lieu";
        cout << "\n\t\t2. Nhap du lieu";
        cout << "\n\t\t3. Sua thong tin nhan vien";
        cout << "\n\t\t4. Xoa thong tin nhan vien";
        cout << "\n\t\t5. Sap xep thong tin tang dan";
        cout << "\n\t\t6. Sap xep thong tin giam dan";
        cout << "\n\t\t7. Tim kiem thong tin nhan vien";
        cout << "\n\t\t8. Dem so luong nhan vien trong cong ty";
        cout << "\n\t\t9. Loc nhan vien";
        cout << "\n\t\t10. Thong ke so luong";
        cout << "\n\t\t11. Tong luong tat ca nhan vien";
        cout << "\n\t\t12. Truy xuat vao Quy 1";
        cout << "\n\t\t13. Truy xuat vao Quy 2";
        cout << "\n\t\t14. Truy xuat vao Quy 3";
        cout << "\n\t\t15. Truy xuat vao Quy 4";
        cout << "\n\t\t16. Ghi file";
        cout << "\n\t\tNhap 0 de thoat";
        cout << "\n\t\tNhap lua chon: ";

        cin >> luaChon;
        if (luaChon == 0)
        {
            break;
        }
        switch (luaChon)
        {
        case 1:
        {
          
           
            xuatThongTinDanhSachNhanVien(l);
            filein.close();
            system("pause");
            break;
        }
        case 2:
        {
            cin.ignore();
            nhapThongTinNhanVien(x,l);
            Node* p = KhoiTaoNode(x);
            themNhanVien(l, p);
           
            break;
        }
        case 3:
        {
            cin.ignore();
            cout << "\n\t\tNhap ma nhan vien sua: ";
            getline(cin, manv);
            suaThongTinNhanVien(l, manv);
            system("pause");
            break;
        }
        case 4:
        {
            cin.ignore();
            cout << "\n\t\tNhap ma nhan vien can xoa: ";
            getline(cin, manv);
            xoaNhanVienTheoMa(l, manv);
            system("pause");
            break;
        }
        case 5:
        {
            int luaChonSXTang;
            while (true)
            {
                system("cls");
                cout << "\n\t\t========SAP XEP TANG======";
                cout << "\n\t\t1. Sap xep theo luong tong ket";
                cout << "\n\t\t2. Sap xep theo luong co ban";
                cout << "\n\t\t3. Sap xep theo ten";
                cout << "\n\t\t4. Sap xep theo nam sinh";
                cout << "\n\t\tNhap 0 de thoat";
                cout << "\n\t\tNhap lua chon: ";
                cin >> luaChonSXTang;

                if (luaChonSXTang == 0)
                {
                    break;
                }
                switch (luaChonSXTang)
                {
                case 1:
                {
                    sapXepTangDanTheoLuongTongKet(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;
                }
                case 2:
                {
                    sapXepTangDanTheoLuongCoBan(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;
                }
                case 3:
                {
                    sapXepTangDanTheoTen(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;
                }
                case 4:
                {
                    sapXepTangDanTheoNamSinh(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;
                }

                default:
                    cout << "\n\t\tLua chon khong phu hop...";
                    system("pause");
                    break;
                }
            }

            break;
        }
        case 6:
        {
            int luaChonSXGiam;
            while (true)
            {
                system("cls");
                cout << "\n\t\t=======SAP XEP GIAM DAN======";
                cout << "\n\t\t1. Sap xep theo luong tong ket";
                cout << "\n\t\t2. Sap xep theo luong co ban";
                cout << "\n\t\t3. Sap xep theo ten";
                cout << "\n\t\t4. Sap xep theo nam sinh";
                cout << "\n\t\tNhap 0 de thoat";
                cout << "\n\t\tNhap lua chon: ";

                cin >> luaChonSXGiam;

                if (luaChonSXGiam == 0)
                {
                    break;
                }

                switch (luaChonSXGiam)
                {
                case 1:
                    sapXepGiamDanTheoLuongTongKet(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;
                case 2:
                    sapXepGiamDanTheoLuongCoBan(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;
                case 3:
                    sapXepGiamDanTheoTen(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;
                case 4:
                    sapXepGiamDanTheoNamSinh(l);
                    xuatThongTinDanhSachNhanVien(l);
                    system("pause");
                    break;

                default:
                    cout << "\n\t\tLua chon khong phu hop...";

                    system("pause");
                    break;
                }
            }
            break;
        }
        case 7:
        {
            cin.ignore();
            cout << "\n\t\tNhap ma nhan vien can tim: ";
            getline(cin, manv);
            Node* timKiem = timKiemThongTinNhanVienTheoMa(l, manv);
            if (timKiem == NULL)
            {
                cout << "\n\t\tKhong tim thay...";
            }
            else
            {

                xuatThongTinNhanVien(timKiem->data);
            }
            system("pause");
            break;
        }
        case 8:
        {
            cout << "\n\t\tSo luong nhan vien trong cong ty: " << demSoLuongNhanVien(l);
            system("pause");
            break;
        }
        case 9:
        {
            int luaChonLoc;
            while (true)
            {
                system("cls");
                cout << "\n\t\t=======LOC NHAN VIEN======";
                cout << "\n\t\t1. Loc theo ten";
                cout << "\n\t\t2. Loc theo nam sinh";
                cout << "\n\t\t3. Loc theo que quan";
                cout << "\n\t\t4. Loc theo phong nhan su";
                cout << "\n\t\t5. Loc theo khoang luong tong ket";
                cout << "\n\t\tNhap 0 de thoat";
                cout << "\n\t\tNhap lua chon: ";

                cin >> luaChonLoc;

                if (luaChonLoc == 0)
                {
                    break;
                }

                switch (luaChonLoc)
                {
                case 1:
                {
                    cin.ignore();
                    string ten;
                    cout << "\n\t\tNhap ten can loc: ";
                    getline(cin, ten);
                    Node* kq = locNhanVienTheoTen(l, ten);
                    if (kq == NULL)
                    {
                        cout << "Khong tim thay...";
                    }
                    system("pause");
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    int namSinh;
                    cout << "\n\t\tNhap nam sinh can loc: ";
                    cin >> namSinh;
                    Node* kq = locNhanVienTheoNamSinh(l, namSinh);
                    if (kq == NULL)
                    {
                        cout << "Khong tim thay...";
                    }
                    system("pause");
                    break;
                }
                case 3:
                {
                    cin.ignore();
                    string qq;
                    cout << "\n\t\tNhap que quan can loc: ";
                    getline(cin, qq);
                    Node* kq = locNhanVienTheoQueQuan(l, qq);
                    if (kq == NULL)
                    {
                        cout << "Khong tim thay...";
                    }
                    system("pause");
                    break;
                }
                case 4:
                {
                    cin.ignore();
                    string pns;
                    cout << "\n\t\tNhap phong nhan su can loc: ";
                    getline(cin, pns);
                    Node* kq = locNhanVienTheoPhongNhanSu(l, pns);
                    if (kq == NULL)
                    {
                        cout << "Khong tim thay...";
                    }
                    system("pause");
                    break;
                }
                case 5:
                {
                    int min, max;
                    cout << "\n\t\tNhap khoang luong min-max: ";
                    cin >> min >> max;
                    Node* kq = locNhanVienTheoKhoangLuongTongKet(l, min, max);
                    if (kq == NULL)
                    {
                        cout << "Khong tim thay...";
                    }
                    system("pause");
                    break;
                }
                default:
                    cout << "\n\t\tLua chon khong phu hop...";

                    system("pause");
                    break;
                }
            }
            break;
        }
        case 10:
        {
            int luaChonTK;
            while (true)
            {
                system("cls");
                cout << "\n\t\t=======THONG KE SO LUONG======";
                cout << "\n\t\t1. Thong ke theo ten";
                cout << "\n\t\t2. Thong ke theo que quan";
                cout << "\n\t\t3. Thong ke theo phong nhan su";
                cout << "\n\t\tNhap 0 de thoat";
                cout << "\n\t\tNhap lua chon: ";

                cin >> luaChonTK;

                if (luaChonTK == 0)
                {
                    break;
                }

                switch (luaChonTK)
                {
                case 1:
                {
                    thongKeSoLuongTheoTen(l);
                    system("pause");
                    break;
                }
                case 2:
                {
                    thongKeSoLuongTheoQueQuan(l);
                    system("pause");
                    break;
                }
                case 3:
                {
                    thongKeSoLuongTheoPhongNhanSu(l);
                    system("pause");
                    break;
                }
                default:
                    cout << "\n\t\tLua chon khong phu hop...";

                    system("pause");
                    break;
                }
            }
            break;
        }

        case 11:
        {
            cout.imbue(locale(cout.getloc(), new g3));
            cout << "\n\t\tTong luong cua tat ca nhan vien: " << tongLuongToanBoNhanVien(l) << "VND";
            system("pause");
            break;
        }

        case 12:
        {
            List A;
            int luaChon;
            khoiTao(A);
            tachTheoQuy1(l, A);
            cout << "\n\t\tNhan phim bat ki de vao Quy 1...";
            system("pause");
            while (true)
            {
                system("cls");
                cout << "\n\t\t=========Quy 1==========";
                cout << "\n\t\t1. Xuat thong tin";
                cout << "\n\t\t2. Tim kiem thong tin";
                cout << "\n\t\t3. Sap xep tang";
                cout << "\n\t\t4. Sap xep giam";
                cout << "\n\t\t5. Loc nhan vien";
                cout << "\n\t\tNhap 0 de thoat...";
                cout << "\n\t\tNhap lua chon: ";
                cin >> luaChon;

                if (luaChon == 0)
                {
                    break;
                    ;
                }
                switch (luaChon)
                {
                case 1:
                {
                    khoiTao(A);
                    tachTheoQuy1(l, A);
                    system("pause");
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    cout << "\n\t\tNhap ma nhan vien can tim: ";
                    getline(cin, manv);
                    Node* timKiem = timKiemThongTinNhanVienTheoMa(A, manv);
                    if (timKiem == NULL)
                    {
                        cout << "\n\t\tKhong tim thay...";
                    }
                    else
                    {

                        xuatThongTinNhanVien(timKiem->data);
                    }
                    system("pause");
                    break;
                }

                case 3:
                    system("cls");
                    int luaChonSXT;
                    cout << "\n\t\t=====Sap xep tang======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSXT;
                    if (luaChonSXT == 0)
                    {
                        break;
                    }

                    switch (luaChonSXT)
                    {

                    case 1:
                    {
                        sapXepTangDanTheoLuongTongKet(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepTangDanTheoLuongCoBan(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepTangDanTheoTen(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepTangDanTheoNamSinh(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 4:
                    system("cls");
                    int luaChonSSG;
                    cout << "\n\t\t=====Sap xep giam======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSSG;
                    if (luaChonSSG == 0)
                    {
                        break;
                    }

                    switch (luaChonSSG)
                    {

                    case 1:
                    {
                        sapXepGiamDanTheoLuongTongKet(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepGiamDanTheoLuongCoBan(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepGiamDanTheoTen(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepGiamDanTheoNamSinh(A);
                        xuatThongTinDanhSachNhanVien(A);
                        system("pause");
                        break;
                    }
                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 5:

                    system("cls");
                    int luaChonLoc;
                    cout << "\n\t\t=====LOC NHAN VIEN====";
                    cout << "\n\t\t1.Loc theo ten";
                    cout << "\n\t\t2. Loc theo nam sinh";
                    cout << "\n\t\t3. Loc theo que quan";
                    cout << "\n\t\t4. Loc theo phong nhan su";
                    cout << "\n\t\t5. Loc theo khoang luong tong ket";
                    cout << "\n\t\tNhap 0 de thoat...";
                    cout << "\n\t\tNhap lua chon cua ban: ";
                    cin >> luaChonLoc;

                    switch (luaChonLoc)
                    {
                    case 1:
                    {
                        cin.ignore();
                        string ten;
                        cout << "\n\t\tNhap ten can loc: ";
                        getline(cin, ten);
                        Node* kq = locNhanVienTheoTen(A, ten);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 2:
                    {
                        cin.ignore();
                        int namSinh;
                        cout << "\n\t\tNhap nam sinh can loc: ";
                        cin >> namSinh;
                        Node* kq = locNhanVienTheoNamSinh(A, namSinh);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        cin.ignore();
                        string qq;
                        cout << "\n\t\tNhap que quan can loc: ";
                        getline(cin, qq);
                        Node* kq = locNhanVienTheoQueQuan(A, qq);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 4:
                    {
                        cin.ignore();
                        string pns;
                        cout << "\n\t\tNhap phong nhan su can loc: ";
                        getline(cin, pns);
                        Node* kq = locNhanVienTheoPhongNhanSu(A, pns);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 5:
                    {
                        int min, max;
                        cout << "\n\t\tNhap khoang luong min-max: ";
                        cin >> min >> max;
                        Node* kq = locNhanVienTheoKhoangLuongTongKet(A, min, max);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                default:
                    cout << "\n\t\tLua chon khong hop le...";
                    break;
                }
            }
            break;
        }

        case 13:
        {
            List B;
            int luaChon;
            khoiTao(B);
            tachTheoQuy2(l, B);
            cout << "\n\t\tNhan phim bat ki de vao Quy 2...";
            system("pause");
            while (true)
            {
                system("cls");
                cout << "\n\t\t=========Quy 2==========";
                cout << "\n\t\t1. Xuat thong tin";
                cout << "\n\t\t2. Tim kiem thong tin";
                cout << "\n\t\t3. Sap xep tang";
                cout << "\n\t\t4. Sap xep giam";
                cout << "\n\t\t5. Loc nhan vien";
                cout << "\n\t\tNhap lua chon: ";
                cout << "\n\t\tNhap 0 de thoat...";
                cin >> luaChon;
                if (luaChon == 0)
                {
                    break;
                }
                switch (luaChon)
                {
                case 1:
                    khoiTao(B);
                    tachTheoQuy2(l, B);
                    system("pause");
                    break;
                case 2:
                {
                    cin.ignore();
                    cout << "\n\t\tNhap ma nhan vien can tim: ";
                    getline(cin, manv);
                    Node* timKiem = timKiemThongTinNhanVienTheoMa(B, manv);
                    if (timKiem == NULL)
                    {
                        cout << "\n\t\tKhong tim thay...";
                    }
                    else
                    {

                        xuatThongTinNhanVien(timKiem->data);
                    }
                    system("pause");
                    break;
                }

                case 3:
                    system("cls");
                    int luaChonSXT;
                    cout << "\n\t\t=====Sap xep tang======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSXT;
                    if (luaChonSXT == 0)
                    {
                        break;
                    }

                    switch (luaChonSXT)
                    {

                    case 1:
                    {
                        sapXepTangDanTheoLuongTongKet(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepTangDanTheoLuongCoBan(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepTangDanTheoTen(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepTangDanTheoNamSinh(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 4:
                    system("cls");
                    int luaChonSSG;
                    cout << "\n\t\t=====Sap xep giam======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSSG;
                    if (luaChonSSG == 0)
                    {
                        break;
                    }

                    switch (luaChonSSG)
                    {

                    case 1:
                    {
                        sapXepGiamDanTheoLuongTongKet(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepGiamDanTheoLuongCoBan(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepGiamDanTheoTen(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepGiamDanTheoNamSinh(B);
                        xuatThongTinDanhSachNhanVien(B);
                        system("pause");
                        break;
                    }
                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 5:

                    system("cls");
                    int luaChonLoc;
                    cout << "\n\t\t=====LOC NHAN VIEN====";
                    cout << "\n\t\t1.Loc theo ten";
                    cout << "\n\t\t2. Loc theo nam sinh";
                    cout << "\n\t\t3. Loc theo que quan";
                    cout << "\n\t\t4. Loc theo phong nhan su";
                    cout << "\n\t\t5. Loc theo khoang luong tong ket";
                    cout << "\n\t\tNhap 0 de thoat...";
                    cout << "\n\t\tNhap lua chon cua ban: ";
                    cin >> luaChonLoc;

                    switch (luaChonLoc)
                    {
                    case 1:
                    {
                        cin.ignore();
                        string ten;
                        cout << "\n\t\tNhap ten can loc: ";
                        getline(cin, ten);
                        Node* kq = locNhanVienTheoTen(B, ten);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 2:
                    {
                        cin.ignore();
                        int namSinh;
                        cout << "\n\t\tNhap nam sinh can loc: ";
                        cin >> namSinh;
                        Node* kq = locNhanVienTheoNamSinh(B, namSinh);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        cin.ignore();
                        string qq;
                        cout << "\n\t\tNhap que quan can loc: ";
                        getline(cin, qq);
                        Node* kq = locNhanVienTheoQueQuan(B, qq);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 4:
                    {
                        cin.ignore();
                        string pns;
                        cout << "\n\t\tNhap phong nhan su can loc: ";
                        getline(cin, pns);
                        Node* kq = locNhanVienTheoPhongNhanSu(B, pns);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 5:
                    {
                        int min, max;
                        cout << "\n\t\tNhap khoang luong min-max: ";
                        cin >> min >> max;
                        Node* kq = locNhanVienTheoKhoangLuongTongKet(B, min, max);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                default:
                    cout << "\n\t\tLua chon khong hop le...";
                    break;
                }
            }
            break;
        }

        case 14:
        {
            List C;
            int luaChon;
            khoiTao(C);
            tachTheoQuy3(l, C);
            cout << "\n\t\tNhan phim bat ki de vao Quy 3...";
            system("pause");
            while (true)
            {
                system("cls");
                cout << "\n\t\t=========Quy 3==========";
                cout << "\n\t\t1. Xuat thong tin";
                cout << "\n\t\t2. Tim kiem thong tin";
                cout << "\n\t\t3. Sap xep tang";
                cout << "\n\t\t4. Sap xep giam";
                cout << "\n\t\t5. Loc nhan vien";
                cout << "\n\t\tNhap 0 de thoat";
                cout << "\n\t\tNhap lua chon: ";
                cin >> luaChon;

                if (luaChon == 0)
                {
                    break;
                }
                switch (luaChon)
                {
                case 1:
                {
                    khoiTao(C);
                    tachTheoQuy3(l, C);
                    system("pause");
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    cout << "\n\t\tNhap ma nhan vien can tim: ";
                    getline(cin, manv);
                    Node* timKiem = timKiemThongTinNhanVienTheoMa(C, manv);
                    if (timKiem == NULL)
                    {
                        cout << "\n\t\tKhong tim thay...";
                    }
                    else
                    {

                        xuatThongTinNhanVien(timKiem->data);
                    }
                    system("pause");
                    break;
                }

                case 3:
                    system("cls");
                    int luaChonSXT;
                    cout << "\n\t\t=====Sap xep tang======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSXT;
                    if (luaChonSXT == 0)
                    {
                        break;
                    }

                    switch (luaChonSXT)
                    {

                    case 1:
                    {
                        sapXepTangDanTheoLuongTongKet(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepTangDanTheoLuongCoBan(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepTangDanTheoTen(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepTangDanTheoNamSinh(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 4:
                    system("cls");
                    int luaChonSSG;
                    cout << "\n\t\t=====Sap xep giam======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSSG;
                    if (luaChonSSG == 0)
                    {
                        break;
                    }

                    switch (luaChonSSG)
                    {

                    case 1:
                    {
                        sapXepGiamDanTheoLuongTongKet(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepGiamDanTheoLuongCoBan(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepGiamDanTheoTen(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepGiamDanTheoNamSinh(C);
                        xuatThongTinDanhSachNhanVien(C);
                        system("pause");
                        break;
                    }
                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 5:

                    system("cls");
                    int luaChonLoc;
                    cout << "\n\t\t=====LOC NHAN VIEN====";
                    cout << "\n\t\t1.Loc theo ten";
                    cout << "\n\t\t2. Loc theo nam sinh";
                    cout << "\n\t\t3. Loc theo que quan";
                    cout << "\n\t\t4. Loc theo phong nhan su";
                    cout << "\n\t\t5. Loc theo khoang luong tong ket";
                    cout << "\n\t\tNhap 0 de thoat...";
                    cout << "\n\t\tNhap lua chon cua ban: ";
                    cin >> luaChonLoc;

                    switch (luaChonLoc)
                    {
                    case 1:
                    {
                        cin.ignore();
                        string ten;
                        cout << "\n\t\tNhap ten can loc: ";
                        getline(cin, ten);
                        Node* kq = locNhanVienTheoTen(C, ten);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 2:
                    {
                        cin.ignore();
                        int namSinh;
                        cout << "\n\t\tNhap nam sinh can loc: ";
                        cin >> namSinh;
                        Node* kq = locNhanVienTheoNamSinh(C, namSinh);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        cin.ignore();
                        string qq;
                        cout << "\n\t\tNhap que quan can loc: ";
                        getline(cin, qq);
                        Node* kq = locNhanVienTheoQueQuan(C, qq);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 4:
                    {
                        cin.ignore();
                        string pns;
                        cout << "\n\t\tNhap phong nhan su can loc: ";
                        getline(cin, pns);
                        Node* kq = locNhanVienTheoPhongNhanSu(C, pns);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 5:
                    {
                        int min, max;
                        cout << "\n\t\tNhap khoang luong min-max: ";
                        cin >> min >> max;
                        Node* kq = locNhanVienTheoKhoangLuongTongKet(C, min, max);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                default:
                    cout << "\n\t\tLua chon khong hop le...";
                    break;
                }
            }
            break;
        }

        case 15:
        {
            List D;
            int luaChon;
            khoiTao(D);
            tachTheoQuy4(l, D);
            cout << "\n\t\tNhan phim bat ki de vao Quy 4...";
            system("pause");
            while (true)
            {
                system("cls");
                cout << "\n\t\t=========Quy 3==========";
                cout << "\n\t\t1. Xuat thong tin";
                cout << "\n\t\t2. Tim kiem thong tin";
                cout << "\n\t\t3. Sap xep tang";
                cout << "\n\t\t4. Sap xep giam";
                cout << "\n\t\t5. Loc nhan vien";
                cout << "\n\t\tNhap 0 de thoat...";
                cout << "\n\t\tNhap lua chon: ";
                cin >> luaChon;
                if (luaChon == 0)
                {
                    break;
                }
                switch (luaChon)
                {
                case 1:
                {
                    khoiTao(D);
                    tachTheoQuy4(l, D);
                    system("pause");
                    break;
                }
                case 2:
                {
                    cin.ignore();
                    cout << "\n\t\tNhap ma nhan vien can tim: ";
                    getline(cin, manv);
                    Node* timKiem = timKiemThongTinNhanVienTheoMa(D, manv);
                    if (timKiem == NULL)
                    {
                        cout << "\n\t\tKhong tim thay...";
                    }
                    else
                    {

                        xuatThongTinNhanVien(timKiem->data);
                    }
                    system("pause");
                    break;
                }

                case 3:
                    system("cls");
                    int luaChonSXT;
                    cout << "\n\t\t=====Sap xep tang======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSXT;
                    if (luaChonSXT == 0)
                    {
                        break;
                    }

                    switch (luaChonSXT)
                    {

                    case 1:
                    {
                        sapXepTangDanTheoLuongTongKet(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepTangDanTheoLuongCoBan(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepTangDanTheoTen(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepTangDanTheoNamSinh(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 4:
                    system("cls");
                    int luaChonSSG;
                    cout << "\n\t\t=====Sap xep giam======";
                    cout << "\n\t\t1. Theo luong tong ket";
                    cout << "\n\t\t2. Theo luong co ban";
                    cout << "\n\t\t3. Theo ten";
                    cout << "\n\t\t4. Theo nam sinh";
                    cout << "\n\t\tNhap 0 de thoat";
                    cout << "\n\t\tNhap lua chon: ";
                    cin >> luaChonSSG;
                    if (luaChonSSG == 0)
                    {
                        break;
                    }

                    switch (luaChonSSG)
                    {

                    case 1:
                    {
                        sapXepGiamDanTheoLuongTongKet(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        sapXepGiamDanTheoLuongCoBan(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        sapXepGiamDanTheoTen(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        sapXepGiamDanTheoNamSinh(D);
                        xuatThongTinDanhSachNhanVien(D);
                        system("pause");
                        break;
                    }
                    default:

                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                case 5:

                    system("cls");
                    int luaChonLoc;
                    cout << "\n\t\t=====LOD NHAN VIEN====";
                    cout << "\n\t\t1.Loc theo ten";
                    cout << "\n\t\t2. Loc theo nam sinh";
                    cout << "\n\t\t3. Loc theo que quan";
                    cout << "\n\t\t4. Loc theo phong nhan su";
                    cout << "\n\t\t5. Loc theo khoang luong tong ket";
                    cout << "\n\t\tNhap 0 de thoat...";
                    cout << "\n\t\tNhap lua chon cua ban: ";
                    cin >> luaChonLoc;

                    switch (luaChonLoc)
                    {
                    case 1:
                    {
                        cin.ignore();
                        string ten;
                        cout << "\n\t\tNhap ten can loc: ";
                        getline(cin, ten);
                        Node* kq = locNhanVienTheoTen(D, ten);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 2:
                    {
                        cin.ignore();
                        int namSinh;
                        cout << "\n\t\tNhap nam sinh can loc: ";
                        cin >> namSinh;
                        Node* kq = locNhanVienTheoNamSinh(D, namSinh);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        cin.ignore();
                        string qq;
                        cout << "\n\t\tNhap que quan can loc: ";
                        getline(cin, qq);
                        Node* kq = locNhanVienTheoQueQuan(D, qq);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 4:
                    {
                        cin.ignore();
                        string pns;
                        cout << "\n\t\tNhap phong nhan su can loc: ";
                        getline(cin, pns);
                        Node* kq = locNhanVienTheoPhongNhanSu(D, pns);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    case 5:
                    {
                        int min, max;
                        cout << "\n\t\tNhap khoang luong min-max: ";
                        cin >> min >> max;
                        Node* kq = locNhanVienTheoKhoangLuongTongKet(D, min, max);
                        if (kq == NULL)
                        {
                            cout << "Khong tim thay...";
                        }
                        system("pause");
                        break;
                    }

                    default:
                        cout << "\n\t\tLua chon khong hop le...";
                        break;
                    }

                    break;

                default:
                    cout << "\n\t\tLua chon khong hop le...";
                    break;
                }
            }
            break;
        }

        case 16: 
        {
            int lcGhi;
            while (true)
            {
                system("cls");
                cout << "\n\t\t=========Ghi du lieu sap xep===========";
                cout << "\n\t\t1. Ghi file sap xep tang dan theo luong tong ket";
                cout << "\n\t\t2. Ghi file sap xep giam dan theo luong tong ket";
                cout << "\n\t\tNhap 0 thoat...";

                cout << "\n\t\tNhap lua chon: ";
                cin >> lcGhi;

                if (lcGhi == 0) {
                    break;
                }

                switch (lcGhi)
                {
                case 1:
                {
                    ghiDanhSachSapXepTheoLuongTKTangDan(l);
                    cout << "\n\t\tGhi du lieu thanh cong!";
                    system("pause");

                    break;
                }
                case 2:
                {
                    ghiDanhSachSapXepTheoLuongTKGiamDan(l);
                    cout << "\n\t\tGhi du lieu thanh cong!";
                    system("pause");

                    break;
                }
                default: 
                    
                    break;
                }
            }
            break;
            
        }
        default:

            cout << "\n\t\tLua chon khong phu hop...";
            system("pause");
            break;
        }
    }
}

int main()
{
    List l;
    khoiTao(l);
    MENU(l);
    return 0;
}