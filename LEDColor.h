#pragma once
class LEDColor 
{
private:
    int rVal;
    int gVal;
    int bVal;
    int wVal;

public:
    LEDColor(int r, int g, int b, int w);
    void setR(int val);
    void setG(int val);
    void setB(int val);
    void setW(int val);
    int getR();
    int getG();
    int getB();
    int getW();
};
