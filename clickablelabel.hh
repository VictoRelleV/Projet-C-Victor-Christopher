#include <QLabel>
#include <QWidget>
#include <QMouseEvent>

class ClickableLabel : public QLabel {
public:
    ClickableLabel(QWidget *parent = nullptr) : QLabel(parent) {}
    int score = 2;
    int positionx = 0;
    int positiony = 0;

    int getScore() const {
    return score;
    }

protected:

    // Surchargez la fonction mousePressEvent pour détecter les clics
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            score++;
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distribution1(0, 400);
            positionx = distribution1(gen);
            positiony = distribution1(gen);
            this->move(positionx, positiony);
            cout << "Score: " << score << endl;
        }
    }
};