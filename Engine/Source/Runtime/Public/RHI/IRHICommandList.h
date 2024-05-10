#pragma once

#include <Core/Containers/Vector.h>
#include <RHI/RHIFoward.h>

namespace ow
{

class IRHICommandList : public RefCountObject
{
public:
	virtual ~IRHICommandList() {}

	virtual void Begin() = 0;
	virtual void End() = 0;

	virtual void BeginRenderPass(IRHISwapChain* pSwapChain) = 0;
	virtual void EndRenderPass() = 0;

	virtual void SetViewport(float width, float height, float x = 0.0f, float y = 0.0f) = 0;
	virtual void SetScissor(uint32 width, uint32 height, uint32 x = 0, uint32 y = 0) = 0;

	virtual void SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingStart = 0) = 0;
	virtual void SetVertexBuffers(const Vector<IRHIBuffer*>& vertexBuffers, uint32 bindingStart = 0) = 0;
	virtual void SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16 = false) = 0;

	virtual void Draw(uint32 vertexCount, uint32 vertexStart = 0) = 0;
	virtual void DrawInstanced(uint32 vertexCount, uint32 instanceCount, uint32 vertexStart = 0, uint32 instanceStart = 0) = 0;
	virtual void DrawIndexed(uint32 indexCount, uint32 indexStart = 0, uint32_t vertexOffset = 0) = 0;
	virtual void DrawIndexedInstanced(uint32 indexCount, uint32 instanceCount = 1, uint32 indexStart = 0, uint32 instanceStart = 0, uint32_t vertexOffset = 0) = 0;
};

}