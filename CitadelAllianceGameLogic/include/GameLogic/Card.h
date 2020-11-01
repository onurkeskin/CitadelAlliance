#pragma once

#include <string>

class Card {
public:
	virtual void Play();
protected:
private:
	std::string cardId;
};
