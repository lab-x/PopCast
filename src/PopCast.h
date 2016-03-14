#pragma once

#include "PopUnity.h"


class TCaster;
class TCasterParams;

__export Unity::ulong	PopCast_Alloc(const char* Filename,Unity::uint ParamBits);
__export bool			PopCast_Free(Unity::ulong Instance);
__export void			PopCast_EnumDevices();
__export bool			PopCast_UpdateRenderTexture(Unity::ulong Instance,Unity::NativeTexturePtr TextureId,Unity::sint Width,Unity::sint Height,Unity::RenderTexturePixelFormat::Type PixelFormat,Unity::sint StreamIndex);
__export bool			PopCast_UpdateTexture2D(Unity::ulong Instance,Unity::NativeTexturePtr TextureId,Unity::sint Width,Unity::sint Height,Unity::Texture2DPixelFormat::Type PixelFormat,Unity::sint StreamIndex);



//	way too many problems with using a struct, reverting to bit flags. (which may also have problems with endianness, container size etc)
//		android ONLY struct is offset
//		IL2CPP bools are 32 bit and NOT garunteed to have bit 1 set if true
//		long is 32 bit on some platforms and 64 on others
namespace TPluginParams
{
	//	copy & paste this to c#
	enum PopCastFlags
	{
		None						= 0,
		ShowFinishedFile			= 1<<0,
		Gif_AllowIntraFrames		= 1<<1,
		Gif_DebugPalette			= 1<<2,
		Gif_DebugIndexes			= 1<<3,
		Gif_DebugTransparency		= 1<<4,
	};
}

namespace PopCast
{
	class TInstance;
	typedef Unity::ulong	TInstanceRef;

	std::shared_ptr<TInstance>	Alloc(TCasterParams Params,std::shared_ptr<Opengl::TContext> OpenglContext=nullptr);
	std::shared_ptr<TInstance>	GetInstance(TInstanceRef Instance);
	bool						Free(TInstanceRef Instance);
};



class PopCast::TInstance
{
public:
	TInstance()=delete;
	TInstance(const TInstance& Copy)=delete;
public:
	explicit TInstance(const TInstanceRef& Ref,TCasterParams Params,std::shared_ptr<Opengl::TContext> OpenglContext);
	
	TInstanceRef	GetRef() const		{	return mRef;	}
	
	void			WriteFrame(Opengl::TTexture Texture,size_t StreamIndex);
	
public:
	std::shared_ptr<Opengl::TContext>	mOpenglContext;
	std::shared_ptr<TCaster>			mCaster;
	SoyTime								mBaseTimestamp;

private:
	TInstanceRef	mRef;
};


