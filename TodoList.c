#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct liste {
    char baslik[100];
    char oncelik[100];
    char aciklama[1000];
    char sontarih[100];
    char durum[100];
    int ilerleme;
    time_t yapilistarihi;
    struct liste* sonraki;
};

struct liste* kafa = NULL;

void listeyikaydet(FILE *kayitliliste) {

    struct liste* gecici = kafa;

    while (gecici != NULL) {
        fprintf(kayitliliste,"%s,%s,%s,%s,%s,%d,%d\n",gecici->baslik, gecici->aciklama, gecici->sontarih,gecici->durum, gecici->oncelik, gecici->ilerleme,gecici->yapilistarihi);
        gecici = gecici->sonraki;
    }
}

void listeoku(FILE* kayitliliste) {
    char sontarih[100],aciklama[1000],oncelik[100],baslik[100],durum[100];
    int ilerleme;

    while(fscanf(kayitliliste,"%99[^,],%999[^,],%99[^,],%99[^,],%99[^,],%d\n",baslik,aciklama,sontarih,durum,oncelik,&ilerleme) == 6) {
        gorevolustur(baslik,aciklama,sontarih,durum,ilerleme,oncelik);
    }
}

void listegoruntule() {
    struct liste* gecici = kafa;
    if(gecici==NULL) {
        printf("Goruntulenecek gorev yok.\n\n");
        return;
    }
    int sayac = 0;
    printf("\n\nGorev Listeniz : \n\n");
    while (gecici != NULL) {
        sayac++;
        printf("%d .) %s\n", sayac,gecici->baslik);
        gecici = gecici->sonraki;
    }
    printf("\n\nGorev Listeniz Sona Ermistir\n\n");
}

void gorevolustur(char *baslik,char*aciklama,char*sontarih,char*durum,int ilerleme,char*oncelik){
    struct liste* gecici=kafa;
    struct liste* yenigorev=(struct liste *)malloc(sizeof(struct liste));
    yenigorev->sonraki=NULL;
    strcpy(yenigorev->baslik,baslik);
    strcpy(yenigorev->aciklama,aciklama);
    strcpy(yenigorev->sontarih,sontarih);
    strcpy(yenigorev->durum,durum);
    strcpy(yenigorev->oncelik,oncelik);
    yenigorev->ilerleme=ilerleme;
    yenigorev->yapilistarihi = time(NULL);

    if (kafa==NULL){
        kafa=yenigorev;
        kafa->sonraki=NULL;
        return;
    }
    while (gecici->sonraki!=NULL){
        gecici=gecici->sonraki;
    }
    gecici->sonraki=yenigorev;
}

void sil(int silinecek) {
    struct liste* gecici=kafa;
    struct liste* onceki=NULL;
    int sayac=0;
    while(gecici != NULL){
        sayac++;
        if (sayac==silinecek){
            if (sayac==1){
                kafa=kafa->sonraki;
                return;
            }
            onceki->sonraki=gecici->sonraki;
        }
        onceki=gecici;
        gecici=gecici->sonraki;
    }
    if (gecici==NULL){
        printf("\nSilinecek Eleman Listede Bulunamadi\n");
    }
}

void sirayagoregoster(int sira){
    struct liste* gecici=kafa;
    int sayac=0;
    while (gecici!=NULL){
        sayac++;
        if (sayac==sira){
            printf("Gorev Basligi : %s\n",gecici->baslik);
            printf("Gorev Aciklamasi : %s\n",gecici->aciklama);
            printf("Gorevin Son Tarihi : %s\n",gecici->sontarih);
            printf("Gorevin Durumu : %s\n",gecici->durum);
            printf("Gorev İlerlemesi : %d\n",gecici->ilerleme);
            printf("Gorev Onceligi : %s\n",gecici->oncelik);
        }
        gecici=gecici->sonraki;
    }
}

void arama(char *baslik){
    struct liste* gecici=kafa;
    int sayac=0;
    int bul=0;
    while(gecici!=NULL){
        sayac++;
        if(strcmp(baslik,gecici->baslik)==0) {
            sirayagoregoster(sayac);
            printf("\n");
            bul=1;
        }
        gecici=gecici->sonraki;
    }
    if(!bul){
        printf("Aranan Gorev Bulunamadi\n");
    }
}

void tariharama(char *tarih){
    struct liste* gecici = kafa;
    int sayac=0;
    int bul=0;
    while (gecici!=NULL){
        sayac++;
        if (strcmp(tarih,gecici->sontarih)==0) {
            sirayagoregoster(sayac);
            printf("\n");
            bul=1;
        }
        gecici=gecici->sonraki;
    }
    if (!bul) {
        printf("Aranan Gorev Bulunamadi\n");
    }
}

void oncelikarama(char *oncelik){
    struct liste* gecici = kafa;
    int sayac=0;
    int bul=0;
    while (gecici!=NULL){
        sayac++;
        if (strcmp(oncelik,gecici->oncelik)==0){
            sirayagoregoster(sayac);
            printf("\n");
            bul=1;
        }
        gecici=gecici->sonraki;
    }

    if(!bul){
        printf("Aranan Gorev Bulunamadi\n");
    }
}

void otosil(){

    struct liste* gecici = kafa;
    struct liste* onceki = NULL;
    time_t bugun = time(NULL);
    int saniye = 1;
    while(gecici !=NULL ){
        if(bugun - gecici->yapilistarihi>=saniye){
            if(kafa == gecici){
                kafa = kafa -> sonraki;
                free(gecici);
                return;
            }
            onceki -> sonraki = gecici -> sonraki;

        }

        onceki = gecici;
        gecici = gecici->sonraki;
    }
    free(gecici);
    free(onceki);


}

int main(){
    int ilerleme,silinecek,secim;
    char sontarih[100],aciklama[1000],oncelik[100],baslik[100],durum[100];
    
    
    FILE *kayitliliste=fopen("213ToDoList.txt","r");
    if(kayitliliste!=NULL){
        listeoku(kayitliliste);
        fclose(kayitliliste);
    }
    
    while(1){
        printf("\n1.) Listenizi Goruntuleyin.\n");
        printf("2.) Yeni Gorev Olusturun.\n");
        printf("3.) Gorev Silin.\n");
        printf("4.) Arama / Filtreleme Yapin.\n");
        printf("5.) Kaydedip Cikis Yapin.\n");
        printf("Seciminizi Girin : ");
        scanf("%d", &secim);
        getchar();

        switch(secim){
            case 1:
                otosil();
                listegoruntule();
                break;
            case 2:
                printf("\nOlusturacaginiz Gorevin Basligini Giriniz : ");
                gets(baslik);
                printf("\nOlusturacaginiz Gorevin Aciklamasini Giriniz : ");
                gets(aciklama);
                printf("\nOlusturacaginiz Son Tarihini Basligini Giriniz : ");
                gets(sontarih);
                printf("\nOlusturacaginiz Gorevin Durumunu Giriniz : (Baslamadi, Devam Ediyor, Tamamlandi) ");
                gets(durum);
                printf("\nOlusturacaginiz Gorevin İlerleme Durumunu (%%) Giriniz : ");
                scanf("%d", &ilerleme);
                getchar();
                printf("\nOlusturacaginiz Gorevin Oncelik Durumunu Giriniz : ");
                gets(oncelik);
                gorevolustur(baslik, aciklama, sontarih, durum, ilerleme, oncelik);
                break;
            case 3:
                listegoruntule();
                printf("Silmek İstediginiz Gorevi Seciniz : ");
                scanf("%d", &silinecek);
                sil(silinecek);
                break;
            case 4:
                printf("1.) Basliga Gore Gorev Aramasi Yapmak\n");
                printf("2.) Son Tarihe Gore Gorev Aramasi Yapmak\n");
                printf("3.) Oncelige Gore Gorev Filtrelemesi Yapmak\n");
                scanf("%d",&secim);
                getchar();
                switch (secim) {
                    case 1:
                        printf("Aramasini Yapmak İstediginiz Basligi Giriniz : ");
                        gets(baslik);
                        arama(baslik);
                        break;
                    case 2:
                        printf("Aramak İstediginiz Son Tarihi Giriniz :");
                        gets(sontarih);
                        tariharama(sontarih);
                        break;
                    case 3:
                        printf("Aramak İstediginiz Onceligi Giriniz :");
                        gets(oncelik);
                        oncelikarama(oncelik);
                        break;
                }
                break;
            case 5:
                kayitliliste=fopen("213ToDoList.txt", "w");
                if (kayitliliste==NULL) {
                    printf("kayitliliste acilamadi.\n");
                    exit(EXIT_FAILURE);
                }
                listeyikaydet(kayitliliste);
                fclose(kayitliliste);
                exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    }
    return 0;
}