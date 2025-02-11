// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of NVIDIA CORPORATION nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Copyright (c) 2008-2025 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#ifndef GU_ACTOR_SHAPE_MAP_H
#define GU_ACTOR_SHAPE_MAP_H

#include "common/PxPhysXCommonConfig.h"
#include "foundation/PxSimpleTypes.h"
#include "foundation/PxHashMap.h"

namespace physx
{
namespace Gu
{
	typedef PxU64	ActorShapeData;

	#define	PX_INVALID_INDEX	0xffffffff

	class ActorShapeMap
	{
		public:
		PX_PHYSX_COMMON_API					ActorShapeMap();
		PX_PHYSX_COMMON_API					~ActorShapeMap();

		PX_PHYSX_COMMON_API	bool			add(PxU32 actorIndex, const void* actor, const void* shape, ActorShapeData actorShapeData);
		PX_PHYSX_COMMON_API	bool			remove(PxU32 actorIndex, const void* actor, const void* shape, ActorShapeData* removed);
		PX_PHYSX_COMMON_API	ActorShapeData	find(PxU32 actorIndex, const void* actor, const void* shape)	const;

			struct ActorShape
			{
				PX_FORCE_INLINE	ActorShape()																	{}
				PX_FORCE_INLINE	ActorShape(const void* actor, const void* shape) : mActor(actor), mShape(shape)	{}

				const void*	mActor;
				const void*	mShape;

				PX_FORCE_INLINE bool operator==(const ActorShape& p) const
				{
					return mActor == p.mActor && mShape == p.mShape;
				}
			};
		private:
			PxHashMap<ActorShape, ActorShapeData>	mDatabase;

			struct Cache
			{
//				const void*		mActor;
				const void*		mShape;
				ActorShapeData	mData;
			};
			PxU32				mCacheSize;
			Cache*				mCache;

			void			resizeCache(PxU32 index);
	};
}
}

#endif
