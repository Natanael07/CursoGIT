integer GetShiftBlockNum()
{
integer ShiftIndex;
integer i;

	ShiftIndex = GaGetIndex("_Shifts");
	if (ShiftIndex < 0 || !UseShift)
		return(-1);
	i = 0;
	while(i<GaGetRows("_Shifts") && ShiftName != GaGetString31(ShiftIndex,i,1))
		i++;	i--;	MyShift = StrToReal(GaGetString31(ShiftIndex,i,1));
	SysGlobalInt19 = MyBlockNumber() + 1; 
	SendMsgToBlock(MyShift, BlockReceive2Msg);
	SetPopupLabels("ShiftPop",ShiftName);	
}
integer CheckNameChange(){	if(SysGlobalInt19 > -1)		// SysGlobalInt19 = -1 means that the name of the Shift has changed		return(0);	ShiftName = GetDialogVariable(MyShift,"ShiftName",0,0);	SetPopUpLabels("ShiftPop",ShiftName);	return(1);	}Procedure SetShiftType(Integer CanNumberShift, Integer InitShift){	if(ShiftName == "")		UseShift = FALSE;	else if(GetDialogVariable(myShift,"ShiftStatusTypePop",0,0) == "2")		UseShift = 2;	else		UseShift = 1;		if(UseShift == 1)		ShiftStatus = TRUE;	else		ShiftStatus = InitShift;	if(!CanNumberShift && UseShift == 2)		{		UserError("The shift specified for "+BlockName(MyBlockNumber())+" block number "+MyBlockNumber()+" must be an On/Off type shift");		abort;		}}Procedure RemoveFromShiftBlock(Integer BlockNum){	if(MyShift > -1)		{		SysGlobalInt19 = -MyBlockNumber()-1;		SendMsgToBlock(BlockNum,Blockreceive2Msg);		}}Procedure AddToShiftBlock(Integer BlockNum){
	SysGlobalInt19 = MyBlockNumber()+1; 
	SendMsgToBlock(Blocknum, BlockReceive2Msg);
	SetPopupLabels("ShiftPop",ShiftName);}procedure DeleteShift(){	RemoveFromShiftBlock(MyShift);}Procedure doShiftPop()
{	if(GaGetIndex("_Shifts") < 0 || ShiftPop <= 0)
		{
		return;

		}
	if(ShiftPop > GAGetRows("_Shifts"))
		{
		SetPopupLabels("ShiftPop","None");
		ShiftName = "";		ShiftPop = 1;		UseShift = FALSE;
		MyShift = -1;
		}
	else
		{		if(ShiftName != "")			RemoveFromShiftBlock(MyShift);
		ShiftName = GaGetString31(ShiftIndex,ShiftPop-1,0);
		MyShift = StrToReal(GaGetString31(ShiftIndex,ShiftPop-1,1));		SetPopupLabels("ShiftPop",ShiftName);		AddToShiftBlock(MyShift);		UseShift = TRUE;		}	ShiftPop = 1;
}		


Procedure InitShift(){	integer i;	integer numShifts;		if(ShiftName == "")		UseShift = FALSE;		if(UseShift)		{		i = 0;		ShiftIndex = GAGetindex("_Shifts");		numShifts = GAGetRows("_shifts");				if(GetDialogVariable(MyShift,"ShiftName",0,0) != ShiftName)			{			while(i<NumShifts && GaGetString31(ShiftIndex,i,0) != ShiftName);				i++;			MyShift = StrToReal(GaGetString31(ShiftIndex,i,1));			}		SysGlobalInt19 = MyBlockNumber() + 1; 		SendMsgToBlock(MyShift, BlockReceive2Msg);		}	if(ShiftName == "")		SetPopupLabels("ShiftPop","none");	else		SetPopupLabels("ShiftPop",ShiftName);}Procedure DoShiftPopup(String31 DName){integer i;integer InitPop;
	if(dname == "ShiftPop")		{//		ThisShift = getDialogVariable(myblockNumber(),Dname ,0,0);	// get the current Attribute name
		ShiftIndex = GAGetindex("_Shifts");		if(ShiftIndex < 0)			SetPopupLabels("ShiftPop","None");		else			{			SetPopupLabels("ShiftPop","");
			initPop = GAFindStringAny(ShiftIndex,ShiftName,0,GaGetRows("_Shifts"),31,FALSE);			for(i=0;i<GaGetRows("_Shifts");i++)				appendPopupLabels("ShiftPop",GaGetString31(ShiftIndex,i,0) + ";");			appendPopupLabels("ShiftPop","-;None");
			if(initPop >= 0)
				ShiftPop  = InitPop;
			else
				ShiftPop = GaGetRows("_Shifts")+2;			}		}}Procedure UpdateShiftPop(){	if(GaGetIndex("_Shifts") < 0)
		{
		HideDialogItem("ShiftText",TRUE);
		HideDialogItem("ShiftPop",TRUE);
		return;

		}
	HideDialogItem("ShiftText",FALSE);
	HideDialogItem("ShiftPop",FALSE);
	ShiftPop = 1;	if(useShift)		SetPopupLabels("ShiftPop",ShiftName);	else		SetPopupLabels("ShiftPop","None");}procedure FindShiftBlocks(){	integer i;				// counters	integer maxBlocks;		// maximum possible number of blocks in the model	integer dummy[4];		// dummy array used in checking the block type	integer ifound;			// flag set if a server list is found				if(UseShift == 0 || ShiftName == "")
		Return;

	MyShift = FindInHierarchy("Shift", "" ,"ShiftName:"+ShiftName,TRUE);
	if(MyShift < 0)
		UserError(BlockName(MyBlockNumber())+" number "+MyBlockNumber()+" failed to find a uniquely identifiable shift block");
	
	return;
	maxBlocks = numBlocks();		iFound = FALSE;	i = 0;	While(i < MaxBlocks && !Ifound)		{		if(3 == getBlockTypePosition(i,dummy))	// only look at the blocks if they are regular blocks (not text or h-blocks)			{			if(BlockName(i) == "Shift" && GetDialogVariable(i,"ShiftName",0,0) == ShiftName)				ifound = 1;			}		i++;		}	if(ifound)		{		MyShift = i;		}	else		{		UserError(BlockName(MyBlockNumber())+" number "+MyBlockNumber()+" uses the shift "+ShiftName+" but this shift is not available in this model. Select a new shift for this block");		ShiftName = "";		MyShift = -1;		}	return;}