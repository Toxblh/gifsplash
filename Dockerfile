# Используем базовый образ Debian
FROM debian:latest

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y \
    build-essential \
    qtbase5-dev \
    qtbase5-dev-tools \
    libqt5widgets5 \
    && rm -rf /var/lib/apt/lists/*

# Создаем рабочую директорию для исходного кода
WORKDIR /app

# Копируем исходный код в контейнер
COPY . .

# Генерируем Makefile с помощью qmake и компилируем проект
RUN qmake gifsplash.pro \
    && make

# Запуск приложения
CMD [ "./gifsplash" ]