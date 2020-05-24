# Ultraviolet_Light_Generator 💜
## 🔰 Phần hướng dẫn dành cho các bạn sinh viên Vật lý Tin học (VL-VLKT - HCMUS) khi cần back-up hoặc sửa chữa lại hệ thống đèn phát UV làm mạch cảm quang:

### 1. Hệ thống mạch bao gồm cách thành phần chính như sau:
![dc55ba5debf911a748e8](https://user-images.githubusercontent.com/48848418/82749121-3b7d1400-9dd1-11ea-81ab-31fda68828cb.jpg)
- 🕶 LCD16x02 hiển thị thông tin.
- 💠 4 phím bấm chức năng - từ trái qua phải: Set (+) thời gian - Set (-) thời gian - Bắt đầu thực hiện chiếu tia - Reset tiến trình bất kì.
- ♻ 3 led đơn biểu thị chức năng riêng: trắng - chế độ set thời gian; đỏ - báo đang trong quá trình phát tia UV; xanh da trời - báo hoàn thành quá trình chiếu tia.
- Buzzer báo hoàn thành quá trình 💢.
- Hệ thống 2 đèn UV lớn ⭕.

### 2. Quá trình sử dụng chung:
2.1. Giai đoạn hẹn giờ (led trắng sáng): 🔜
- ⏫ Bấm nút số 1 để tăng thời gian hẹn giờ lên 1 phút (có thể đè lâu 1 chút rồi nhả để +5 phút/lần).
- ⏬ Bấm nút số 2 để giảm thời gian hẹn giờ xuống 1 phút (cũng có thể đè lâu 1 chút rồi nhả để +5 phút/lần).
- ☮ Bấm nút số 4 để reset thời gian trở về lại 00:00.
![7385257477d08d8ed4c1](https://user-images.githubusercontent.com/48848418/82749137-59e30f80-9dd1-11ea-8fbb-12e0ff77407e.jpg)

2.2. Giai đoạn thực hiện chiếu tia (led đỏ sáng): 〰
- 🔱Bấm nút số 3 để bắt đầu quá trình chiếu tia (lúc này màn hình bắt đầu đếm ngược thời gian).
- ☮ Có thể ngắt tiến trình ngay lập tức bằng cách nhấn giữ nút số 4 khoảng 1 giây để reset lại tiến trình hẹn giờ.
![551ac5e097446d1a3455](https://user-images.githubusercontent.com/48848418/82749139-5c456980-9dd1-11ea-8874-46c7fa96e555.jpg)

2.3. Giai đoạn kết thúc (led xanh sáng): ☑
- Lúc này tiến trình chiếu tia UV đã tắt, buzzer bắt đầu kêu để báo đã xong. ✅
- Tiến hành bấm giữ nút số 4 khoảng 1.5 - 2 giây để tắt thông báo và reset lại tiến trình ban đầu. ♻ 🌐
![1d7910814225b87be134](https://user-images.githubusercontent.com/48848418/82749140-5ea7c380-9dd1-11ea-8e22-48c123057ab6.jpg)

### 3. Thực hiện back-up hoặc sửa chữa lại mạch:
- Source code đính kèm sử dụng Arduino Platform để lập trình cho hệ thống. Các bạn có thể sử dụng bất kì vi điều khiển thuộc nền tảng Arduino nào để sửa chữa lại cho hệ thống (nếu cần).
- Cách liên kết mạch được đính kèm trong folder Diagrams các bạn có thể tham khảo để sửa chữa khi cần thiết. 💌

![13bc0d415fe5a5bbfcf4](https://user-images.githubusercontent.com/48848418/82749157-7aab6500-9dd1-11ea-8caf-159532521c4f.jpg)

`` Chúc các bạn thành công! Mọi thắc mắc về sản phẩm xin liên hệ Thanh Tùng - 0912.522.913 ``

#### Author: Phan Thanh Tung
