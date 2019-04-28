/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2017, ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef PCCBitstreamEncoder_H
#define PCCBitstreamEncoder_H

#include "PCCCommon.h"
#include "PCCEncoderParameters.h"
#include "PCCCodec.h"
#include "PCCMetadata.h"

#include <map>

namespace pcc {

class PCCBitstream;
class PCCContext;
class ProfileTierLevel;
class SequenceParameterSet;
class OccupancyParameterSet;
class GeometrySequenceParams;
class AttributeParameterSet;
class PatchSequenceDataUnit;
class PatchSequenceUnitPayload;
class PatchSequenceParameterSet;
class GeometryFrameParameterSet;
class AttributeFrameParameterSet;
class GeometryPatchParameterSet;
class GeometryPatchParams;
class AttributePatchParameterSet;
class AttributePatchParams;
class GeometryFrameParams;
class PatchFrameLayerUnit;
class PatchFrameParameterSet;
class PatchFrameHeader;
class RefListStruct;
class PatchFrameDataUnit;
class PatchInformationData;
class PatchDataUnit;
class DeltaPatchDataUnit;
class PCMPatchDataUnit;
class PointLocalReconstruction;
class GeometryParameterSet;
class AttributeSequenceParams;
class AttributeFrameParams;

class PCCBitstreamEncoder {
 public:
  PCCBitstreamEncoder();
  ~PCCBitstreamEncoder();

  int  encode( PCCContext& context, PCCBitstream& bitstream );
  void setParameters( PCCEncoderParameters params );


  // 7.3.2.1 General V-PCC unit syntax
  void vpccUnit( PCCContext& context, PCCBitstream& bitstream, VPCCUnitType vpccUnitType );

  // 7.3.2.2 V-PCC unit header syntax
  void vpccUnitHeader( PCCContext& context, PCCBitstream& bitstream, VPCCUnitType vpccUnitType );

  // 7.3.2.3 PCM separate video data syntax
  void pcmSeparateVideoData( PCCContext& context, PCCBitstream& bitstream, uint8_t bitCount );

  // 7.3.2.4 V-PCC unit payload syntax
  void vpccUnitPayload( PCCContext& context, PCCBitstream& bitstream, VPCCUnitType vpccUnitType );

  void vpccVideoDataUnit( PCCContext& context, PCCBitstream& bitstream, VPCCUnitType vpccUnitType );

  // 7.3.4.1 General Sequence parameter set syntax
  void sequenceParameterSet( SequenceParameterSet& sequenceParameterSet, PCCBitstream& bitstream );

  // 7.3.4.2 Byte alignment syntax
  void byteAlignment( PCCBitstream& bitstream );

  // 7.3.4.2 Profile, tier, and level
  void profileTierLevel( ProfileTierLevel& profileTierLevel, PCCBitstream& bitstream );

  // 7.3.4.3 Occupancy parameter set syntax
  void occupancyParameterSet( OccupancyParameterSet& occupancyParameterSet, PCCBitstream& bitstream );

  // 7.3.4.4 Geometry parameter set syntax 
  void geometryParameterSet( GeometryParameterSet& geometryParameterSet,
                             SequenceParameterSet& sequenceParameterSet,
                             PCCBitstream&         bitstream );

  // OLD 7.3.11 Geometry sequence metadata syntax TODO: remove
  void geometrySequenceParams( GeometrySequenceParams& geometrySequenceParams, PCCBitstream& bitstream );

  // 7.3.4.5 Attribute parameter set syntax
  void attributeParameterSet( AttributeParameterSet& attributeParameterSet,
                              SequenceParameterSet&  sequenceParameterSet,
                              PCCBitstream&          bitstream );

  // OLD 7.3.13 Attribute sequence Params
  void attributeSequenceParams( AttributeSequenceParams& attributeSequenceParams,
                                uint8_t                  dimension,
                                PCCBitstream&            bitstream );

  // 7.3.5.1 General patch data group unit syntax TODO: rename(?)
  void patchSequenceDataUnit( PCCContext& context, PCCBitstream& bitstream );

  // 7.3.5.2 Patch data group unit payload syntax TODO: rename(?)
  void patchSequenceUnitPayload( PatchSequenceUnitPayload& patchSequenceUnitPayload,
                                 PatchSequenceUnitPayload& psupPrevPFLU,
                                 size_t                    frameIndex,
                                 PCCContext&               context,
                                 PCCBitstream&             bitstream );

  // 7.3.5.3 Patch sequence parameter set syntax
  void patchSequenceParameterSet( PatchSequenceParameterSet& patchSequenceParameterSet, PCCBitstream& bitstream );

  // 7.3.5.4 Patch frame geometry parameter set syntax TODO: rename(?)
  void geometryFrameParameterSet( GeometryFrameParameterSet& geometryFrameParameterSet,
                                  GeometryParameterSet&      geometryParameterSet,
                                  PCCBitstream&              bitstream );

  // 7.3.5.5 Geometry frame Params syntax
  void geometryFrameParams( GeometryFrameParams& geometryFrameParams, PCCBitstream& bitstream );

  // 7.3.5.6 Patch frame attribute parameter set syntax TODO: rename(?)
  void attributeFrameParameterSet( AttributeFrameParameterSet& attributeFrameParameterSet,
                                   AttributeParameterSet&      attributeParameterSet,
                                   PCCBitstream&               bitstream );

  // 7.3.5.7 Attribute frame Params syntax 
  void attributeFrameParams( AttributeFrameParams& attributeFrameParams, size_t dimension, PCCBitstream& bitstream );

  // 7.3.5.8 Geometry patch parameter set syntax 
  void geometryPatchParameterSet( GeometryPatchParameterSet& geometryPatchParameterSet,
                                  GeometryFrameParameterSet& geometryFrameParameterSet,
                                  PCCBitstream&              bitstream );

  // 7.3.5.9 Geometry patch Params syntax 
  void geometryPatchParams( GeometryPatchParams&       geometryPatchParams,
                            GeometryFrameParameterSet& geometryFrameParameterSet,
                            PCCBitstream&              bitstream );

  // 7.3.5.10 Attribute patch parameter set syntax
  void attributePatchParameterSet( AttributePatchParameterSet& attributePatchParameterSet,
                                   AttributeParameterSet&      attributeParameterSet,
                                   AttributeFrameParameterSet& attributeFrameParameterSet,
                                   PCCBitstream&               bitstream );

  // 7.3.5.11 Attribute patch Params syntax
  void attributePatchParams( AttributePatchParams&       attributePatchParams,
                             AttributeFrameParameterSet& afps,
                             size_t                      dimension,
                             PCCBitstream&               bitstream );

  // 7.3.5.12 Patch frame parameter set syntax
  void patchFrameParameterSet( PatchFrameParameterSet& patchFrameParameterSet,
                               SequenceParameterSet&   sequenceParameterSet,
                               PCCBitstream&           bitstream );

  // 7.3.5.13 Patch frame layer unit syntax
  void patchFrameLayerUnit( PatchFrameLayerUnit& patchFrameLayerUnit,
                            PatchFrameLayerUnit& pfluPrev,
                            PCCContext&          context,
                            PCCBitstream&        bitstream );

  // 7.3.5.14 Patch frame header syntax
  void patchFrameHeader( PatchFrameHeader& patchFrameHeader,
                         PatchFrameHeader& pfhPrev,
                         PCCContext&       context,
                         PCCBitstream&     bitstream );

  // 7.3.5.15 Reference list structure syntax
  void refListStruct( RefListStruct&             refListStruct,
                      PatchSequenceParameterSet& patchSequenceParameterSet,
                      PCCBitstream&              bitstream );

  // 7.3.5.16 Patch frame data unit syntax 
  void patchFrameDataUnit( PatchFrameDataUnit& pfdu,
                           PatchFrameHeader&   patchFrameHeader,
                           PCCContext&         context,
                           PCCBitstream&       bitstream );

  // 7.3.5.17 Patch information data syntax
  void patchInformationData( PatchInformationData&    pid,
                             size_t                   patchMode,
                             PatchFrameHeader&        pfh,
                             PCCContext&              context,
                             PCCBitstream&            bitstream );

  // 7.3.5.18 Patch data unit syntax
  void patchDataUnit( PatchDataUnit&           pdu,
                      PatchFrameHeader&        pfh,
                      PCCContext&              context,
                      PCCBitstream&            bitstream );

  // 7.3.5.19  Delta Patch data unit 
  void deltaPatchDataUnit( DeltaPatchDataUnit&      dpdu,
                           PatchFrameHeader&        pfh,
                           PCCContext&              context,
                           PCCBitstream&            bitstream );

  // 7.3.5.20 PCM patch data unit syntax
  void pcmPatchDataUnit( PCMPatchDataUnit&        ppdu,
                         PatchFrameHeader&        pfh,
                         PCCContext&              context,
                         PCCBitstream&            bitstream );

  // 7.3.5.21 Point local reconstruction syntax 
  void pointLocalReconstruction( PointLocalReconstruction& plr,
                                 PCCContext&               context,
                                 PCCBitstream&             bitstream );

  // 7.3.5.22 Supplemental enhancement information message syntax TODO: declaration missing

  PCCEncoderParameters params_;
};

};  // namespace pcc

#endif /* PCCBitstreamEncoder_H */
