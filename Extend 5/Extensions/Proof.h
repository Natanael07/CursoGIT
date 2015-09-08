constant	attach 	is 1;
constant	create 	is 2;
constant	destroy	is 3;
constant	detach 	is 4;
constant	move	is 5;
constant	placeat	is 6;
constant	placein	is 7;
constant	placeon	is 8;
constant	rotate	is 9;
constant	setclass is 10;
constant	setclear is 11;
constant	setcolor is 12;
constant	setdir	is 13;
constant	setnondir is 14;
constant	setspeed is 15;
constant	settravel is 16;
constant	pathspeed is 17;
constant	proofWrite is 18;

////
Sends the message to the Proof control block which sends the trace line to proof//

Procedure ProofAnimate(integer ProofIndex, Real SendValue)
{	if(UseProof && GetDimension(ProofStuff) == 0)		{		UserError("Proof animation has been selected for this block, but the proof animation action has not been selected. Please select a Proof animation action from the animate tab");		abort;		}
	if(UseProof && (GAGetInteger(ProofStuff[0],ConcurrentRow,0) || GAGetInteger(ProofStuff[0],TraceRow,0)))
		{
		GASetInteger(MyBlockNumber(),ProofStuff[0],BlockNumber,0);	// what block is animating
		GASetInteger(ProofStuff[1],ProofStuff[0],CommandType,0);	// what is the Command
		GASetInteger(ProofIndex,ProofStuff[0],ItemIndexRow,0);	// what is the item
		SysGlobal11 = SendValue;
		SendMsgToBlock(GAGetInteger(ProofStuff[0],0,0),BlockReceive4Msg);
		}}



on doProof
{
integer GAProof;

	GAProof = GaGetIndex("_proof");					// does the proof global array exist
	if(GAProof < 0)
		{
		UserError("You must add the Proof control block from the Proof library before you can access the proof animation for this block");
		abort;
		}
	if(GetDimension(ProofStuff) < 1)
		{
		MakeArray(ProofStuff,5);

		MakeArray(ProofStr,2);		// ProofStuff[0] = Proof global array index
		// ProofStuff[1] = CommandType
		// ProofStuff[2+] = Command Parameters
		}
	if(GetBlockType(MyBLockNumber()) == "Routing")

		ProofStuff[1] = Destroy;
	else if(GetBlockType(MyBLockNumber()) == "Generators")

		ProofStuff[1] = Create;
	else if(GetBlockType(MyBLockNumber()) == "Resources")

		ProofStuff[1] = Create;	else if(ProofStuff[1] < 1)

		ProofStuff[1] = 7;
	// ProofStr[0] = Proof object
	// ProofStr[1] = Attribute
	ProofStuff[0] = GAProof;
	GASetInteger(MyBlockNumber(),GAProof,BlockNumber,0);	// set the paused flag in the global array
	GASetInteger(ProofStuff[1],GAProof,CommandType,0);
	SendMsgToBlock(GaGetInteger(GAProof,ProofControlRow,0),BlockReceive3Msg);

}


Procedure initProof()
	{
	if(UseProof)
	ProofStuff[0] = GaGetIndex("_proof");					// does the proof global array exist
	}


Procedure HideProofMac()
{
		
	if(!PLATFORMWINDOWS)		{		DoProof = FALSE;		HideDialogItem("DoProof",TRUE);		HideDialogITem("UseProof",TRUE);		}	else		{		HideDialogItem("DoProof",FALSE);		HideDialogITem("UseProof",FALSE);		}
}
	

		