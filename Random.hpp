/*
 * Random.hpp
 *
 *  Created on: 14 Dec 2020
 *      Author: julianporter
 */

#ifndef DIRTYLFO_RANDOM_HPP_
#define DIRTYLFO_RANDOM_HPP_

#include "base.hpp"

namespace meromorph {

struct MSWS {
	uint64 x;
	uint64 w;
	uint64 s;

	MSWS(const uint64 x_ = 0,const uint64 w_ = 0,const uint64 s_ = 0xb5ad4eceda1ce2a9) : x(x_), w(w_), s(s_) {};
	MSWS(const MSWS&) = default;
	MSWS & operator=(const MSWS&) = default;
	virtual ~MSWS() = default;

	void reset(const uint64 x_ = 0,const uint64 w_ = 0,const uint64 s_ = 0xb5ad4eceda1ce2a9);
	uint32 operator()();
};

class RNDBase {
protected:
	MSWS rng;
	const static float32 I32Max;
	const static uint64 sconst[];


	static uint64 seed(const uint64 n);


	float32 nextFloat() { return float32(rng())/I32Max; }

	virtual float32 next() = 0;

public:
	RNDBase(const float32 lower_ = 0,const float32 upper_ = 1) : rng() {};
	virtual ~RNDBase() = default;

	void init(const uint64 n);
};

class Random : public RNDBase {
	float32 lower;
	float32 upper;
public:

	Random(const float32 lower_ = 0,const float32 upper_ = 1) : RNDBase(), lower(lower_), upper(upper_) {};
	virtual ~Random() = default;

	virtual float32 next();
	float32 operator()() { return next(); }
};

class Bernoulli : public RNDBase  {
private:
	float32 p;

public:
	Bernoulli(const float32 p_=0.5) : RNDBase(), p(p_) {};
	virtual ~Bernoulli() = default;

	int32 nextInt(const uint32 n = I32Max) { return rng() % n; }
	virtual float32 next() { return nextFloat(); }
	operator bool() { return next()<p; }
	void setThreshold(const float32 p_) { p=p_; }

};






} /* namespace meromorph */

#endif /* DIRTYLFO_RANDOM_HPP_ */
