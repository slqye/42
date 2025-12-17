FROM debian:bullseye

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y mariadb-server
RUN mkdir -p /run/mysqld /var/lib/mysql
RUN chown -R mysql:mysql /run/mysqld /var/lib/mysql
RUN chmod 755 /run/mysqld /var/lib/mysql

COPY ./imports/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY ./imports/mysql_configure.sh /

RUN chmod +x /mysql_configure.sh
USER root

ENTRYPOINT [ "./mysql_configure.sh" ]