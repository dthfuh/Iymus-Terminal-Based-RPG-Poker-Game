#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

#define HARITA_GENISLIK 80
#define HARITA_YUKSEKLIK 30
#define KAMERA_GENISLIK 30
#define KAMERA_YUKSEKLIK 15

string sabitHarita[HARITA_YUKSEKLIK] = {
    "################################################################################",
    "#......................^^^^^^^........................T..T.....................#",
    "#..+-------------+.....^^^^^^^.......................T....T....................#",
    "#..|             |......^^^^..........................T..T.....................#",
    "#..|             |.............................................................#",
    "#..|E            |......T............................+-------------+...........#",
    "#..+----+ +------+...................................|             |...........#",
    "#.......| |..........................................|             |...........#",
    "#.......| |..........................................|             |...........#",
    "#.......| |..........................................+------+ +----+...........#",
    "#.......==...............+--------+..+-------+......^^^^^^^^| |^^^^............#",
    "#.......=................|        |..|       |......^^^^^^^^| |^^^^............#",
    "#.......=................|        |..|       |......^^^......=.................#",
    "#.......=................+---+ +--+..|       |...............====..............#",
    "#......T=.....T..............| |.....+--+ +--+..................=..............#",
    "#.......========================........| |.....................=..............#",
    "#......T...=..T..........................=......................=..............#",
    "#..........=.............................=..........+------+....=..............#",
    "#.....^^^^^=^............................=..........|      |....=..............#",
    "#.....^^^^^=^............................=..........|      |....=..............#",
    "#.......^^^=.............................=..........+--+ +-+....=..............#",
    "#..........=.............................=.............| |......=..............#",
    "#..........======================================================..............#",
    "#.....T........................................................................#",
    "#....T.T.......................................................................#",
    "#.....T...................................................^^^^^^...............#",
    "#........................................................^^^^^^................#",
    "#..............................................................................#",
    "#..............................................................................#",
    "################################################################################"
};

class Kart {
public:
    string renk; 
    int deger;   
    
    Kart() : renk(""), deger(0) {}
    Kart(string r, int d) : renk(r), deger(d) {}

    string degeriMetneCevir() {
        if(deger <= 10) return to_string(deger); 
        if(deger == 11) return "J"; 
        if(deger == 12) return "Q";
        if(deger == 13) return "K"; 
        if(deger == 14) return "A"; 
        return "";
    }
    string renkKoduAl() {
        if(renk == "♥" || renk == "♦") return "\033[1;31m"; 
        return "\033[1;36m"; 
    }
};

// =================================================================
// LINKED LIST YEHUU
// Log tutmak için kullandim 0_= 
// =================================================================
class LogDugumu {
public:
    string mesaj;
    LogDugumu* sonraki;
    LogDugumu(string m) : mesaj(m), sonraki(nullptr) {}
};

class SavasGecmisiBagliListesi {
private:
    LogDugumu* bas;
    LogDugumu* son;
    int boyut;
    int maksimumKapasite;

public:
    SavasGecmisiBagliListesi(int kapasite = 5) : bas(nullptr), son(nullptr), boyut(0), maksimumKapasite(kapasite) {}

    void logEkle(string yeniMesaj) {
        LogDugumu* yeniDugum = new LogDugumu(yeniMesaj);
        if (!bas) bas = son = yeniDugum;
        else { son->sonraki = yeniDugum; son = yeniDugum; }
        boyut++;

        if (boyut > maksimumKapasite) {
            LogDugumu* silinecek = bas;
            bas = bas->sonraki;
            delete silinecek; 
            boyut--;
        }
    }

    void loglariEkranaYazdir() {
        LogDugumu* gecici = bas;
        if(!gecici) cout << "  [Savas basladi, hamleni yap...]\n";
        while(gecici) {
            cout << "  > " << gecici->mesaj << "\n";
            gecici = gecici->sonraki;
        }
    }

    void listeyiTemizle() {
        while(bas) {
            LogDugumu* silinecek = bas;
            bas = bas->sonraki;
            delete silinecek;
        }
        son = nullptr;
        boyut = 0;
    }
};

class Dusman {
public:
    string isim; 
    int can; 
    int maksimumCan; 
    int x, y; 
    int saldiriGucu; 
    bool yenildiMi;

    Dusman() {} 
    Dusman(string i, int c, int mc, int cx, int cy, int sg, bool ym) {
        isim = i;
        can = c;
        maksimumCan = mc;
        x = cx;
        y = cy;
        saldiriGucu = sg;
        yenildiMi = ym;
    }
};

class Oyun {
private:
    int oyuncuX, oyuncuY;
    int oyuncuCan, oyuncuPuan;
    
    Dusman dusmanlar[8];             
    string kazanilanKupalar[8];      
    int kupaSayisi;                  

    Kart oyuncuEli[8];               
    
    Kart deste[52];                  
    int kalanKartSayisi;             

    string semboller[4] = {"♥", "♦", "♣", "♠"};
    SavasGecmisiBagliListesi savasLoglari; 
    string dusmanReplikleri[4] = {
        "Yiyosa pasaport pizza onu gel", "Insallah ben olmem...", 
        "Kardesim hosgeldin", "Korkuyosan kacsana kardesim!"
    };

    void dusmanlariYukle() {
        //              (Isim, GuncelCan, MaxCan, X, Y, SaldiriGucu, YenildiMi)
        dusmanlar[0] = Dusman("hursit", 100, 100, 15, 5, 10, false);
        dusmanlar[1] = Dusman("iyimuz", 150, 150, 30, 11, 15, false);
        dusmanlar[2] = Dusman("sermuz", 200, 200, 41, 12, 20, false);
        dusmanlar[3] = Dusman("baskan", 250, 250, 20, 17, 25, false);
        dusmanlar[4] = Dusman("han", 300, 300, 54, 18, 30, false);
        dusmanlar[5] = Dusman("yufka", 350, 350, 10, 25, 35, false);
        dusmanlar[6] = Dusman("yusa", 400, 400, 70, 25, 40, false);
        dusmanlar[7] = Dusman("hasan", 1000, 1000, 60, 7, 60, false);
    }

    void desteyiOlustur() {
        kalanKartSayisi = 0;
        for(int i = 0; i < 4; i++) {
            for(int d = 2; d <= 14; d++) {
                deste[kalanKartSayisi] = Kart(semboller[i], d);
                kalanKartSayisi++;
            }
        }
        
        for(int i = kalanKartSayisi - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Kart gecici = deste[i];
            deste[i] = deste[j];
            deste[j] = gecici;
        }
    }

    Kart kartCek() {
        if(kalanKartSayisi == 0) desteyiOlustur(); 
        kalanKartSayisi--; 
        return deste[kalanKartSayisi];
    }

    int sinirla(int deger, int minDeger, int maxDeger) {
        if (deger < minDeger) return minDeger;
        if (deger > maxDeger) return maxDeger;
        return deger;
    }

    void haritayiCiz() {
        system("cls"); 
        cout << "=== IYMUS  OYUN === [W/A/S/D] Hareket | [Q] Duraklat/Menu\n";
        
        int kameraX = sinirla(oyuncuX - (KAMERA_GENISLIK / 2), 0, HARITA_GENISLIK - KAMERA_GENISLIK);
        int kameraY = sinirla(oyuncuY - (KAMERA_YUKSEKLIK / 2), 0, HARITA_YUKSEKLIK - KAMERA_YUKSEKLIK);

        for(int y = 0; y < KAMERA_YUKSEKLIK; y++) {
            for(int x = 0; x < KAMERA_GENISLIK; x++) {
                int gercekY = kameraY + y; int gercekX = kameraX + x;
                bool objeCizildi = false;

                if(oyuncuX == gercekX && oyuncuY == gercekY) {
                    cout << "\033[1;32mP\033[0m "; objeCizildi = true;
                } else {
                    for(int i = 0; i < 8; i++) {
                        if(!dusmanlar[i].yenildiMi && dusmanlar[i].x == gercekX && dusmanlar[i].y == gercekY) {
                            if(dusmanlar[i].isim == "hasan" && kupaSayisi < 7) continue;
                            cout << "\033[1;31mD\033[0m "; objeCizildi = true; break;
                        }
                    }
                }
                if(!objeCizildi) cout << sabitHarita[gercekY][gercekX] << " ";
            }
            cout << "\n";
        }
        cout << "\nCan: " << oyuncuCan << " | Puan: " << oyuncuPuan << " | Yenilen Dusman: " << kupaSayisi << "/8\n";
    }

    int pokerEliniDegerlendir(Kart secilenler[5], string& elIsmi) {
        int tabanHasar = 0; bool renkAyniMi = true; bool siraliMi = true;
        string ilkRenk = secilenler[0].renk;
        int degerler[5];
        
        for(int i = 0; i < 5; i++) { 
            degerler[i] = secilenler[i].deger; 
            if(secilenler[i].renk != ilkRenk) renkAyniMi = false; 
        }
        
        for(int i=0; i<4; i++) {
            for(int j=0; j<4-i; j++) {
                if(degerler[j] > degerler[j+1]) {
                    int gecici = degerler[j];
                    degerler[j] = degerler[j+1];
                    degerler[j+1] = gecici;
                }
            }
        }
        
        for(int i=0; i<4; i++) {
            if(degerler[i+1] - degerler[i] != 1) siraliMi = false;
        }
        
        if(!siraliMi && degerler[0]==2 && degerler[1]==3 && degerler[2]==4 && degerler[3]==5 && degerler[4]==14) siraliMi = true; 
        for(int i=0; i < 5; i++) tabanHasar += degerler[i];

        int frekans[15] = {0}; 
        for(int i=0; i < 5; i++) frekans[degerler[i]]++;

        int maksimumAyni = 1, ciftSayisi = 0; bool ucluVarMi = false;
        for(int i=2; i<=14; i++) {
            if(frekans[i] > maksimumAyni) maksimumAyni = frekans[i];
            if(frekans[i] == 3) ucluVarMi = true;
            if(frekans[i] == 2) ciftSayisi++;
        }

        if(renkAyniMi && siraliMi) { elIsmi = "Sirali Renk"; return tabanHasar * 10; }
        if(maksimumAyni == 4) { elIsmi = "Kare"; return tabanHasar * 8; }
        if(ucluVarMi && ciftSayisi == 1) { elIsmi = "Full"; return tabanHasar * 7; }
        if(renkAyniMi) { elIsmi = "Renk"; return tabanHasar * 5; }
        if(siraliMi) { elIsmi = "Kent"; return tabanHasar * 4; }
        if(ucluVarMi) { elIsmi = "Uclu"; return tabanHasar * 3; }
        if(ciftSayisi == 2) { elIsmi = "Doper"; return tabanHasar * 2 + 10; }
        if(ciftSayisi == 1) { elIsmi = "Per"; return tabanHasar * 2; }
        
        elIsmi = "Yuksek Kart"; return tabanHasar;
    }

    void savasArayuzunuCiz(Dusman& dusman, int imlec, bool secimler[8], int kalanDegistirme) {
        system("cls");
        cout << "\n================= SAVAS ALANI =================\n";
        cout << "      [" << dusman.isim << "]                          [SEN]\n";
        cout << "      CAN: " << dusman.can << " / " << dusman.maksimumCan << "                   CAN: " << oyuncuCan << " / 500\n";
        cout << "        \\_O_/                           O  \n";
        cout << "          |                            /|\\ \n";
        cout << "         / \\                           / \\ \n";
        cout << "\n  \033[1;35m--- SAVAS KAYITLARI (COK ONEMLI LINKED LIST) ---\033[0m\n";
        savasLoglari.loglariEkranaYazdir(); 
        cout << "  \033[1;35m------------------------------------------------\033[0m\n\n";
        
        for(int i=0; i<8; i++) cout << (secimler[i] ? "\033[1;33m+-----+\033[0m " : "+-----+ "); cout << "\n";
        for(int i=0; i<8; i++) {
            string d = oyuncuEli[i].degeriMetneCevir();
            string r = oyuncuEli[i].renkKoduAl();
            cout << "|" << r << d << "\033[0m" << (d.length() == 2 ? "   | " : "    | ");
        } cout << "\n";
        for(int i=0; i<8; i++) {
            cout << "|  " << oyuncuEli[i].renkKoduAl() << oyuncuEli[i].renk << "\033[0m  | ";
        } cout << "\n";
        for(int i=0; i<8; i++) {
            string d = oyuncuEli[i].degeriMetneCevir();
            string r = oyuncuEli[i].renkKoduAl();
            cout << "|" << (d.length() == 2 ? "   " : "    ") << r << d << "\033[0m| ";
        } cout << "\n";
        for(int i=0; i<8; i++) cout << (secimler[i] ? "\033[1;33m+-----+\033[0m " : "+-----+ "); cout << "\n";
        for(int i=0; i<8; i++) cout << (i == imlec ? "   \033[1;32m^\033[0m    " : "        "); cout << "\n";

        cout << "\n[A/D] Kartlarda Gezin | [SPACE] Sec/Birak\n";
        cout << "[ENTER] Saldir (5 Kart) | [X] Kartlari Degistir (Kalan: " << kalanDegistirme << ")\n";
        cout << "[E] Savastan Kac\n";
    }

    void savasiBaslat(Dusman& dusman) {
        desteyiOlustur();
        savasLoglari.listeyiTemizle();
        savasLoglari.logEkle(dusman.isim + " ile karsilastin! Diyor ki: \"" + dusmanReplikleri[rand() % 4] + "\"");

        for(int i=0; i<8; i++) oyuncuEli[i] = kartCek();
        int kalanDegistirme = 3;

        while(oyuncuCan > 0 && dusman.can > 0) {
            int imlec = 0;
            bool secimler[8] = {false}; 
            int secilenMiktar = 0;
            bool turBittiMi = false;

            while(!turBittiMi) {
                savasArayuzunuCiz(dusman, imlec, secimler, kalanDegistirme);
                char tus = _getch(); 

                if(tus == 'a' || tus == 'A') {
                    imlec--; if(imlec < 0) imlec = 7;
                } 
                else if(tus == 'd' || tus == 'D') {
                    imlec++; if(imlec >= 8) imlec = 0;
                } 
                else if(tus == ' ') {
                    if(secimler[imlec]) { secimler[imlec] = false; secilenMiktar--; }
                    else if(secilenMiktar < 5) { secimler[imlec] = true; secilenMiktar++; }
                } 
                else if(tus == '\r' || tus == '\n') { 
                    if(secilenMiktar == 5) {
                        Kart saldiriKartlari[5]; 
                        int sayac = 0;
                        
                        for(int i=0; i<8; i++) {
                            if(secimler[i]) {
                                saldiriKartlari[sayac] = oyuncuEli[i]; 
                                oyuncuEli[i] = kartCek(); 
                                sayac++;
                            }
                        }
                        
                        string elIsmi;
                        int vurulanHasar = pokerEliniDegerlendir(saldiriKartlari, elIsmi);
                        
                        savasLoglari.logEkle("\033[1;32m[" + elIsmi + "]\033[0m yaptin! " + to_string(vurulanHasar) + " hasar vurdun.");
                        dusman.can -= vurulanHasar;
                        turBittiMi = true; 
                    } else {
                        savasLoglari.logEkle("\033[1;31mHATA:\033[0m Saldiri icin tam 5 kart secmelisin!");
                    }
                } 
                else if(tus == 'x' || tus == 'X') { 
                    if(secilenMiktar > 0 && kalanDegistirme > 0) {
                        for(int i=0; i<8; i++) {
                            if(secimler[i]) {
                                oyuncuEli[i] = kartCek(); 
                            }
                        }
                        
                        kalanDegistirme--;
                        savasLoglari.logEkle(to_string(secilenMiktar) + " kart degistirildi. Sira sende.");
                        
                        for(int i=0; i<8; i++) secimler[i] = false; 
                        secilenMiktar = 0; 
                        imlec = 0; 
                    }
                }
                else if(tus == 'e' || tus == 'E') { 
                    float canOrani = (float)dusman.can / dusman.maksimumCan;
                    if((rand() % 100) < (100 - (canOrani * 80))) {
                        cout << "\n>> Kactin!\nDevam etmek icin bir tusa bas..."; _getch(); return;
                    } else {
                        int alinanHasar = dusman.saldiriGucu / 2; oyuncuCan -= alinanHasar; 
                        savasLoglari.logEkle("\033[1;31mKACAMADIN!\033[0m Panikle " + to_string(alinanHasar) + " hasar aldin.");
                        turBittiMi = true; 
                    }
                }
            }

            if(dusman.can > 0) {
                int dusmanHasari = dusman.saldiriGucu + (rand() % 10);
                savasLoglari.logEkle("\033[1;31m" + dusman.isim + " saldirdi!\033[0m Sana " + to_string(dusmanHasari) + " hasar vurdu.");
                oyuncuCan -= dusmanHasari; 
            }
        }

        if(oyuncuCan <= 0) { 
            system("cls"); cout << "\n=== OLDUN ===\nPuanin: " << oyuncuPuan << "\nCikmak icin tusa bas..."; _getch(); exit(0); 
        } 
        else {
            system("cls"); cout << "\n*** " << dusman.isim << " yendin! ***\nDevam etmek icin tusa bas...";
            dusman.yenildiMi = true; 
            oyuncuPuan += dusman.maksimumCan * 2; 
            kazanilanKupalar[kupaSayisi] = dusman.isim; 
            kupaSayisi++;
            _getch();
        }
    }

    void konumuKontrolEt() {
        if(sabitHarita[oyuncuY][oyuncuX] == 'E') {
            system("cls");
            cout << "\n[EV] Evinize dondunuz. Buralar cok sessiz...\n"; 
            if(kupaSayisi > 0) { 
                cout << "Alinan Kelleler: "; 
                for(int i=0; i<kupaSayisi; i++) cout << "[" << kazanilanKupalar[i] << "] "; cout << "\n"; 
            }
            cout << "\nHaritaya donmek icin bir tusa bas..."; _getch();
            oyuncuX++; return; 
        }

        for(int i=0; i<8; i++) {
            if(!dusmanlar[i].yenildiMi && dusmanlar[i].x == oyuncuX && dusmanlar[i].y == oyuncuY) {
                if(dusmanlar[i].isim == "hasan" && kupaSayisi < 7) {} 
                else savasiBaslat(dusmanlar[i]);
            }
        }
    }

    bool gecerliHamleMi(int hedefX, int hedefY) {
        if(hedefX < 0 || hedefX >= HARITA_GENISLIK || hedefY < 0 || hedefY >= HARITA_YUKSEKLIK) return false;
        char zemin = sabitHarita[hedefY][hedefX];
        if(zemin == '#' || zemin == '^' || zemin == 'T' || zemin == '+' || zemin == '-' || zemin == '|') return false; 
        return true;
    }

    void pokerRehberiniGoster() {
        system("cls");
        cout << "=== POKER KOMBİNASYON REHBERI ===\n\n";
        cout << "1. Per (Pair) [Carpani: x2]\n   | \033[1;31m♥A\033[0m | | \033[1;36m♠A\033[0m | | \033[1;36m♣5\033[0m | | \033[1;31m♦8\033[0m | | \033[1;36m♠3\033[0m |\n\n";
        cout << "2. Doper (Two Pairs) [Carpani: x2 + 10]\n   | \033[1;31m♥A\033[0m | | \033[1;36m♠A\033[0m | | \033[1;36m♣K\033[0m | | \033[1;31m♦K\033[0m | | \033[1;36m♠3\033[0m |\n\n";
        cout << "3. Uclu (Three of a Kind) [Carpani: x3]\n   | \033[1;31m♥A\033[0m | | \033[1;36m♠A\033[0m | | \033[1;36m♣A\033[0m | | \033[1;31m♦8\033[0m | | \033[1;36m♠3\033[0m |\n\n";
        cout << "4. Kent (Straight) [Carpani: x4]\n   | \033[1;31m♥5\033[0m | | \033[1;36m♠6\033[0m | | \033[1;31m♦7\033[0m | | \033[1;36m♣8\033[0m | | \033[1;31m♥9\033[0m |\n\n";
        cout << "5. Renk (Flush) [Carpani: x5]\n   | \033[1;31m♥2\033[0m | | \033[1;31m♥5\033[0m | | \033[1;31m♥8\033[0m | | \033[1;31m♥J\033[0m | | \033[1;31m♥K\033[0m |\n\n";
        cout << "6. Full (Full House) [Carpani: x7]\n   | \033[1;31m♥A\033[0m | | \033[1;36m♠A\033[0m | | \033[1;36m♣A\033[0m | | \033[1;31m♦K\033[0m | | \033[1;36m♠K\033[0m |\n\n";
        cout << "7. Kare (Four of a Kind) [Carpani: x8]\n   | \033[1;31m♥A\033[0m | | \033[1;36m♠A\033[0m | | \033[1;36m♣A\033[0m | | \033[1;31m♦A\033[0m | | \033[1;36m♠3\033[0m |\n\n";
        cout << "8. Sirali Renk (Straight Flush) [Carpani: x10]\n   | \033[1;36m♠5\033[0m | | \033[1;36m♠6\033[0m | | \033[1;36m♠7\033[0m | | \033[1;36m♠8\033[0m | | \033[1;36m♠9\033[0m |\n\n";
        cout << "Duraklatma menusune donmek icin bir tusa basin...";
        _getch();
    }

    bool oyunuDuraklatMenu() {
        while(true) {
            system("cls");
            cout << "=== OYUN DURAKLATILDI ===\n\n";
            cout << "[1] Oyuna Devam Et\n";
            cout << "[2] Poker Kombinasyonlari (Rehber)\n";
            cout << "[3] Ana Menuye Don (Mevcut Oyun Kapanir)\n\nSeciminiz: ";
            char secim = _getch();
            
            if(secim == '1') return false; 
            else if(secim == '2') pokerRehberiniGoster();
            else if(secim == '3') return true; 
        }
    }

public:
    Oyun() {
        srand(time(0)); 
        oyuncuX = 4; oyuncuY = 5; 
        oyuncuCan = 500; oyuncuPuan = 0; kupaSayisi = 0;
        dusmanlariYukle();
    }

    void oyna() {
        while(true) {
            haritayiCiz();
            char hareket = _getch();
            int yeniX = oyuncuX, yeniY = oyuncuY;

            if(hareket == 'w' || hareket == 'W') yeniY--;
            else if(hareket == 's' || hareket == 'S') yeniY++;
            else if(hareket == 'a' || hareket == 'A') yeniX--;
            else if(hareket == 'd' || hareket == 'D') yeniX++;
            else if(hareket == 'q' || hareket == 'Q') {
                bool anaMenuyeDon = oyunuDuraklatMenu();
                if(anaMenuyeDon) return; 
                else continue; 
            }

            if(gecerliHamleMi(yeniX, yeniY)) { oyuncuX = yeniX; oyuncuY = yeniY; }
            konumuKontrolEt();

            if(kupaSayisi == 8) {
                system("cls"); cout << "\n*** OYUNU KAZANDIN! PUAN: " << oyuncuPuan << " ***\n"; 
                cout << "Ana menuye donmek icin tusa bas..."; _getch();
                return;
            }
        }
    }
};

void anaMenuGoster() {
    while(true) {
        system("cls");
        cout << "==========================================\n";
        cout << "               IYMUS   OYUN   \n";
        cout << "==========================================\n\n";
        cout << "  [1] Basla\n  [2] Cikis\n\nSeciminiz: ";
        char secim = _getch();
        if(secim == '1') {
            Oyun o; 
            o.oyna(); 
        }
        else if(secim == '2') exit(0);
    }
}

int main() { 
    SetConsoleOutputCP(CP_UTF8); 
    anaMenuGoster(); 
    return 0; 
}