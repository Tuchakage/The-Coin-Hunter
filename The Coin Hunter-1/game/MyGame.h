#pragma once


#include "Game.h"


class CMyGame : public CGame
{
public:
	CMyGame();
	~CMyGame();

    // ----  Declare your game variables and objects here -------------

	// Variables
	int score;
	int coins;
	int quest;
	int edown;
	int ecounter;
	bool pwave;
	bool IsAttacking;
	bool scorereset;

    // Models and Model Lists
    CModelMd2 player;   // animated player model
    CModel box;		// another box (obj model)
	
	
	// todo: Declare more models
	CModel grass;
	CModel plant;
	CModel coin;
	CModel wall;
	CModelMd2 cobra;
	CModelMd2 python;
	CModelMd2 alien;
	CModelMd2 ogre;

	//Model Lists
	CModelList grassList;
	CModelList plantList;
	CModelList coinList;
	CModelList cobraList;
	CModelList shotList;
	CModelList pythonList;
	CModelList alienList;
	CModelList ogreList;
	CModelList wallList;
	
	//Sound
	CSoundPlayer shotEffect;
	CSoundPlayer collectEffect;
	CSoundPlayer coinboxEffect;
	CSoundPlayer backgroundMusic;
	CSoundPlayer menuMusic;
	
	// slash screen
	CSprite screen;
	CSprite gameOverScreen;
	CSprite completeScreen;
	

	// game world floor
	CFloor floor;
	
	// health indicator
	CHealthBar hbar;
	CHealthBar ebar;
	CHealthBar bbar;
	
	// Font
	CFont font;

   // -----   Add you member functions here ------
   
   void PlayerControl();
   void CheckQuests();
   void EnemyControl();
   void AlienControl();
   void OgreControl();
  
   
   void CameraControl(CGraphics* g);

   // ---------------------Event Handling --------------------------

	// Game Loop Funtions
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);
	virtual void OnRender3D(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartLevel(int level);
	virtual void OnStartGame();
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
