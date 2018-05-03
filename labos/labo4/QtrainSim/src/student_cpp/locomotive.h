#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include <QString>
#include <QThread>
class Locomotive /*: public QThread */
{

public:

    /** Constructeur.
     * Initialise la locomotive avec un numero invalide et une vitesse nulle.
     */
    Locomotive();

    /** Constructeur.
     * Initialise la locomotive en precisant son numero et sa vitesse initiale.
     * @param numero Numero de la locomotive.
     * @param vitesse Vitesse initiale de la locomotive.
     */
    Locomotive(int numero, int vitesse);

    /** Retourne le numero de la locomotive.
     * @return Numero de la locomotive.
     */
    int numero() const;

    QList<int> parcours() const;

    /** Fixe le numero de la locomotive.
     * @param numero Numero de la locomotive.
     */
    void fixerNumero(int numero);

    /** Retourne la vitesse actuelle de la locomotive.
     * @return Vitesse actuelle de la locomotive.
     */
    int vitesse() const;

    /** Fixe la vitesse de la locomotive.
     * Si la locomotive est en fonction, alors sa vitesse est modifiee en
     * consequence.
     * @param vitesse Vitesse de la locomotive.
     */
    void fixerVitesse(int vitesse);

    /** Determine la position initiale de la locomotive.
     * @param contactAvant Contact vers lequel la locomotive va se diriger.
     * @param contactArrier Contact a l'arriere de la locomotive.
     */
    void fixerPosition(int contactAvant, int contactArriere);

    /** Affiche un message.
     * @param message Message a afficher.
     */
    void afficherMessage(const QString &message);

    //! Allume les phares de la locomotive.
    void allumerPhares();

    //! Eteint les phares de la locomotive.
    void eteindrePhares();

    //! Demarre la locomotive.
    void demarrer();

    //! Arrete la locomotive.
    void arreter();

    //! Change le sens de marche de la locomotive.
    void inverserSens();

    void setParcoursUrgence(QList<int> parcoursUrgence);

    bool emergency();

    void setEmergency(bool takingEmergencyPath);



   /* void run(); */

    //void parcourir();
    //void parcourirInverse();

    void setParcours(QList<int> parcours);
    QList<int> parcoursUrgence() const;
    void setStartCS(int start);
    int startCS();
    void setEndCS(int end);
    int endCS();

    void inverserSensParcours();

private:
    int _numero;
    int _vitesse;
    bool _enFonction;
    QList<int> _parcours;
    QList<int> _parcoursUrgence;
    int _startCS;
    int _endCS;
    bool _emergency;
};

#endif // LOCOMOTIVE_H
