#ifndef NFA_H
#define NFA_H

enum OP
{
    CHAR,
    CONCAT,
    UNION,
    STAR
};

struct TreeOp
{
    enum OP nodeOp;
    struct TreeOp * children;
    int childCount; //0-2
    int id;
    char * usefulData;
};
#endif