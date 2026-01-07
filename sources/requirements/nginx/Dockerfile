FROM debian:bullseye

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y nginx openssl
RUN mkdir -p /etc/nginx/ssl /var/www/wordpress
RUN chmod 755 /var/www/wordpress
RUN openssl req -x509 -nodes -out /etc/nginx/ssl/inception.crt -keyout /etc/nginx/ssl/inception.key -subj "/C=FR/ST=IDF/L=Mulhouse/O=42/OU=42/CN=uwywijas.42.fr/UID=uwywijas"

COPY ./imports/nginx.conf /etc/nginx/nginx.conf

CMD ["nginx", "-g", "daemon off;"]