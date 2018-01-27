#include <stdio.h>
#include <stdlib.h>

int sayi_al(int,int);
int yarismaciNoTekrarKontolu(int [],int,int,int);
void sirala(int yarismaciSayisi,int *topPuan,int *kocPuanDizisi,int *seyirciPuanDizisi,int *yarismaciNoDizisi);
void kucuktenBuyuge(int yarismaciSayisi,int *genelTopPuan,int *genelKocPuanDizisi,int *genelSeyirciPuanDizisi,int *genelYarismaciNoDizisi);
void sirala2(int yarismaciSay,int *genel,int *no);
int main()
{
    int secim;
    int devam,devam2;
    char cevap;
    int yarismaciSayisi,haftaSayisi;
    int i,j,s;
    int k,gecici;
    int puanVermeDizisi[3]= {1,2,3};
    int kontrolDizisi[3]= {0};
    int kocIndex;
    int katsayi;

    int topPuan[20]= {0};
    int genelTopPuan[20]= {0};
    int kocPuanDizisi[20]= {0};
    int genelKocPuanDizisi[20]= {0};
    int seyirciPuanDizisi[20]= {0};
    int genelSeyirciPuanDizisi[20]= {0};
    int yarismaciNoDizisi[20]= {0};
    int genelYarismaciNoDizisi[20]= {0};
    int koclarinPuanTablosu[20][20]= {{0}};
    int genelKoclarinPuanTablosu[20][20]= {{0}};
    int haftalikMatris[20][20]= {{0}};
    int birincilikDizisi[20]= {0};
    int a,max,p;
    int birinciMaddeKontrol=0;
    int genelKopya1[20],genelKopya2[20],noKopya1[20],noKopya2[20];
    int e=0;//ana menuden 1.maddeyi 1 kere bile secse 1 yaparız.
    do
    {
        devam=0;//Ana menuye tekrar donulup donulmeyecegini kontrol etmek icin.
        printf("   ANA MENU   \n");
        printf("1. Yeni Yarisma Duzenleme\n");
        printf("2. Son Duzenlenen Yarismanin Istatistiklerini Goruntuleme\n");
        printf("3. Cikis\n");

        printf("Seciminizi giriniz:\n");
        secim=sayi_al(1,3);
        switch(secim)
        {
        case 1:
        {
            birinciMaddeKontrol=1;
            if(e==1)//genel tablolarin sifirlanmasi
            {
                for(i=0; i<yarismaciSayisi; i++)
                {
                    genelKocPuanDizisi[i]=0;
                    genelSeyirciPuanDizisi[i]=0;
                    genelTopPuan[i]=0;
                    genelYarismaciNoDizisi[i]=0;
                    birincilikDizisi[i]=0;
                    for(j=0; j<yarismaciSayisi; j++)
                    {
                        koclarinPuanTablosu[i][j]=0;
                        genelKoclarinPuanTablosu[i][j]=0;
                        haftalikMatris[i][j]=0;
                    }

                }
            }
            p=0;
            printf("Yarismaci sayisini giriniz:\n");
            yarismaciSayisi=sayi_al(5,20);
            katsayi=yarismaciSayisi-1;//seyirci icin

            printf("Yarismanin devam edecegi hafta sayisini giriniz:\n");
            scanf("%d",&haftaSayisi);

            while(haftaSayisi<3)
            {
                printf("Yarisma en az 3 hafta surmeli.\nLutfen tekrar deneyiniz.\n");
                scanf("%d",&haftaSayisi);
            }

            //her hafta icin gerceklesecek olanlar
            for(s=0; s<haftaSayisi; s++)
            {
                for(j=0; j<yarismaciSayisi; j++) //burada yarismaci sayisi koc sayisidir.Her koc icin donecek.
                {
                    kocIndex=j+1;

                    printf("Puan vermek istediginiz 3 tane yarismaci no giriniz:");
                    for(k=0; k<3; k++)
                    {
                        gecici=sayi_al(1,yarismaciSayisi);
                        gecici=yarismaciNoTekrarKontolu(kontrolDizisi,gecici,kocIndex,yarismaciSayisi);
                        //ayni yarismaci no girilirse farkli bir yarismaci no alip geciciye atar.
                        //aynı zamanda kocun kendi yarismacisina puan vermesini engeller.
                        kontrolDizisi[k]=gecici;
                        koclarinPuanTablosu[gecici-1][j]=puanVermeDizisi[k];
                        genelKoclarinPuanTablosu[gecici-1][j]+=puanVermeDizisi[k];
                        haftalikMatris[gecici-1][s]+=puanVermeDizisi[k];
                        printf("\n");

                    }

                    for(i=0; i<3; i++)
                        kontrolDizisi[i]=0;
                }
                for(i=0; i<3; i++)
                    kontrolDizisi[i]=0;

                //seyircilerin puan verdigi kisim

                kocIndex=-1;
                //seyirciler icin yarismaciNoTekrarKontolu fonksiyonu kullanilacak
                //kocIndex parametresi hata vermesin diye -1 atandı.
                printf("Seyirciler puan veriyor:\n");

                for(k=0; k<3; k++)
                {
                    gecici=sayi_al(1,yarismaciSayisi);
                    gecici=yarismaciNoTekrarKontolu(kontrolDizisi,gecici,kocIndex,yarismaciSayisi);
                    kontrolDizisi[k]=gecici;
                    seyirciPuanDizisi[gecici-1]=katsayi*puanVermeDizisi[k];
                    haftalikMatris[gecici-1][s]+=katsayi*puanVermeDizisi[k];
                    //koclarin ve seyircilerin verdikleri puanlar esit agirlikta olsun diye.
                    printf("\n");
                }
                for(i=0; i<3; i++)
                    kontrolDizisi[i]=0;

                for(i=0; i<yarismaciSayisi; i++)
                {
                    topPuan[i]+=seyirciPuanDizisi[i];

                    yarismaciNoDizisi[i]=i+1;


                    for(j=0; j<yarismaciSayisi; j++)
                    {
                        //seyircilerin ve koclarin verdikleri puanlar topPuan dizisinde toplaniyor.
                        topPuan[i]+=koclarinPuanTablosu[i][j];


                        kocPuanDizisi[i]+=koclarinPuanTablosu[i][j];

                    }



                }



                //puanlama sonuclari
                printf("%d. haftanin sonuclari:\n",s+1);
                for(i=0; i<yarismaciSayisi; i++)
                {
                    genelYarismaciNoDizisi[i]=yarismaciNoDizisi[i];
                    genelTopPuan[i]+=topPuan[i];
                    genelKocPuanDizisi[i]+=kocPuanDizisi[i];
                    genelSeyirciPuanDizisi[i]+=seyirciPuanDizisi[i];
                }
                //topPuan siralaniyor.sirala fonksiyonunda siralama ve listeleme yapiliyor.
                sirala(yarismaciSayisi,topPuan,kocPuanDizisi,seyirciPuanDizisi,yarismaciNoDizisi);


                //genel durumlar hatali
                printf("%d. hafta sonunda genel durum:\n",s+1);


                sirala(yarismaciSayisi,genelTopPuan,genelKocPuanDizisi,genelSeyirciPuanDizisi,genelYarismaciNoDizisi);

                //yarismaci no'ya gore siralaniyor en son ki bir sonraki turda indekslerde bir sonrakinin puanlarini eklerken sorun olmasin.
                kucuktenBuyuge(yarismaciSayisi,genelTopPuan,genelKocPuanDizisi,genelSeyirciPuanDizisi,genelYarismaciNoDizisi);
                for(i=0; i<yarismaciSayisi; i++)
                {
                    seyirciPuanDizisi[i]=0;
                    kocPuanDizisi[i]=0;
                    topPuan[i]=0;
                    yarismaciNoDizisi[i]=0;
                    for(j=0; j<yarismaciSayisi; j++)
                    {
                        koclarinPuanTablosu[i][j]=0;
                    }
                }
            }

            //ana menuye donmek icin devam 1 yapılır.
            for(i=0; i<yarismaciSayisi; i++)
            {
                if(p<haftaSayisi)
                {
                    a=0;
                    max=haftalikMatris[0][p];
                    for(j=0; j<haftaSayisi; j++)
                    {
                        if(haftalikMatris[j][i]>max)
                        {
                            max=haftalikMatris[j][i];
                            a=j;
                        }
                    }
                    birincilikDizisi[a]+=1;
                }
                else
                    break;
                p++;
            }
            devam=1;
            e=1;

        }
        break;
        case 2:

            if(birinciMaddeKontrol==1)
            {


                do
                {

                    devam2=0;//alt menuye geri donmek icin

                    printf("   ISTATISTIK ALT MENUSU\n");
                    printf("1. Sadece koclarin puanlamasi dikkate alindiginda genel durumun listelenmesi\n");
                    printf("2. Sadece seyircilerin puanlamasi dikkate alindiginda genel durumun listelenmesi\n");
                    printf("3. Yarismacilarin her hafta aldiklari toplam puanlarin listelenmesi\n");
                    printf("4. Yarismacilarin her koctan aldiklari toplam puanlarin listelenmesi\n");
                    printf("5. Ana Menu\n");
                    printf("Seciminizi giriniz:\n");
                    secim=sayi_al(1,5);
                    switch (secim)
                    {
                    case 1:
                        for(i=0; i<yarismaciSayisi; i++)
                        {
                            genelKopya1[i]=genelKocPuanDizisi[i];
                            noKopya1[i]=genelYarismaciNoDizisi[i];
                        }
                        sirala2(yarismaciSayisi,genelKopya1,noKopya1);
                        devam2=1;
                        break;
                    case 2:
                        for(i=0; i<yarismaciSayisi; i++)
                        {
                            genelKopya2[i]=genelSeyirciPuanDizisi[i];
                            noKopya2[i]=genelYarismaciNoDizisi[i];
                        }
                        sirala2(yarismaciSayisi,genelKopya2,noKopya2);
                        devam2=1;
                        break;
                    case 3:

                        printf("Yarismacilarin her hafta aldiklari toplam puanlar:\n");
                        printf("Yarismaci No  1.Hafta  2.Hafta  3.Hafta  4.Hafta  5.Hafta  1.lik Sayisi\n");
                        printf("------------  -------  -------  -------  -------  -------  ------------\n");
                        //yarismacino'ya haftaliik bir matrisi dolasiyoruz.
                        for(i=0; i<yarismaciSayisi; i++)
                        {
                            j=0;
                            printf("%5d%8d%9d%10d%11d%12d%13d\n",i+1,haftalikMatris[i][j],haftalikMatris[i][j+1],haftalikMatris[i][j+2],haftalikMatris[i][j+3],haftalikMatris[i][j+4],birincilikDizisi[i]);

                        }
                        devam2=1;
                        break;
                    case 4:
                        printf("Yarismacilarin her koctan aldiklari toplam puanlar:\n");
                        printf("Yarismaci No  Koc 1   Koc 2   Koc 3   Koc 4   Koc 5\n");
                        printf("------------  -----   -----   -----   -----   -----\n");
                        for(i=0; i<yarismaciSayisi; i++)
                        {
                            j=0;
                            printf("%5d%10d%11d%12d%13d%13d\n",i+1,genelKoclarinPuanTablosu[i][j],genelKoclarinPuanTablosu[i][j+1],genelKoclarinPuanTablosu[i][j+2],genelKoclarinPuanTablosu[i][j+3],genelKoclarinPuanTablosu[i][j+4]);


                        }
                        devam2=1;
                        break;
                    case 5:
                        devam2=0;
                        devam=1;//ana menuye donmek icin
                        break;


                    }

                }
                while(devam2==1);
            }
            else
            {
                printf("\n\nDaha once yarisma duzenlenmedigi icin gosterilecek herhangi bir istatistik yok.\n\n");
            }
            //ana menuye donmek icin devam 1 yapılır.
            devam=1;
            break;
        case 3:
            do
            {
                printf("Programdan cikmak istediginize emin misiniz:(E e H h)\n");
                fflush(stdin);
                cevap=getchar();
            }
            while(!(cevap=='E'||cevap=='e'||cevap=='H'||cevap=='h'));
            if(cevap=='E' ||cevap=='e')
                devam=0;
            else
                devam=1;
            break;
        }
    }
    while(devam==1);
    return 0;
}
int sayi_al(int alt_sinir,int ust_sinir)
{
    int sayi;
    scanf("%d",&sayi);
    while(sayi<alt_sinir || sayi>ust_sinir)
    {
        printf("\nLutfen uygun aralikta bir secim yapiniz:");
        scanf("%d",&sayi);
    }
    return sayi;
}
int yarismaciNoTekrarKontolu(int kontolDizisi[3],int gecici,int kocIndex,int yarismaciSayisi)
{
    int k;

    for(k=0; k<3; k++)
    {
        while(kontolDizisi[k]==gecici)
        {
            printf("Bu yarismaciya daha once puan verildi.\nLutfen baska bir yarismaci no giriniz:\n");
            gecici=sayi_al(1,yarismaciSayisi);
        }
        while(gecici==kocIndex)
        {
            printf("Kendi yarismaciniza puan veremezsiniz.\nLutfen baska bir yarismaci no giriniz:\n");
            gecici=sayi_al(1,yarismaciSayisi);
        }
    }

    return gecici;
}
void sirala(int yarismaciSayisi,int* topPuan,int* kocPuanDizisi,int* seyirciPuanDizisi,int* yarismaciNoDizisi)
{
    int i,j;
    int temp,temp2,temp3,temp4;

    for(i=1; i<yarismaciSayisi; i++)
    {
        for(j=0; j<yarismaciSayisi-i; j++)
        {
            if(topPuan[j]<topPuan[j+1])
            {
                temp=topPuan[j+1];
                topPuan[j+1]=topPuan[j];
                topPuan[j]=temp;

                temp2=kocPuanDizisi[j+1];
                kocPuanDizisi[j+1]=kocPuanDizisi[j];
                kocPuanDizisi[j]=temp2;

                temp3=seyirciPuanDizisi[j+1];
                seyirciPuanDizisi[j+1]=seyirciPuanDizisi[j];
                seyirciPuanDizisi[j]=temp3;

                temp4=yarismaciNoDizisi[j+1];
                yarismaciNoDizisi[j+1]=yarismaciNoDizisi[j];
                yarismaciNoDizisi[j]=temp4;

            }
            else if(topPuan[j]==topPuan[j+1])
            {
                if(kocPuanDizisi[j]<kocPuanDizisi[j+1])
                {
                    temp=topPuan[j+1];
                    topPuan[j+1]=topPuan[j];
                    topPuan[j]=temp;

                    temp2=kocPuanDizisi[j+1];
                    kocPuanDizisi[j+1]=kocPuanDizisi[j];
                    kocPuanDizisi[j]=temp2;

                    temp3=seyirciPuanDizisi[j+1];
                    seyirciPuanDizisi[j+1]=seyirciPuanDizisi[j];
                    seyirciPuanDizisi[j]=temp3;

                    temp4=yarismaciNoDizisi[j+1];
                    yarismaciNoDizisi[j+1]=yarismaciNoDizisi[j];
                    yarismaciNoDizisi[j]=temp4;
                }
                else if(kocPuanDizisi[j]==kocPuanDizisi[j+1])
                {

                    if(yarismaciNoDizisi[j]>yarismaciNoDizisi[j+1])
                    {
                        temp=topPuan[j];
                        topPuan[j]=topPuan[j+1];
                        topPuan[j+1]=temp;

                        temp2=kocPuanDizisi[j];
                        kocPuanDizisi[j]=kocPuanDizisi[j+1];
                        kocPuanDizisi[j+1]=temp2;

                        temp3=seyirciPuanDizisi[j];
                        seyirciPuanDizisi[j]=seyirciPuanDizisi[j+1];
                        seyirciPuanDizisi[j+1]=temp3;

                        temp4=yarismaciNoDizisi[j];
                        yarismaciNoDizisi[j]=yarismaciNoDizisi[j+1];
                        yarismaciNoDizisi[j+1]=temp4;
                    }

                }
            }
        }
    }

    printf("Sira No   Yarismaci No   Koc Puani   Seyirci Puani   Toplam Puani\n");
    printf("-------   ------------   ---------   -------------   ------------\n");
    for(i=0; i<yarismaciSayisi; i++)
    {
        printf("%3d%9d%15d%17d%25d\n",i+1,yarismaciNoDizisi[i],kocPuanDizisi[i],seyirciPuanDizisi[i],topPuan[i]);
    }


}
void kucuktenBuyuge(int yarismaciSayisi,int *genelTopPuan,int *genelKocPuanDizisi,int *genelSeyirciPuanDizisi,int *genelYarismaciNoDizisi)
{
    int i,j;
    int temp,temp2,temp3,temp4;
    for(i=1; i<yarismaciSayisi; i++)
    {
        for(j=0; j<yarismaciSayisi-i; j++)
        {
            if(genelYarismaciNoDizisi[j]>genelYarismaciNoDizisi[j+1])
            {
                temp=genelTopPuan[j];
                genelTopPuan[j]=genelTopPuan[j+1];
                genelTopPuan[j+1]=temp;

                temp2=genelKocPuanDizisi[j];
                genelKocPuanDizisi[j]=genelKocPuanDizisi[j+1];
                genelKocPuanDizisi[j+1]=temp2;

                temp3=genelSeyirciPuanDizisi[j];
                genelSeyirciPuanDizisi[j]=genelSeyirciPuanDizisi[j+1];
                genelSeyirciPuanDizisi[j+1]=temp3;

                temp4=genelYarismaciNoDizisi[j];
                genelYarismaciNoDizisi[j]=genelYarismaciNoDizisi[j+1];
                genelYarismaciNoDizisi[j+1]=temp4;
            }
        }
    }

}
void sirala2(int yarismaciSay,int *genel,int *no)
{
    int i,j,temp,temp2;
    for(i=1; i<yarismaciSay; i++)
    {
        for(j=0; j<yarismaciSay-i; j++)
        {
            if(genel[j]<genel[j+1])
            {
                temp=genel[j+1];
                genel[j+1]=genel[j];
                genel[j]=temp;

                temp2=no[j+1];
                no[j+1]=no[j];
                no[j]=temp2;

            }
        }
    }
    printf("Sira No   Yarismaci No   Puan   \n");
    printf("-------   ------------   ----   \n");
    for(i=0; i<yarismaciSay; i++)
    {
        printf("%3d%9d%15d\n",i+1,no[i],genel[i]);
    }

}
