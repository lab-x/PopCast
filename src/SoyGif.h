#pragma once

#include <SoyTypes.h>
#include <SoyMedia.h>

class GifWriter;
class GifPalette;
class TRawWriteDataProtocol;


//	https://github.com/ginsweater/gif-h/blob/master/gif.h
namespace Gif
{
	std::shared_ptr<TMediaEncoder>	AllocEncoder(std::shared_ptr<TMediaPacketBuffer>& OutputBuffer,size_t StreamIndex);

	class TMuxer;
	class TEncoder;
}

class Gif::TMuxer : public TMediaMuxer
{
public:
	TMuxer(std::shared_ptr<TStreamWriter>& Output,std::shared_ptr<TMediaPacketBuffer>& Input,const std::string& ThreadName);
	~TMuxer();
	
protected:
	virtual void			Finish() override;
	virtual void			SetupStreams(const ArrayBridge<TStreamMeta>&& Streams) override;
	virtual void			ProcessPacket(std::shared_ptr<TMediaPacket> Packet,TStreamWriter& Output) override;

	void					WriteToBuffer(const ArrayBridge<uint8>&& Data);
	void					FlushBuffer();
	
public:
	std::mutex					mBusy;
	std::shared_ptr<GifWriter>	mWriter;
	
	std::shared_ptr<GifPalette>		mPrevPalette;
	std::shared_ptr<SoyPixelsImpl>	mPrevImage;
	
	//	data being written to by GifWriter
	std::shared_ptr<TRawWriteDataProtocol>	mBuffer;
};


class Gif::TEncoder : public TMediaEncoder, public SoyWorkerThread
{
public:
	TEncoder(std::shared_ptr<TMediaPacketBuffer>& OutputBuffer,size_t StreamIndex);
	
	virtual void			Write(const Opengl::TTexture& Image,SoyTime Timecode,Opengl::TContext& Context) override;
	virtual void			Write(const std::shared_ptr<SoyPixelsImpl> Image,SoyTime Timecode) override;

protected:
	virtual bool					CanSleep() override;
	virtual bool					Iteration() override;
	void							PushFrame(std::shared_ptr<TMediaPacket> Frame);
	std::shared_ptr<TMediaPacket>	PopFrame();

public:
	size_t					mStreamIndex;
	size_t					mPacketsWritten;
	
	std::mutex				mPendingFramesLock;
	Array<std::shared_ptr<TMediaPacket>>	mPendingFrames;
};
