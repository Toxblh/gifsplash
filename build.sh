#!/bin/bash

print_green() {
    echo -e "\033[0;32m$1\033[0m"
}

print_red() {
    echo -e "\033[0;31m$1\033[0m"
}


# Название вашего приложения
APP_NAME=gif_viewer

# Имя временного контейнера
CONTAINER_NAME=temp_$APP_NAME

# Собираем Docker образ
print_green "sudo podman build . -t $APP_NAME" 
sudo podman build . -t $APP_NAME

if [ $? -ne 0 ]; then
    print_red "The build command failed. Exiting the script."
    exit 1
fi

# Создаем контейнер из образа
print_green "sudo podman create --name $CONTAINER_NAME $APP_NAME"
sudo podman create --name $CONTAINER_NAME $APP_NAME

# Копируем исполняемый файл из контейнера на хост
print_green "sudo podman cp $CONTAINER_NAME:/app/$APP_NAME ."
sudo podman cp $CONTAINER_NAME:/app/$APP_NAME .

# Удаляем контейнер
print_green "sudo podman rm $CONTAINER_NAME"
sudo podman rm $CONTAINER_NAME

# Опционально: удаляем образ, если он больше не нужен
# docker rmi $APP_NAME