#ifndef PARCOURS
#define PARCOURS
class Parcours : public QThread{
public:
    Parcours::Parcours(QList<int> parcours);
    void run();
private:
    QList<int> parcours;
};

#endif // PARCOURS

