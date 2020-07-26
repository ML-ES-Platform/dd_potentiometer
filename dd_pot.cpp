/*
 * dd_pot.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#include "dd_pot.h"

#ifdef PLATFORM_CONFIG_ENABLE
extern POT_ChannelType POT_Channels[DD_POT_CHANNEL_NR_OF];
#else
POT_ChannelType POT_Channels[DD_POT_CHANNEL_NR_OF];
#endif

POT_ChannelType* POT_GetChannelRef(Std_ChannelIdType channelId) {
	POT_ChannelType *channelRef = &POT_Channels[channelId];
	return channelRef;

}


Std_ReturnType DD_POT_ChannelSetup(Std_ChannelIdType channelId, uint8_t rawChannelId) {
	Std_ReturnType error;
	if (channelId < DD_POT_CHANNEL_NR_OF) {
		POT_ChannelType *channelRef = POT_GetChannelRef(channelId);
		channelRef->rawChannelId = rawChannelId;
		error = E_OK;
	} else {
		error = E_NOT_OK;
	}
	return error;
}


//---------------------
Std_ReturnType DD_POT_SetPullMethod( Std_ChannelIdType channelId,  Std_RawGetterType GetRaw){
	Std_ReturnType error;
	if (channelId < DD_POT_CHANNEL_NR_OF) {
		POT_ChannelType *channelRef = POT_GetChannelRef(channelId);
		channelRef->GetRaw = GetRaw;
		error = E_OK;
	} else {
		error = E_NOT_OK;
	}
	return error;
}


Std_ReturnType POT_GroupSetup(Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		Std_ChannelIdType targhetId = targhetIds[i];
		error += DD_POT_ChannelSetup(srcId, targhetId);
	}
	return error;
}
Std_ReturnType POT_SetGroupRawGetter(Std_ChannelIdType *srcIds, Std_RawGetterType GetRaw, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		error += DD_POT_SetPullMethod(srcId, GetRaw);
	}
	return error;
}

void POT_SetRawLimits(POT_ChannelType * channelRef, Std_RawDataType RAW_MIN, Std_RawDataType RAW_MAX) {
	channelRef->RAW_MIN = RAW_MIN;
	channelRef->RAW_MAX = RAW_MAX;

}

void POT_SetPosLimits(POT_ChannelType * channelRef, Std_PhyDataType POS_MIN, Std_PhyDataType POS_MAX) {
	channelRef->POS_MIN = POS_MIN;
	channelRef->POS_MAX = POS_MAX;
}

Std_RawDataType POT_GetRaw(POT_ChannelType *channelRef) {
	if (channelRef->GetRaw)
		return channelRef->GetRaw(channelRef->rawChannelId);
	 else
		return 0;

}

Std_RawDataType POT_GetRaw(Std_ChannelIdType channelId) {
	POT_ChannelType *channelRef = &POT_Channels[channelId];
	Std_RawDataType rawVal = POT_GetRaw(channelRef);
	return rawVal;
}

Std_PhyDataType POT_GetPosition(POT_ChannelType * channelRef) {
	Std_RawDataType rawVal = POT_GetRaw(channelRef);
	Std_PhyDataType posVal = map_float(rawVal, channelRef->RAW_MIN, channelRef->RAW_MAX, channelRef->POS_MIN, channelRef->POS_MAX);
	return posVal;
}

Std_PhyDataType POT_GetPosition(Std_ChannelIdType channelId) {
	POT_ChannelType *channelRef = &POT_Channels[channelId];
	Std_PhyDataType posVal = POT_GetPosition(channelRef);
	return posVal;
}
