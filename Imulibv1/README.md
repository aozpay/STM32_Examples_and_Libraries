# STM32_Examples_and_Libraries
Bu repo STM32 örnekleri ve hazırlanmış kütüphaneler içerir.

Bitirme projem olan self-balancing robot için 
YAW,PITCH,ROLL açıları gerekmektedir.Bu yüzden 6 dof IMU kullanılması yeterlidir.(GYRO ve ACC) fakat GYRO VE ACC sensörleri bazı 
durumlarda (Genelde hızlı değişen) farklı tepki sürelerinde cevap verip çıkışta farklı değerler sunar.Bunu önlemek için
diğer bir sensör olan Magnetometre kullanılmıştır.
Bu 9DOF IMU kullanılarak yaw,pitch,roll açıları elde edilip kalman filtresi ile PID girişine aktarılacaktır.
Bu yüzden kütüphane STM32F3 serisi içinde bulunan IMU sensörleri için yazılmıştır
Çoğu register kullanılmamıştır.Bu yüzden kullancının yapması gereken sadece,
MEMS_Init fonksiyonunu aktif edip,
Mems_acc_getxyz()
Mems_mag_getxyz()
Mems_gyro_getxyz()
fonksiyonlarına parametre olarak dizi gönderip ham dataları elde etmek.
