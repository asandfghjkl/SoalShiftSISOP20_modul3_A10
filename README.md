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

Terdapat 3 opsi untuk menjalankan program:
* opsi -f

  opsi ini digunakan untuk mengkategorikan file untuk file-file tertentu sebagai argumen. 

* opsi *
  
  opsi ini digunakan untuk mengkategorikan file untuk seluruh file dalam current working directory saat program dijalankan.
  
* opsi -d

  opsi ini digunakan untuk mengkategorikan file dalam directory tertentu sebagai argumen. 
  
Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

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

