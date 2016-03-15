#pragma once

#include <SoyOpenglContext.h>
#include "TBlitter.h"

namespace Opengl
{
	class TBlitter;
}



class Opengl::TBlitter : public Soy::TBlitter
{
public:
	~TBlitter();
	void			BlitTexture(TTexture& Target,ArrayBridge<Opengl::TTexture>&& Source,TContext& Context,const TTextureUploadParams& UploadParams,std::shared_ptr<Opengl::TShader> OverrideShader=nullptr);
	void			BlitTexture(TTexture& Target,ArrayBridge<Opengl::TTexture>&& Source,TContext& Context,const TTextureUploadParams& UploadParams,const char* OverrideShader);
	void			BlitTexture(TTexture& Target,ArrayBridge<SoyPixelsImpl*>&& Source,TContext& Context,const TTextureUploadParams& UploadParams,const char* OverrideShader=nullptr);
	void			BlitError(TTexture& Target,const std::string& Error,TContext& Context);
	
	std::shared_ptr<TRenderTarget>			GetRenderTarget(Opengl::TTexture& Target,TContext& Context);
	std::shared_ptr<TGeometry>				GetGeo(Opengl::TContext& Context);
	std::shared_ptr<TShader>				GetShader(ArrayBridge<Opengl::TTexture>& Sources,TContext& Context);

	std::shared_ptr<TShader>				GetShader(const std::string& Name,const char* Source,TContext& Context);
	std::shared_ptr<TShader>				GetBackupShader(TContext& Context);		//	shader for when a shader doesn't compile
	std::shared_ptr<TShader>				GetErrorShader(TContext& Context);

	std::shared_ptr<TTexture>				GetTempTexturePtr(SoyPixelsMeta Meta,TContext& Context,GLenum Mode);
	Opengl::TTexture&						GetTempTexture(SoyPixelsMeta Meta,TContext& Context,GLenum Mode);

public:
	Array<std::shared_ptr<TTexture>>	mTempTextures;
	std::shared_ptr<TRenderTargetFbo>	mRenderTarget;
	std::shared_ptr<TGeometry>			mBlitQuad;
	std::map<const char*,std::shared_ptr<TShader>>	mBlitShaders;	//	shader mapped to it's literal content address
};


