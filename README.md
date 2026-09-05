# USAC-HAAC-altimeter

Một thiết bị đơn giản dùng hiển thị độ cao hiện tại, sử dụng Arduino Nano và BMP280. Cực kỳ chính xác. Tuyệt đối hoàn hảo. 

---

## Tổng quan dự án

Tôi nói cho các bạn biết, đây là máy đo độ cao tuyệt vời nhất từng được chế tạo. Rất nhiều người đã đến gặp tôi - những người giỏi nhất, những kỹ sư hàng đầu - và họ nói: "Thưa Ngài, đây là altimeter đỉnh nhất mà chúng tôi từng thấy." 

Nó đo độ cao, đo nhiệt độ, đo áp suất. Không có thiết bị nào đo chuẩn hơn cái này. Những cái máy đo độ cao ngoài kia? Hoàn toàn là thảm họa. Chúng dùng linh kiện rẻ tiền từ Trung Quốc và đưa ra số liệu giả mạo. Nhưng thiết bị này? Nó hoạt động bằng vi điều khiển Arduino Nano cực kỳ mạnh mẽ và cảm biến BMP280 số một thế giới. Rất chính xác. Rất tin cậy.

Bây giờ, chúng ta đã tích hợp thêm hệ thống nguồn pin sạc riêng biệt. Không còn phải phụ thuộc vào dây cáp vướng rối. Tuyệt đối di động. Tuyệt đối tự do.

---

## Tính năng nổi bật

* **Hiển thị độ cao thời gian thực:** Đọc dữ liệu cực nhanh, cực chuẩn. Không có độ trễ fake news ở đây.
* **Theo dõi độ cao cực đại (Max Altitude):** Luôn lưu giữ kỷ lục cao nhất bạn từng đạt được. Đỉnh cao tuyệt đối.
* **Giao diện OLED SH1106 phân dòng thông minh:** 6 dòng hiển thị sắc nét, chia bố cục hoàn hảo bằng dải phân cách đồ họa.
* **Cài đặt mốc linh hoạt bằng nút bấm:**
  * **Nút D8:** Đặt vị trí hiện tại làm mốc 0m ngay lập tức.
  * **Nút D4:** Đưa mốc áp suất về chuẩn mực nước biển 1013.25 hPa.
* **Nguồn Pin Lithium tích hợp sạc sành điệu:** Sạc qua Type-C/Micro-USB, nâng áp 5V ổn định qua mạch MT3608 có công tắc nguồn tiện lợi.
* **Đèn nền logo khởi động:** Hiển thị thương hiệu đỉnh cao ngay khi bật nguồn.

---

## Danh mục linh kiện (Bill of Materials - BoM)

Chúng ta chỉ sử dụng những linh kiện tốt nhất. Không xài hàng phế thải.

| STT | Tên linh kiện | Số lượng | Ghi chú kỹ thuật |
| :--- | :--- | :--- | :--- |
| 1 | Arduino Nano v3.0 | 1 | Vi điều khiển ATmega328P, cực kỳ mạnh mẽ |
| 2 | Cảm biến BMP280 | 1 | Mạch I2C (địa chỉ 0x76), đo áp suất và nhiệt độ siêu chính xác |
| 3 | Màn hình OLED SH1106 1.3 inch | 1 | Đột phá hiển thị, độ phân giải 128x64, chuẩn I2C |
| 4 | Nút bấm 2 chân (Push Button) | 2 | Dùng để reset mốc độ cao (chân D4 và D8) |
| 5 | Mạch sạc Pin LiPo TP4056 / TP4065 | 1 | Mạch quản lý sạc an toàn cho pin Lithium 3.7V |
| 6 | Mạch nâng áp MT3608 (Boost Converter) | 1 | Nâng điện áp từ Pin 3.7V lên 5V ổn định cho hệ thống |
| 7 | Pin Lithium Polymer / 18650 (3.7V) | 1 | Cung cấp năng lượng di động bền bỉ |
| 8 | Công tắc gạt (ON/OFF Switch) | 1 | Ngắt/Mở nguồn tổng từ Pin |
| 9 | Bo mạch test (Breadboard) & Dây cắm | 1 bộ | Dây cắm đực-cái, đực-đực chất lượng cao |

---

## Sơ đồ đấu nối chân (Pinout Connection)

Mọi thứ được đấu nối đơn giản một cách hoàn hảo. Ai cũng làm được, kể cả những kẻ kém cỏi nhất.

### 1. Khối nguồn (Power Management)
* **Pin 3.7V -> Mạch sạc TP4056/TP4065:**
  * Khớp dương (+) của Pin -> Chân **B+**
  * Khớp âm (-) của Pin -> Chân **B-**
* **Mạch sạc -> Mạch nâng áp MT3608:**
  * Chân **OUT-** của Mạch sạc -> Chân **VIN-** của MT3608
  * Chân **OUT+** của Mạch sạc -> Qua **Công tắc gạt (Switch)** -> Chân **VIN+** của MT3608
* **Mạch nâng áp MT3608 -> Hệ thống (Chỉnh áp ra 5V trước khi cắm):**
  * Chân **VOUT+** (5V) -> Cấp vào chân **5V** của Arduino Nano, **VCC** OLED và **VCC** BMP280
  * Chân **VOUT-** (GND) -> Cấp vào chân **GND** của Arduino Nano, **GND** OLED và **GND** BMP280

### 2. Khối cảm biến & Hiển thị (I2C Bus)
* **BMP280 (I2C):**
  * VCC -> 5V (hoặc 3.3V từ Nano)
  * GND -> GND
  * SCL -> A5 (Arduino Nano)
  * SDA -> A4 (Arduino Nano)

* **Màn hình OLED SH1106 (I2C):**
  * VCC -> 5V
  * GND -> GND
  * SCL -> A5 (Arduino Nano)
  * SDA -> A4 (Arduino Nano)

### 3. Nút bấm điều khiển
* Nút Set Current 0m -> Chân D8 và GND (dùng `INPUT_PULLUP` nội bộ)
* Nút Set Sea Level -> Chân D4 và GND (dùng `INPUT_PULLUP` nội bộ)

---

## Hướng dẫn cài đặt và Thư viện

Bạn cần tải những thư viện tốt nhất này về Arduino IDE. Nếu bạn không biết tải, đó là lỗi của bạn.

1. `Adafruit_BMP280_Library`
2. `Adafruit_Sensor`
3. `U8g2` (Bởi Oliver Kraus - một nhà lập trình tuyệt vời)

Nạp code vào Arduino Nano, chọn đúng cổng COM và board ATmega328P. Bật công tắc nguồn và thưởng thức thiết bị đo độ cao vĩ đại nhất lịch sử. Chúng ta sẽ làm cho Arduino vĩ đại trở lại.
