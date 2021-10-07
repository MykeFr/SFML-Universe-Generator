#pragma once

#include "GraphicsFramework/Tools.h"

class cLehmer32
{
public:

	cLehmer32(uint32_t seed) { nProcGen = seed; }

	double getD(double min, double max)
	{
		return ((double)Lehmer() / (double)(0x7FFFFFFF)) * (max - min) + min;
	}

	int getI(int min, int max)
	{
		return (Lehmer() % (max - min)) + min;
	}

	uint32_t Lehmer()
	{
		nProcGen += 0xe120fc15;
		uint64_t tmp;
		tmp = (uint64_t)nProcGen * 0x4a39b70d;
		uint32_t m1 = (tmp >> 32) ^ tmp;
		tmp = (uint64_t)m1 * 0x12fad5c9;
		uint32_t m2 = (tmp >> 32) ^ tmp;
		return m2;
	}

	void setSeed(uint32_t seed) { nProcGen = seed; }

private:
	uint32_t nProcGen;

};

extern cLehmer32 Lehmer32;