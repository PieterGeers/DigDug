#pragma once
struct MVector2_INT
{
	MVector2_INT(int ix, int iy) : x(ix), y(iy) {}
	int x, y;

	auto operator-(const MVector2_INT& v) const
	{
		return MVector2_INT(x - v.x, y - v.y);
	}
	auto operator+(const MVector2_INT& v) const
	{
		return MVector2_INT(x + v.x, y + v.y);
	}
	auto GetAbs() const
	{
		return MVector2_INT(abs(x), abs(y));
	}
};

struct Cell	
{
	Cell(unsigned idx, const MVector2_INT& position, bool can_walk_on)
		: idx(idx),
		  position(position),
		  canWalkOn(can_walk_on)
	{}
	Cell(){}

	unsigned idx = 0;
	MVector2_INT position = MVector2_INT(0,0);
	bool canWalkOn = false;
};

enum Direction
{
	up,
	down,
	left,
	right,
	none
};

struct Boundaries
{
	int top, bottom, left, right;
};

struct SpriteInfo
{
	unsigned startColumn, startRow, ColumnOffset, RowOffset;
};

struct Animation
{
	std::string name;
	SpriteInfo info;
};

inline std::shared_ptr<Animation> CreateAnimation(const std::string& name, unsigned startRow, unsigned startCol, unsigned rOff, unsigned cOff)
{
	std::shared_ptr<Animation> temp = std::make_shared<Animation>();
	temp->name = std::move(name);
	temp->info.startColumn = startCol;
	temp->info.startRow = startRow;
	temp->info.ColumnOffset = cOff;
	temp->info.RowOffset = rOff;
	return temp;
}

enum GamepadIndex : DWORD
{
	PlayerOne = 0,
	PlayerTwo = 1,
	PlayerThree = 2,
	PlayerFour = 3
};

enum InputTriggerState
{
	Pressed,
	Released,
	Down
};

struct InputAction
{
	InputAction() :
		ActionID(-1),
		TriggerState(Pressed),
		KeyboardCode(-1),
		GamepadButtonCode(0),
		PlayerIndex(PlayerOne),
		IsTriggered(false) {}

	InputAction(int actionID, InputTriggerState triggerState = Pressed, int keyboardCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne) :
		ActionID(actionID),
		TriggerState(triggerState),
		KeyboardCode(keyboardCode),
		GamepadButtonCode(gamepadButtonCode),
		PlayerIndex(playerIndex),
		IsTriggered(false) {}

	int ActionID;
	InputTriggerState TriggerState;
	int KeyboardCode;
	WORD GamepadButtonCode; 
	GamepadIndex PlayerIndex;
	bool IsTriggered;

};

enum BasicActions
{
	B_Quit = -1,
	B_Up = -2,
	B_Down = -3,
	B_Select = -4
};

enum LogLevel
{
	Warning,
	Error
};

struct M_Rectangle
{
	M_Rectangle()
		: TopLeft(0,0)
		, BottomRight(0,0)
	{}

	MVector2_INT TopLeft, BottomRight;
};

