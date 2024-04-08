#include <QApplication>
#include <QLabel>
#include <QMovie>
#include <QScreen>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Проверка наличия аргумента с путем к GIF
    if (argc < 2) {
        qWarning("Usage: gifsplash path_to_your_gif.gif");
        return -1;
    }

    // Создаем виджет без рамки и фона
    QWidget window;
    window.setWindowFlags(Qt::FramelessWindowHint);
    window.setAttribute(Qt::WA_NoSystemBackground, true);
    window.setAttribute(Qt::WA_TranslucentBackground, true);

    // Создаем QLabel для отображения GIF
    QLabel label(&window);
    QMovie *movie = new QMovie(argv[1]); // Получаем путь до GIF файла из аргументов
    label.setMovie(movie);

    // Устанавливаем размер виджета равным размеру GIF для корректного отображения
    movie->start();
    label.adjustSize();

    // Рассчитываем координаты для размещения окна по центру экрана
    QScreen *screen = QApplication::screens().at(0);
    int x = (screen->geometry().width() - window.width()) / 2;
    int y = (screen->geometry().height() - window.height()) / 2;
    window.setGeometry(x, y, label.width(), label.height());

    window.show();

    return app.exec();
}
