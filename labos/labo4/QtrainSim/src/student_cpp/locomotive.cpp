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

QList<int> Locomotive::parcours() const{
    return _parcours;
}

QList<int> Locomotive::parcoursUrgence() const{
    return _parcoursUrgence;
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

void Locomotive::setParcoursUrgence(QList<int> parcoursUrgence){
    this->_parcoursUrgence = parcoursUrgence;
}


void Locomotive::inverserSensParcours(){
    std::reverse(this->_parcours.begin(), this->_parcours.end());
    if(parcoursUrgence().size() != 0)
        std::reverse(this->_parcoursUrgence.begin(), this->_parcoursUrgence.end());

}

void Locomotive::switchParcours(){
    QList<int> tmpP = _parcours;
    afficherMessage(QString("tm: %1").arg(tmpP.at(0)));
    _parcours = _parcoursUrgence;
    afficherMessage(QString("tm Par: %1").arg(_parcours.at(0)));
    _parcoursUrgence = tmpP;
    afficherMessage(QString("tm: %1").arg(_parcoursUrgence.at(0)));
}
