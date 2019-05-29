#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::edge edge;
    typedef typename G::EdgeSeq EdgeSeq;

    EdgeSeq edges;

    Node(){}
    Node(N value){data = value; x = y = reached = 0;}
    Node(N value, double xAxis, double yAxis){data = value; x= xAxis; y = yAxis, reached = 0;}

    N getData() {return data;}
    void setData(N newData) {data = newData;}

    double getX(){return x;}
    void setX(double X){x = X;}

    double getY(){return y;}
    void setY(double Y){y = Y;}

    bool getReached() {return reached;}
    void setReached(bool Reached) {reached = Reached;}

private:
    N data = NULL;
    double x;
    double y;
    bool reached;
};

#endif
