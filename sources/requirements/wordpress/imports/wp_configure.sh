#!/bin/bash
echo "wp_configure.sh [20s]"
sleep 20
cd /var/www/wordpress
wp core download --allow-root --path=/var/www/wordpress
wp config create --dbname=${SQL_DATABASE} --dbuser=${SQL_USER} --dbpass=${SQL_PASSWORD} --dbhost=mariadb:3306 --allow-root --dbprefix=wp_ --path=/var/www/wordpress
wp core install --url=${WP_URL} --title=${WP_TITLE} --admin_user=${WP_ADMIN_USER} --admin_password=${WP_ADMIN_PASS} --admin_email=${WP_ADMIN_EMAIL} --allow-root --skip-email --path=/var/www/wordpress
wp user create ${WP_USER} ${WP_USER_EMAIL} --user_pass=${WP_USER_PASSWORD} --role=author --allow-root --path=/var/www/wordpress
exec php-fpm7.4 -F