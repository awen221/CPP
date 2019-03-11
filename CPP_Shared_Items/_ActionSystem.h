#ifndef _ACTION_SYSTEM_H_
#define _ACTION_SYSTEM_H_

#include<vector>

#include "GetAsyncKeyStateManger.h"
#include "point_base.h"

class EventKey
{
public:
	enum {KEY_DOWN ,KEY_UP ,KEY_TriggerDown ,KEY_TriggerUP ,KEY_Double ,
		//CursorX_Shift ,CursorY_Shift ,
		PARAM_COUNT } ;
	int KeyCode ;
	int Param ;

	KeyStateManager keyStateManager;

	EventKey():KeyCode(0) ,Param(0)
	{
	}
	void Init()
	{
		keyStateManager = KeyStateManager();
		keyStateManager.AddKeyState(KeyCode);
	}
	bool Work()
	{
		if(Param == KEY_DOWN)
			if(keyStateManager.IsDown(KeyCode))
				return true;

		if(Param == KEY_UP)
			if(keyStateManager.IsUp(KeyCode))
				return true;

		if(Param == KEY_TriggerDown)
			if(keyStateManager.IsTriggerDown(KeyCode))
				return true;

		if(Param == KEY_TriggerUP)
			if(keyStateManager.IsTriggerUp(KeyCode))
				return true;

		if(Param == KEY_Double)
			if(keyStateManager.IsDouble(KeyCode))
				return true;

		//if(Param == CursorX_Shift)
		//	if(keyStateManager.X_Chang())
		//		return true;

		//if(Param == CursorY_Shift)
		//	if(keyStateManager.Y_Chang())
		//		return true;

		return false;
	}

	void Write	(FILE* pFile)
	{
		int version = 0 ;
		fwrite (&version		,sizeof (version)		, 1, pFile) ;

		fwrite (&Param			,sizeof (Param)			, 1, pFile) ;
		fwrite (&KeyCode		,sizeof (KeyCode)		, 1, pFile) ;
	}
	void Read	(FILE* pFile)
	{
		int version = 0 ;
		fread (&version			,sizeof (version)		, 1, pFile) ;

		fread (&Param			,sizeof (Param)			, 1, pFile) ;
		fread (&KeyCode			,sizeof (KeyCode)		, 1, pFile) ;
	}
};
typedef std::vector<EventKey> V_EVENT_KEY;

class ActionEvent
{
public:
	enum {TYPE_PARAM ,TYPE_MOVE ,TYPE_DIR ,TYPE_COUNT} ;
	int BeginTime, EndTime ;
	V_EVENT_KEY v_EventKey;

	ActionEvent():BeginTime(0), EndTime(0)
	{
	}
	void Init()
	{
		for(int i = 0 ; i < v_EventKey.size() ; i++)
			v_EventKey[i].Init();
	}
	bool WorkTime(int& curActTime)
	{
		return ((BeginTime <= curActTime) && (EndTime >= curActTime)) ;
	}
	bool Param()
	{
		V_EVENT_KEY::iterator pi = v_EventKey.begin();
		while(pi != v_EventKey.end())
		{
			if(!pi->Work())
				return false;
			pi++;
		}
		return true;
	}
	virtual void Write	(FILE* pFile)
	{
		int version = 0 ;
		fwrite (&version,		 sizeof (version)		, 1, pFile) ;

		fwrite (&BeginTime		,sizeof (BeginTime)		, 1, pFile) ;
		fwrite (&EndTime		,sizeof (EndTime)		, 1, pFile) ;

		int count = v_EventKey.size () ;	
		fwrite (&count			,sizeof (count)			, 1, pFile) ;
		V_EVENT_KEY::iterator pi = v_EventKey.begin () ;
		while (pi != v_EventKey.end ())
		{
			pi->Write(pFile) ;
			++ pi ;
		}		
	}
	virtual void Read	(FILE* pFile)
	{
		int version = 0 ;
		fread (&version,		 sizeof (version)		, 1, pFile) ;

		fread (&BeginTime		,sizeof (BeginTime)		, 1, pFile) ;
		fread (&EndTime			,sizeof (EndTime)		, 1, pFile) ;

		int count ;	
		fread (&count			,sizeof (count)		, 1, pFile) ;
		v_EventKey.resize (count) ;
		V_EVENT_KEY::iterator pi = v_EventKey.begin () ;
		while (pi != v_EventKey.end ())
		{
			pi->Read(pFile);
			++ pi ;
		}
	}
};
class EventParam:public ActionEvent
{
public:
	int EventActionID;		//紀錄本事件中下一個動作編號	

	bool Work(int& curActTime , int& nextActID)
	{
		if(Param() && WorkTime(curActTime))
		{
			nextActID = EventActionID;
				return true;
		}
		return false;
	}
	void Write	(FILE* pFile)
	{
		ActionEvent::Write(pFile);
		int version = 0 ;
		fwrite (&version		,sizeof (version)		, 1, pFile) ;

		fwrite (&EventActionID	,sizeof (EventActionID)	, 1, pFile) ;
	}
	void Read	(FILE* pFile)
	{
		ActionEvent::Read(pFile);
		int version = 0 ;
		fread (&version			,sizeof (version)		, 1, pFile) ;

		fread (&EventActionID	,sizeof (EventActionID)	, 1, pFile) ;
	}
};
typedef std::vector<EventParam> V_EVENT_PARAM;

class EventMove:public ActionEvent
{
public:
	enum{Type_Auto ,Type_Key};
	bool MoveType ;
	
	float Dir ;
	float Len ;

	bool Work(PointBase& pnt ,int& curActTime)
	{
		if(WorkTime(curActTime))
		{
			if(MoveType == Type_Auto)
				pnt.SetDirMove(Len ,Dir) ;	//往角色方向的偏移角度移動 ,0為往角色方向移動
			else
			{
				if(Param() || v_EventKey.size() == 0)
					pnt.SetDirMove(Len ,Dir) ;
			}
		}
		return false ;
	}
	void Write	(FILE* pFile)
	{
		ActionEvent::Write(pFile);
		int version = 0 ;
		fwrite (&version		,sizeof (version)		, 1, pFile) ;

		fwrite (&MoveType		,sizeof (MoveType)		, 1, pFile) ;
		fwrite (&Dir			,sizeof (Dir)			, 1, pFile) ;
		fwrite (&Len			,sizeof (Len)			, 1, pFile) ;
	}
	void Read	(FILE* pFile)
	{
		ActionEvent::Read(pFile);
		int version = 0 ;
		fread (&version			,sizeof (version)		, 1, pFile) ;

		fread (&MoveType		,sizeof (MoveType)		, 1, pFile) ;
		fread (&Dir				,sizeof (Dir)			, 1, pFile) ;
		fread (&Len				,sizeof (Len)			, 1, pFile) ;
	}
};
typedef std::vector<EventMove> V_EVENT_MOVE;

class EventDir:public ActionEvent
{
public:
	enum{Type_Set ,Type_Shift ,Type_CursorShift} ;
	int DirType ;
	int	Val ;

	bool Work(PointBase& pnt ,int& curActTime)
	{
		if(WorkTime(curActTime))
		{
			if(Param() || v_EventKey.size() == 0)
			{
				if(DirType == Type_Set)
					pnt.SetDir(Val) ;
				else if(DirType == Type_Shift)
					pnt.DirShfit(Val) ;
				else if(DirType == Type_CursorShift)
				{
					if(ShareInput::Input.CursorX_Chang)
						pnt.DirShfit(ShareInput::Input.CursorX_Shift*Val) ;
				}
			}
		}
		return false ;
	}
	void Write	(FILE* pFile)
	{
		ActionEvent::Write(pFile);
		int version = 0 ;
		fwrite (&version		,sizeof (version)		, 1, pFile) ;

		fwrite (&DirType		,sizeof (DirType)			, 1, pFile) ;
		fwrite (&Val			,sizeof (Val)				, 1, pFile) ;
	}
	void Read	(FILE* pFile)
	{
		ActionEvent::Read(pFile);
		int version = 0 ;
		fread (&version			,sizeof (version)		, 1, pFile) ;

		fread (&DirType			,sizeof (DirType)		, 1, pFile) ;
		fread (&Val				,sizeof (Val)			, 1, pFile) ;
	}
};
typedef std::vector<EventDir> V_EVENT_DIR;

class Action
{
public:
	V_EVENT_PARAM v_EventParam;
	V_EVENT_MOVE v_EventMove;
	V_EVENT_DIR v_EventDir;
	int ID;
	TcString Name;
	int TimeLength;
	int NextActionID;

	Action():ID(0),NextActionID(0),TimeLength(0)
	{
		Name = L"未定義" ;
	}
	void Init()
	{
		for(int i = 0 ; i < v_EventParam.size() ; i++)
			v_EventParam[i].Init();
		for(int i = 0 ; i < v_EventMove.size() ; i++)
			v_EventMove[i].Init();
		for(int i = 0 ; i < v_EventDir.size() ; i++)
			v_EventDir[i].Init();
	}
	bool Work(PointBase& pnt , int& curActTime , int& nextActID)
	{
		for(int i = 0 ; i < v_EventParam.size() ; i++)
			if(v_EventParam[i].Work (curActTime,nextActID))
				return true;
		for(int i = 0 ; i < v_EventMove.size() ; i++)
			v_EventMove[i].Work (pnt,curActTime);
		for(int i = 0 ; i < v_EventDir.size() ; i++)
			v_EventDir[i].Work (pnt,curActTime);

		if (curActTime >= TimeLength)
		{
			curActTime -= TimeLength ;
			if (NextActionID != ID)
			{
 				nextActID = NextActionID ;
				return true ;
			}
		}
		return false;
	}
	void Action::Write (FILE* pFile)
	{
		int version = 0 ;
		fwrite (&version,		 sizeof (version)		, 1, pFile) ;

		fwrite (&ID				,sizeof (ID)			, 1, pFile) ;
		fwrite (&NextActionID	,sizeof (NextActionID)	, 1, pFile) ;
		fwrite (&Name			,sizeof (Name)			, 1, pFile) ;
		fwrite (&TimeLength		,sizeof (TimeLength)	, 1, pFile) ;

		int count = v_EventParam.size () ;
		fwrite (&count			, sizeof (count)		, 1, pFile) ;

		for(int i=0; i<v_EventParam.size (); i++)
			v_EventParam[i].Write(pFile) ;

		count = v_EventMove.size () ;
		fwrite (&count			, sizeof (count)		, 1, pFile) ;

		for(int i=0; i<v_EventMove.size (); i++)
			v_EventMove[i].Write(pFile) ;

		count = v_EventDir.size () ;
		fwrite (&count			, sizeof (count)		, 1, pFile) ;

		for(int i=0; i<v_EventDir.size (); i++)
			v_EventDir[i].Write(pFile) ;
	}
	void Action::Read (FILE* pFile)
	{
		int version = 0 ;
		fread (&version,		 sizeof (version)		, 1, pFile) ;

		fread (&ID				,sizeof (ID)			, 1, pFile) ;
		fread (&NextActionID	,sizeof (NextActionID)	, 1, pFile) ;
		fread (&Name			,sizeof (Name)			, 1, pFile) ;
		fread (&TimeLength		,sizeof (TimeLength)	, 1, pFile) ;

		int count;
		fread (&count			, sizeof (count)		, 1, pFile) ;
		v_EventParam.resize (count) ;

		for(int i=0; i<v_EventParam.size (); i++)
			v_EventParam[i].Read(pFile) ;

		fread (&count			, sizeof (count)		, 1, pFile) ;
		v_EventMove.resize (count) ;

		for(int i=0; i<v_EventMove.size (); i++)
			v_EventMove[i].Read(pFile) ;

		fread (&count			, sizeof (count)		, 1, pFile) ;
		v_EventDir.resize (count) ;

		for(int i=0; i<v_EventDir.size (); i++)
			v_EventDir[i].Read(pFile) ;
	}
};
typedef std::vector<Action> V_Action;

class ActionSystem
{
public:
	enum{ACT_STAND};
	V_Action v_Action;
	int CurAction;
	int CurActionTime;
	int PreTime;
	bool bChangeAct;	
	bool bControl;

	ShareInput key ;

	void Init()
	{
		for(int i = 0 ; i < v_Action.size() ; i++)
			v_Action[i].Init();
	}
	void ChangeAction(int next_actID)
	{
		int offset = 0 ;
		V_Action::iterator pi = v_Action.begin();
		while(pi != v_Action.end())
		{
			if(pi->ID == next_actID)
			{
				CurAction = offset;
				CurActionTime = 0 ;
				break;
			}
			++pi;
			offset++;
		}
	}
	void Work(PointBase& pnt ,int timepass)
	{
		if(CurAction >= v_Action.size())
		{
			CurAction = ACT_STAND ;
			return;
		}
		int newActID;
		bChangeAct = v_Action[CurAction].Work(pnt,CurActionTime,newActID) ;
		if(bChangeAct)
			ChangeAction(newActID);
	}
	void Draw(HDC hdc ,const PointBase& pnt)
	{
		TextOut (hdc, pnt.X, pnt.Y,v_Action[CurAction].Name, strlen (v_Action[CurAction].Name)) ;
	}
	ActionSystem():CurAction(0) ,CurActionTime(0) ,PreTime(0) ,bChangeAct(false) ,bControl(true)
	{
		//{
		//	Action act;
		//	act.ID = 10 ;
		//	act.Name = "站立" ;
		//	act.NextActionID = 10 ;
		//	act.TimeLength = 1000 ;

		//	{
		//		EventParam par;
		//		par.BeginTime = 0 ;
		//		par.EndTime	= 1000	;
		//		par.EventActionID = 20 ;

		//		EventKey key;
		//		key.Param = EventKey::KEY_DOWN ;
		//		key.KeyCode = VK_UP ;
		//		par.v_EventKey.push_back(key);
		//		act.v_EventParam.push_back(par);
		//	}
		//	{
		//		EventParam par;
		//		par.BeginTime = 0 ;
		//		par.EndTime	= 1000	;
		//		par.EventActionID = 20 ;

		//		EventKey key;
		//		key.Param = EventKey::KEY_DOWN ;
		//		key.KeyCode = VK_DOWN ;
		//		par.v_EventKey.push_back(key);
		//		act.v_EventParam.push_back(par);
		//	}
		//	{
		//		EventParam par;
		//		par.BeginTime = 0 ;
		//		par.EndTime	= 1000	;
		//		par.EventActionID = 20 ;

		//		EventKey key;
		//		key.Param = EventKey::KEY_DOWN ;

		//		key.KeyCode = VK_LEFT ;
		//		par.v_EventKey.push_back(key);
		//		act.v_EventParam.push_back(par);
		//	}
		//	{
		//		EventParam par;
		//		par.BeginTime = 0 ;
		//		par.EndTime	= 1000	;
		//		par.EventActionID = 20 ;

		//		EventKey key;
		//		key.Param = EventKey::KEY_DOWN ;

		//		key.KeyCode = VK_RIGHT ;
		//		par.v_EventKey.push_back(key);
		//		act.v_EventParam.push_back(par);
		//	}
		//	v_Action.push_back(act);			
		//}
		//{
		//	Action act;
		//	act.ID = 20 ;
		//	act.Name = "走路" ;
		//	act.NextActionID = 20 ;
		//	act.TimeLength = 1000 ;

		//	{
		//		EventParam par;
		//		par.BeginTime = 0 ;
		//		par.EndTime	= 1000	;
		//		par.EventActionID = 10 ;

		//		EventKey key;
		//		key.Param = EventKey::KEY_UP ;

		//		key.KeyCode = VK_UP ;
		//		par.v_EventKey.push_back(key);
		//		key.KeyCode = VK_DOWN ;
		//		par.v_EventKey.push_back(key);
		//		key.KeyCode = VK_LEFT ;
		//		par.v_EventKey.push_back(key);
		//		key.KeyCode = VK_RIGHT ;
		//		par.v_EventKey.push_back(key);

		//		act.v_EventParam.push_back(par);
		//	}
		//	v_Action.push_back(act);			
		//}
		Load("act.act");
	}
	void ActionSystem::Write(FILE* pFile)
	{
		int version = 0 ;
		fwrite (&version, sizeof (version)	, 1, pFile) ;

		int count = v_Action.size () ;
		fwrite (&count	, sizeof (count)	, 1, pFile) ;

		V_Action::iterator pi = v_Action.begin () ;
		while (pi != v_Action.end ())
		{
			pi->Write (pFile) ;
			++ pi ;
		}
	}
	void ActionSystem::Save	(const char* fname)
	{
		FILE* pFile = fopen (fname, "wb") ;
		if (pFile == NULL)
			return ;

		Write (pFile) ;

		fclose (pFile) ;
	}
	void ActionSystem::Read (FILE* pFile)
	{
		int version = 0 ;
		fread (&version, sizeof (version)	, 1, pFile) ;

		int count ;
		fread (&count	, sizeof (count)	, 1, pFile) ;

		v_Action.resize (count) ;
		V_Action::iterator pi = v_Action.begin () ;
		while (pi != v_Action.end ())
		{
			pi->Read (pFile) ;
			++ pi ;
		}
	}
	void ActionSystem::Load (const char* fname)
	{
		FILE* pFile = fopen (fname, "rb") ;
		if (pFile == NULL)
			return ;

		Read (pFile) ;

		fclose (pFile) ;
	}
};
#endif