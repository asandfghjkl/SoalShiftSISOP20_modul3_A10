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

**4b) Buatlah program C kedua dengan nama soal4b.c. Program ini akan mengambil variabel hasil perkalian matriks dari program soal4a.c (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar. Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai penjumlahan dari 1 hingga n, dan tampilkan hasilnya ke layar dengan format seperti matriks.**

**4c)  Buatlah program C ketiga dengan nama soal4c.c. Program ini tidak memiliki hubungan terhadap program yang lalu. Pada program ini, diminta mengetahui jumlah file dan folder di direktori saat ini dengan command `ls | wc -l`.**

