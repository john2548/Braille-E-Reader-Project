#ifndef PIN_H
#define PIN_H


typedef enum {
	false = 0,
	true = 1
} bool;

typedef struct {
	//Pin * t(bool raised);
	bool raised;
} Pin;

Pin createPin(bool rVal) {
	Pin newPin;
	newPin.raised = rVal;
	return newPin;
}


#endif // !PIN_H
