# SoalShiftSISOP20_modul3_A10
**Sandra Agnes Oktaviana  (05111840000124)**

**Adrian Danindra Indarto (05111840000068)**

## table of contents
* [soal3](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10#soal3)
* [soal4](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10#soal4)

## soal3
source code: [soal3.c](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/soal3/soal3.c)

### penyelesaian & penjelasan soal

**3) Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.**

Inisialisasi variabel global:
```
pthread_t tid[1000000];
char cwd[1000];
char folder[1000];
```

* `pthread_t tid[1000000];` untuk inisialisasi array untuk menampung thread
* `char cwd[1000];` untuk menyimpan current working directory
* `char folder[1000];`untuk menyimpan path folder untuk opsi -d

Fungsi main:
```
int main(int argc, char *argv[]) {
	getcwd(cwd, sizeof(cwd));
	int err;
	memset(folder, '\0', sizeof(folder));

	if(argc < 2) {
		printf("argumen invalid");
		return 0;
	}
  ... 
}
```
* `int argc` untuk menghitung jumlah argumen. apabila `argc < 2` maka argumen salah, return 0
* `char *argv[]` untuk menyimpan argumen
* `getcwd(cwd, sizeof(cwd));` menyimpan curent working directory ke cwd
* `int err;` untuk cek thread
* `memset(folder, '\0', sizeof(folder));` untuk memset string folder, untuk cek apakah opsi -d. apabila iya, maka folder akan diisikan path to folder


Terdapat 3 opsi untuk menjalankan program, dimana setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat:

* opsi -f

  opsi ini digunakan untuk mengkategorikan file untuk file-file tertentu sebagai argumen. 
  
  ```
  if(strcmp(argv[1], "-f") == 0) {
		for(int i=2; i<argc; i++) {
			err = pthread_create(&tid[i], NULL, movefile, (void *)argv[i]);
			if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));
		}
		for(int j=2; j<argc; j++)
			pthread_join(tid[j], NULL);
	}
  ```
  Untuk setiap argumen path to file yang akan di sortir, maka akan di loop `for(int i=2; i<argc; i++)`
    * `err = pthread_create(&tid[i], NULL, movefile, (void *)argv[i]);` membuat thread `movefile` dan passing `(void *)argv[i]` 
    * `if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));` cek error
    
* opsi *
  
  opsi ini digunakan untuk mengkategorikan file untuk seluruh file dalam current working directory saat program dijalankan.
  
* opsi -d

  opsi ini digunakan untuk mengkategorikan file dalam directory tertentu sebagai argumen. 
  
Karena ditemukan kesamaan dalam opsi * dan -d, dimana keduanya sama-sama mengkategorikan file dalam suatu directory, maka keduanya dapat dijadikan dalam satu kondisi. Bedanya untuk opsi * akan mengkategorikan file di curent working directory (`cwd`), sedangkan untuk opsi -d akan mengkategorikan file di directory dalam argumen.

  ```
  else {
		DIR *dir;
		struct dirent *tmp;
		int i=0;
		if(strcmp(argv[1], "-d") == 0) {
      dir = opendir(argv[2]);
		  strcpy(folder, argv[2]);
		}
		else if((argv[1][0]=='*') && (strlen(argv[1])==1)) {
			dir = opendir(cwd);
		}
		else {
			printf("argumen invalid");
                	return 0;
		}

		while((dir!=NULL) && (tmp=readdir(dir))) {
      if(strcmp(tmp->d_name, ".")==0 || strcmp(tmp->d_name, "..")==0 || strcmp(tmp->d_name, "soal3.c")==0 || strcmp(tmp->d_name, "soal3")==0 || tmp->d_type==DT_DIR) continue;

      err = pthread_create(&tid[i], NULL, movefile, tmp->d_name);
      if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));
      i++;
    }
    for(int j=0; j<i; j++)
       pthread_join(tid[j], NULL);
    closedir(dir);
	}
  ```
  
* apabila opsi -d
  ```
  if(strcmp(argv[1], "-d") == 0) {
    dir = opendir(argv[2]);
	  strcpy(folder, argv[2]);
	}
  ```
  * `dir` akan menyimpan `opendir(argv[2])`
  * `strcpy(folder, argv[2]);` argv[2] akan disimpan di folder
  
* apabila opsi *
  ```
  else if((argv[1][0]=='*') && (strlen(argv[1])==1)) {
	  dir = opendir(cwd);
	}
  ```
  * `dir` akan menyimpan `cwd`
  
* apabila argumen tidak sesuai dengan keduanya, maka argumen invalid, return 0

Kemudian untuk setiap file dalam `dir` dilakukan loop dan menyimpan file ke `tmp`

```
    while((dir!=NULL) && (tmp=readdir(dir))) {
      if(strcmp(tmp->d_name, ".")==0 || strcmp(tmp->d_name, "..")==0 || strcmp(tmp->d_name, "soal3.c")==0 || strcmp(tmp->d_name, "soal3")==0 || tmp->d_type==DT_DIR) continue;

      err = pthread_create(&tid[i], NULL, movefile, tmp->d_name);
      if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));
      i++;
    }
```
* `if(strcmp(tmp->d_name, ".")==0 || strcmp(tmp->d_name, "..")==0 || strcmp(tmp->d_name, "soal3.c")==0 || strcmp(tmp->d_name, "soal3")==0 || tmp->d_type==DT_DIR) continue;` untuk file-file tersebut, maka akan dilewati
* `err = pthread_create(&tid[i], NULL, movefile, tmp->d_name);` membuat thread `movefile` dan passing `tmp->d_name` 
* `if(err != 0) printf("\ncan't create thread : [%s]",strerror(err));` cek error
* `i++` untuk index thread

Kemudian seluruh thread dijoin-kan dan `dir` ditutup
```
    for(int j=0; j<i; j++)
       pthread_join(tid[j], NULL);
    closedir(dir);
```

Fungsi `movefile` untuk mengkategorikan file:
```
void *movefile(void *arg) {
  char *filepath = (char *)arg;
  
  // cek ekstensi file
  int dot = '.';
  char *extension = NULL;
  extension = strrchr(filepath, dot);
  
  char extlower[1000];
  memset(extlower, '\0', sizeof(extlower));
  if(extension) {
    extension++;
    for(int i=0; i<strlen(extension); i++) {
      extlower[i] = tolower(extension[i]);
    }
  }
  else strcpy(extlower, "Unknown");
  
  // simpan nama file
  int slash = '/';
  char *filename = NULL;
  filename = strrchr(filepath, slash);
  if(filename) filename++;
  else filename = filepath;
  
  char folderpath[1000];
  strcpy(folderpath, cwd);
  strcat(folderpath, "/");
  strcat(folderpath, extlower);
  
  // buat directory
  mkdir(folderpath, S_IRWXU);
  
  if(strlen(folder) > 1) {    // untuk opsi -d
    char fullname[1000];
    strcpy(fullname, folder);
    strcat(fullname, "/");
    strcat(fullname, filename);
    strcat(folderpath, "/");
    strcat(folderpath, filename);
    
    // move file
    rename(fullname, folderpath);
  }
  else{   // untuk opsi lain
    strcat(folderpath, "/");
    strcat(folderpath, filename);
    
    // move file
    rename(filepath, folderpath);
  }
  return NULL;
}
```
* `char *filepath = (char *)arg;` argumen path to file hasil passing disimpan di pointer to char `filepath`
* Untuk cek ekstensi
  ```
  int dot = '.';
  char *extension = NULL;
	extension = strrchr(filepath, dot);
  ```
  * `filepath` akan di cek dengan reverse string atau dari belakang, apabila ditemukan dot atau '.' maka akan disimpan dalam pointer to char `extension`
  
* Karena ekstensi file tidak case sensitive, maka ekstensi akan disimpan dalam bentuk lowercase 
  ```
  char extlower[1000];
	memset(extlower, '\0', sizeof(extlower));
	if(extension) {
		extension++;
    for(int i=0; i<strlen(extension); i++) {
      extlower[i] = tolower(extension[i]);
    }
	}
	else strcpy(extlower, "Unknown");
  ```
  * `char extlower[1000];` untuk menyimpan ekstensi lowercase, kemudian memset extlower `memset(extlower, '\0', sizeof(extlower));`
  
  Apabila ditemukan ekstensi file atau ditemukan dot atau '.'
    ```
    if(extension) {
		  extension++;
      for(int i=0; i<strlen(extension); i++) {
        extlower[i] = tolower(extension[i]);
      }
	  }
    ```
  * `extension++` pointer to char `extension` akan ditambah, sehingga menyimpan karakter pertama ekstensi dari file tersebut
  * kemudian untuk setiap karakter ekstensi akan di loop diubah menjadi lowercase dan disimpan dalam `extlower`
  
  Apabila tidak ditemukan ekstensi file:
  ```
  else strcpy(extlower, "Unknown");
  ```
  maka `extlower` akan menyimpan "Unknown"
  
* Menyimpan nama file tanpa path to file
  ```
  int slash = '/';
  char *filename = NULL;
  filename = strrchr(filepath, slash);
  if(filename) filename++;
	else filename = filepath;
  ```
   * `filepath` akan di cek dengan reverse string atau dari belakang, apabila ditemukan dot atau '/' maka akan disimpan dalam pointer to char `filename` 
   * Apabila `filename` atau ditemukan slash atau '/' maka pointer to char `filename` akan ditambah, sehingga menyimpan karakter pertama nama file tersebut
   * Apabila tidak, maka filename akan menyimpan filepath. Artinya filepath merupakan nama file asli tanpa path to file
  
  
* Menyimpan path folder ekstensi
  ```
  char folderpath[1000];
	strcpy(folderpath, cwd);
	strcat(folderpath, "/");
	strcat(folderpath, extlower);
  ```
  Hasil mengkategorikan file akan disimpan dalam folder sesuai ekstensi di curent working direktori (`cwd`). Maka path folder ekstensi akan disimpan dengan format "cwd/extlower"
  
* Membuat folder ekstensi
```
	mkdir(folderpath, S_IRWXU);
```

* Untuk memindahkan file ke folder ekstensi, dilakukan dengan `rename()`
  ```
  if(strlen(folder) > 1) {    // untuk opsi -d
		char fullname[1000];
	  strcpy(fullname, folder);
		strcat(fullname, "/");
		strcat(fullname, filename);

		strcat(folderpath, "/");
    strcat(folderpath, filename);
    
    // move file
    rename(fullname, folderpath);
	}
	else{   // untuk opsi lain
	  strcat(folderpath, "/");
    strcat(folderpath, filename);

		// move file
	  rename(filepath, folderpath);
	}
  ```
  * untuk opsi -d, rename dilakukan dari "folder/filename" ke "folderpath/filename"
  * untuk opsi lain, rename dilakukan dari filepath ke "folderpath/filename"
  
Hasil Run:
* opsi -f

![soal3(-f)](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/pictures/soal3(-f).png)

* opsi -d

![soal3(-d)](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/pictures/soal3(-d).png)

* opsi *

![soal3(star)](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/pictures/soal3(star).png)


## soal4
source code: 
* [soal4a.c](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/soal4/soal4a.c)
* [soal4b.c](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/soal4/soalba.c)
* [soal4c.c](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/soal4/soalca.c)

### penyelesaian & penjelasan soal
**4a) Buatlah program C dengan nama soal4a.c, yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka). Tampilkan matriks hasil perkalian tadi ke layar.**

Sebelum memasuki perkalian matriks, program akan membuat matriks yang berukuran 4x2 dan 2x5 dengan menggunakan `rand()`. Setelah program ini menginisialisasikan matriks, progra akan membuat thread dengan jumlah yang sesuai matriks hasil. di dalam thread itu elemen-elemen yang dibutuhkan untuk perkalian matriks akan dikalikan dan thread akan mengembalikan hasil dari perkalian tersebut. setelah semua thread selesai melakukan perkalian, semua thread akan digabungkan dangen program utama dan hasil tiap thread akan dmasukkan ke matriks hasil dan ditampilkan di layar. Program akan menginisialisasi shared memory untuk memberikan data ke program 4b dan menulisakna data di matiks hasil untuk dibaca di program 4b.

**4b) Buatlah program C kedua dengan nama soal4b.c. Program ini akan mengambil variabel hasil perkalian matriks dari program soal4a.c (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai penjumlahan dari 1 hingga n, dan tampilkan hasilnya ke layar dengan format seperti matriks.**

Program ini menerima data hasil perkalian dari matriks 4a dengan menggunakan shared memory dengan key yang sama dengan yang ada di program 4a. Setelah menerima data, program ini menampilkan semua data yang diterima terlebih dahulu. Program menginisialisasi thread sejumlah data yang diterima untuk melakukan penjumlahan dari 1 sampai n. Fungsi akan menyelesaikan penjumlahan dengan menggunakan rumus n * (n+1) / 2 . Setelah semua thread menyelesaikan operasi, program utama akan mengumpulkan semua hasil dan menampilkan hasil operasi thread dengan format matriks.

**4c)  Buatlah program C ketiga dengan nama soal4c.c. Program ini tidak memiliki hubungan terhadap program yang lalu. Pada program ini, diminta mengetahui jumlah file dan folder di direktori saat ini dengan command `ls | wc -l`.**

Program ini akan membuat 1 pipe agar memungkinkan program untuk transfer data dari program 1 ke program lainnya. Program akan melakukan fork agar memungkinkan terjadinya 2 proses secara bersamaan. Di parent process, program akan menjalankan perintah `ls` dan memasukkan hasilnya ke pipe yang akan dibaca oleh child process. Child process menunggu data dari pipe yang ditulis oleh parent dan menghitung jumlah file dengan menggunakan perintah `ls -h`. 

Hasil Run:
* soal4a dan soal4b

![soal4a soal4b](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/pictures/soal4a%20soal4b.png)

* soal4c

![soal4c](https://github.com/asandfghjkl/SoalShiftSISOP20_modul3_A10/blob/master/pictures/soal4c.png)

