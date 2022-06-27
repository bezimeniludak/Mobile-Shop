#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funkcije
void izbor_pocetni();				//prikaz pocetnog menija
void glavni_meni();					//prikaz glavnog menija
void spisak();						//prikaz spiska telefona
void dodaj_tel();					//dodavanje telefona u spisak
void izbrisi_tel();					//brisanje telefona sa spiska
void izbor_tel();					//funkcija za izbor telefona za izmenu ili pisanje u datoteku
void cena(int redni_br);			//izmena cene izabranog telefona		}
void kolicina(int redni_br);		//izmena kolicine izabranog telefona	} prosledjen im je redni broj telefona iz funkcije izbor_tel()
void datoteka(int redni_br);		//upis telefona u datoteku				}
void provera();						//provera dinamicke dodele memorije prilikom dodavanja ili brisanja telefona u spisak telefona
void clrscr();						//brisanje teksta sa konzole zarad preglednosti

//Definicija tipa strukture telefon koja sadrzi clanove (marka, model, cena i kolicina)
struct telefon {
  char marka[30];
  char model[30];
  float cena;
  int kolicina;
};

int n = 5;							//broj telefona u nizu telefona
int n_dat = 1;						//redni broj telefona u datoteci
struct telefon * telefoni;			//pokazivac na niz telefona
int broj;							//broj koji korisnik unosi za kretanje kroz meni

main() {
  telefoni = (struct telefon * ) malloc(n * sizeof(struct telefon));

  //Prvi telefon
  strcpy(telefoni[0].marka, "Xiaomi");
  strcpy(telefoni[0].model, "Mi 10");
  telefoni[0].cena = 72720.00f;
  telefoni[0].kolicina = 1;

  //Drugi telefon
  strcpy(telefoni[1].marka, "Samsung");
  strcpy(telefoni[1].model, "Galaxy Z Fold2");
  telefoni[1].cena = 235920.00f;
  telefoni[1].kolicina = 20;

  //Treci telefon
  strcpy(telefoni[2].marka, "Apple");
  strcpy(telefoni[2].model, "IPhone XS MAX");
  telefoni[2].cena = 129600.00f;
  telefoni[2].kolicina = 15;

  //Cetvrti telefon
  strcpy(telefoni[3].marka, "Nokia");
  strcpy(telefoni[3].model, "5310");
  telefoni[3].cena = 5760.00f;
  telefoni[3].kolicina = 50;

  //Peti telefon
  strcpy(telefoni[4].marka, "Huawei");
  strcpy(telefoni[4].model, "P40 Pro+");
  telefoni[4].cena = 125160.00f;
  telefoni[4].kolicina = 30;

  izbor_pocetni();
}

void izbor_pocetni() {
  do {
    puts("Dobro dosli u prodavnicu telefona\n\nLista opcija:\n1-Glavni meni\n2-Izlaz iz programa");
    scanf("%d", & broj);
    clrscr();
    if (broj < 1 || broj > 2) puts("Niste uneli ni jedan od ponudjenih brojeva. Pokusajte ponovo.");
  } while (broj < 1 || broj > 2);

  switch (broj) {
  case 1:
    clrscr();
    glavni_meni();
    break;
  case 2:
    free(telefoni);
    exit(1);
    break;
  default:
    break;
  }
}

void glavni_meni() {
  do {
    spisak();
    puts("\nLista opcija:\n1-Dodajte telefon\n2-Izbrisite telefon\n3-Izbor telefona za izmenu podataka ili upis u datoteku\n4-Nazad");
    scanf("%d", & broj);
    clrscr();
    if (broj < 1 || broj > 4) puts("Niste uneli ni jedan od ponudjenih brojeva. Pokusajte ponovo");
  } while (broj < 1 || broj > 4);

  switch (broj) {
  case 1:
    clrscr();
    dodaj_tel();
    break;
  case 2:
    clrscr();
    izbrisi_tel();
    break;
  case 3:
    clrscr();
    izbor_tel();
    break;
  case 4:
    clrscr();
    izbor_pocetni();
    break;
  default:
    break;
  }
}

void dodaj_tel() {
  char marka[30];
  char model[30];
  float cena;
  int kolicina;

  n++;
  telefoni = (struct telefon * ) realloc(telefoni, n * sizeof(struct telefon));
  provera();
  fflush(stdin);

  puts("Unesite marku novog telefona");
  gets(marka);
  strcpy(telefoni[n - 1].marka, marka);

  puts("Unesite model novog telefona");
  gets(model);
  strcpy(telefoni[n - 1].model, model);

  do {
    puts("Unesite cenu novog telefona");
    scanf("%f", & cena);
    if (cena < 1000) {
      clrscr();
      puts("Cena telefona ne moze biti manja od 1000 RSD. Pokusajte ponovo");
    }
  } while (cena < 1000);
  telefoni[n - 1].cena = cena;

  do {
    puts("Unesite kolicinu novog telefona");
    scanf("%d", & kolicina);
    if (kolicina < 1) {
      clrscr();
      puts("Broj telefona ne moze biti manji od 1. Pokusajte ponovo.\n(Ukoliko je broj telefona 0, molimo vas da izbrisete telefon sa liste)");
    }
  } while (kolicina < 1);
  telefoni[n - 1].kolicina = kolicina;

  clrscr();
  puts("Novi telefon je uspesno dodat");
  glavni_meni();
}

void izbrisi_tel() {
  int redni_br, j;
  do {
    spisak();
    puts("\nUnesite redni broj telefona koji zelite da obrisete");
    scanf("%d", & redni_br);
    clrscr();
    if (redni_br >= n + 1 || redni_br < 1)
      puts("Telefon sa ovim rednim brojem ne postoji. Pokusajte ponovo");
  } while (redni_br >= n + 1 || redni_br < 1);

  for (j = redni_br - 1; j < n - 1; j++)
    telefoni[j] = telefoni[j + 1];
  clrscr();
  n--;
  telefoni = (struct telefon * ) realloc(telefoni, n * sizeof(struct telefon));
  puts("Telefon uspesno izbrisan\n\nUnesite bilo koji karakter za povratak na glavni meni.");
  fflush(stdin);
  getchar();
  clrscr();
  glavni_meni();
}

void izbor_tel() {
  int redni_br;
  do {
    spisak();
    puts("\nUnesite redni broj telefona za telefon koji zelite da izaberete:");
    scanf("%d", & redni_br);
    clrscr();
    if (redni_br >= n + 1 || redni_br < 1)
      puts("Telefon sa ovim rednim brojem ne postoji. Pokusajte ponovo.");
  } while (redni_br >= n + 1 || redni_br < 1);

  clrscr();

  do {
    puts("Izabrani telefon je:");
    printf("\n%d. %s, %s, cena: %.2f RSD, kolicina: %d\n", redni_br, telefoni[redni_br - 1].marka, telefoni[redni_br - 1].model, telefoni[redni_br - 1].cena, telefoni[redni_br - 1].kolicina);
    puts("\nUnesite broj:\n1-Izmena cene\n2-Izmena kolicine\n3-Dodajte u datoteku\n4-Nazad na glavni meni");
    scanf("%d", & broj);
    clrscr();
    if (broj < 1 || broj > 4) puts("Niste uneli ni jedan od ponudjenih brojeva. Pokusajte ponovo.");
  } while (broj < 1 || broj > 4);

  switch (broj) {
  case 1:
    clrscr();
    cena(redni_br);
    break;
  case 2:
    clrscr();
    kolicina(redni_br);
    break;
  case 3:
    clrscr();
    datoteka(redni_br);
    break;
  case 4:
    clrscr();
    glavni_meni();
  default:
    break;
  }
}

void cena(int redni_br) {
  float cena;

  do {
    puts("Unesite novu cenu telefona");
    scanf("%f", & cena);
    clrscr();
    if (cena < 1000)
      puts("Cena telefona ne moze biti manja od 1000 RSD. Pokusajte ponovo");
  } while (cena < 1000);

  telefoni[redni_br - 1].cena = cena;
  puts("Cena telefona je uspesno izmenjena\nTelefon sa azuriranim podatkom\n");
  printf("%d. %s, %s, cena: %.2f RSD, kolicina: %d\n", redni_br, telefoni[redni_br - 1].marka, telefoni[redni_br - 1].model, telefoni[redni_br - 1].cena, telefoni[redni_br - 1].kolicina);
  puts("\nUnesite bilo koji karakter za povratak na glavni meni.");
  fflush(stdin);
  getchar();
  clrscr();
  glavni_meni();
}

void kolicina(int redni_br) {
  int kolicina;
  do {
    puts("Unesite novu kolicinu telefona");
    scanf("%d", & kolicina);
    clrscr();
    if (kolicina < 1)
      puts("Broj telefona ne moze biti manji od 1. Pokusajte ponovo.\n(Ukoliko je broj telefona 0, molimo vas da izbrisete telefon sa liste)");
  } while (kolicina < 1);

  telefoni[redni_br - 1].kolicina = kolicina;
  puts("Kolicina telefona je uspesno izmenjena\nIzabrani telefon sa izmenjenim podatkom\n");
  printf("\n%d. %s, %s, cena: %.2f RSD, kolicina: %d\n", redni_br, telefoni[redni_br - 1].marka, telefoni[redni_br - 1].model, telefoni[redni_br - 1].cena, telefoni[redni_br - 1].kolicina);
  puts("\nUnesite bilo koji karakter za povratak na glavni meni.");
  fflush(stdin);
  getchar();
  clrscr();
  glavni_meni();
}

void datoteka(int redni_br) {
  FILE * fptr;
  char ime[80 + 1];

  puts("Unesite ime datoteke:");
  fflush(stdin);
  gets(ime);
  do {
    fptr = fopen(ime, "a");
    if (fptr == NULL)
      puts("Neuspelo otvaranje datoteke za upis telefona");
  } while (fptr == NULL);

  fprintf(fptr, "%d. %s, %s, cena: %.2f RSD, kolicina: %d\n", n_dat, telefoni[redni_br - 1].marka, telefoni[redni_br - 1].model, telefoni[redni_br - 1].cena, telefoni[redni_br - 1].kolicina);
  n_dat++;
  fclose(fptr);
  clrscr();
  puts("Telefon uspesno dodat u datoteku");
  puts("\nUnesite bilo koji karakter za povratak na glavni meni.");
  fflush(stdin);
  getchar();
  clrscr();
  glavni_meni();

}

void provera() {
  if (telefoni == NULL) {
    puts("Nije uspela dodela memorije. Program ce se zatvoriti.");
    free(telefoni);
    exit(1);
  }
}

void spisak() {
  int i;
  puts("Spisak mobilnih telefona:");
  for (i = 0; i < n; i++)
    printf("\n%d. %s, %s, cena: %.2f RSD, kolicina: %d\n", i + 1, telefoni[i].marka, telefoni[i].model, telefoni[i].cena, telefoni[i].kolicina);
}

void clrscr() {
  system("cls||clear");
}