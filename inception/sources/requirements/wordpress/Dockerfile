FROM debian:bullseye

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y php7.4 php7.4-fpm php7.4-mysql curl
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp
RUN mkdir -p /run/php && touch /run/php/php7.4-fpm.pid

COPY ./imports/www.conf /etc/php/7.4/fpm/pool.d/www.conf
COPY ./imports/wp_configure.sh /

RUN chmod +x /wp_configure.sh

ENTRYPOINT [ "./wp_configure.sh" ]