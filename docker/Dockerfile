FROM base/archlinux

RUN useradd --no-create-home --shell=/bin/false cpp-rest-service-user \
 && usermod -L cpp-rest-service-user \
 && echo "cpp-rest-service-user ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers \
 && echo "root ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm openssl-1.0 sudo base-devel git boost websocketpp jsoncpp libnsl libuv libxml2 rhash shared-mime-info cmake libmongoc

RUN git clone https://aur.archlinux.org/cpprestsdk.git cpprestsdk-aur \
 && chown cpp-rest-service-user cpprestsdk-aur \
 && cd cpprestsdk-aur \
 && sudo -u cpp-rest-service-user makepkg -r \
 && ls \
 && pacman -U --noconfirm *.pkg.tar* \
 && cd .. \
 && rm -rf cpprestsdk-aur

RUN git clone https://aur.archlinux.org/mongo-cxx-driver.git mongo-cxx-driver-aur \
 && chown cpp-rest-service-user mongo-cxx-driver-aur \
 && cd mongo-cxx-driver-aur \
 && sudo -u cpp-rest-service-user makepkg -r \
 && ls \
 && pacman -U --noconfirm *.pkg.tar* \
 && cd .. \
 && rm -rf mongo-cxx-driver-aur \
 && cp -r /usr/local/lib64/* /usr/lib64

RUN pacman -Rns --noconfirm sudo git jsoncpp libnsl libuv libxml2 rhash shared-mime-info cmake
RUN pacman -Syyu --noconfirm

RUN mkdir /opt/cpp-rest-service
COPY installed /opt/cpp-rest-service
RUN chmod a+rx /opt/cpp-rest-service/cpp-rest-service

EXPOSE 6502

WORKDIR "/opt/cpp-rest-service"

ENTRYPOINT ["./cpp-rest-service"]

