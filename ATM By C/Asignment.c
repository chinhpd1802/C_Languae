#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include <conio.h>
#include<windows.h>

// Struct Account chứa thông tin lưu vào file VTCA_Bank.dat
struct Account{
    char soTK[20];
    char nameAccount[50];
    float soDu;
    char donVi[10];
    int trangThai;
};

// Struct Account chứa thông tin lưu vào file VTCA_Bank_Log.dat
struct logAcc{
    char soTK[15];
    char nameAccount[25];
    float soTienGiaoDich;
    char timeGiaoDich[30];
    char NoiDung[50];
    char ghiChu[200];
};

char *checkSoTK;

void kiemTraSoDu();
int read_count();
struct Account *R_VTCA_Bank(int count);
void W_VTCA_Bank(int count, struct Account *acc);

void rutTien();
int read_Number(int check);
struct logAcc *R_VTCA_BANK_Log(int Number);
float CheckSoTienGiaoDich(int count,int check,struct Account *acc);
struct logAcc giaoDich(char *Name, float tien, int check);
void A_VTCA_Bank_Log(struct logAcc GiaoDich);

void chuyenKhoan();
char *checkTKchuyenTien(int count, struct Account *acc);

void DoiMaPin();
void checkMaPin(int check, int maPin);
void menu();

int  main()
{
    char *fileName;
    int maPin, check;

    fileName = (char *)malloc(sizeof(char)*15);
    checkSoTK = (char *)malloc(sizeof(char)*15);
    
    while(1)
    {
        system("cls");
        printf("======= Ngan Hang VTCAcademy =======\n");
        printf("----- Hay dua the cua ban vao ------\n");
        printf("Ten file: ");
        fflush(stdin);
        gets(fileName);
        strcat(fileName, ".dat");
        FILE *fp;                           // Tên tài khoản cũng là tên file
        fp = fopen(fileName , "r");         // Nên nếu không mở được file thì thông báo tài khoản không tồn tại.
        if(fp == NULL)
        {
            printf("Tai khoan khong ton tai!!!\nMoi ban nhap lai!");
            fflush(stdin);
            getchar();
        }
        else
        {
            fscanf(fp, "%s%d", checkSoTK, &check);  //Lấy ra số tài khoản gán vào biến toàn cục checkSoTK
            fclose(fp);                             // Và lấy mã pin để kiểm tra.
            while(1)
            {
                printf("Nhap ma pin: ");
                scanf("%d", &maPin);
                printf("--- Dang kiem tra thong tin---------\n");
                Sleep(1000);
                if(maPin == check)
                {
                    printf("====================================\n");
                    int count = read_count();         
                    struct Account *acc;
                    acc = R_VTCA_Bank(count);   
 
                    for(int i = 0; i<count; i++)
                    {
                        if(strcmp(checkSoTK, acc[i].soTK)==0 )
                        {  
                            printf("Xin chao mung %s", acc[i].nameAccount);
                            break;
                        }
                    }

                    fflush(stdin);
                    getchar();
                    menu();
                    break;
                }else{
                    printf("Sai ma pin!\nMoi ban nhap lai!");
                    fflush(stdin);
                    getchar();
                    system("cls");
                }

            }
            break;

        }

    }

    return 0;
}


// Hàm read_count() để lấy ra số lượng tài khoản
int read_count()
{

    int count = 0;
    FILE *f;
                    
    f = fopen("VTCA_Bank.dat", "rb");  //Phần tử đầu tiên của file VTCA_Bank.dat lưu số lượng phần tử của file đó
    if (f != NULL)
    {
        fread(&count, sizeof(int), 1, f);
        fclose(f);
    }

    return count;
}



// đọc file VTCA_Bank.dat và gán vào mảng acc
struct Account *R_VTCA_Bank(int count)
{
    struct Account *acc;
    FILE *f;
          
    f = fopen("VTCA_Bank.dat", "rb");

    if (f != NULL && count > 0)
    {
        fseek(f,sizeof(int),SEEK_SET);
        acc = (struct Account *)malloc(sizeof(struct Account) * count);
        fread(acc, sizeof(struct Account), count, f);

        fclose(f);
    }

    return  acc;
}

// Viết mảng acc vào file VTCA_Bank.dat
void  W_VTCA_Bank(int count,struct Account *acc)
{
    FILE *f;
    f = fopen("VTCA_Bank.dat", "wb");
    if (f != NULL)
    {
        
        fwrite(&count, sizeof(int), 1, f);
        
        fwrite(acc, sizeof(struct Account), count, f);
        fclose(f);
    }
}

void menu()
{
    int choice;
    do
    {
        system("cls");
        printf("=================================================\n");
        printf("------ Cac chuc nang may ATM cua VTCA Bank ------\n");
        printf("=================================================\n");
        printf("1. Kiem tra so du tai khoan.\n2. Rut tien\n3. Chuyen khoan\n");
        printf("4. Doi ma pin\n5. Ket thuc giao dich.\n");
        printf("=================================================\n");
        printf("#Chon: ");
        fflush(stdin);
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            system("cls");
            kiemTraSoDu();
            fflush(stdin);
            getchar();
            break;

            case 2 :
            system("cls");
            rutTien();
            break;

            case 3:
            system("cls");
            chuyenKhoan();
            break;

            case 4:
            system("cls");
            DoiMaPin();
            fflush(stdin);
            getchar();
            break;
            case 5:
                printf("=================================================\n");
                printf("\nXin chao va hen gap lai!");
                Sleep(1500);
                break;
            default: 

            break;
        }
    }while(choice != 5);

}


// Kiểm tra số dư và thông tin lần giao dịch gần nhất
void kiemTraSoDu()
{
    // Mở đọc file VTCA_Bank lấy dữ liệu
    printf("=================================================\n");
    char dv[10];                
    int count = read_count(), check = 0;
    struct Account *acc;
    acc = R_VTCA_Bank(count);   
    //Tìm thông tin của tài khoản đang đăng nhập và in dữ liệu ra màn hình
    for(int i = 0; i<count; i++)
    {
        if(strcmp(checkSoTK, acc[i].soTK)==0 )
        {  
            printf("So du trong tai khoan: %.3f %s\n", acc[i].soDu, acc[i].donVi);
            strcpy(dv,acc[i].donVi);
            break;
        }
    }
    

    // Mở đọc file VTCA_Bank_Log lấy dữ liệu
    int Number = read_Number(0);
    struct logAcc *lgAccount;
    lgAccount = R_VTCA_BANK_Log(Number);
    //Duyệt mảng từ cuối lên để lấy thông tin từ lần giao dịch gần nhất
    if(Number != 0)
    {
        for(int i = Number-1; i>=0; i--)
        {
            if(strcmp(checkSoTK, lgAccount[i].soTK)==0 )
            {

                printf("Lan giao dich gan nhat: %sNoi dung: %s\nSo tien giao dich: %.3f %s", lgAccount[i].timeGiaoDich, lgAccount[i].NoiDung, lgAccount[i].soTienGiaoDich, dv);
                printf("\nGhi chu: %s", lgAccount[i].ghiChu);
                check = 1;
                break;
            }
        }
        // Duyệt hết mảng mà không có hoặc file chưa tồn tại thì báo chưa giao dịch lần nào.
        if(check == 0)
        {
            printf("Ban chua giao dich lan nao!");
        }
    }else
    {
        printf("Ban chua giao dich lan nao!");
    }
    
}

// Đọc số lượng phần tử của file VTCA_BANK_Log
int read_Number(int check)
{
    int Number;
    FILE *f;
    f = fopen("Count.dat", "r");  // số lượng phần tử của file VTCA_BANK_Log được lưu trong mảng Count.dat


    if(f != NULL)
    {
        fseek(f, 0, SEEK_END);

        int len = ftell(f);
        if(len != 0)            //Kiểm tra mảng có rỗng hay không
        {
            rewind(f); //fseek(f,0,SEEK_SET);
            fscanf(f, "%d", &Number);
        }else{
            Number = 0;
        }
        fclose(f);
    }else
    {
        Number = 0;
    }   //Nếu rỗng hoặc không mở được file thì trả về 0

    if(check == 2)  //Number tăng khi được gọi ở chức năng chuyển tiền và rút tiền
    {
        Number ++;
        f = fopen("Count.dat", "w");
        if(f!=NULL)
        {
            fprintf(f, "%d", Number);   
            fclose(f);
        }
    }
    return Number;
}

// Đọc dữ liệu từ file VTCA_BANK_Log và lưu vào mảng lgAccount.
struct logAcc *R_VTCA_BANK_Log(int Number)
{
    FILE *f;
    struct logAcc *lgAccount;

    f = fopen("VTCA_Bank_Log.dat", "rb");
    if (f != NULL)
    {   
        lgAccount = (struct logAcc *)malloc(sizeof(struct logAcc)*Number);
        fread(lgAccount, sizeof(struct logAcc), Number, f);
        fclose(f);
    }

    return lgAccount;
    
}


// Hàm thực hiện chức năng rút tiền
void rutTien()
{
    //Đọc dữ liệu từ file VTCA_Bank.dat ra mảng acc.
    printf("=================================================\n");
    char dv[20];
    int count = read_count();
    struct Account *acc;
    acc = R_VTCA_Bank(count);

    float soDu;
    char Name[50], Choice;

    //Kiểm tra số tiền cần rút
    float tien = CheckSoTienGiaoDich(count,2,acc);

    printf("Ban co muon rut so tien nay? (y/n): ");
    fflush(stdin);
    scanf("%c", &Choice);
    if(Choice == 'y')
    {   
        printf("...Dang thuc hien rut tien..........\n");
        Sleep(1000);
        for(int i = 0; i<count; i++)
        {
            if(strcmp(checkSoTK, acc[i].soTK)==0 )
            {
                acc[i].soDu = (acc[i].soDu - tien);
                soDu = acc[i].soDu;
                strcpy(dv, acc[i].donVi);
                strcpy(Name, acc[i].nameAccount);
                break;
            }

        }
        
        //Ghi dữ liệu đã chỉnh sửa vào lại file
        W_VTCA_Bank(count, acc);
        printf("...Xong..............................\n");
        printf("So du trong tai khoan: %.3f %s\n", soDu, dv);

        //Tạo biến chứa thông tin của file VTCA_Bank_Log và thêm thông tin vào cuối file.
        struct logAcc GiaoDich;
        GiaoDich = giaoDich(Name, tien, 2);

        read_Number(2);

        A_VTCA_Bank_Log(GiaoDich);

            printf("Ban co muon in phieu? (y/n): ");
            fflush(stdin);
            scanf("%c", &Choice);
            
            if(Choice == 'y')
            {
                system("cls");
                printf("=================================================\n");
                printf("Tai khoan: %s tai VTC Bank\n-%.3f %s vao %s", GiaoDich.soTK, GiaoDich.soTienGiaoDich, dv, GiaoDich.timeGiaoDich);
                printf("So du trong tai khoan: %.3f %s\n", soDu, dv);
                printf("Noi Dung: %s\n", GiaoDich.NoiDung);
                printf("Ghi chu: %s",GiaoDich.ghiChu);
            }

            fflush(stdin);
            getchar();
    }
        

}

// Hàm kiểm tra số tiền muốn chuyển hoặc muốn rút có hợp lệ không
float CheckSoTienGiaoDich(int count,int check,struct Account *acc)
{
    float tien;
    while(1)
    {
        if(check == 2)
        {
            printf("Nhap so tien can rut: ");
        }else if(check == 3)
        {
            printf("Nhap so tien ban muon chuyen: ");
        }
        fflush(stdin);
        scanf("%f", &tien);
        if(tien<=0)         //Số tiền nhập vào không được âm.
        {
            printf("So tien khog hop le!\n");
            fflush(stdin);
            getchar();
            system("cls");
            printf("=================================================\n");
        }
        else
        {
            for(int i = 0; i<count; i++)
            {
                if(strcmp(checkSoTK, acc[i].soTK)==0 )
                {  
                    if(acc[i].soDu < tien)          // Số tiền nhập vào không vượt quá số dư trong TK
                    {
                        printf("So du cua ban khong du!\nMoi ban nhap lai!\n");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        printf("=================================================\n");
                    }else
                    {
                        check = 1;
                    }
                    break;
                }
            }
            if(check == 1)
            {
                break;
            }
        }

    }
    return tien;
}

//Tạo một biến chứa thông tin khi rút hoặc chuyển khoản
struct logAcc giaoDich(char *Name, float tien, int check)
{
    char choice;
    struct logAcc GiaoDich;
    strcpy(GiaoDich.soTK, checkSoTK);
    strcpy(GiaoDich.nameAccount, Name);
    GiaoDich.soTienGiaoDich = tien;
    time_t rawtime;
    time( &rawtime );
    strcpy(GiaoDich.timeGiaoDich, asctime(localtime( &rawtime )));
    if(check == 2)
    {
        strcpy(GiaoDich.NoiDung, "Rut Tien Tai ATM");
    }else if(check == 3)
    {

        strcpy(GiaoDich.NoiDung, "Chuyen khoan tai ATM");
    }
    
    printf("Ban Muon ghi chu gi khong?(y/n): ");
    fflush(stdin);
    scanf("%c", &choice);

    if(choice == 'y')
    {   
        printf("Ghi chu: ");
        fflush(stdin);
        scanf("%[^\n]s", GiaoDich.ghiChu);
    }else{
        strcpy(GiaoDich.ghiChu, "Khong Co Ghi Chu!");
    }

    return GiaoDich;
}

// Viết thông tin từ biến GiaoDich vào file VTCA_Bank_Log.dat
void A_VTCA_Bank_Log(struct logAcc GiaoDich)
{
    FILE *fp;
    fp = fopen("VTCA_Bank_Log.dat", "ab");
    if (fp != NULL)
    {   

        fwrite(&GiaoDich, sizeof(struct logAcc), 1, fp);
        fclose(fp);
    }
}

//Chức năng chuyển khoản
void chuyenKhoan()
{
    printf("=================================================\n");
    int check;
    char dv[20];
    int count = read_count();
    struct Account *acc;
    acc = R_VTCA_Bank(count);


    float soDu;
    char choice, *tkMuonChuyen, *Name;
    tkMuonChuyen = (char *)malloc(sizeof(char)*15);
    Name = (char *)malloc(sizeof(char)*50);

    tkMuonChuyen = checkTKchuyenTien(count, acc); //Check tài khoản muốn chuyển tiền tới có không


    float tien = CheckSoTienGiaoDich(count,3 ,acc); //Check số tiền muốn chuyển khoản có hợp lệ

    printf("Ban co muon chuyen so tien nay?(y/n): ");
    fflush(stdin);
    scanf("%c", &choice);
    if(choice == 'y')
    {
        printf("...Dang chuyen.......................\n");
        Sleep(1000);
        for(int i = 0; i<count; i++)
        {
            if(strcmp(tkMuonChuyen, acc[i].soTK)==0 )
            {
                acc[i].soDu = (acc[i].soDu + tien);     //Tăng số dư của tk được chuyển
                break;
            }
            
        }
        
        

        for(int i = 0; i<count; i++)
        {
            if(strcmp(checkSoTK, acc[i].soTK)==0 )
            {
                acc[i].soDu = (acc[i].soDu - tien);     //giảm số dư của chủ tk
                soDu = acc[i].soDu;
                strcpy(dv, acc[i].donVi);
                strcpy(Name, acc[i].nameAccount);
                break;
            }
            
        }

        // Viết các thông tin vừa cập nhật vào file VTCA_Bank và file VTCA_Bank_log
        W_VTCA_Bank(count,acc);



        printf("...Xong..............................\n");
        printf("So du trong tai khoan: %.3f %s\n", soDu, dv);




        struct logAcc GiaoDich = giaoDich(Name, tien, 3);

        read_Number(2);


        A_VTCA_Bank_Log(GiaoDich);

        printf("Ban co muon in phieu? (y/n): ");
        fflush(stdin);
        scanf("%c", &choice);
        
        if(choice == 'y')
        {
            system("cls");
            printf("=================================================\n");
            printf("Tai khoan: %s tai VTC Bank\n-%.3f %s vao %s", GiaoDich.soTK, GiaoDich.soTienGiaoDich, dv, GiaoDich.timeGiaoDich);
            printf("So du trong tai khoan: %.3f %s\n", soDu, dv);
            printf("Noi Dung: %s\n", GiaoDich.NoiDung);
            printf("Den tai khoan: %s\n", tkMuonChuyen);
            printf("Ghi chu: %s\n",GiaoDich.ghiChu);
        }

        fflush(stdin);
        getchar();
    }

}


char *checkTKchuyenTien(int count, struct Account *acc)
{
    int check;
    char *fileName, *tkMuonChuyen, *Name;
    fileName = (char *)malloc(sizeof(char)*15);
    tkMuonChuyen = (char *)malloc(sizeof(char)*15);
    Name = (char *)malloc(sizeof(char)*50);
    while(1)
    {
        for(int i = 0; i<count; i++)
        {
            if(strcmp(checkSoTK, acc[i].soTK)==0 )
            {  
                printf("So du trong tai khoan cua ban: %.3f %s\n", acc[i].soDu, acc[i].donVi);
                break;
            }
        }
        printf("Nhap tai khoan ban muon chuyen: ");
        fflush(stdin);
        scanf("%s", fileName);
        if(strcmp(fileName, checkSoTK)==0)
        {
            printf("Ban khong the tu chuyen khoan cho minh!\nMoi ban nhap lai!\n");
            fflush(stdin);
            getchar();
            system("cls");
            printf("=================================================\n");
        }else
        {
            strcat(fileName, ".dat");
            FILE *f;
            f = fopen(fileName, "r");
            if(f != NULL)
            {
                fscanf(f, "%s%d", tkMuonChuyen, &check);
                fclose(f);
                break;
            }
            else
            {
                printf("Khong tim thay tai khoan!\nMoi ban nhap lai!\n");
                fflush(stdin);
                getchar();
                system("cls");
                printf("=================================================\n");
            }
        }
        
    }
    return tkMuonChuyen;
}



// Chức năng đổi mã pin
void DoiMaPin()
{
    printf("=================================================\n");
    FILE *f;
    char *soTaiKhoan;
    int maPin, maPinMoi, CheckMaPin;

    soTaiKhoan = (char *)malloc(sizeof(char)*15);
    strcpy(soTaiKhoan, checkSoTK);
    strcat(soTaiKhoan, ".dat");

    f = fopen(soTaiKhoan, "r");
    if(f != NULL)
    {
        fscanf(f, "%s%d", checkSoTK, &maPin);       //Lấy mã pin cũ của TK hiện tại
        fclose(f);
    }

    FILE *fp;

    
    printf("nhap ma pin hien tai: ");
    checkMaPin(1, maPin);                   //Check mã pin hiện tại và mã pin nhập vào

    printf("\nNhap ma pin moi: ");
    fflush(stdin);

    char kytu;
    kytu = ' ';
    fp=fopen("password.dat","w+b");         //Lưu mã pin mới vào File pasword.dat
    while(kytu != 13)
    {
        kytu = getch();
        printf("*");
        if(kytu != 13 && kytu != ' ')
        {
            fprintf(fp,"%c",kytu);
        }

    }

    fseek(fp,0,SEEK_SET);
    fscanf(fp, "%d", &CheckMaPin );         //Đọc mã pin vừa nhập từ file pasword và gán vào biến CheckMapin
    fclose(fp);

    printf("\nxac nhan lai ma Pin moi: ");
    
    checkMaPin(2, CheckMaPin);              //Check mã pin hiện tại(CheckMapin) và mã pin nhập vào
                
    printf("\n...Dang doi ma Pin.........\n");
    Sleep(1000);

    f = fopen(soTaiKhoan, "w");
    if(f != NULL)
    {
        fprintf(f, "%s %d", checkSoTK, maPin);      //Đổi mã pin trong file.
        fclose(f);
    }
    printf("...xong....................\n");
}



void checkMaPin(int check, int maPin)
{
    char kytu;
    int checkMaPin;
    FILE *fp;
    do
    {   
        //Dùng file để lưu từng ký tự nhập vào đồng thời in ra *
        kytu = ' ';
        fp=fopen("password.dat","w+b");
        while(kytu != 13)                  //Nhập đến khi gặp ký tự xuống dòng
        {
            kytu = getch();
            printf("*");
            if(kytu != 13 && kytu != ' ') //Không lưu khoảng trắng và ký tự xuống dòng
            {
                fprintf(fp,"%c",kytu);
            }

        }
        
        fseek(fp,0,SEEK_SET);           //Đưa con trỏ về đầu file, đọc ra mã Pin vừa nhập vào và so sánh với mã Pin cũ.
        fscanf(fp, "%d", &checkMaPin );
        fclose(fp);
        if(checkMaPin != maPin)
        {
            system("cls");
            printf("=================================================\n");
            if(check == 1)
            {
                printf("Ma PIN khong dung!\nMoi ban nhap lai: ");
            }else
            {
                printf("Ma PIN moi khong dung!\nMoi ban nhap lai: ");
            }
        }
        
        
    }while(checkMaPin != maPin);
}