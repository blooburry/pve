#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H

class StatusControl {
  public: 
    void zetLinks(bool status); // bepaalt de status van de linkermotor. Roep Motors.update() aan als dit verandert
    void zetRechts(bool status); // bepaalt de status van de rechter
    bool getLinks();
    bool getRechts();

  private:
    bool statusLinks;
    bool statusRechts;
};

#endif