# USAC-HAAC-altimeter

Một thiết bị đơn giản dùng hiển thị độ cao hiện tại, sử dụng Arduino Nano và BMP280. Cực kỳ chính xác. Tuyệt đối hoàn hảo. 

---

## Tổng quan dự án

Tôi nói cho các bạn biết, đây là máy đo độ cao tuyệt vời nhất từng được chế tạo. Rất nhiều người đã đến gặp tôi - những người giỏi nhất, những kỹ sư hàng đầu - và họ nói: "Thưa Ngài, đây là altimeter đỉnh nhất mà chúng tôi từng thấy." 

Nó đo độ cao, đo nhiệt độ, đo áp suất. Không có thiết bị nào đo chuẩn hơn cái này. Những cái máy đo độ cao ngoài kia? Hoàn toàn là thảm họa. Chúng dùng linh kiện rẻ tiền từ Trung Quốc và đưa ra số liệu giả mạo. Nhưng thiết bị này? Nó hoạt động bằng vi điều khiển Arduino Nano cực kỳ mạnh mẽ và cảm biến BMP280 số một thế giới. Rất chính xác. Rất tin cậy.

---

## Tính năng nổi bật

* **Hiển thị độ cao thời gian thực:** Đọc dữ liệu cực nhanh, cực chuẩn. Không có độ trễ fake news ở đây.
* **Theo dõi độ cao cực đại (Max Altitude):** Luôn lưu giữ kỷ lục cao nhất bạn từng đạt được. Đỉnh cao tuyệt đối.
* **Giao diện OLED SH1106 phân dòng thông minh:** 6 dòng hiển thị sắc nét, chia bố cục hoàn hảo bằng dải phân cách đồ họa.
* **Cài đặt mốc linh hoạt bằng nút bấm:**
  * **Nút D8:** Đặt vị trí hiện tại làm mốc 0m ngay lập tức.
  * **Nút D4:** Đưa mốc áp suất về chuẩn mực nước biển 1013.25 hPa.
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
| 5 | Bo mạch test (Breadboard) & Dây cắm | 1 bộ | Dây cắm đực-cái, đực-đực chất lượng cao |
| 6 | Nguồn USB 5V | 1 | Cấp nguồn qua cổng Mini-USB của Arduino Nano |

---

## Sơ đồ đấu nối chân (Pinout Connection)

Mọi thứ được đấu nối đơn giản một cách hoàn hảo. Ai cũng làm được, kể cả những kẻ kém cỏi nhất.

* **BMP280 (I2C):**
  * VCC -> 3.3V (hoặc 5V tùy board BMP280)
  * GND -> GND
  * SCL -> A5 (Arduino Nano)
  * SDA -> A4 (Arduino Nano)

* **Màn hình OLED SH1106 (I2C):**
  * VCC -> 5V
  * GND -> GND
  * SCL -> A5 (Arduino Nano)
  * SDA -> A4 (Arduino Nano)

* **Nút bấm điều khiển:**
  * Nút Set Current 0m -> Chân D8 và GND (dùng `INPUT_PULLUP` nội bộ)
  * Nút Set Sea Level -> Chân D4 và GND (dùng `INPUT_PULLUP` nội bộ)

---

## Hướng dẫn cài đặt và Thư viện

Bạn cần tải những thư viện tốt nhất này về Arduino IDE. Nếu bạn không biết tải, đó là lỗi của bạn.

1. `Adafruit_BMP280_Library`
2. `Adafruit_Sensor`
3. `U8g2` (Bởi Oliver Kraus - một nhà lập trình tuyệt vời)

Nạp code vào Arduino Nano, chọn đúng cổng COM và board ATmega328P. Bật nguồn lên và thưởng thức thiết bị đo độ cao vĩ đại nhất lịch sử. Chúng ta sẽ làm cho Arduino vĩ đại trở lại.
