Compilación de la librería

La librería libfprint-ci24 se encuentra basada dentro del entorno de compilación meson:
https://mesonbuild.com/

El cual utiliza la plataforma de compilación ninja:
https://ninja-build.org/


Instrucciones de isntalación de dependencias

- Desinstalar la librería libfprint-dev si existe
sudo apt-get update
sudo apt-get remove libfprint-dev

- Instalación de dependencias
sudo apt-get install libglib2.0-dev libnss3-dev libpixman-1-dev libusb-1.0.0-dev pkg-config ninja-build

- Instalación de dependencias para el entorno de meson
sudo apt-get install python3 python3-pip ninja-build

- Instalar el meson para python
pip3 install --user meson


Instrucciones de compilación

1. Eliminar la protección contra escritura con la que cuenta la partición root
mount -o remount,rw /

2. Pararse sobre la ruta de root
cd

3. Clonar el repositorio
git clone https://github.com/MovilesCi24/libfprint-ci24.git

4. Pararse sobre la carpeta
cd libfprint-ci24/

5. Realizar la generación de los cósigos sobre el entorno meson
~/.local/bin/meson build

6. Entrar a la carpeta build
cd build

7. Ejecutar el comando ninja para subir las librerías
ninja


Adición de las librerías al LDCONFIG
La adición de las liibrerías al ldconfig se realiza por medio del siguiente paso:

1. Entrar a la carptea ld.so 
cd /etc/ld.so.conf.d/

2. Crear el archivo
nano fprintlibs.conf

Adicionando la siguiente línea
/root/fprintbuild/libfprint-master/build/libfprint/

3. Cargar de nuevo las librerías con el comando
ldconfig


Generación del programa fprinthandler

1. Entrar a la carpeta
/root/libfprint-ci24/fprinthandler/ç

2. Ejecutar el comando 
make








