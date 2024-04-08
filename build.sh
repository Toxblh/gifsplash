#!/bin/bash

# Название вашего приложения
APP_NAME=gifsplash

# Имя временного контейнера
CONTAINER_NAME=temp_$APP_NAME

# Собираем Docker образ
sudo podman build . -t $APP_NAME

# Создаем контейнер из образа
sudo podman create --name $CONTAINER_NAME $APP_NAME

# Копируем исполняемый файл из контейнера на хост
sudo podman cp $CONTAINER_NAME:/app/$APP_NAME .

# Удаляем контейнер
sudo podman rm $CONTAINER_NAME

# Опционально: удаляем образ, если он больше не нужен
# docker rmi $APP_NAME