VERSION 5.00
Begin VB.Form Form1 
   BackColor       =   &H8000000A&
   Caption         =   "Extend OLE Example"
   ClientHeight    =   6135
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6960
   LinkTopic       =   "Form1"
   ScaleHeight     =   6135
   ScaleWidth      =   6960
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame4 
      Caption         =   "3. Execute ModL command"
      Height          =   855
      Left            =   120
      TabIndex        =   16
      Top             =   3480
      Width           =   6615
      Begin VB.TextBox CommandText 
         Height          =   285
         Left            =   240
         TabIndex        =   17
         Text            =   "RunSimulation(FALSE);"
         Top             =   360
         Width           =   6135
      End
   End
   Begin VB.TextBox ModelName 
      Height          =   285
      Left            =   2760
      TabIndex        =   3
      Text            =   "c:\extend5\mymodel.mox"
      Top             =   1920
      Width           =   3615
   End
   Begin VB.OptionButton UserModel 
      Caption         =   "Your model:"
      Height          =   255
      Left            =   1440
      TabIndex        =   2
      Top             =   1920
      Width           =   1215
   End
   Begin VB.OptionButton ExModel 
      Caption         =   "VB Example.mox"
      Height          =   255
      Left            =   1440
      TabIndex        =   1
      Top             =   1560
      Value           =   -1  'True
      Width           =   2775
   End
   Begin VB.CommandButton DoAll 
      Caption         =   "Execute all"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   2040
      TabIndex        =   0
      Top             =   5520
      Width           =   2535
   End
   Begin VB.Frame Frame1 
      Caption         =   "1. Load model"
      Height          =   1095
      Left            =   120
      TabIndex        =   6
      Top             =   1200
      Width           =   6615
      Begin VB.Label Label10 
         Caption         =   "Use model:"
         Height          =   255
         Left            =   480
         TabIndex        =   7
         Top             =   360
         Width           =   975
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "2. Set dialog variable"
      Height          =   975
      Left            =   120
      TabIndex        =   8
      Top             =   2400
      Width           =   6615
      Begin VB.TextBox SetBlock 
         Height          =   285
         Left            =   1200
         TabIndex        =   23
         Text            =   "0"
         Top             =   360
         Width           =   855
      End
      Begin VB.TextBox SetDialog 
         Height          =   285
         Left            =   3360
         TabIndex        =   22
         Text            =   "MeanDist"
         Top             =   360
         Width           =   855
      End
      Begin VB.TextBox SetValue 
         Height          =   285
         Left            =   4920
         TabIndex        =   21
         Text            =   "2"
         Top             =   360
         Width           =   855
      End
      Begin VB.Label Label1 
         Caption         =   "Block number"
         Height          =   255
         Index           =   0
         Left            =   120
         TabIndex        =   11
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label Label1 
         Caption         =   "Dialog variable"
         Height          =   255
         Index           =   1
         Left            =   2160
         TabIndex        =   10
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label Label2 
         Caption         =   "Value"
         Height          =   255
         Left            =   4440
         TabIndex        =   9
         Top             =   360
         Width           =   495
      End
   End
   Begin VB.Frame Frame3 
      Caption         =   "4. Get dialog variable"
      Height          =   855
      Left            =   120
      TabIndex        =   12
      Top             =   4440
      Width           =   6615
      Begin VB.TextBox GetValue 
         BackColor       =   &H8000000A&
         Enabled         =   0   'False
         Height          =   285
         Left            =   5160
         TabIndex        =   20
         Top             =   360
         Width           =   855
      End
      Begin VB.TextBox GetDialog 
         Height          =   285
         Left            =   3600
         TabIndex        =   19
         Text            =   "MeanVal"
         Top             =   360
         Width           =   855
      End
      Begin VB.TextBox GetBlock 
         Height          =   285
         Left            =   1440
         TabIndex        =   18
         Text            =   "1"
         Top             =   360
         Width           =   855
      End
      Begin VB.Label Label3 
         Caption         =   "Value"
         Height          =   255
         Left            =   4560
         TabIndex        =   15
         Top             =   360
         Width           =   495
      End
      Begin VB.Label Label1 
         Caption         =   "Dialog variable"
         Height          =   255
         Index           =   2
         Left            =   2400
         TabIndex        =   14
         Top             =   360
         Width           =   1095
      End
      Begin VB.Label Label1 
         Caption         =   "Block number"
         Height          =   255
         Index           =   3
         Left            =   360
         TabIndex        =   13
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.Label Label8 
      Alignment       =   2  'Center
      Caption         =   $"command.frx":0000
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1035
      Left            =   240
      TabIndex        =   5
      Top             =   120
      Width           =   6405
   End
   Begin VB.Label Label7 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   13.5
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   120
      TabIndex        =   4
      Top             =   1080
      Width           =   1575
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub DoAll_Click()

    ' The Extend application is an object

    Dim ExtendApp As Object
    Dim GettingObject
    Dim ExtendPath As String
    
    'Create an instance of Extend
    
    On Error GoTo ErrorHandler:      ' If Extend is not loaded an error will be returned and the CreateObject method will be called
    GettingObject = 1
    
    ' Get the active Extend object. If Extend is not open, this will cause an error
    '   and will go to the ErrorHandler label. Here, the CreateObject function is called
    
    Set ExtendApp = GetObject(, "Extend.Application")
    
loadmodel:
    
    GettingObject = 0
    
    ' Find out where Extend is installed
    
    If ExModel.Value = True Then  ' opening the standard model
     
         ExtendApp.Execute "GlobalStr0 = GetAppPath();"     ' get the path to extend
    
         ExtendPath = ExtendApp.Request("System", "GlobalStr0+:0:0:0")
         
         ' open the model
         
         ExtendApp.Execute "OpenExtendFile(" + """" + ExtendPath + "ModLTips\Ole Automation\vb\VB Example.mox" + """" + ");"
    
    Else
    
         ' Open the user model
    
         ExtendApp.Execute "OpenExtendFile(" + """" + ModelName.Text + """" + ");"
    
    End If
    
    ' Poke the value into the dialog of the block
    
    ExtendApp.Poke "System", SetDialog.Text + ":#" + SetBlock.Text + ":0:0", SetValue.Text
    
    ' Execute the listed command
    
    ExtendApp.Execute CommandText.Text
    
    'Request the dialog variable from Extend

    GetValue.Text = ExtendApp.Request("System", GetDialog.Text + ":#" + GetBlock.Text + ":0:0")

    ' Destroy the Extend object
    
    Set ExtendApp = Nothing
    
    GoTo done:


ErrorHandler:

    If GettingObject Then
    
       ' Extend is not running (otherwise GetObject would have worked) so we
       '   call create object to start Extend
    
       Set ExtendApp = CreateObject("Extend.Application")
       GoTo loadmodel:
    Else
        MsgBox Error$
    End If

done:

End Sub

