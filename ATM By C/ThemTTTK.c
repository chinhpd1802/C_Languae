#include<stdio.h>
#include<string.h>
#include<stdlib.h>


struct Account{
    char soTK[20];
    char nameAccount[50];
    float soDu;
    char donVi[10];
    int trangThai;
};

int main()
{
    struct Account *Acc;
    char AccNum1[20], AccNum2[20];
    int n = 0, maPin;
    char choice;
    
    Acc = (struct Account *)malloc(sizeof(struct Account)*(n+1));
    while(1)
    {
        Acc = (struct Account *)realloc( Acc, sizeof(struct Account)*(n+1+1));
        printf("Them thong tin cho 1 tai khoan\n");
        printf("Nhap so TK: ");
        fflush(stdin);
        scanf("%s", Acc[n].soTK);
        printf("Nhap ma pin: ");
        fflush(stdin);
        scanf("%d", &maPin);
        printf("Nhap ten TK: ");
        fflush(stdin);
        scanf("%[^\n]s", Acc[n].nameAccount);
        printf("Nhap so du trong TK: ");
        fflush(stdin);
        scanf("%f", &Acc[n].soDu);
        printf("Nhap don vi: ");
        fflush(stdin);
        scanf("%s", Acc[n].donVi);
        Acc[n].trangThai = 1;
        
        strcpy(AccNum1, Acc[n].soTK);
        strcpy(AccNum2, Acc[n].soTK);
        strcat(AccNum1, ".dat");
        FILE *f;
        f = fopen(AccNum1, "w");
        if(f != NULL)
        {
            fprintf(f, "%s %d", AccNum2, maPin);
            fclose(f);
        }
        


        printf("Da them tai khoan thanh cong!\nBan co muon them tai khoan nua?(y/n) ");
        fflush(stdin);
        scanf("%c", &choice);
        n ++;
        fflush(stdin);

        if(choice == 'n')
        {
            FILE *fp;
            fp = fopen("VTCA_Bank.dat", "wb");
            if (fp != NULL)
            {
                
                fwrite(&n, sizeof(int), 1, fp);
                
                fwrite(Acc, sizeof(struct Account), n, fp);
                fclose(fp);
            }
            break;

        }
         
    }

    return 0;
}