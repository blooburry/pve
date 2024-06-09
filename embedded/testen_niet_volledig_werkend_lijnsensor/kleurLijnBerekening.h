#ifndef KLEURLIJNBEREKENING_H
#define KLEURLIJNBEREKENING_H
//#include <Zumo32U4.h>


class kleurlijnberekening{
    private:
    int thZwart = 800;
    int thWit = 200;
    int thRoodMin = 201;
    int thRoodMax = 399; 
    int thGroenMin = 400;
    int thGroenMax = 599;
    int thBruinMin = 600;
    int thBruinMax = 799;
    int kleurstatus = 0;

    public:
    kleurlijnberekening();
    ~kleurlijnberekening();
    void vindLijnKleurStatus();
    void stuurStatus(int);

};
#endif