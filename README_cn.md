# Windows开发和使用
## 硬件和驱动

#### JTAG硬件
淘宝中购买FT2232HL开发板

安装JTAG硬件的驱动
使用zadig为FT2232HL安装WinUSB

FT2232HL在Windows中显示USB <-> Serial Converter (Interface 0)或USB <-> Serial Converter (Interface 1)，
zadig下载地址：
https://github.com/pbatard/libwdi/releases/download/v1.5.1/zadig-2.9.exe

### 安装MSYS2
下载
https://github.com/msys2/msys2-installer/releases/download/2025-08-30/msys2-x86_64-20250830.exe

### 启动MSYS2 MINGW64，设置必要的环境
```shell
# 必要的MSYS2包
pacman -S libtool autoconf automake texinfo pkg-config make autogen git unzip bzip2 gettext-devel base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-libusb mingw-w64-x86_64-libusb-compat-git mingw-w64-x86_64-hidapi mingw-w64-x86_64-libftdi mingw-w64-x86_64-cmake python python-devel python-pip

# 需要先确定一下python所在的位置和版本
where python
which python && python --version

# 如不是MSYS2中的python，可将windows的PATH增加，例如：D:\msys64\mingw64\bin
# 同时在PATH中取消掉其他路径的python


#如果出问题 SSL certificate problem: unable to get local issuer certificate
GIT_SSL_NO_VERIFY=1

# git clone
git clone https://github.com/hiok2000/urjtag

# cd to path
cd urjtag/urjtag

# 创建虚拟环境，msys2不安装虚拟环境就不让pip执行
python -m venv myenv

# 激活虚拟环境
source myenv/bin/activate

# 安装模块
pip install -i https://mirrors.aliyun.com/pypi/simple/ --trusted-host mirrors.aliyun.com setuptools

# 退出虚拟环境
deactivate
```

# 生成可执行文件、开发和编译

```shell
# 先激活虚拟环境
source myenv/bin/activate

# 在虚拟环境中
# --enable-python 产生python模块
# --without-libintl-prefix 不加会出错
# --without-ftd2xx 不需要官方的ftd2xx，默认用libftdi库
# --disable-nls  不需要本地化，全英文，没有乱码
# --enable-relocatable   data目录在jtag.exe所在目录的../share/urjtag中，而不是在系统目录中
./autogen.sh --enable-python --without-libintl-prefix --without-ftd2xx --disable-nls --enable-relocatable
make

# 把exe lib dll data等文件归集到一个目录，而不是安装到系统目录中
make install prefix=/d/urjtag/urjtag/build/myurjtag

# autoconf成功后，可以使用以下指令看看支持哪些编译选项
./configure --help
```
# 使用
主要参考urjtag/urjtag/doc/UrJTAG.txt

可执行文件在/d/urjtag/urjtag/build/myurjtag/bin中，需要调用的器件库在D:\urjtag\urjtag\build\myurjtag\share中，请根据原有的器件库，新增自己的part。如果有BSDL文件，可以用bsdl2jtag转换。下面是一个运行svf文件的示例：
```shell
# use ft2232 interface B
cable ft2232 pid=0x6010 vid=0x403 interface=1 driver=ftdi-mpsse
frequency 1000000
detect
svf erase.svf progress stop
```
# Python使用
make成功后，make install会直接将python相关文件安装到MSYS2的python环境中，需要退出虚拟环境才能使用。

这里使用以下方法就能将模块安装到虚拟环境下。
```shell
cd bindings/python
make whl
cd dist
pip install urjtag-2021.3-cp312-cp312-mingw_x86_64_msvcrt_gnu.whl
```
就能安装到虚拟环境下了。

在虚拟环境下，python使用请看examples目录。

urjtag自带的bindings/python生成出来的文件，能在MSYS2中的python使用，但可能无法直接在Windows的python中使用。

# 二次开发
## 在MSYS2中的开发（推荐）
请看examples目录的example.c文件。可使用静态和动态方式。

另外，如果直接使用urjtag生成出来的jtag.exe，会有较多的依赖（MSYS2的组件）。这里放了一个jtag.c，用下面编译出来的jtag.exe，就能完全不依赖dll。
```shell
cd  examples
gcc -static -o jtag jtag.c -I"../include" -I"../" -L"../src/.libs" -lurjtag -lftdi1 -lusb-1.0 -lintl -lreadline -lncurses
```
## 在Visual Studio 2022中的开发
无法使用静态库，只能使用动态库

包含目录加入：urjtag/include

附加库目录加入：urjtag/src/.libs

附加依赖项加入：liburjtag.dll.a

# 执行文件依赖
如果Windows没有安装或找到MSYS2 MINGW64目录，按上面的选项配置，需要以下文件跟exe文件在同一个目录中。
```
libftdi1.dll libreadline8.dll libtermcap-0.dll libusb-1.0.dll libwinpthread-1.dll liburjtag-0.dll
```