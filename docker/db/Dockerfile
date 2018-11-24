FROM base/archlinux

RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm postgresql

COPY ./postgresql.sh /usr/bin/postgresql.sh
RUN chmod +x /usr/bin/postgresql.sh

USER postgres
VOLUME ["/var/lib/postgres"]
EXPOSE 5432/tcp
ENTRYPOINT ["/usr/bin/postgresql.sh"]


