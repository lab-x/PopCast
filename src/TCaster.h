#pragma once

#include <SoyTypes.h>
#include <SoyThread.h>
#include "PopUnity.h"


class TCasterParams
{
public:
	std::string		mName;
};

class TCastDeviceMeta
{
public:
	TCastDeviceMeta() :
		mReference	( nullptr )
	{
	}
	
	bool			IsValid() const	{	return !mName.empty();	}
	
	std::string		mName;
	std::string		mAddress;
	std::string		mSerial;
	std::string		mVendor;
	std::string		mModel;
	void*			mReference;	//	get rid of this!
};
inline std::ostream& operator<<(std::ostream &out,const TCastDeviceMeta&in)
{
	out << in.mName << "@" << in.mAddress << "/" << in.mModel << "/" << in.mVendor << "(" << in.mSerial << ")";
	return out;
}


class TCaster
{
public:
};



