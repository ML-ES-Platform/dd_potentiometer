/*
 * dd_pot.h
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#ifndef _DD_POT_H_
#define _DD_POT_H_

#include "dd_pot_cfg.h"

#ifndef DD_POT_CONFIG
enum DD_POT_IdType {POT__CHANNEL_NR_OF = 0 };
#endif

typedef struct POT_ChannelType_t {
	Std_ChannelIdType rawChannelId = 0;

	Std_RawDataType RAW_MIN = 0;
	Std_RawDataType RAW_MAX = 1023;
	Std_RawDataType rawVal = 0;

	Std_PhyDataType POS_MIN = 0;
	Std_PhyDataType POS_MAX = 100;
	Std_PhyDataType posVal = 0;

	Std_RawGetterType GetRaw = NULL;
} POT_ChannelType;

POT_ChannelType* POT_GetChannelRef(Std_ChannelIdType channelId);
Std_ReturnType DD_POT_ChannelSetup(Std_ChannelIdType potChannelId, Std_ChannelIdType rawChannelId);
Std_ReturnType POT_GroupSetup(Std_ChannelIdType *srcIdGroup, Std_ChannelIdType *targhetIdGroup, uint8_t nr_of_channels);
Std_ReturnType DD_POT_SetPullMethod( Std_ChannelIdType channelId,  Std_RawGetterType GetRaw);
Std_ReturnType POT_SetGroupRawGetter(Std_ChannelIdType *srcIdGroup, Std_RawGetterType GetRaw, uint8_t nr_of_channels);

void POT_SetRawLimits(POT_ChannelType *channelRef, Std_RawDataType RAW_MIN, Std_RawDataType RAW_MAX);
void POT_SetPosLimits(POT_ChannelType *channelRef, Std_PhyDataType POS_MIN, Std_PhyDataType POS_MAX);

Std_RawDataType POT_GetRaw(POT_ChannelType *channelRef);
Std_RawDataType POT_GetRaw(Std_ChannelIdType channelId);
Std_PhyDataType POT_GetPosition(POT_ChannelType *channelRef);
Std_PhyDataType POT_GetPosition(Std_ChannelIdType channelId);

#endif /* _DD_POT_H_ */
