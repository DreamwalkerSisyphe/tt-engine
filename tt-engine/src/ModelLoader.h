#ifndef LOAD_NECO_H
#define LOAD_NECO_H


#include "raylib.h"

class Neco {
private:
	Model neco;
public:
	Neco();
	~Neco();
	Model& GetNeco();
};





#endif // !LOAD_NECO_H

