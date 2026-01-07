default: up

up:
	@mkdir -p /home/uwywijas/data/mariadb /home/uwywijas/data/wordpress
	@docker compose -f ./sources/docker-compose.yml up --build

stop:
	@docker compose -f ./sources/docker-compose.yml stop

down:
	@docker compose -f ./sources/docker-compose.yml down

build:
	@mkdir -p /home/uwywijas/data/mariadb /home/uwywijas/data/wordpress
	@docker compose -f ./sources/docker-compose.yml build

fclean:
	@docker compose -f ./sources/docker-compose.yml down -v --rmi all
	@rm -rf /home/uwywijas/data/mariadb/ /home/uwywijas/data/wordpress/
	@docker system prune -af

re: fclean build up