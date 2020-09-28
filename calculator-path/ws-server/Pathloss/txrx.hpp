#include "coordinate.hh"
#include "coordinate.hh"
#include "lossreport.hh"
#include <vector>

class Pairtxrx{
public:
    void setTx(struct site tx);
    void setRx(struct site rx);
    struct site getstx();
    void assignPar(Coord tx, Coord rx);
    void setLoss(int propmodel, int pmenv);
    double getLoss();
    Coord& getTx();
    Coord& getRx();
 
private:
    std::vector<Coord> vp;
    struct site tx;
    struct site rx;
    double loss;
};