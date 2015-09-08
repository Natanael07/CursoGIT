Procedure NameTrace(integer WhichCon, integer WhichTrace, Integer MultiSim)
{
integer i;
integer BlockNum;
String31 ThisName;
String15 ConType;
integer FoundOutCon;
String15 ThisCon;
Integer ConNumber;
Integer UseCon;

	ThisName = GetSignalName(0,WhichTrace);
	
	if(ThisName == Labels[WhichCon])			// this name has not been changed by the user
		{

		if(MultiSim)
			UseCon = 0;
		else	
			UseCon = WhichCon;		BlockNum = GetConnectedTextBlock(MyBlockNumber(),UseCon); // get the block number of the text block connected to this conn
		if(BlockNum >= 0)								// is a text block connected to the input connector
			Labels[WhichCon] = BlockName(BlockNum);	// Get the text in the text block
		else											// check for a library block
			{
			GetConBlocks(MyBlockNumber(),UseCon,ConBlocks);	// get all of the connected library blocks
			if(GetDimension(ConBlocks) > 0)						// if at least one is connected
				{
				FoundOutCon = FALSE;
				i = 0;
				while(i < GetDimension(ConBlocks) && !FoundOutCon)		// look through all of the connectors until we find the output connector
					{
					ThisName = GetConName(ConBlocks[i][0],ConBlocks[i][1]);	// Get the name of the connector
					ConType = StrPart(ThisName,StrLen(ThisName) - 3,3);		// get the connector suffix
					if(ConType == "Out")									// this is an output connector
						{
						Labels[WhichCon] = StrPart(ThisName,0,StrLen(ThisName) - 3);	// Store the connector name
						FoundOutCon = TRUE;
						}
					else
						i++;
					}
				DisposeArray(ConBlocks);
				}
			}
		if(MultiSim)			Labels[WhichCon] += " "+WhichCon;

		SetSignalName(0,WhichTrace,Labels[WhichCon]);				// set the name of the traces
		}
}
