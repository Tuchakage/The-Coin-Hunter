#include "MyGame.h"

using namespace std;

CMyGame::CMyGame(void) 
{ 
	score = 0;
	coins = 0;
	edown = 0;
	quest = 1;
	ecounter = 0;
	pwave = false;
	IsAttacking = false;
	scorereset = false;
}

CMyGame::~CMyGame(void) {}


// --------  game initialisation --------
void CMyGame::OnInitialize()
{

	// Loading graphics and sound assets
	cout << "Loading assets" << endl;
	
	font.LoadDefault(); 
	
	CTexture::smooth=true;
	
	// enable lighting
	Light.Enable();

	// load abarlith model
	player.LoadModel("Abarlith.md2","Abarlith.bmp"); 
	player.SetScale( 3.5f);
	
	// todo: load grass model
	grass.LoadModel("grass.obj", "grass.tga");
	grass.SetScale(1.5f);
	
	// Plant Model
	plant.LoadModel("varen.obj", "varen.tga");
	plant.SetScale(1.0f);


	// todo: load box model
	box.LoadModel("Wooden Crate.obj", "Wooden Crate_Crate_BaseColor.bmp");
	box.SetScale(20.0f);
	/*Old Box Model
	box.LoadModel("box.obj", "box.bmp");
	box.SetScale(7.0f);*/
	
	
	// todo: load coin model
	coin.LoadModel("coin.obj", "coin.bmp");
	coin.SetScale(7.0f);
	
	// todo: load snake model
	cobra.LoadModel("cobra.md2","cobra.bmp");
	cobra.SetScale(5.0f);
	
	// todo: load python model
	python.LoadModel("python.md2", "python.bmp");
	python.SetScale(6.5f);

	// Alien (xenotype)
	alien.LoadModel("xenotype.md2", "xenotype.bmp");
	alien.SetScale(5.0f);
	
	//Ogre 
	ogre.LoadModel("Ogro.md2", "Ogro.bmp");
	ogre.SetScale(5.0f);

	//Wall
	wall.LoadModel("Bricks wall");
	wall.SetScale(2500.0f);

	// load screen sprite image
	screen.LoadImage("startScreen.bmp");
	screen.SetPosition(Width/2.0f, Height/2.0f);

	gameOverScreen.LoadImage("gameOver.bmp");
	gameOverScreen.SetPosition(Width / 2.0f, Height / 2.0f);

	completeScreen.LoadImage("gameComplete.bmp");
	completeScreen.SetPosition(Width / 2.0f, Height / 2.0f);

	
	// load floor texture
	floor.LoadTexture("grass.bmp");
	floor.SetTiling(true);
	
	
	// player health bar
	hbar.SetSize(30,5);
	hbar.SetHealth(100);

	//Enemy Health Bar
	ebar.SetSize(30, 5);
	
	//Box Health
	bbar.SetSize(100, 15);
	bbar.SetPosition(830, 680);


}

	
void CMyGame::OnStartLevel(int level)
{
	menuMusic.Stop();
  // set size of the game world
  floor.SetSize(6000,6000);
  
  // todo: set box position, size and motion
  box.SetPosition(200, 25, 200);
  box.SetHealth(100);
 
  
  // player position and player health
  player.SetPosition(100,100,100); player.SetStatus(0);
  player.SetHealth(100);
  
 
  //This code is used if you want to restart the quest 
  if (quest == 1) 
  {
	  score = 0;
	  coins = 0;
  }

  if (quest == 2) 
  {
	  edown = 0;
	  pwave = false;
  }

  if (quest == 3) 
  {
	  edown = 0;
  }

  if (quest == 4) 
  {
	  score = 0;
	  coins = 0;
	  pwave = false;
  }

  if (quest == 5) 
  {
	  //Resets The Whole Game
	  quest = 1;

	  score = 0;
	  coins = 0;
	  edown = 0;
	  ecounter = 0;
	  pwave = false;
	  IsAttacking = false;
	  scorereset = false;
  }
  // todo: clearing lists
  grassList.clear();
  plantList.clear();
  coinList.clear();
  cobraList.clear();
  pythonList.clear();
  alienList.clear();
  ogreList.clear();
  wallList.clear();

  //Background Music
  backgroundMusic.Play("gameplayMusic.wav", -1);

  //Left Border
  CModel* lWall = wall.Clone();
  lWall->SetPosition(-3050, 25, 0);
  lWall->SetSize(60, 6000, 6000);
  wallList.push_back(lWall);

  //Right Border
  CModel* rWall = wall.Clone();
  rWall->SetPosition(3050, 25, 0);
  rWall->SetSize(60, 6000, 6000);
  wallList.push_back(rWall);

  //Top Border
  CModel* tWall = wall.Clone();
  tWall->SetPosition(0, 25, -3050);
  tWall->SetSize(6000, 6000, 60);
  wallList.push_back(tWall);

  //Bottom Border
  CModel* bWall = wall.Clone();
  bWall->SetPosition(0, 25, 3050);
  bWall->SetSize(6000, 6000, 60);
  wallList.push_back(bWall);

  // todo: set python position and speed
  CModel* pPython = python.Clone();
  pPython->SetSpeed(100);
  pPython->SetHealth(100);
  pPython->PlayAnimation(1, 8, 7, true);
  pPython->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
  pythonList.push_back(pPython);

  // todo: adding grass

  for (int n = 0; n < 200; n++) 
  {
	  CModel* pGrass = grass.Clone();
	  pGrass->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
	  grassList.push_back(pGrass);

	  CModel* pPlant = plant.Clone();
	  pPlant->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
	  plantList.push_back(pPlant);

  }

  //Adding Plants

  for (int n = 0; n < 50; n++)
  {

	  CModel* pPlant = plant.Clone();
	  pPlant->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
	  plantList.push_back(pPlant);

  }
  
  // todo: adding coins
  if (quest == 1)
  {
	  for (int n = 0; n < 7; n++)
	  {
		  CModel* pCoin = coin.Clone();
		  pCoin->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
		  pCoin->SetOmega(50);
		  coinList.push_back(pCoin);
	  }
  }

  
  
  // todo: adding cobras
 
 
  for (int n = 0; n < 30; n++) 
  {
	  CModel* pCobra = cobra.Clone();
	  pCobra->SetPosition(float(3000 - rand() % 6000), 100, float(3000 - rand() % 6000));
	  pCobra->SetHealth(100);
	  pCobra->SetStatus(0);
	  cobraList.push_back(pCobra);
	  
  }
	
}

// Game Logic in the OnUpdate function called every frame @ 30 fps

void CMyGame::OnUpdate() 
{
	if (IsMenuMode() || IsGameOver()) return;
	
	long t =  GetTime();
	
	// --- updating models ----
	box.Update(t);
	for (CModel* pGrass : grassList) pGrass->Update(t);
	for (CModel* pPlant : plantList) pPlant->Update(t);
	for (CModel* pCoin : coinList) pCoin->Update(t);
	for (CModel* pCobra : cobraList) pCobra->Update(t);
	for (CModel* pPython : pythonList) pPython->Update(t);
	for (CModel* pShot : shotList) pShot->Update(t);

	if (quest == 3) 
	{
		for (CModel* pAlien : alienList) pAlien->Update(t);
		AlienControl();
	}

	if (quest == 4) 
	{
		for (CModel* pOgre : ogreList) pOgre->Update(t);
	}
		
	
	for (CModel* pPython : pythonList) 
	{
		pPython->SetDirectionAndRotationToPoint(player.GetX(), player.GetZ());
	}

	for (CModel* pAlien : alienList) 
	{
		pAlien->SetDirectionAndRotationToPoint(box.GetX(), box.GetZ());
	}

	for (CModel* pOgre : ogreList)
	{
		pOgre->SetDirectionAndRotationToPoint(player.GetX(), player.GetZ());
	}


	for (CModel* pShot : shotList)
	{
		if (pShot->HitTest(&box))
		{
			pShot->Delete();
		}
	}

	shotList.delete_if(deleted);
	if (box.GetHealth() <= 0) 
	{
		//Breaking Box Sound?
		box.Delete();
		GameOver();
	}
	
	//Reset the score on the 4th quest
	if (quest == 4)
	{
		if (scorereset == true)
		{
			score = 0;
			scorereset = false;
		}
	}

	PlayerControl();
	EnemyControl();
	CheckQuests();
	OgreControl();

}

void CMyGame::PlayerControl()
{
	
	player.Update( GetTime());
	
	if (IsKeyDown(SDLK_w) || player.IsAutoMoving())
	{
      player.SetSpeed(500);
	}
	else player.SetSpeed(0);
	
	//Border
	for (CModel* pWall : wallList) 
	{
		if (player.HitTest(pWall)) 
		{
			player.SetVelocity(0, 0, 0);
		}
	}
	// collision between box and player
	if (player.HitTestFront(&box)) 
	{
		player.SetSpeed(0);
		if (coins > 0) 
		{
			score = score + coins;
			
			coins = 0;
			

			player.SetHealth(100);
			coinboxEffect.Play("Cha Ching Sound Effect.wav");
		}
	}
	

	for (CModel* pCoin : coinList) 
	{
		if (player.HitTest(pCoin)) 
		{
			if (coins < 2) 
			{
				coins++;
				pCoin->Delete();
				collectEffect.Play("collect.wav");
			}
			
		}
	}
	coinList.delete_if(deleted);

		
	// play running sequence when UP key is pressed
	// otherwise play standing sequence
	
	if (IsKeyDown(SDLK_w) || player.IsAutoMoving() || player.GetSpeed() > 0)  player.PlayAnimation(40,45,7,true);
	else player.PlayAnimation(1,39,7,true);
	
    
    if (player.GetHealth() <= 0) GameOver();

	
}

void CMyGame::EnemyControl()
{
	//Spawn 10 Pythons when on the 2nd quest only once
	if (quest == 2 && pwave == false) 
	{
		for (int n = 0; n < 10; n++)
		{
			CModel* pPython = python.Clone();
			pPython->SetSpeed(100);
			pPython->SetHealth(100);
			pPython->PlayAnimation(1, 8, 7, true);
			pPython->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
			pythonList.push_back(pPython);

		}
		pwave = true;
	}


	
	//Cobra Hit test
	for (CModel* pCobra : cobraList)
	{
		if (pCobra->GetHealth() <= 0) 
		{
			pCobra->Delete();
		//	pCobra->PlayAnimation(20, 26, 7, false);

			if (quest == 2)
			{
				edown += 1;
			}
		}
		if (player.HitTest(pCobra))
		{
			pCobra->SetStatus(1);
			pCobra->PlayAnimation(8, 16, 7, false); // attack animation played once only
			pCobra->SetRotationToPoint(player.GetX(), player.GetZ()); // rotate towards player
			player.SetHealth(player.GetHealth() - 1);

		}
		else 
		{
			pCobra->PlayAnimation(1, 7, 7, true);
		}

		//Shot Detection
		for (CModel* pShot : shotList)
		{
			if (pShot->HitTest(pCobra))
			{
				pShot->Delete();
				pCobra->SetHealth(pCobra->GetHealth() - 60);	
			}
		}
	}
	cobraList.delete_if(deleted);
	shotList.delete_if(deleted);

	//Python
	for (CModel* pPython : pythonList) 
	{


		if (pPython->GetHealth() <= 0) 
		{
			pPython->Delete();
			if (quest == 2) 
			{
				edown += 1;
			}
		}
		//Shot Detection

		//Python Hit test 
		if (player.HitTest(pPython))
		{
			player.SetHealth(player.GetHealth() - 1);
			pPython->PlayAnimation(9, 17, 7, false);
		}

		for (CModel* pShot : shotList)
		{
			if (pShot->HitTest(pPython))
			{
				pShot->Delete();
				pPython->SetHealth(pPython->GetHealth() - 20);
			}
		}

		//If the Python is deleted in Quest 1 it will respawn again in a random place
		if (pPython->IsDeleted() && quest == 1) 
		{
			CModel* pPython = python.Clone();
			pPython->SetSpeed(100);
			pPython->SetHealth(100);
			pPython->PlayAnimation(1, 8, 7, true);
			pPython->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
			pythonList.push_back(pPython);
		}

	}

	pythonList.delete_if(deleted);
	shotList.delete_if(deleted);


}
void CMyGame::AlienControl() 
{
	if (rand() % 60 == 0) 
	{
		//Randomly chooses a side
		int s = rand() % 4;

		CModel* pAlien = alien.Clone();

		//Depending on which number was chosen one of these will be activated
		if (s == 0) pAlien->SetPosition(3000, float(1000 - rand() % 2000));
		else if (s == 1) pAlien->SetPosition(-3000, float(1000 - rand() % 2000));
		else if (s == 2) pAlien->SetPosition(float(1000 - rand() % 2000), 3000);
		else pAlien->SetPosition(float(1000 - rand() % 2000), -3000);

		pAlien->SetSpeed(100);
		pAlien->SetHealth(100);
		pAlien->PlayAnimation(41, 47, 7, true);
		//pAlien->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));

		alienList.push_back(pAlien);
	}

	for (CModel* pAlien : alienList)
	{
		if (pAlien->GetHealth() <= 0) 
		{
			pAlien->Delete();
			if (quest == 3) 
			{
				edown += 1;
			}
		}
		if (pAlien->HitTest(&box) && IsAttacking == false) 
		{
			pAlien->SetVelocity(0,0,0);
			ecounter = 30;
			IsAttacking = true;
		}
		//Counter that will play the enemy attack and deal damage after a short amount of time
		if (ecounter > 0 && IsAttacking == true && pAlien->HitTest(&box)) 
		{
			ecounter--;
			if (ecounter == 14) 
			{
				pAlien->PlayAnimation(47, 54, 7, true);
				box.SetHealth(box.GetHealth() - 5);
			}

			if (ecounter <= 0) 
			{
				IsAttacking = false;
			}
		}

		for (CModel* pShot : shotList)
		{
			if (pShot->HitTest(pAlien))
			{
				pShot->Delete();
				pAlien->SetHealth(pAlien->GetHealth() - 15);
			}
		}
	}

	alienList.delete_if(deleted);
	shotList.delete_if(deleted);
}

void CMyGame::OgreControl() 
{
	//Spawn 10 Pythons when on the 2nd quest only once
	if (quest == 4 && pwave == false)
	{
		for (int n = 0; n < 7; n++)
		{
			CModel* pOgre = ogre.Clone();
			pOgre->SetSpeed(100);
			pOgre->SetHealth(100);
			pOgre->PlayAnimation(155, 159, 7, true);
			pOgre->SetPosition(float(3000 - rand() % 6000), 25, float(3000 - rand() % 6000));
			ogreList.push_back(pOgre);

		}
		pwave = true;
	}

	for (CModel* pOgre : ogreList) 
	{
		if (pOgre->GetHealth() <= 0) 
		{
			pOgre->Delete();
			CModel* pCoin = coin.Clone();
			pCoin->SetPosition(pOgre->GetX(), 25, pOgre->GetZ());
			pCoin->SetOmega(50);
			coinList.push_back(pCoin);

		}

		for (CModel* pShot : shotList) 
		{
			if (pOgre->HitTest(pShot)) 
			{
				pShot->Delete();
				pOgre->SetHealth(pOgre->GetHealth() - 5);
			}
		}

		if (pOgre->HitTest(&player) && IsAttacking == false) 
		{
			
			ecounter = 30;
			IsAttacking = true;
			
		}

		if (ecounter > 0 && IsAttacking == true && pOgre->HitTest(&player))
		{
			ecounter--;
			if (ecounter == 14)
			{
				pOgre->PlayAnimation(47, 54, 7, true);
				player.SetHealth(player.GetHealth() - 10);
			}

			
		}

		if (ecounter <= 0)
		{
			IsAttacking = false;
			pOgre->PlayAnimation(155, 159, 7, true);
			

		}
	}
	ogreList.delete_if(deleted);
	shotList.delete_if(deleted);
}
void CMyGame::CheckQuests()
{
	//Quest 1
	
	if (score >= 7 && quest == 1)
	{
		quest = 2;
		coins = 0;
		player.SetHealth(100);
	}
	

	//Quest 2
	if (edown >= 10 && quest == 2)
	{
		quest = 3;
		player.SetHealth(100);
		edown = 0;
		pwave = false;
	}

	//Quest 3
	if (quest == 3 && edown >= 20) 
	{
		quest = 4;
		scorereset = true;
		
	}

	if (quest == 4 && score >= 7 && scorereset == false) 
	{
		quest = 5;
	}

	//When you go to the Complete game screen everything will be deleted so that no noise will be made and the game over screen wont show up
	if (quest == 5) 
	{
		grassList.clear();
		plantList.clear();
		coinList.clear();
		cobraList.clear();
		pythonList.clear();
		alienList.clear();
		ogreList.clear();

		shotEffect.Stop();
		collectEffect.Stop();
		coinboxEffect.Stop();
	}

	
	/*for (CModel* pModel : coinList)
	{
		if (player.HitTest(pModel) && quest == 1)
		{
			quest = 2;
			pModel->Delete();
		}
	}
	coinList.delete_if(deleted);*/

}




//-----------------  Draw 2D overlay ----------------------
void CMyGame::OnDraw(CGraphics* g)
{
	if (IsMenuMode()) 
	{
		// draw screen here
		screen.Draw(g);
		
		 
		return;
	}



	if (IsGameMode())
	{
		font.SetSize(32); font.SetColor(CColor::Green());
		switch (quest)
		{
		case 0:
			//font.DrawText(250, 600, "Find the treasure box");
			break;

		case 1:
			font.DrawText(0, 600, "Collect 7 Coins and bring them back to the box");
			break;

		case 2:
			font.DrawText(0, 600, "Now you must defeat 10 enemies");
			break;

		case 3:
			font.DrawText(0, 600, "Protect the box and get rid of 20 aliens!");
			break;
		case 4:
			font.SetSize(27); font.DrawText(0, 600, "Oh No a different species snuck up and stole the coins, get it back");
			break;

		case 5:
			completeScreen.Draw(g);
			return;
			break;

		}
	}

	if (IsGameOver())
	{
		gameOverScreen.Draw(g);

		return;
	}
	
	// draw GTEC 3D text
	//font.SetColor( CColor::Blue()); font.SetSize( 32); font.DrawText( Width-200,Height-50, "Explorer" );
	// draw score
	font.SetColor( CColor::Red()); font.DrawText(0, Height - 50, "Coins Secured:"); font.DrawNumber(225,Height-50, score);

	if (quest == 1 || quest == 4) 
	{
		font.SetColor(CColor::Yellow()); font.DrawText(550, 5, "Coins In Pocket:"); font.DrawNumber(820, 5, coins);
	}
	if (quest == 2) 
	{
		font.SetColor(CColor::Yellow()); font.DrawText(560, 5, "Enemys Defeated:"); font.DrawNumber(820, 5, edown);
	}
	if (quest == 3) 
	{
		bbar.SetHealth(box.GetHealth());
		bbar.Draw(g);
		font.SetColor(CColor::Yellow()); font.DrawText(560, 5, "Aliens Defeated:"); font.DrawNumber(820, 5, edown);
	}
	
	
	// drawing the healthbar (which is a sprite object drawn in 2D)
	CVector pos=WorldToScreenCoordinate(player.GetPositionV());
	hbar.SetPosition(pos.x,pos.y+50); 
	hbar.SetHealth( player.GetHealth());
	hbar.Draw(g);
	
	for (CModel* pCobra : cobraList) 
	{
		if (pCobra->GetStatus() == 1)
		{
			CVector pos = WorldToScreenCoordinate(pCobra->GetPositionV());
			ebar.SetPosition(pos.x, pos.y + 50);
			ebar.SetHealth(pCobra->GetHealth());
			ebar.Draw(g);
		}

	}

	for (CModel* pPython : pythonList) 
	{
		CVector pos = WorldToScreenCoordinate(pPython->GetPositionV());
		ebar.SetPosition(pos.x, pos.y + 50);
		ebar.SetHealth(pPython->GetHealth());
		ebar.Draw(g);
	}

	for (CModel* pAlien : alienList)
	{
		if (quest == 3) 
		{
			CVector pos = WorldToScreenCoordinate(pAlien->GetPositionV());
			ebar.SetPosition(pos.x, pos.y + 50);
			ebar.SetHealth(pAlien->GetHealth());
			ebar.Draw(g);
		}

	}

	for (CModel* pOgre : ogreList) 
	{
		if (quest == 4) 
		{
			CVector pos = WorldToScreenCoordinate(pOgre->GetPositionV());
			ebar.SetPosition(pos.x, pos.y + 50);
			ebar.SetHealth(pOgre->GetHealth());
			ebar.Draw(g);
		}

	}
	//Draw at Full Capacity if trying to get coins when you already have 5

	if (coins == 2) 
	{
		font.SetSize(64); font.SetColor(CColor::Red()); font.DrawText(0, 0, "At Full Capacity");
	}
	
	
	// draw GAME OVER if game over
   	if (IsGameOver())
   	{
		font.SetSize(64); font.SetColor( CColor::Red()); font.DrawText( 250,300, "GAME OVER");	
	}
	
}

void CMyGame::CameraControl(CGraphics* g)
{
	// game world tilt
    float tilt=50;
    float scale=1.3f;
	//float scale = 0.1f;
	
	// ------ Global Transformation Functions -----
	
	//glTranslatef(0,-100,0);  // move game world down 
	glRotatef(tilt,1,0,0);			// tilt game world around x axis
    glScalef(scale,scale,scale);			// scaling the game world
	
	// ---- 3rd person camera setup -----
	//glRotatef( rotation,0,1,0);		// rotate game world around y axis
	glTranslatef(-player.GetX(), 0, -player.GetZ());    // position game world
		
	UpdateView();
	Light.Apply();
}


// ----------------   Draw 3D world -------------------------
void CMyGame::OnRender3D(CGraphics* g)
{
	CameraControl(g);
	
	// ------- Draw your 3D Models here ----------
	
	floor.Draw(g); // if true with grid, false without grid
	
	player.Draw(g);

	//for (CModel* pWall : wallList) pWall->Draw(g);

	box.Draw(g);
	for (CModel* pGrass : grassList) pGrass->Draw(g);
	for (CModel* pPlant : plantList) pPlant->Draw(g);
	for (CModel* pCoin : coinList) pCoin->Draw(g);
	for (CModel* pCobra : cobraList) 
	{
		if (pCobra->GetStatus() == 1) 
		{
			pCobra->Draw(g);
		}
		
	}
	for (CModel* pPython : pythonList) pPython->Draw(g);
	for (CModel* pShot : shotList) pShot->Draw(g);
	if (quest == 3) 
	{
		for (CModel* pAlien : alienList) pAlien->Draw(g);
	}

	if (quest == 4)
	{
		for (CModel* pOgre : ogreList) pOgre->Draw(g);
	}
	
	
	
	
	
	
	//ShowBoundingBoxes();
	//ShowCoordinateSystem();
}





// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	menuMusic.Play("menuMusic.wav", -1);
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
     OnStartLevel(1);	
}


// called when Game is Over
void CMyGame::OnGameOver()
{
	
}

// one time termination code
void CMyGame::OnTerminate()
{
	
}

// -------    Keyboard Event Handling ------------

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_SPACE)
	{
		if (IsPaused()) ResumeGame();
		else PauseGame();

	}
	if (sym == SDLK_F2) 
	{
		backgroundMusic.Stop();
		NewGame();
	} 

  
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	
}

// -----  Mouse Events Handlers -------------

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	CVector pos=ScreenToFloorCoordinate(x,y);
	
	player.SetDirectionAndRotationToPoint(pos.x,pos.z);
	
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{    
   if (IsMenuMode()) StartGame();
   else 
   {
	   // create a new shot as a short line
	   CModel* pShot = new CLine(player.GetPositionV(), 50);
	   shotEffect.Play("shot.wav");
	   // rotation and direction same as the player
	   pShot->SetDirection(player.GetDirection());
	   pShot->SetRotation(player.GetRotation());
	   pShot->SetSpeed(1000);
	   pShot->Die(2000);
	   shotList.push_back(pShot);
   }
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
