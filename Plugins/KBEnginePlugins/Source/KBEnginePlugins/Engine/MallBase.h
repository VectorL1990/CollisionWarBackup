/*
	Generated by KBEngine!
	Please do not modify this file!
	Please inherit this module, such as: (class Mall : public MallBase)
	tools = kbcmd
*/

#pragma once
#include "KBECommon.h"
#include "Entity.h"
#include "KBETypes.h"
#include "ServerErrorDescrs.h"
#include "EntityCallMallBase.h"

class Method;
class Property;
class MemoryStream;

// defined in */scripts/entity_defs/Mall.def
class KBENGINEPLUGINS_API MallBase : public Entity
{
public:
	EntityBaseEntityCall_MallBase* pBaseEntityCall;
	EntityCellEntityCall_MallBase* pCellEntityCall;



	void onGetBase() override;
	void onGetCell() override;
	void onLoseCell() override;

	EntityCall* getBaseEntityCall() override;
	EntityCall* getCellEntityCall() override;

	void onRemoteMethodCall(Method* pMethod, MemoryStream& stream) override;
	void onUpdatePropertys(Property* pProp, MemoryStream& stream) override;
	void callPropertysSetMethods() override;

	MallBase();
	virtual ~MallBase();

};

