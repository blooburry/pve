#include <Zumo32U4.h>

#ifndef MOTORS_H
#define MOTORS_H

/*! Beheert de encoder en motor klassen uit de Zumo library. */
class Motors {
  public:
    /*! constructor */
    Motors();

    /* 
    deze snelheden worden gebruikt door de KeyInterpreter
    */
    static const int MEDIUM_SPEED = 200; //!< middelsnelheid
    static const int SLOW_SPEED = 100; //!< langzame snelheid
    static const int MAX_SPEED = 400; //!< snelle snelheid

    /*! deze methode set de snelheid van de motoren op basis van de ontvangen waardes */
    void setSpeeds(int, int);

  private:
    Zumo32U4Motors motors; //!< motoren object om de snelheden te setten
};

#endif