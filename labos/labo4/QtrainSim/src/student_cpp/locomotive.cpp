#include "locomotive.h"
#include "ctrain_handler.h"

Locomotive::Locomotive() :
    _numero(-1),
    _vitesse(0),
    _enFonction(false)
{

}

Locomotive::Locomotive(int numero, int vitesse) :
    _numero(numero),
    _vitesse(vitesse),
    _enFonction(false)
{

}

int Locomotive::numero() const
{
    return _numero;
}

void Locomotive::fixerNumero(int numero)
{
    _numero = numero;
}

int Locomotive::vitesse() const
{
    return _vitesse;
}

void Locomotive::fixerVitesse(int vitesse)
{
    _vitesse = vitesse;

    if (_enFonction)
        mettre_vitesse_progressive(_numero, vitesse);
}

void Locomotive::fixerPosition(int contactAvant, int contactArriere)
{
    assigner_loco(contactAvant, contactArriere, _numero, _vitesse);
}

void Locomotive::afficherMessage(const QString &message)
{
    afficher_message_loco(_numero, qPrintable(message));
}

void Locomotive::allumerPhares()
{
    mettre_fonction_loco(_numero, ALLUME);
}

void Locomotive::eteindrePhares()
{
    mettre_fonction_loco(_numero, ETEINT);
}

void Locomotive::demarrer()
{
    mettre_vitesse_progressive(_numero, _vitesse);
    _enFonction = true;
}

void Locomotive::arreter()
{
    arreter_loco(_numero);
    _enFonction = false;
}

void Locomotive::inverserSens()
{
    inverser_sens_loco(_numero);
}

void Locomotive::setParcours(QList<int> parcours){
    this->_parcours = parcours;
}

void Locomotive::run(){

    this->demarrer();
    this->afficherMessage("Ready!");
    this->parcourir();
    this->parcourir();
    this->inverserSens();
    this->parcourir();

}


void Locomotive::parcourir(){

         for (int i = 0; i < this->_parcours.size(); i++) {

            attendre_contact(this->_parcours.at(i));
            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                        .arg(this->numero()).arg(this->_parcours.at(i))));
            this->afficherMessage(QString("I've reached contact no. %1.").arg(this->_parcours.at(i)));
        }
}

void Locomotive::parcourirInverse(){
        for (int i = this->_parcours.size()-1; i >= 0; i--) {
            attendre_contact(this->_parcours.at(i));
            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.")
                                        .arg(this->numero()).arg(this->_parcours.at(i))));
            this->afficherMessage(QString("I've reached contact no. %1.").arg(this->_parcours.at(i)));
        }
}
