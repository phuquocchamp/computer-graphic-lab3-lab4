# 3D Transformations và Quan Sát Vật Thể 3D

## 1. Cài đặt các phép biến đổi 3D:

- Tịnh tiến

- Đối xứng qua mặt phẳng xoy, yoz, xoz

- Tỉ lệ với tâm tỉ lệ (x0, y0, z0)

- Quay quanh các trục tọa độ.

## 2.Viết chương trình cho phép quan sát vật thể 3D

a) Vật thể được biểu diễn theo mô hình khung kết nối.

b) Vật thể được biểu diễn theo mô hình mặt đa giác

Yêu cầu: Dùng ma trận biến đổi hệ quan sát để quan sát vật thể bằng cách:

- Thay đổi phép chiếu: song song hoặc phối cảnh

- Thay đổi góc quan sát theta, phi để xoay vật thể

- Thay đổi vị trí quan sát (điểm nhìn)

- Phóng to, thu nhỏ vật thể


## 0. Hướng Dẫn Cài Đặt Môi Trường
**Step 1: Cài đặt thư viện**
```bash
chmod +x ./install_dependencies.sh
```

```bash
./install_dependencies.sh
```

**Step 2: Build Compiler & Run App**
```bash
cd build
cmake ..
make
```

```bash
./app
```

## 1. Cài Đặt Các Phép Biến Đổi 3D

### a) Tịnh Tiến
Phép tịnh tiến được thực hiện bằng hàm `translate(float tx, float ty, float tz)` để di chuyển vật thể theo các hướng x, y, và z với các giá trị dịch chuyển `tx`, `ty`, và `tz`. Trong chương trình này, phép tịnh tiến có thể được áp dụng để di chuyển vật thể đến một vị trí mong muốn trước khi thực hiện các phép biến đổi khác.

```cpp
void translate(float tx, float ty, float tz)
{
    glTranslatef(tx, ty, tz);
}
```

### b) Đối Xứng Qua Mặt Phẳng
Các phép đối xứng (phản chiếu) giúp tạo ra ảnh đối xứng của vật thể qua các mặt phẳng XOY, YOZ, và XOZ:
- **Đối xứng qua mặt phẳng XOY**: Sử dụng `mirrorXY()` để thực hiện đối xứng qua trục z (phản chiếu dọc trục z).
- **Đối xứng qua mặt phẳng YOZ**: Sử dụng `mirrorYZ()` để phản chiếu dọc trục x.
- **Đối xứng qua mặt phẳng XOZ**: Sử dụng `mirrorXZ()` để phản chiếu dọc trục y.

```cpp
void mirrorXY() { glScalef(1.0f, 1.0f, -1.0f); }
void mirrorYZ() { glScalef(-1.0f, 1.0f, 1.0f); }
void mirrorXZ() { glScalef(1.0f, -1.0f, 1.0f); }
```

### c) Tỉ Lệ với Tâm Tỉ Lệ (x0, y0, z0)
Phép tỉ lệ cho phép thay đổi kích thước của vật thể theo tỷ lệ `sx`, `sy`, `sz` và được thực hiện với một tâm tỉ lệ `(x0, y0, z0)`. Điều này giúp vật thể co giãn với một điểm gốc xác định.

```cpp
void scale(float sx, float sy, float sz, float x0, float y0, float z0)
{
    glTranslatef(x0, y0, z0);
    glScalef(sx, sy, sz);
    glTranslatef(-x0, -y0, -z0);
}
```

### d) Quay Quanh Các Trục Tọa Độ
Phép quay thực hiện việc quay vật thể quanh một trục xác định `(x, y, z)` với góc quay `angle`. Hàm `rotate(float angle, float x, float y, float z)` áp dụng phép quay với các giá trị trên.

```cpp
void rotate(float angle, float x, float y, float z)
{
    glRotatef(angle, x, y, z);
}
```

## 2. Viết Chương Trình Cho Phép Quan Sát Vật Thể 3D

### a) Biểu Diễn Mô Hình Khung Kết Nối
Chương trình cho phép hiển thị vật thể dưới dạng mô hình khung dây (wireframe) bằng cách sử dụng `glutWireTeapot(0.5)`. Chế độ này được thiết lập mặc định và có thể thay đổi qua phím `m` để chuyển đổi giữa mô hình khung dây và mô hình mặt đầy đủ.

```cpp
if (wireframeMode)
{
    glutWireTeapot(0.5);
}
```

### b) Biểu Diễn Mô Hình Mặt Đa Giác
Khi người dùng nhấn phím `m`, chế độ hiển thị được chuyển sang mô hình mặt đa giác (solid polygon) bằng cách sử dụng `glutSolidTeapot(0.5)`.

```cpp
else
{
    glutSolidTeapot(0.5);
}
```

## 3. Dùng Ma Trận Biến Đổi Hệ Quan Sát Để Quan Sát Vật Thể

Chương trình sử dụng hệ tọa độ quan sát để thiết lập góc nhìn và vị trí của camera khi quan sát vật thể.

### a) Thay Đổi Phép Chiếu: Song Song hoặc Phối Cảnh
Hàm `setProjection(bool perspective)` cho phép người dùng chọn giữa phép chiếu phối cảnh (`gluPerspective`) hoặc phép chiếu song song (`glOrtho`).

```cpp
void setProjection(bool perspective)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (perspective)
    {
        gluPerspective(60.0, 1.0, 1.0, 100.0);
    }
    else
    {
        glOrtho(-2.0, 2.0, -2.0, 2.0, 1.0, 100.0);
    }
    glMatrixMode(GL_MODELVIEW);
}
```

### b) Thay Đổi Góc Quan Sát theta, phi Để Xoay Vật Thể
Người dùng có thể sử dụng các phím `w`, `s`, `a`, và `d` để điều chỉnh các giá trị góc `theta` và `phi`, cho phép thay đổi góc nhìn xung quanh vật thể:

- Phím `w/s`: Thay đổi góc `phi` để xoay vật thể lên hoặc xuống.
- Phím `a/d`: Thay đổi góc `theta` để xoay vật thể sang trái hoặc phải.

```cpp
switch (key)
{
    case 'w':
        phi += 0.1f;
        break;
    case 's':
        phi -= 0.1f;
        break;
    case 'a':
        theta -= 0.1f;
        break;
    case 'd':
        theta += 0.1f;
        break;
}
```

### c) Thay Đổi Vị Trí Quan Sát (Điểm Nhìn)
Hàm `gluLookAt()` trong `display()` được dùng để thiết lập điểm nhìn dựa trên các giá trị `theta`, `phi`, và `zoom`. Người dùng có thể quan sát vật thể từ các vị trí khác nhau dựa trên sự thay đổi của các thông số này.

```cpp
gluLookAt(5.0 * sin(theta) * cos(phi), 5.0 * sin(phi), 5.0 * cos(theta) * cos(phi),
          0.0, 0.0, 0.0,
          0.0, 1.0, 0.0);
```

### d) Phóng To, Thu Nhỏ Vật Thể
Phép phóng to, thu nhỏ được thực hiện bằng cách điều chỉnh giá trị `zoom`. Người dùng có thể sử dụng phím `+` để phóng to và phím `-` để thu nhỏ vật thể.

```cpp
case '+':
    zoom += 0.1f;
    break;
case '-':
    zoom -= 0.1f;
    break;
```

---
