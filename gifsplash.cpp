#include <QApplication>
#include <QLabel>
#include <QMovie>
#include <QScreen>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    // Check for the required arguments
    if (argc < 3) {
        qWarning("Usage: gifsplash path_to_your_gif.gif width");
        return -1;
    }

    // Parse the desired width from the command line arguments
    bool conversionOk = false;
    int desiredWidth = QString(argv[2]).toInt(&conversionOk);
    if (!conversionOk) {
        qWarning("Please provide a valid width");
        return -1;
    }

    // Create a widget without borders and background
    QWidget window;
    window.setWindowFlags(Qt::FramelessWindowHint);
    window.setAttribute(Qt::WA_NoSystemBackground, true);
    window.setAttribute(Qt::WA_TranslucentBackground, true);

    // Create a QLabel to display the GIF
    QLabel label(&window);
    QMovie *movie = new QMovie(argv[1]); // Get the path to the GIF file from the arguments
    label.setMovie(movie);

    // Start the movie to calculate aspect ratio
    movie->start();
    int originalWidth = movie->frameRect().width();
    int originalHeight = movie->frameRect().height();

    double scaleFactor = static_cast<double>(desiredWidth) / originalWidth;
    int newHeight = static_cast<int>(originalHeight * scaleFactor);

    if (originalWidth != 0) {
        movie->setScaledSize(QSize(desiredWidth, newHeight));
    } else {
        qWarning("Cannot retrieve the original size of the GIF.");
        return -1;
    }

    // Adjust label size to fit scaled movie
    label.adjustSize();

    // Calculate coordinates to position the window in the center of the screen
    QScreen *screen = QApplication::screens().at(0);
    int x = (screen->geometry().width() - window.width()) / 2;
    int y = (screen->geometry().height() - window.height()) / 2;
    window.setGeometry(x, y, label.width(), label.height());

    window.show();

    return app.exec();
}