#pragma once

#include <Core/Containers/Vector.h>
#include <Core/Math/Box.hpp>
#include <RHI/RHIFoward.h>

namespace ow
{

class IRHICommandList : public RefCountObject
{
public:
	virtual ~IRHICommandList() {}

	virtual void Begin() = 0;
	virtual void End() = 0;

	// Binding
	virtual void BeginRenderPass(IRHISwapChain* pSwapChain) = 0;
	virtual void EndRenderPass() = 0;

	// Resource
	virtual void SetVertexBuffer(IRHIBuffer* pVertexBuffer, uint32 bindingSlot = 0) = 0;
	virtual void SetIndexBuffer(IRHIBuffer* pIndexBuffer, bool useUInt16 = false) = 0;

	// View
	virtual void SetViewport(const Viewport& viewport) = 0;
	virtual void SetScissor(const Rect& rect) = 0;
	//virtual void SetShadingRate() = 0;

	// Dispatch
	virtual void Dispath(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ) = 0;
	//virtual void DispatchIndirect() = 0;
	//virtual void DispatchRays() = 0;
	//virtual void DispatchMesh(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ) = 0;

	// Draw
	virtual void Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance) = 0;
	virtual void DrawIndirect(IRHIBuffer* pArgBuffer, uint32 offset, uint32 drawCount, uint32 stride) = 0;
	//virtual void DrawIndirectCount() = 0;
	virtual void DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, uint32 vertexOffset, uint32 firstInstance) = 0;
	//virtual void DrawIndexedIndirect() = 0;
	//virtual void DrawIndexedIndirectCount() = 0;

	// Raytracing
	// virtual void BuildRaytracingAccelerationStructure() = 0;

	// Copy
	//virtual void CopyBuffer(IRHIBuffer* pSrc, IRHIBuffer* pDst) = 0;
	//virtual void CopyTexture(IRHITexture* pSrc, IRHITexture* pDst) = 0;
	//virtual void CopyBufferToTexture(IRHIBuffer* pSrc, IRHITexture* pDst) = 0;
	//virtual void CopyRaytracingAccelerationStructure(IRHIAccelerationStructure* pSrc, IRHIAccelerationStructure* pDst) = 0;
};

}