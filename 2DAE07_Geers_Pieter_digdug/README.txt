//GITHUB============================================//
// https://github.com/PieterGeers/DigDug-Assignment //
//==================================================//


Game Loop: Ik heb gekozen voor een game loop met zowel een fixed als een normale update. "Elapsed secondse" en "Fixed Elapsed Seconds" worden opgeslaan in een singleton class
		zodat niet aan elke update een variable moet overgeërfd worden.

Command Pattern: Gebruikt een "index" zodat ik weet op welke character die bepaalde command uitgevoerd moet worden.

State Machine: Ik maak gebruik van base Action en Condition class. Conditions worden gebruikt in combinatie met States in de Transition class. Omdat DigDug relatief weinig Agents heeft,
		heb ik ervoor gekozen om elke Agent zijn eigen state machine te hebben. De agents maken gebruik van AStarPathFinding om een path te vinden tot de dichtste player.

Observer Pattern & Multi Threading: Ik heb geen gebruik gemaakt van deze twee zaken omdat ik er te veel tijd aan ging kwijtgeraken.

Collision: Ik heb Box2D toegevoegd aan minigin en geprobeerd om hiermee collision te simuleren. Uiteindelijk heb ik mijn eigen collision gemaakt die enkel quads support.
		De scene moet de collision handelen via een static function. De pointer van alle collision objecten worden opgeslaan in een static map zodat deze allemaal op 1 plaatst staan.
		Op deze manier kon ik simpel checken welke quads er overlappen met welke andere quads en alle tags waarmee een object collide opslaan om later te kunnen checken wat met wat gecollide heeft.
		Elke keer de collision opnieuw gechecked word word de vector met die tags gecleared en opnieuw opgevult als er al dan niet collision is.

BaseComponent: Elk component is derived van een BaseComponent of van een ander component die dan wel derived is van het BaseComponent. Ik heb ervoor gekozen om aan elk Component een render function te geven.
		Op deze manier kan het GameObject alles dat gerendered moet worden in 1 keer allemaal renderen en dan hoef ik geen check te doen in het GameObject om te controlleren of een component wel een 
		render component is. Het BaseComponent bevat ook een ptr naar het GameObject zodat ik gemakkelijk van 1 component naar een ander component kan gaan.
		(component.GetGameObject->GetComponent<OtherComponent>()->DoSomething();)

CharacterComponent: Dit is een base class met wat basic functionality waar ik later een derived classe van maakte voor zowel de playable DigDug als de playable Fygar.

LevelComponent: Dit is een base class met basic level functionality. In de base class word de graph aangemaakt waar later de agents path finding op kunnen doen.

ButtonComponent: Dit is een component dat ik gebruik om alle buttons in de UI te handelen. Elke button heeft een function ptr zodat als ik die button selecteer, die function uitgevoerd word.
		Alle buttons worden in een button manager gestoken die aangemaakt word in de scene als ik het nodig heb.

FPSComponent: Ik heb ervoor gekozen om elke seconds alle frames op te tellen. Op deze manier weet ik exact hoeveel frames ik had in de vorige seconde. Moest ik ervoor gekozen hebben om 1/delteT te doen,
		dan zou mijn fps counter flikkeren omdat deze elke update dan zou veranderen. Elke frame een de fps update zou ook niet goed zijn voor performance omdat van text een texture maken geen goedkope operatie is.
		Ik zou dan die fps kunnen updaten 1 keer per seconde, maar dan zou ik een momentopname hebben, hiermee wil ik zeggen dat als er weinig moet geupdate worden, de delteT zeer klein zal zijn waardoor de fps extreem hoog is.
		En moest er veel geupdate worden voor die ene frame dan zou de deltaT relatief groot zijn waardoor de fps extreem laag is.
		Ik heb er ook voor gekozen om die fps lock flag te verwijderen aangezien het anders useless was dat ik een 2de update had met een fixed timestep.

TextRenderComponent: Ik heb ervoor gezorgd dat de texture enkel moet geupdate worden eenmaal de tekst aangepast is, anders zou elke frame een nieuwe texture moeten gemaakt worden wat niet goed is voor performance.

TextureRenderComponent: Dit component kan zowel textures als sprites renderen. Als het een texture is dan kan deze ook geroteerd worden. Sprites kunnen niet geroteerd worden.

Bedug: Ik heb een logger gemaakt die een SDL_MessageBox in uw gezicht duwd als je iets verkeerd gedaan hebt. Hiermee kunnen errors gelogged worden en warnings. Bij warnings heb je nog de keuze om de game verder te laten lopen
		als de warning niet te erg is. Bij een error ben je verplicht om te application te sluiten.

Animator: Voor het gebruik van sprites simpelder te maken heb ik een animator toegevoegd. Elke "Animation" bestaat uit een start row en column op de sprite en de row en column offset en een name. Via de name kan die bepaalde
		animation active gezet worden.

Renderer: Deze heb ik lichtjes aangepast om sprites te supporten en texture rotation.

Texture2D: Deze heb ik ook lichtjes aangepast zodat ik aan de width en heigt information van die texture kon.

Structs.h: Deze bevat een eigen vector2 en wat basic operators. Voor de rest is dit een header met alle structs en enums op 1 plaats.

GameObject: Hiermee kan ik GetComponent doen om een component op te vragen, HasComponent om te kijken of een gameobject een bepaalde component bevat en HasComponentDerived om te kijken of er een derived component in dat gameobject zit.
		Een gameobject kan ook child objecten hebben maar die child heeft geen weet van zijn parent. Een child kan opgevraagd worden via zijn tag.

GameScene: Deze class is een base class voor alle scenes in digdug.

SceneManager: Deze behandeld het switchen van scenes.

Sound: Dan heb ik ook nog sound toegevoegd. De soundmanager bevat alle songs en effects en kan afspelen waar ze nodig zijn. Deze class is een singleton.

LevelBuilderTool: Dit is een tool voor mezelf om gemakkelijk extra levels aan te maken.

DigDugGame: Dit project bevat de logic voor de game + alle scenes die ik gebruikt. In de credit scene staan de credits van naar alle personen waarvan ik art/sound/textures gepakt hebt.