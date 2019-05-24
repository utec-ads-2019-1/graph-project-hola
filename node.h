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
    Node(N value){data = value;}
    Node(double xAxis, double yAxis){x = xAxis; y = yAxis;}
    Node(N value, double xAxis, double yAxis){data = value; x= xAxis; y = yAxis;}

    N getData() {return data;}
    void setData(N newData) {data = newData;}

private:
    N data;
    double x;
    double y;
};

#endif
