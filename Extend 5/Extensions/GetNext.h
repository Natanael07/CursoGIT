Procedure GetNext(integer MyOutCon){integer i;integer found;string15 conInOut;integer numCons;integer searching;	outBlock = 0;	GetConBlocks(MyBlockNumber(), MyOutCon, connected);	if (GetDimension(connected) == 1)		{		outBlock	= connected[0][0];		nextBlock 	= outBlock;		outConn		= connected[0][1];		NextCon		= outConn;		Found = FALSE;		while(!Found)			{			numCons = GetNumCons(NextBlock);			i = 0;			Searching = TRUE;			if(GetDialogVariable(nextBlock,"passingType"+nextCon,0,0) == "Passing")				{				while(i<numCons && searching)					{					conInOut = StrPart(GetConName(NextBlock,i),strlen(GetConName(NextBlock,i))-3,3);					if(GetConnectedType2(NextBlock,i) == 14 && conInOut == "out")  // is this an item output connector						{						if(GetConBlocks(NextBlock,i,connected) == 1)					// the output is only connected to one block							{							NextBlock = connected[0][0];							nextCon	  = connected[0][1];							searching = FALSE;							}						else															// parallel processing - don't optimize							{							found = TRUE;							}						}					i++;					}				}			if(searching)																// if we are still looking for the next block and we have gone through all of the connectors				found = TRUE;			}		}	DisposeArray(connected);}	